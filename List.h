#pragma once
#ifndef _FL
#define _FL
#include "Node.h"
#include <initializer_list>
#include <iostream>

using namespace std;
template <class T> class FL {
    Node<T> *head;

  public:
    FL() : head(nullptr) {};
    FL(const initializer_list<T> &nums) : head(nullptr) {
        for (const T &val : nums) {
            ins_atend(val);
        }
    }
    FL(const FL<T> &list) {

        for (const T &val : list) {
            ins_atend(val);
        }
    }

    FL(int n, const T &val) : head(nullptr) {
        for (int i = 0; i < n; ++i)
            ins_atend(val);
    }

  private:
    Node<T> *getHead() const {
        return head;
    }

    void setHead(Node<T> *newHead) {
        head = newHead;
    }

  public:
    class Iterator {
        Node<T> *curr;

      public:
        Iterator(Node<T> *n = nullptr) {
            this->curr = n;
        }
        T &operator*() const {
            if (!curr)
                throw runtime_error("Not Found");
            return curr->data;
        }

        Iterator &operator++() {
            if (curr)
                curr = curr->next;
            return *this;
        }
        Iterator operator++(T) {
            Iterator it = *this;
            if (curr)
                curr->next;
            return it;
        }
        bool operator!=(const Iterator &it) const {
            return curr != it.curr;
        }
        bool operator==(const Iterator &it) const {
            return curr == it.curr;
        }
        Node<T> *getnode() const {
            return curr;
        }
    };

    void ins_atend(const T &val) {
        Node<T> *tem = new Node<T>(val);
        if (!head) {
            head = tem;
            head->next = nullptr;
            return;
        }

        if (!head->next) {
            head->next = tem;
            tem->next = nullptr;
            return;
        }

        Node<T> *temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = tem;
    }

    void print() const {
        if (!head)
            return;
        Node<T> *tem = head;
        while (tem) {
            if (tem->next)
                cout << tem->data << "->";
            else
                cout << tem->data;
            tem = tem->next;
        }
    }
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
    void ins_front(const T &val) {
        Node<T> *tem = new Node<T>(val);
        if (!head) {
            head = tem;
            return;
        }

        tem->next = head;
        head = tem;
        return;
    }
    int size() const {
        int res = 0;
        for (auto it = head; it != nullptr; it = it->next) {
            ++res;
        }
        return res;
    }
    Iterator next(const Iterator &it, int step) {
        if (!head)
            return Iterator(nullptr);
        if (step == 0)
            return it;
        Iterator tem = it;
        for (int i = 0; i < step; ++i) {
            ++tem;
        }
        return tem;
    }
    void ins_atpos(const Iterator &it, const T &val) {
        if (!head)
            return;
        if (it == this->begin()) {
            ins_front(val);
            return;
        }

        if (it == this->end()) {
            ins_atend(val);
            return;
        }

        Iterator tem = head;
        while (this->next(tem, 1) != it && tem != end())
            ++tem;
        if (it.getnode()) {
            Node<T> *newnode = new Node<T>(val);
            newnode->next = tem.getnode()->next;
            tem.getnode()->next = newnode;
        }
    }
    void pop_front() {
        if (!head) {
            throw runtime_error("Empty FL");
        }
        Node<T> *tem = head;
        head = head->next;
        delete tem;
        tem = nullptr;
    }
    void pop_back() {
        if (!head) {
            throw runtime_error("Empty FL");
        }
        if (!head->next) {
            head = nullptr;
            return;
        }
        Node<T> *tem = head;
        while (tem->next->next) {
            tem = tem->next;
        }
        Node<T> *tail = tem->next;
        delete tail;
        tem->next = nullptr;
        tail = nullptr;
    }
    void del_atpos(const Iterator &it) {
        if (!head) {
            throw runtime_error("Empty FL");
        }
        if (it == end())
            throw runtime_error("Not Valid");

        if (it == begin()) {
            pop_front();
            return;
        }

        if (it == next(begin(), this->size() - 1)) {
            pop_back();
            return;
        }

        if (it.getnode()) {
            Iterator prev = begin();
            while (prev != end() && next(prev, 1) != it) {
                ++prev;
            }
            Node<T> *deleted = it.getnode();
            prev.getnode()->next = deleted->next;
            delete deleted;
        }
    }

    ~FL() {
        if (!head)
            return;
        if (head->next) {
            head = nullptr;
            return;
        }
        Iterator tem = Iterator(head);
        while (tem != end()) {
            auto it = tem;
            ++tem;
            delete it.getnode();
        }
        head = nullptr;
    }
    T back() const {
        if (!head)
            throw runtime_error("FL is empty");

        if (!head->next)
            return head->data;
        Iterator tem = head;
        while (tem.getnode()->next)
            ++tem;
        return *tem;
    }
    void merge(FL<T> &l2) {

        if (l2.empty())
            return;

        if (this->empty()) {
            head = l2.head;
            l2.head = nullptr;
            return;
        }

        Node<T> *dummy = new Node<T>();
        Node<T> *current = dummy;

        Node<T> *temp1 = head;
        Node<T> *temp2 = l2.head;

        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->data < temp2->data) {
                current->next = temp1;
                temp1 = temp1->next;
            } else {
                current->next = temp2;
                temp2 = temp2->next;
            }
            current = current->next;
        }

        if (temp1 != nullptr) {
            current->next = temp1;
        }

        if (temp2 != nullptr) {
            current->next = temp2;
        }

        head = dummy->next;

        delete dummy;
        l2.head = nullptr;
    }
    void swap_n(const int &k) {
        if (this->empty() || this->size() < k)
            return;
        Node<T> *pre = new Node<T>();
        Node<T> *curr = head;
        Node<T> *sec = head->next;
        for (int i = 0; i < this->size() / 2; ++i) {
            Node<T> *next_step = sec->next;
            curr->next = next_step;
            sec->next = curr;
            if (!pre) {
                head = sec;

            } else {
                pre->next = sec;
            }
            pre = curr;
            curr = next_step->next;
            sec = next_step;
        }
    }

    bool empty() const {
        if (!head)
            return true;
        return false;
    }
    void reverse() {
        if (empty())
            return;
        Node<T> *curr = head;
        Node<T> *pre = nullptr;
        Node<T> *sec = nullptr;
        while (curr) {
            sec = curr->next;
            curr->next = pre;
            pre = curr;

            curr = sec;
        }
        head = pre;
    }
    void remove(const T &val) {
        if (empty())
            throw runtime_error("Empty List");
        if (!head->next && head->data != val)
            return;
        Node<T> *tem = head;
        while (tem) {
            if (tem->next && tem->next->data == val) {
                Node<T> *del = tem->next;
                tem->next = tem->next->next;
                delete del;
                del = nullptr;
                break;
            }
            tem = tem->next;
        }
    }
    FL(const Iterator &be, const Iterator &en) : head(nullptr) {

        Iterator it = be;
        while (it != en) {
            ins_atend(*it);
            ++it;
        }
    }
    void clear() {
        if (empty())
            return;
        Node<T> *tem = head;
        while (tem) {
            Node<T> *del = tem;
            tem = tem->next;
            delete del;
            del = nullptr;
        }
        head = nullptr;
    }
    FL &operator=(FL &&other) {
        if (this != &other) {
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }
    FL &operator=(const FL<T> &other) {
        if (this != &other) {
            if (!this->empty()) {
                clear();
            }
            for (const T &v : other) {
                ins_atend(v);
            }
        }
        return *this;
    }

    FL(FL &&other) : head(other.head) {
        other.head = nullptr;
    }

    void resize(const int &n) {
        if (n == 0) {
            head = nullptr;
            return;
        }
        if (n == this->size())
            return;
        if (n > this->size()) {
            Node<T> *tem = head;
            while (tem->next) {
                tem = tem->next;
            }
            int x = this->size();
            for (int i = 0; i < n - x; ++i) {
                Node<T> *new_node = new Node(T());
                tem->next = new_node;
                tem = new_node;
            }
        }

        else {
            Node<T> *tem = head;
            for (int i = 0; i < n; ++i) {
                if (i != n - 1) {
                    tem = tem->next;
                } else {
                    tem->next = nullptr;
                }
            }
        }
    }
};
template <class Iterator> Iterator Next(Iterator it, int step) {
    for (int i = 0; i < step; ++i) {
        ++it;
    }
    return it;
}

#endif