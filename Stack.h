#ifndef STACK_H
#define STACK_H
#include <initializer_list>
#include <vector>
#pragma once
using namespace std;
template <class T> class Stack {
    vector<T> tem;

  public:
    void emplace(T val) {
        tem.push_back(val);
    }
    T top() const {
        if (tem.empty())
            return NULL;
        return tem[tem.size() - 1];
    }
    int size() const {
        return tem.size();
    }
    bool empty() const {
        if (tem.size() == 0)
            return true;
        return false;
    }
    void pop() {
        if (tem.empty())
            return;
        tem.erase(tem.end() - 1);
    }
    template <class Container> void push_range(const Container &c) {
        for (const auto &it : c) {
            this->emplace(it);
        }
    }

    void Swap(const Stack &st) {
        swap(*this, st);
    }

    Stack(const Stack &st) {
        this->tem.reserve(st.size());
        for (const T &i : st.tem) {
            tem.push_back(i);
        }
    }
    Stack &operator=(const Stack &st) {
        if (this == &st)
            return *this;
        tem.clear();
        tem.reserve(st.tem.size());
        for (const T &i : st.tem) {
            tem.push_back(i);
        }
        return *this;
    }
    Stack(Stack &&st) noexcept {
        tem = move(st.tem);
    }
    Stack &operator=(Stack &&st) noexcept {
        if (this == &st)
            return *this;
        tem = move(st.tem);
        return *this;
    }
    void print() const {
        Stack<int> s = *this;
        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
    }

    Stack() = default;
};
#endif