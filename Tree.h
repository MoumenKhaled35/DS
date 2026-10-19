#pragma once
#ifndef _TREE
#define _TREE
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

template <class T> class BT {
    struct Node {
        T val;
        Node *left;
        Node *right;
        Node(const T &val) {
            this->val = val;
            this->right = this->left = nullptr;
        }
        Node(const T &val, Node *left, Node *right) {
            this->val = val;
            this->right = right;
            this->left = left;
        }
        Node() {
        }
    };

    Node *root;
    int sz;

    void insert_pri(const T &val) {
        Node *new_node = new Node(val);
        if (!root) {
            root = new_node;
            root->left = root->right = nullptr;
            return;
        }
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();
            if (!curr->left) {
                curr->left = new_node;
                ++sz;
            } else {
                q.push(curr->left);
            }
            if (!curr->right) {
                curr->right = new_node;
                q.push(curr->right);
                ++sz;
            } else {
                q.push(curr->right);
            }
        }
    }

    void preorder_pri(Node *root, bool &first) {
        if (!root)
            return;
        if (first) {
            cout << root->val;
            first = !first;
        } else {
            cout << "->" << root->val;
        }
        preorder_pri(root->left, first);
        preorder_pri(root->right, first);
    }

    void postorder_pri(Node *root, bool &first) {
        if (!root)
            return;
        postorder_pri(root->left, first);
        postorder_pri(root->right, first);
        if (first) {
            cout << root->val;
            first = !first;
        } else {
            cout << "->" << root->val;
        }
    }

    void inorder_pri(Node *root, bool &first) {
        if (!root)
            return;
        inorder_pri(root->left, first);
        if (first) {
            cout << root->val;
            first = !first;
        } else {
            cout << "->" << root->val;
        }
        inorder_pri(root->right, first);
    }

    int height(Node *node) {
        if (!node)
            return 0;

        return max(height(node->left), height(node->right)) + 1;
    }
    int height_node(Node *root, const T &val) {
        if (!root)
            return -1;

        if (root->val == val)
            return height(root);

        int left = height_node(root->left, val);

        if (left != -1)
            return left;

        return height_node(root->right, val);
    }

    int sum_pri(Node *root) const {
        if (!root)
            return 0;
        return root->val + sum_pri(root->left) + sum_pri(root->right);
    }

    int mx_sum(Node *root) {
        if (!root)
            return 0;
        Node *l = root->left;
        Node *r = root->right;
        return max(sum_pri(l), sum_pri(r)) + root->val;
    }

    Node *get_root() {
        return root;
    }

    int leafs(Node *root) {
        if (!root)
            return 0;
        if (!root->left && !root->right)
            return 1;
        return leafs(root->left) + leafs(root->right);
    }

    void lvl_order(Node *root) {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);
        bool first = 1;
        while (!q.empty()) {
            for (int i = 0; i < q.size(); ++i) {
                Node *curr = q.front();
                q.pop();
                if (first) {
                    cout << curr->val;
                    first = !first;
                } else {
                    cout << "->" << curr->val;
                }
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
    }

    Node *mirror_pri(Node *root) {
        if (!root)
            return nullptr;
        Node *newnode = new Node(root->val);
        newnode->left = mirror_pri(root->right);
        newnode->right = mirror_pri(root->left);
        return newnode;
    }

    int mx_lvl(Node *root) {
        if (!root)
            return 0;
        queue<Node *> q;
        q.push(root);
        int mx = 0;
        while (!q.empty()) {
            for (int i = 0; i < q.size(); ++i) {
                Node *curr = q.front();
                q.pop();
                mx = max(mx, curr->val);
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
        return mx;
    }

    void clear_pri(Node *node) {
        if (!node)
            return;
        queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
            delete curr;
            sz--;
        }
    }

    bool Identical(Node *root1, Node *root2) {
        if (!root1 && !root2)
            return true;
        if (!root1 || !root2)
            return false;
        return Identical(root1->left, root2->left) &&
               Identical(root1->right, root2->right) &&
               (root1->val == root2->val);
    }

    bool Balance(Node *root) {
        if (!root)
            return true;
        int leftHeight = heigh_pri(root->left);
        int rightHeight = heigh_pri(root->right);
        return abs(leftHeight - rightHeight) <= 1 && Balance(root->left) &&
               Balance(root->right);
    }

    void spiral(Node *node) {
        if (!node)
            return;
        stack<Node *> s1, s2;
        s1.push(node);
        bool c = true;
        while (!s1.empty() || !s2.empty()) {
            if (c) {
                while (!s1.empty()) {
                    Node *curr = s1.top();
                    cout << curr->val << " ";
                    s1.pop();
                    if (curr->right)
                        s2.push(curr->right);
                    if (curr->left)
                        s2.push(curr->left);
                }
            } else {
                while (!s2.empty()) {
                    Node *curr = s2.top();
                    cout << curr->val << " ";
                    s2.pop();
                    if (curr->left)
                        s1.push(curr->left);
                    if (curr->right)
                        s1.push(curr->right);
                }
            }
            c = !c;
        }
    }

    void left_view(Node *root) {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                Node *curr = q.front();
                q.pop();
                if (i == 0)
                    cout << curr->val << " ";
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
    }

    void right_view(Node *root) {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                Node *curr = q.front();
                q.pop();
                if (i == n - 1)
                    cout << curr->val << " ";
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
    }

    void pre_iter(Node *root) {
        if (!root)
            return;
        stack<Node *> s;
        s.push(root);
        while (!s.empty()) {
            Node *curr = s.top();
            cout << curr->val << " ";
            s.pop();
            if (curr->right)
                s.push(curr->right);
            if (curr->left)
                s.push(curr->left);
        }
    }

    void post_iter(Node *root) {
        if (!root)
            return;
        stack<Node *> s;
        stack<T> res;
        s.push(root);
        while (!s.empty()) {
            Node *curr = s.top();
            s.pop();
            res.push(curr->val);
            if (curr->left)
                s.push(curr->left);
            if (curr->right)
                s.push(curr->right);
        }
        while (!res.empty()) {
            cout << res.top() << " ";
            res.pop();
        }
    }

    T max_ele(Node *root) {
        if (!root)
            return T();
        return max({root->val, max_ele(root->left), max_ele(root->right)});
    }

    void inorder_iter(Node *root) {
        if (!root)
            return;
        stack<Node *> s;
        Node *curr = root;
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->val << " ";
            curr = curr->right;
        }
    }

    template <class Container, class Iter>
    Node *build_pre_in(const Container &pre, const Container &in, Iter l,
                       Iter r, Iter &pre_idx, unordered_map<T, int> &mp) {
        if (l == r)
            return nullptr;
        T rootVal = *pre_idx;
        pre_idx++;
        Node *node = new Node(rootVal);
        Iter mid = next(in.begin(), mp[rootVal]);
        node->left = build_pre_in(pre, in, l, mid, pre_idx, mp);
        node->right = build_pre_in(pre, in, next(mid, 1), r, pre_idx, mp);
        return node;
    }

    template <class Container, class Iter>
    Node *build_post_in(const Container &pre, const Container &in, Iter l,
                        Iter r, Iter &post_idx, unordered_map<T, int> &mp) {
        if (l == r)
            return nullptr;
        T rootVal = *post_idx;
        post_idx--;
        Node *node = new Node(rootVal);
        Iter mid = next(in.begin(), mp[rootVal]);
        node->right = build_post_in(pre, in, next(mid, 1), r, post_idx, mp);
        node->left = build_post_in(pre, in, l, mid, post_idx, mp);
        return node;
    }
    void Vertical(Node *root) {
        if (!root)
            return;

        queue<pair<Node *, int>> q;
        map<int, vector<T>> mp;

        q.push({root, 0});

        while (!q.empty()) {
            auto [curr, col] = q.front();
            q.pop();

            mp[col].push_back(curr->val);

            if (curr->left)
                q.push({curr->left, col - 1});

            if (curr->right)
                q.push({curr->right, col + 1});
        }

        for (auto &[col, vec] : mp) {
            for (auto &x : vec)
                cout << x << " ";
            cout << '\n';
        }
    }

    void diagonal(Node *root, int d, map<int, vector<T>> &mp) {
        if (!root)
            return;

        mp[d].push_back(root->val);

        diagonal(root->right, d, mp);
        diagonal(root->left, d + 1, mp);
    }

    void Bound(Node *node) {
        if (!node)
            return;
        vector<T> res;
        queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                Node *curr = q.front();
                q.pop();
                if (i == 0 || (!curr->left && !curr->right)) {
                    res.push_back(curr->val);
                }
                if (curr->left && curr->left->val != -1) {
                    q.push(curr->left);
                }
                if (curr->right && curr->right->val != -1) {
                    q.push(curr->right);
                }
            }
        }
        Node *tem = root;
        stack<T> res2;
        while (tem->right) {
            res2.push(tem->val);
            tem = tem->right;
        }
        for (const T &v : res)
            cout << v << " ";
        while (!res2.empty()) {
            cout << res2.top() << " ";
            res2.pop();
        }
    }

    void remove_pri(const T &v) {
        if (!root)
            return;
        Node *deep = nullptr;
        Node *target = nullptr;
        Node *parent = nullptr;
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();

            if (curr->val == v) {
                target = curr;
            }
            if (curr->left && curr->left->val != -1) {
                parent = curr;
                deep = curr->left;
                q.push(curr->left);
            }
            if (curr->right && curr->right->val != -1) {
                parent = curr;
                deep = curr->right;
                q.push(curr->right);
            }
        }
        target->val = deep->val;
        if (parent->right == deep) {
            delete parent->right;
            parent->right = nullptr;
        } else if (parent->left == deep) {
            delete parent->left;
            parent->left = nullptr;
        }
    }

    void morres_in(Node *node) {
        while (node) {

            if (!node->left) {
                cout << node->val << " ";
                node = node->right;
            } else {
                Node *pre = node->left;
                while (pre->right && pre->right != node) {
                    pre = pre->right;
                }
                if (!pre->right) {
                    pre->right = node;
                    node = node->left;
                } else {
                    pre->right = nullptr;
                    cout << node->val << " ";
                    node = node->right;
                }
            }
        }
    }

    void morres_pre(Node *node) {
        while (node) {

            if (!node->left) {
                cout << node->val << " ";
                node = node->right;
            } else {
                Node *pre = node->left;
                while (pre->right && pre->right != node) {
                    pre = pre->right;
                }
                if (!pre->right) {
                    cout << node->val << " ";
                    pre->right = node;
                    node = node->left;
                } else {
                    pre->right = nullptr;
                    node = node->right;
                }
            }
        }
    }

    void morres_post(Node *root, vector<T> &res) {
        Node *current = root;

        while (current != NULL) {
            if (current->right == NULL) {
                res.push_back(current->val);
                current = current->left;
            } else {
                Node *predecessor = current->right;
                while (predecessor->left != NULL &&
                       predecessor->left != current) {
                    predecessor = predecessor->left;
                }

                if (predecessor->left == NULL) {
                    res.push_back(current->val);
                    predecessor->left = current;
                    current = current->right;
                }

                else {
                    predecessor->left = NULL;
                    current = current->left;
                }
            }
        }

        for (int i = res.size() - 1; i >= 0; --i) {
            cout << res[i] << " ";
        }
    }

    void flat(Node *root) {
        if (!root)
            return;
        Node *cur = root;
        while (cur) {
            if (!cur->left) {
                cur = cur->right;
            } else {
                Node *pre = cur->left;
                while (pre->right) {
                    pre = pre->right;
                }
                pre->right = cur->right;
                cur->right = nullptr;
                cur = cur->left;
            }
        }
    }

    bool is_bst(Node *node) {
        if (!node)
            return false;
        queue<Node *> q;
        q.push(node);

        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();

            if (curr->left) {
                if (curr->left->val > curr->val)
                    return false;

                q.push(curr->left);
            }

            if (curr->right) {
                if (curr->right->val <= curr->val)
                    return false;

                q.push(curr->right);
            }
        }

        return true;
    }

    bool is_bst_recursive(Node *node) {
        if (!node)
            return true;
        if (node->left) {
            if (node->left->val > node->val) {
                return false;
            }
        }
        if (node->right) {
            if (node->right->val <= node->val) {
                return false;
            }
        }
        return is_bst_recursive(node->left) && is_bst_recursive(node->right);
    }

    void fixed(Node *node) {
        if (!node)
            return;
        stack<Node *> s;
        vector<T> vec_sorted, vec;
        vec_sorted.reserve(sz);
        vec.reserve(sz);
        Node *curr = root;
        s.push(curr);
        while (curr || !s.empty()) {
            while (curr) {
                curr = curr->left;
                s.push(curr);
            }
            curr = s.top();
            s.pop();
            vec_sorted.push_back(curr->val);
            vec.push_back(curr->val);
            curr = curr->right;
        }
        sort(vec_sorted.begin(), vec_sorted.end());
        T f, sec;
        bool first = 1;
        for (int i = 0; i < sz; ++i) {
            if (vec_sorted[i] != vec[i]) {
                if (first) {
                    f = vec_sorted[i];
                    first = !first;
                } else {
                    sec = vec_sorted[i];
                }
            }
        }
        Node *n1 = get_bst(f);
        n1->val = s;
        Node *n2 = get_bst(s);
        n2->val = f;
    }

    Node *get_bst(Node *node, const T &n) {
        if (!node)
            return nullptr;
        if (node->val == n)
            return node;
        if (n <= node->val) {
            return get_bst(node->left, n);
        } else {
            return get_bst(node->right, n);
        }
    }

    // Node *first = nullptr;
    // Node *second = nullptr;
    // Node *prev = nullptr;

    // void recover(Node *node) {
    //     if (!node)
    //         return;

    //     recover(node->left);

    //     if (prev && prev->val > node->val) {
    //         if (!first)
    //             first = prev;

    //         second = node;
    //     }

    //     prev = node;

    //     recover(node->right);
    // }

    int size_sub_tree(Node *n) {
        if (!n)
            return 0;

        return size_sub_tree(n->left) + size_sub_tree(n->right) + 1;
    }
    Node *get_node(Node *node, const T &v) {
        if (!node)
            return nullptr;
        if (node->val == v)
            return node;
        get_node(node->left, v);
        get_node(node->right, v);
    }

    int large_bst(Node *node, int &res = 0) {
        if (!node)
            return 0;
        if (is_bst(node)) {
            res = max(res, size_sub_tree(node));
        }
        large_bst(node->left, res);
        large_bst(node->right, res);
        return res;
    }

    int max_bst(Node *node, int &res = 0) {
        if (!node)
            return 0;
        if (is_bst(node)) {
            res = max(res, sum_pri(node));
        }
        max_bst(node->left, res);
        max_bst(node->right, res);
        return res;
    }

    bool max_heap(Node *node) {
        if (!node)
            return true;

        if (node->left && node->val < node->left->val)
            return false;

        if (node->right && node->val < node->right->val)
            return false;

        return max_heap(node->left) && max_heap(node->right);
    }

    // bool is_heap(Node *node) {
    //     if (!node)
    //         return true;
    //     return (node->val > node->left->val) &&  مش هينفع عشان هنا مش بيتاكد
    //     اذا كان في ابن ايمن او ايسر او لا
    //            (node->val > node->right->val) && is_heap(node->left) &&
    //            is_heap(node->right);
    // }

    bool min_heap(Node *node) {
        if (!node)
            return true;

        if (node->left && node->val > node->left->val)
            return false;

        if (node->right && node->val > node->right->val)
            return false;

        return min_heap(node->left) && min_heap(node->right);
    }

    void heapify(Node *node) {
        if (!node)
            return;
        vector<T> vec;
        stack<Node *> s;
        s.push(root);
        Node *curr = root;
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            if (curr->val != -1)
                vec.push_back(curr->val);

            curr = curr->right;
        }
        curr = root;
        while (!s.empty()) {
            s.pop();
        }
        s.push(curr);
        stack<Node *> res;
        while (!s.empty()) {
            Node *curr = s.top();
            res.push(curr);
            s.pop();
            if (curr->left && curr->left->val != -1) {
                s.push(curr->left);
            }
            if (curr->right && curr->right->val != -1) {
                s.push(curr->right);
            }
        }
        int i = 0;
        while (!res.empty() && i < vec.size()) {
            res.top()->val = vec[i++];
            res.pop();
            if (i == vec.size())
                break;
        }
    }

  public:
    BT() : root(nullptr), sz(0) {
    }

    BT(const initializer_list<T> &vec) : root(nullptr), sz(0) {
        if (vec.size() == 0)
            return;
        auto it = vec.begin();
        if (*it == T(-1))
            return;
        root = new Node(*it);
        sz++;
        ++it;
        queue<Node *> q;
        q.push(root);
        while (!q.empty() && it != vec.end()) {
            Node *curr = q.front();
            q.pop();
            if (it != vec.end() && *it != T(-1)) {
                curr->left = new Node(*it);
                ++sz;
                q.push(curr->left);
            }
            if (it != vec.end())
                ++it;
            if (it != vec.end() && *it != T(-1)) {
                curr->right = new Node(*it);
                ++sz;
                q.push(curr->right);
            }
            if (it != vec.end())
                ++it;
        }
    }

    template <class Container> BT(const Container &vec) : root(nullptr), sz(0) {
        if (vec.size() == 0)
            return;
        auto it = vec.begin();
        if (*it == T(-1))
            return;
        root = new Node(*it);
        sz++;
        ++it;
        queue<Node *> q;
        q.push(root);
        while (!q.empty() && it != vec.end()) {
            Node *curr = q.front();
            q.pop();
            if (it != vec.end() && *it != T(-1)) {
                curr->left = new Node(*it);
                ++sz;
                q.push(curr->left);
            }
            if (it != vec.end())
                ++it;
            if (it != vec.end() && *it != T(-1)) {
                curr->right = new Node(*it);
                ++sz;
                q.push(curr->right);
            }
            if (it != vec.end())
                ++it;
        }
    }

    BT(const initializer_list<T> &post, const initializer_list<T> &in)
        : root(nullptr), sz(0) {
        unordered_map<T, int> mp;
        int idx = 0;
        for (const T &v : in)
            mp[v] = idx++;
        auto post_idx = post.end();
        --post_idx;
        root = build_post_in(post, in, in.begin(), in.end(), post_idx, mp);
        sz = in.size();
    }

    template <class Cont, class Iter>
    BT(const Cont &pre, const Cont &in) : root(nullptr), sz(0) {
        unordered_map<T, int> mp;
        int idx = 0;
        for (const T &v : in)
            mp[v] = idx++;
        Iter pre_idx = pre.begin();
        root = build_pre_in(pre, in, in.begin(), in.end(), pre_idx, mp);
        sz = in.size();
    }

    BT(const BT<T> &tree) : root(nullptr), sz(0) {
        if (!tree.empty()) {
            root = new Node(tree.root->val);
            ++sz;
            queue<Node *> q, t;
            t.push(tree.root);
            q.push(root);
            while (!q.empty()) {
                for (int i = 0; i < t.size(); ++i) {
                    Node *curr_Bulid = q.front();
                    q.pop();
                    Node *needed = t.front();
                    t.pop();
                    if (needed->left && needed->left->val != T(-1)) {
                        curr_Bulid->left = new Node(needed->left->val);
                        ++sz;
                        q.push(curr_Bulid->left);
                        t.push(needed->left);
                    }
                    if (needed->right && needed->right->val != T(-1)) {
                        curr_Bulid->right = new Node(needed->right->val);
                        ++sz;
                        q.push(curr_Bulid->right);
                        t.push(needed->right);
                    }
                }
            }
        }
    }

    BT(BT &&other) noexcept : root(other.root), sz(other.sz) {
        other.root = nullptr;
        other.sz = 0;
    }

    ~BT() {
        clear();
    }

    void insert(const T &val) {
        insert_pri(val);
    }

    void preorder() {
        bool x = true;
        preorder_pri(root, x);
        cout << "\n";
    }

    void postorder() {
        bool x = true;
        postorder_pri(root, x);
        cout << "\n";
    }

    void inorder() {
        bool x = true;
        inorder_pri(root, x);
        cout << "\n";
    }

    int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    int heigh() {
        return heigh_pri(root);
    }

    int heigh_node(const T &v) {
        return heigh_node(root, v);
    }

    int sum() const {
        return sum_pri(root);
    }

    int max_sum() {
        return mx_sum(root);
    }

    void lvl_order() {
        lvl_order(root);
    }

    int mx_lvl() {
        return mx_lvl(root);
    }

    void clear() {
        clear_pri(root);
        root = nullptr;
    }

    BT &operator=(const BT<T> &tree) {
        if (this != &tree) {
            this->clear();
            root = new Node(tree.root->val);
            ++sz;
            queue<Node *> q, t;
            t.push(tree.root);
            q.push(root);
            while (!q.empty()) {
                for (int i = 0; i < t.size(); ++i) {
                    Node *curr_Bulid = q.front();
                    q.pop();
                    Node *needed = t.front();
                    t.pop();
                    if (needed->left && needed->left->val != T(-1)) {
                        curr_Bulid->left = new Node(needed->left->val);
                        ++sz;
                        q.push(curr_Bulid->left);
                        t.push(needed->left);
                    }
                    if (needed->right && needed->right->val != T(-1)) {
                        curr_Bulid->right = new Node(needed->right->val);
                        ++sz;
                        q.push(curr_Bulid->right);
                        t.push(needed->right);
                    }
                }
            }
        }
        return *this;
    }

    BT &operator=(BT &&other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            sz = other.sz;
            other.root = nullptr;
            other.sz = 0;
        }
        return *this;
    }

    bool Identical(const BT<T> &tree) {
        return Identical(root, tree.root);
    }

    void mirror() {
        root = mirror_pri(root);
    }

    bool Balance() {
        return Balance(root);
    }

    void spiral() {
        spiral(root);
    }

    void left_view() {
        left_view(root);
    }

    void right_view() {
        right_view(root);
    }

    void pre_iter() {
        pre_iter(root);
    }

    void post_iter() {
        post_iter(root);
    }

    T max_ele() {
        return max_ele(root);
    }

    void inorder_iter() {
        inorder_iter(root);
    }

    void ver() {
        Vertical(root);
    }

    void DiagonalTraversal() {
        map<int, vector<T>> mp;

        diagonal(root, 0, mp);

        for (auto &[_, vec] : mp)
            for (auto x : vec)
                cout << x << " ";
    }

    void Bound() {
        Bound(root);
    }

    void remove(const T &val) {
        remove_pri(val);
        --sz;
    }

    void morres_in() {
        morres_in(root);
    }

    void morres_pre() {
        morres_pre(root);
    }

    void morres_post() {
        morres_post(root);
    }

    void flat() {
        flat(root);
    }

    bool is_bst() {
        return is_bst(root);
    }

    bool is_bst_recursive() {
        return is_bst_recursive(root);
    }

    Node *get_bst(const T &n) {
        return get_bst(root, n);
    }

    Node *get_node(const T &v) {
        return get_node(root, v);
    }

    int size_sub_tree(const T &v) {
        return size_sub_tree(get_node(v));
    }
    int large_bst() {
        int res = 0;
        int ans = large_bst(root, res);
        return res;
    }

    int max_bst() {
        int res = 0;
        return max_bst(root, res);
    }

    bool is_heap() {
        return min_heap(root) || max_heap(root);
    }

    void heapify() {

        heapify(root);
    }
};

#endif