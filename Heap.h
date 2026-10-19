#pragma once
#ifndef _HEAP
#define _HEAP
#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

template <class T, class Compare = std::less<T>> class Heap {
    vector<T> vec;
    int sz;
    Compare comp;

    bool better(const T &a, const T &b) {
        return comp(a, b);
    }

    void heapify(vector<T> &vec, int sz, int idx) {
        int best = idx;
        int l = 2 * idx + 1;
        int r = 2 * idx + 2;

        if (l < sz && better(vec[l], vec[best]))
            best = l;
        if (r < sz && better(vec[r], vec[best]))
            best = r;

        if (best != idx) {
            swap(vec[idx], vec[best]);
            heapify(vec, sz, best);
        }
    }

    int height(int idx) {
        if (idx <= 0)
            return 0;
        return 1 + height((idx - 1) / 2);
    }

    T kth_element(int idx, int k, int &cnt, bool isMin) {
        if (idx >= sz)
            return T();

        if (k == 1) {
            cnt = 1;
            return vec[idx];
        }

        int l = 2 * idx + 1;
        int r = 2 * idx + 2;

        int first = l, second = r;
        if (r < sz) {
            if (isMin ? (vec[l] > vec[r]) : (vec[l] < vec[r])) {
                swap(first, second);
            }
        }

        if (second < sz) {
            T res = kth_element(first, k - 1, cnt, isMin);
            if (cnt == k - 1)
                return res;
            return kth_element(second, k - 1, cnt, isMin);
        }

        if (first < sz) {
            return kth_element(first, k - 1, cnt, isMin);
        }

        return T();
    }

  public:
    Heap() : sz(0), comp(Compare()) {
    }

    Heap(int n) : sz(0), comp(Compare()) {
        vec.reserve(n);
    }

    Heap(const initializer_list<T> &list) : sz(0), comp(Compare()) {
        for (const T &x : list)
            insert(x);
    }

    Heap(const Heap &h) : vec(h.vec), sz(h.sz), comp(h.comp) {
    }

    Heap(Heap &&h) noexcept
        : vec(std::move(h.vec)), sz(h.sz), comp(std::move(h.comp)) {
        h.sz = 0;
    }

    Heap &operator=(const Heap &h) {
        if (this != &h) {
            vec = h.vec;
            sz = h.sz;
            comp = h.comp;
        }
        return *this;
    }

    Heap &operator=(Heap &&h) noexcept {
        if (this != &h) {
            vec = std::move(h.vec);
            sz = h.sz;
            comp = std::move(h.comp);
            h.sz = 0;
        }
        return *this;
    }

    ~Heap() {
        clear();
    }

    void insert(const T &val) {
        vec.push_back(val);
        int idx = sz;
        ++sz;

        while (idx > 0) {
            int par = (idx - 1) / 2;

            if (!better(vec[idx], vec[par]))
                break;

            swap(vec[par], vec[idx]);
            idx = par;
        }
    }

    void remove() {
        if (sz == 0)
            return;

        vec[0] = vec.back();
        vec.pop_back();
        --sz;

        int idx = 0;

        while (2 * idx + 1 < sz) {
            int best = 2 * idx + 1;

            if (2 * idx + 2 < sz && better(vec[2 * idx + 2], vec[best]))
                best = 2 * idx + 2;

            if (!better(vec[best], vec[idx]))
                break;

            swap(vec[idx], vec[best]);
            idx = best;
        }
    }

    T top() const {
        return vec.front();
    }

    bool empty() const {
        return sz == 0;
    }
    int size() const {
        return sz;
    }
    void clear() {
        vec.clear();
        sz = 0;
    }

    void print() const {
        for (const T &x : vec)
            cout << x << ' ';
        cout << '\n';
    }

    void sort() {
        for (int i = (sz / 2) - 1; i >= 0; --i) {
            heapify(vec, sz, i);
        }
        for (int i = sz - 1; i > 0; --i) {
            swap(vec[i], vec[0]);
            heapify(vec, i, 0);
        }
    }

    int height() {
        return height(sz - 1);
    }

    T kth_smallest(int k) {
        int cnt = 0;
        return kth_element(0, k, cnt, true);
    }

    T kth_largest(int k) {
        int cnt = 0;
        return kth_element(0, k, cnt, false);
    }
};

#endif