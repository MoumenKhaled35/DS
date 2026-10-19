#pragma once
#ifndef _LL
#define _LL
#include "Dnode.h"
#include <initializer_list>
#include <iostream>
using namespace std;
template <class T> class LL {
    Dnode<T> *head;
    Dnode<T> *tail;

  public:
    LL() : head(nullptr), tail(nullptr) {};

    LL(const initializer_list<T> &FL) : head(nullptr), tail(nullptr) {
        for (const T &val : FL) {
            ins_atend(val);
        }
    }

    LL(const int n, const T &val) {
        for (int i = 0; i < n; ++i) {
            ins_atend(val);
        }
    }

    LL(const LL<T> &list) {

        for (const auto &v : list)
            ins_atend(v);
    }

    LL &operator=(const LL<T> &list) {
        if (this != &list) {
            this->clear();
            for (const T &v : list)
                ins_atend(v);
        }
        return *this;
    }

    LL(LL &&other) noexcept : head(other.head), tail(other.tail) {
        other.head = other.tail = nullptr;
    }

    LL &operator=(LL &&other) noexcept {
        if (this != &other) {
            head = other.head;
            tail = other.tail;
            other.head = other.tail = nullptr;
        }
        return *this;
    }

    class Iterator {
        Dnode<T> *curr;

      public:
        Iterator(Dnode<T> *curr = nullptr) {
            this->curr = curr;
        }

        T &operator*() const {
            if (!curr)
                throw runtime_error("Not Valid");
            return curr->data;
        }

        Iterator &operator++() {
            if (!curr)
                throw runtime_error("Not Valid");
            curr = curr->next;
            return *this;
        }
        Iterator operator++(int) {
            if (!curr)
                throw runtime_error("Not Valid");
            Iterator tem = *this;
            curr = curr->next;
            return tem;
        }
        Iterator &operator--() {
            if (!curr)
                throw runtime_error("Not Valid");
            curr = curr->pre;
            return *this;
        }
        Iterator operator--(int) {
            if (!curr)
                throw runtime_error("Not Valid");
            Iterator tem = *this;
            curr = curr->pre;
            return tem;
        }
        bool operator!=(const Iterator &other) const {
            return curr != other.curr;
        }
        bool operator==(const Iterator &other) const {
            return curr == other.curr;
        }
        Dnode<T> *getnode() const {
            return curr;
        }
        Iterator begin() const;
        Iterator end() const;
        Iterator begin();
        Iterator end();
    };

    class reverse_iterator {
        Dnode<T> *curr;

      public:
        reverse_iterator(Dnode<T> *node = nullptr) : curr(node) {
        }

        T &operator*() const {
            if (!curr)
                throw runtime_error("Invalid iterator");
            return curr->data;
        }

        reverse_iterator &operator--() {
            if (!curr)
                throw runtime_error("Cannot increment");
            curr = curr->next;
            return *this;
        }

        reverse_iterator &operator++() {
            if (!curr)
                throw runtime_error("Cannot decrement");
            curr = curr->pre;
            return *this;
        }

        reverse_iterator operator--(T) {
            if (!curr)
                throw runtime_error("Cannot increment");
            reverse_iterator tem = *this;
            curr = curr->next;
            return tem;
        }

        reverse_iterator operator++(T) {
            if (!curr)
                throw runtime_error("Cannot decrement");
            reverse_iterator tem = *this;
            curr = curr->pre;
            return tem;
        }

        bool operator!=(const reverse_iterator &other) const {
            return curr != other.curr;
        }

        bool operator==(const reverse_iterator &other) const {
            return curr == other.curr;
        }
        Dnode<T> *getnode() const {
            return curr;
        }
    };

    reverse_iterator rbegin() {
        return reverse_iterator(tail);
    }

    reverse_iterator rend() {
        return reverse_iterator(nullptr);
    }

    reverse_iterator rbegin() const {
        return reverse_iterator(tail);
    }

    reverse_iterator rend() const {
        return reverse_iterator(nullptr);
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return (nullptr);
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    Iterator next(const Iterator &it, int step) {
        if (step < 0 && it == begin())
            throw runtime_error("Out of range");
        if (!head)
            throw runtime_error("Empty FL");
        if (step == 0)
            return it;
        Iterator tem = it;
        if (step > 0) {
            for (int i = 0; i < step; ++i) {
                ++tem;
            }
        } else {
            for (int i = 0; i < -step; ++i)
                --tem;
        }
        return tem;
    }

    void forward() const {

        for (auto it = head; it != nullptr; it = it->next) {
            if (it->next)
                cout << it->data << "<->";
            else
                cout << it->data;
        }
    }

    void backward() const {

        for (auto it = tail; it != nullptr; it = it->pre) {
            if (it->pre)
                cout << it->data << "<->";
            else
                cout << it->data;
        }
    }

    void ins_atend(const T &val) {
        Dnode<T> *newnode = new Dnode<T>(val);
        if (empty()) {
            head = tail = newnode;
            return;
        }
        if (!head->next) {
            tail = newnode;
            head->next = tail;
            tail->pre = head;
            return;
        }
        tail->next = newnode;
        newnode->pre = tail;
        tail = newnode;
    }

    void ins_atpos(const Iterator &it, const T &val) {

        if (it == begin()) {
            ins_front(val);
            return;
        }

        if (it == end()) {
            ins_atend(val);
            return;
        }

        if (!it.getnode())
            throw runtime_error("Not valid");
        Dnode<T> *newnode = new Dnode<T>(val);
        newnode->next = it.getnode();
        it.getnode()->pre->next = newnode;
        newnode->pre = it.getnode()->pre;
        it.getnode()->pre = newnode;
    }

    void ins_front(const T &val) {
        Dnode<T> *newnode = new Dnode<T>(val);
        if (empty()) {
            head = tail = newnode;
            return;
        }
        newnode->next = head;
        head->pre = newnode;
        head = newnode;
    }

    void pop_front() {
        if (empty())
            throw runtime_error("Empty FL");
        if (!head->next) {
            head = tail = nullptr;
            return;
        }
        Dnode<T> *tem = head;
        head = head->next;
        head->pre = nullptr;
        delete tem;
        tem = nullptr;
    }

    void pop_back() {
        if (empty())
            throw runtime_error("Empty FL");
        if (!head->next) {
            head = tail = nullptr;
            return;
        }
        Dnode<T> *tem = tail;
        tail = tail->pre;
        tail->next = nullptr;
        delete tem;
        tem = nullptr;
    }

    void del_atpos(const Iterator &it) {
        if (empty())
            throw runtime_error("Empty FL");
        if (!it.getnode())
            throw runtime_error("Not found");
        if (it == begin()) {
            pop_front();
            return;
        }
        if (it.getnode() == tail) {
            pop_back();
            return;
        }
        if (it.getnode()) {
            Dnode<T> *curr = it.getnode();
            Dnode<T> *prev = it.getnode()->pre;
            Dnode<T> *sec = it.getnode()->next;
            prev->next = sec;
            sec->pre = prev;
            delete curr;
            curr = nullptr;
        }
    }

    int size() const {
        if (empty())
            return 0;
        int len = 0;
        Dnode<T> *tem = head;
        while (tem) {
            ++len;
            tem = tem->next;
        }
        return len;
    }

    bool empty() const {
        if (!head && !tail)
            return true;
        return false;
    }

    void clear() {
        if (!head)
            return;
        if (head->next) {
            head = tail = nullptr;
            return;
        }
        Iterator tem = begin();
        while (tem != end()) {
            auto it = tem;
            ++tem;
            delete it.getnode();
        }
        head = tail = nullptr;
    }

    ~LL() {
        clear();
    }

    void remove(const T &v) {
        if (empty() || (!head->next && head->data != v))
            return;
        Iterator tem = begin();
        while (tem != end()) {
            if (tem.getnode()->data == v) {
                del_atpos(tem);
            }
            tem++;
        }
    }

    T front() const {
        if (empty())
            throw runtime_error("Empty");
        return head->data;
    }

    T back() const {
        if (empty())
            throw runtime_error("Empty");
        return tail->data;
    }

    void reverse() {
        if (empty())
            return;
        Dnode<T> *the_next = nullptr;
        Dnode<T> *curr = head;
        Dnode<T> *previous = nullptr;
        while (curr) {
            the_next = curr->next;
            curr->next = previous;
            curr->pre = the_next;
            previous = curr;
            curr = the_next;
        }
        head = previous;
    }
};

template <typename Iterator> Iterator Next_ll(Iterator it, int step) {

    for (int i = 0; i < step && it != Iterator{}; ++i) {
        ++it;
    }
    return it;
}

template <typename Iterator> Iterator Prev_ll(Iterator it, int step) {
    for (int i = 0; i < step; ++i) {
        --it;
    }
    return it;
}
#endif