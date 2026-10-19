#pragma once
#ifndef _NODE
#define _NODE
template <class T> struct Node {
    T data;
    Node *left;
    Node *right;
    Node() : data(T()), left(nullptr), right(nullptr) {};
    Node(const T &data) : data(data), left(nullptr), right(nullptr) {};
    Node(const T &data, Node *left, Node *right),
        : data(data), left(left), right(right) {};
};
#endif