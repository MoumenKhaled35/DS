#pragma once
#ifndef _VEC
#define _VEC
#include <algorithm>
#include <initializer_list>
#include <iostream>
using namespace std;
template <class T> class Vec {
    size_t size;
    size_t cap;
    T *arr;

  public:
    Vec() : size(0), arr(nullptr), cap(0) {};
    template <class Container> Vec(const Container &list) {
        int len = list.size();
        arr = new T[len];
        int i = 0;
        for (const auto &v : list) {
            arr[i++] = v;
        }
        size = cap = len;
    }
    Vec(const initializer_list<T> &list) {
        int len = list.size();
        arr = new T[len];
        int i = 0;
        for (const T &v : list) {
            arr[i++] = v;
        }
        size = cap = len;
    }

    Vec(const Vec<T> &vec) {
        if (!vec.empty()) {
            arr = new T[vec.cap];
            for (int i = 0; i < (int)vec.size; ++i) {
                arr[i] = vec.arr[i];
            }
            size = vec.size;
            cap = vec.cap;
        } else {
            arr = nullptr;
            size = cap = 0;
        }
    }

    Vec &operator=(const Vec<T> &vec) {
        if (this != &vec) {
            delete[] arr;
            if (!vec.empty()) {
                arr = new T[vec.cap];
                for (int i = 0; i < (int)vec.size; ++i) {
                    arr[i] = vec.arr[i];
                }
                size = vec.size;
                cap = vec.cap;
            } else {
                arr = nullptr;
                size = cap = 0;
            }
        }
        return *this;
    }

    Vec(Vec &&other) noexcept {
        arr = other.arr;
        cap = other.cap;
        size = other.size;
        other.arr = nullptr;
        other.cap = other.size = 0;
    }

    Vec &operator=(Vec &&other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            cap = other.cap;
            size = other.size;
            other.arr = nullptr;
            other.cap = other.size = 0;
        }
        return *this;
    }

    Vec(const int &n, const T &v = T()) {
        arr = new T[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = v;
        }
        size = cap = n;
    }

    class Iterator {
        T *curr;

      public:
        Iterator(T *curr = nullptr) {
            this->curr = curr;
        }

        Iterator &operator++() {
            ++curr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++curr;
            return temp;
        }

        Iterator &operator--() {
            --curr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --curr;
            return temp;
        }

        T &operator*() const {
            return *curr;
        }

        T *operator->() const {
            return curr;
        }

        Iterator operator+(const int &n) {
            return Iterator(curr + n);
        }

        Iterator operator-(const int &n) {
            return Iterator(curr - n);
        }

        bool operator!=(const Iterator &other) const {
            return curr != other.curr;
        }

        bool operator==(const Iterator &other) const {
            return curr == other.curr;
        }

        T *ptr() const {
            return curr;
        }
        ptrdiff_t operator-(const Iterator &it) const {
            return curr - it.curr;
        }
    };

    Iterator begin() {
        return Iterator(arr);
    }
    Iterator end() {
        return Iterator(arr + size);
    }
    Iterator begin() const {
        return Iterator(arr);
    }
    Iterator end() const {
        return Iterator(arr + size);
    }

    class Rev_iterator {
        T *curr;

      public:
        Rev_iterator(T *curr = nullptr) {
            this->curr = curr;
        }
        T &operator*() const {
            return *curr;
        }

        Rev_iterator &operator++() {
            --curr;
            return *this;
        }

        Rev_iterator operator++(int) {
            Rev_iterator tem = *this;
            --curr;
            return tem;
        }

        Rev_iterator &operator--() {
            ++curr;
            return *this;
        }

        Rev_iterator operator--(int) {
            Rev_iterator tem = *this;
            ++curr;
            return tem;
        }

        bool operator!=(const Rev_iterator &other) const {
            return curr != other.curr;
        }

        bool operator==(const Rev_iterator &other) const {
            return curr == other.curr;
        }
    };

    Rev_iterator rbegin() {
        return Rev_iterator(arr + size - 1);
    }
    Rev_iterator rend() {
        return Rev_iterator(arr - 1);
    }
    Rev_iterator rbegin() const {
        return Rev_iterator(arr + size - 1);
    }
    Rev_iterator rend() const {
        return Rev_iterator(arr - 1);
    }

    T &operator[](const int &n) const {
        if (n >= (int)cap || n < 0)
            throw runtime_error("Not found");
        return arr[n];
    }

    void clear() {
        delete[] arr;
        arr = nullptr;
        cap = size = 0;
    }

    bool empty() const {
        return size == 0;
    }

    int len() const {
        return (int)size;
    }

    void push_back(const T &val) {
        if (empty()) {
            cap = 1;
            arr = new T[cap];
            arr[0] = val;
            size = 1;
            return;
        }
        if (size == cap) {
            int data_cap = 2 * cap;
            T *data = new T[data_cap];
            for (int i = 0; i < (int)size; ++i)
                data[i] = arr[i];
            data[size] = val;
            delete[] arr;
            arr = data;
            ++size;
            cap = data_cap;
            return;
        }
    }

    void pop_back() {
        if (empty())
            throw runtime_error("Empty Vec");
        arr[size - 1] = T();
        --size;
    }

    void insert(const Iterator &it, const T &val) {
        int idx = index(it.ptr());
        if (idx < 0 || idx > (int)size)
            throw runtime_error("Not Valid");
        if (it == end()) {
            push_back(val);
            return;
        }
        if (size < cap) {
            for (int i = size; i > idx; --i) {
                arr[i] = arr[i - 1];
            }
            arr[idx] = val;
            ++size;
            return;
        }
        int newcap = cap * 2;
        T *data = new T[newcap];
        memcpy_s(data, newcap * sizeof(T), arr, sizeof(T) * cap);
        for (int i = size; i > idx; --i) {
            data[i] = data[i - 1];
        }
        data[idx] = val;
        delete[] arr;
        arr = data;
        cap = newcap;
        size++;
    }

    void insert(const Iterator &it, const int &n, const T &val) {
        int pos = index(it.ptr());
        if (pos < 0 || pos > (int)size)
            throw runtime_error("Out of Range");
        if ((int)(size + n) <= (int)cap) {
            for (int i = cap - 1; i >= pos + n; --i) {
                arr[i] = arr[i - n];
            }
            for (int i = pos; i < pos + n; ++i) {
                arr[i] = val;
            }
            return;
        }
        int newcap = cap + n;
        T *data = new T[newcap];
        memcpy_s(data, sizeof(T) * newcap, arr, sizeof(T) * cap);
        for (int i = newcap - 1; i >= pos + n; --i) {
            data[i] = data[i - n];
        }
        for (int i = pos; i < pos + n; ++i) {
            data[i] = val;
        }
        delete[] arr;
        arr = data;
        cap = newcap;
        size += n;
    }

    void resize(const int &n, const T &v = T()) {
        if (n < 0) {
            throw runtime_error("Not Valid");
        }

        if (this->size == 0) {
            arr = new T[n];
            std::fill_n(arr, n, v);
            this->size = n;
            this->cap = n;
            return;
        }

        if (this->size == n) {
            std::fill_n(arr, n, v);
            return;
        }

        T *data = new T[n];

        if (n > this->size) {
            copy_n(arr, size, data);

            std::fill_n(data + this->size, n - this->size, v);
        } else {
            copy_n(arr, n, data);
        }

        delete[] arr;
        arr = data;
        this->size = n;
        this->cap = n;
    }

    void erase(const Iterator &it) {
        if (empty())
            throw runtime_error("Not valid");
        int idx = index(it.ptr());
        if (idx == size - 1) {
            pop_back();
            return;
        }
        if (idx < 0 || idx >= (int)size)
            throw runtime_error("Out of Range");
        for (int i = idx; i < (int)size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        arr[size - 1] = T();
        --size;
    }

    void erase(const Iterator &b, const Iterator &e) {
        if (empty())
            throw runtime_error("Not valid");
        int idx1 = index(b.ptr());
        int idx2 = index(e.ptr());
        if (idx1 == idx2)
            return;
        if (idx1 > idx2 || idx1 < 0 || idx2 > (int)size)
            throw runtime_error("Out of Range");
        T *data = new T[size - (e - b)];
        copy_n(arr, (b - begin()), data);
        copy_n(arr + (e - begin()), size - (e - begin()), data + (e - b) - 1);
        delete[] arr;
        arr = data;
        cap -= (e - b);
        size -= (e - b);
    }

    ~Vec() {
        clear();
    }

    int capacity() const {
        return (int)cap;
    }

    void reserve(const int &n) {
        if (n < 0)
            throw runtime_error("Not Valid");
        if (n <= (int)cap)
            return;
        T *data = new T[n];
        for (int i = 0; i < (int)size; ++i)
            data[i] = arr[i];
        delete[] arr;
        arr = data;
        cap = n;
    }

    T at(const int &n) const {
        if (n < 0 || n >= (int)size)
            throw runtime_error("Out of Range");
        return arr[n];
    }

    T back() const {
        if (empty())
            return T();
        return arr[size - 1];
    }

    T front() const {
        if (empty())
            return T();
        return arr[0];
    }

    void append_range(Vec &&other) {
        if (other.empty())
            return;
        int needed = (int)(size + other.size);
        if (needed > (int)cap) {
            int newCap = needed;
            T *newData = new T[newCap];
            for (int i = 0; i < (int)size; ++i)
                newData[i] = arr[i];
            for (int i = 0; i < (int)other.size; ++i)
                newData[size + i] = move(other.arr[i]);
            delete[] arr;
            arr = newData;
            cap = newCap;
            size = needed;
        } else {
            for (int i = 0; i < (int)other.size; ++i)
                arr[size + i] = move(other.arr[i]);
            size = needed;
        }
        other.arr = nullptr;
        other.size = 0;
        other.cap = 0;
    }

    void reverse() {
        if (this->empty() || this->len() == 1)
            return;
        int x = this->len() / 2;
        Iterator b = begin();
        Iterator e = end() - 1;
        for (int i = 0; i < x; ++i) {
            iter_swap(b++, e--);
        }
    }
    void swap(Vec &other) noexcept {
        std::swap(arr, other.arr);
        std::swap(size, other.size);
        std::swap(cap, other.cap);
    }

  private:
    int index(const T *ptr) const {
        return (int)(ptr - arr);
    }
};

#endif