#pragma once
#ifndef _AVL
#define _AVL

#include "BST.h"

template <class T> class AVL : public BST<T> {

  protected:
    using Node = typename BST<T>::Node;

    int height(Node *node) {
        if (!node)
            return 0;
        return std::max(height(node->left), height(node->right)) + 1;
    }

    int balance(Node *node) {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *t2 = y->left;

        y->left = x;
        x->right = t2;

        return y;
    }

    Node *insert(Node *node, const T &v) {

        if (!node) {
            this->len++;
            return new Node(v);
        }

        if (v <= node->data)
            node->left = insert(node->left, v);
        else
            node->right = insert(node->right, v);

        int bf = balance(node);

        if (bf > 1 && v < node->left->data)
            return rightRotate(node);

        if (bf < -1 && v > node->right->data)
            return leftRotate(node);

        if (bf > 1 && v > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bf < -1 && v < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *remove(Node *node, const T &v) {

        if (!node)
            return nullptr;

        if (v < node->data)
            node->left = remove(node->left, v);

        else if (v > node->data)
            node->right = remove(node->right, v);

        else {

            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }

            if (!node->left) {
                Node *temp = node->right;
                delete node;
                return temp;
            }

            if (!node->right) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = node->right;

            while (temp->left)
                temp = temp->left;

            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        int bf = balance(node);

        if (bf > 1 && balance(node->left) >= 0)
            return rightRotate(node);

        if (bf > 1 && balance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bf < -1 && balance(node->right) <= 0)
            return leftRotate(node);

        if (bf < -1 && balance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

  public:
    AVL() : BST<T>() {
    }

    AVL(const initializer_list<T> &list) : BST<T>() {
        for (const T &v : list)
            insert(v);
    }

    void insert(const T &v) {
        this->root = insert(this->root, v);
    }

    void remove(const T &v) {
        root = remove(root, v);
    }
};

#endif