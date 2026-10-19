#pragma once
#ifndef _STR
#define _STR
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Str {
    char *st;
    size_t len;
    size_t cap = 100;

  public:
    Str(int capacity = 100) : cap(capacity), len(0), st(new char[capacity]) {
        st[0] = '\0';
    }

    Str(const Str &s) {
        len = s.len;
        cap = s.cap;
        st = new char[cap + 1];
        strncpy_s(st, cap + 1, s.st, len + 1);
    }

    Str(const char *x) {
        len = strlen(x);
        cap = len;
        st = new char[cap + 1];
        strncpy_s(st, cap + 1, x, len + 1);
    }

    Str(const string &s) {

        len = s.size();
        cap = len;
        st = new char[cap + 1];
        strncpy_s(st, cap + 1, s.c_str(), len + 1);
    }

    Str(const int &n, const char &ch) {
        st = new char[n + 1];
        len = n;
        cap = len;
        for (int i = 0; i < n; ++i) {
            st[i] = ch;
        }
        st[len] = '\0';
    }

    Str &operator=(const Str &s) {
        if (this != &s) {
            delete[] st;
            cap = s.cap;
            len = s.len;
            st = new char[cap + 1];
            strncpy_s(st, cap + 1, s.st, len + 1);
        }
        return *this;
    }

    Str(Str &&other) noexcept : st(other.st), len(other.len), cap(other.cap) {
        other.st = nullptr;
        other.cap = 0;
        other.len = 0;
    }
    template <class Iter> Str(const Iter &b, const Iter &end) {
        st = new char[distance(b, end) + 1];
        int i = 0;
        for (Iter it = b; it != end; ++it) {
            st[i++] = *it;
        }
        st[i] = '\0';
        len = i;
        cap = i;
    }

    Str &operator=(Str &&other) noexcept {
        if (this != &other) {
            delete[] st;
            st = other.st;
            len = other.len;
            cap = other.cap;
            other.st = nullptr;
            other.cap = 0;
            other.len = 0;
        }
        return *this;
    }

    Str &operator=(const char *x) {
        if (st != x) {

            len = strlen(x);
            cap = len;
            delete[] st;
            st = new char[cap + 1];
            strncpy_s(st, cap + 1, x, len + 1);
        }
        return *this;
    }

    char &operator[](const int &n) const {
        if (n >= len || n < 0)
            throw runtime_error("Index out of range");
        return st[n];
    }

    class Iterator {
        char *curr;

      public:
        Iterator() : curr(nullptr) {};

        Iterator(char *curr) : curr(curr) {};
        char &operator*() const {
            return *curr;
        }
        Iterator &operator++() {
            ++curr;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tem = *this;
            curr++;
            return tem;
        }

        Iterator &operator--() {
            --curr;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tem = *this;
            curr--;
            return tem;
        }

        Iterator operator+(const int &n) {
            return Iterator(curr + n);
        }

        Iterator operator-(const int &n) {
            return Iterator(curr - n);
        }

        int operator-(const Iterator &it) const {
            return curr - it.curr;
        }

        bool operator==(const Iterator &s) const {
            return curr == s.curr;
        }
        bool operator!=(const Iterator &s) const {
            return curr != s.curr;
        }
        ptrdiff_t operator-(const Iterator &it) {
            return curr - it.curr;
        }
    };

    Iterator begin() {
        return Iterator(st);
    };
    Iterator end() {
        return Iterator(st + len);
    };

    Iterator begin() const {
        return Iterator(st);
    };
    Iterator end() const {
        return Iterator(st + len);
    };

    class Rev_Iterator {
        char *curr;

      public:
        Rev_Iterator() : curr(nullptr) {};
        Rev_Iterator(char *curr) : curr(curr) {};
        char &operator*() const {
            return *curr;
        }
        Rev_Iterator &operator++() {
            --curr;
            return *this;
        }

        Rev_Iterator operator++(int) {
            Rev_Iterator tem = *this;
            curr--;
            return tem;
        }

        Rev_Iterator &operator--() {
            ++curr;
            return *this;
        }
        Rev_Iterator operator--(int) {
            Rev_Iterator tem = *this;
            curr++;
            return tem;
        }

        int operator-(const Rev_Iterator &it) {
            return it.curr - curr;
        }

        Rev_Iterator operator+(const int &n) {
            return Rev_Iterator(curr - n);
        }

        Rev_Iterator operator-(const int &n) {
            return Rev_Iterator(curr + n);
        }

        bool operator==(const Rev_Iterator &s) const {
            return curr == s.curr;
        }
        bool operator!=(const Rev_Iterator &s) const {
            return curr != s.curr;
        }
    };

    Rev_Iterator rbegin() {
        return Rev_Iterator(st + len - 1);
    };

    Rev_Iterator rend() {
        return Rev_Iterator(st - 1);
    };
    Rev_Iterator rbegin() const {
        return Rev_Iterator(st + len - 1);
    };

    Rev_Iterator rend() const {
        return Rev_Iterator(st - 1);
    };

    friend ostream &operator<<(ostream &out, const Str &s) {
        out << s.st;
        return out;
    }

    friend istream &operator>>(istream &in, Str &s) {
        in.getline(s.st, s.cap);
        return in;
    }

    void push_back(char ch) {
        if (empty()) {
            len = 1;
            cap = len;
            st = new char[cap + 1];
            st[0] = ch;
            st[len] = '\0';
            return;
        }
        if (len + 1 <= cap) {
            st[len] = ch;
            ++len;
            st[len] = '\0';
            cap = len;
            return;
        }
        int newcap = cap + 1;
        char *data = new char[newcap + 1];
        strncpy_s(data, newcap + 1, st, cap + 1);
        data[len] = ch;
        ++len;
        data[len] = '\0';
        delete[] st;
        st = data;
        cap = newcap;
        len = cap;
    }
    void clear() {
        delete[] st;
        len = cap = 0;
    }
    ~Str() {
        clear();
    }

  private:
    int idx(const char &ch) const {
        for (size_t i = 0; i < len; ++i) {
            if (st[i] == ch)
                return i;
        }
        return -1;
    }

  public:
    template <class Iter> void insert(const Iterator &pos, Iter b, Iter e) {
        int index = idx(*pos);
        if (len + (e - b) <= cap) {
            for (int i = cap - 1; i > index; --i) {
                st[i] = st[i - (e - b)];
            }
            Iter tem = b;
            for (int i = index; i < index + (e - b); ++i) {
                st[i] = *(tem++);
            }
            return;
        }
        int newcap = cap + (e - b);
        char *data = new char[newcap + 1];
        strncpy_s(data, newcap + 1, st, cap + 1);
        for (int i = newcap - 1; i >= index + (e - b); --i) {
            data[i] = data[i - (e - b)];
        }
        Iter tem = b;
        for (int i = index; i < index + (e - b); ++i) {
            data[i] = *(tem++);
        }
        data[newcap] = '\0';
        delete[] st;
        st = data;
        cap = newcap;
        len = len + (e - b);
    }
    void insert(const Iterator &it, const int &n, const char &ch) {
        if (n == 0)
            return;
        int index = idx(*it);
        if (index < 0 || index > len)
            throw runtime_error("Not valid");
        if (len + n <= cap) {
            for (int i = cap - 1; i > index; --i) {
                st[i] = st[i - 1];
            }
            for (int i = index; i < index + n; ++i) {
                st[i] = ch;
            }
            return;
        }
        int newcap = cap + n;
        char *data = new char[newcap + 1];
        strncpy_s(data, newcap + 1, st, cap + 1);
        for (int i = newcap - 1; i > index; --i) {
            data[i] = data[i - n];
        }
        for (int i = index; i < index + n; ++i) {
            data[i] = ch;
        }
        data[newcap] = '\0';
        delete[] st;
        st = data;
        cap = newcap;
        len = len + n;
    }

    int capacity() const {
        return cap;
    }
    bool empty() const {
        return (len == 0) ? true : false;
    }

    void erase(const Iterator &it) {

        if (empty() || it == end())
            throw runtime_error("Not Valid");
        int newcap = cap - 1;
        int idx = it - begin();
        char *data = new char[cap];
        for (int i = 0; i < idx; ++i) {
            data[i] = st[i];
        }
        for (int i = idx; i < len - 1; ++i) {
            data[i] = st[i + 1];
        }
        len = newcap;
        data[len] = '\0';
        delete[] st;
        st = data;
        cap = newcap;
    }
    int size() const {
        return len;
    }

    void erase(const Iterator &b, const Iterator &e) {
        if (empty() || b == e)
            return;
        int newcap = cap - (e - b);
        char *data = new char[newcap + 1];
        for (int i = 0; i < (b - begin()); ++i) {
            data[i] = st[i];
        }
        for (int i = (e - begin()); i < len; ++i) {
            data[i - (e - b)] = st[i];
        }
        data[newcap] = '\0';
        delete[] st;
        st = data;
        cap = newcap;
        len = newcap;
    }
};

#endif