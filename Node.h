#pragma once
#ifndef _NODE
#define _NODE
template <class T> struct Node {
    T data;
    Node<T> *next;
    Node() : data(0), next(nullptr) {};
    Node(const T &data, Node<T> *next = nullptr) {
        this->data = data;
        this->next = next;
    }
};
#endif