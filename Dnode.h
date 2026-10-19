#pragma once
#ifndef DNODE
#define DNODE
template <class T> struct Dnode {
    T data;
    Dnode *next;
    Dnode *pre;
    Dnode() : data(T()), pre(nullptr), next(nullptr) {
    }

    explicit Dnode(const T &val) : data(val), pre(nullptr), next(nullptr) {
    }

    Dnode(const T &val, Dnode *p = nullptr, Dnode *n = nullptr)
        : data(val), pre(p), next(n) {
    }
};
#endif