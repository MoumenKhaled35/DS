#pragma once
#ifndef _BST
#define _BST
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

template <class T> class BST {
  protected:
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node(const T &v) : data(v), left(nullptr), right(nullptr) {
        }
    };

    Node *root;
    int len;

  private:
    void insert(Node *&node, const T &v) {
        if (!node) {
            node = new Node(v);
            ++len;
            return;
        }

        if (v <= node->data)
            insert(node->left, v);
        else
            insert(node->right, v);
    }

    void inorder(Node *node, bool &first) const {
        if (!node)
            return;

        inorder(node->left, first);

        if (!first)
            cout << "->";
        else
            first = false;

        cout << node->data;

        inorder(node->right, first);
    }

    void preorder(Node *node, bool &first) const {
        if (!node)
            return;

        if (!first)
            cout << "->";
        else
            first = false;

        cout << node->data;

        preorder(node->left, first);
        preorder(node->right, first);
    }

    void postorder(Node *node, bool &first) const {
        if (!node)
            return;

        postorder(node->left, first);
        postorder(node->right, first);

        if (!first)
            cout << "->";
        else
            first = false;

        cout << node->data;
    }

    void levelorder(Node *node, bool &first) const {
        if (!node)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();

            if (!first)
                cout << "->";
            else
                first = false;

            cout << curr->data;

            if (curr->left)
                q.push(curr->left);

            if (curr->right)
                q.push(curr->right);
        }
    }

    bool search(Node *node, const T &v) const {
        if (!node)
            return false;

        if (node->data == v)
            return true;

        if (v <= node->data)
            return search(node->left, v);

        return search(node->right, v);
    }

    void clear(Node *node) {
        if (!node)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

    Node *getroot() const {
        return root;
    }

    int height(Node *node) const {
        if (!node)
            return 0;

        return max(height(node->left), height(node->right)) + 1;
    }
    int height_node(Node *root, const T &val) const {
        if (!root)
            return -1;

        if (root->val == val)
            return height(root);

        int left = height_node(root->left, val);

        if (left != -1)
            return left;

        return height_node(root->right, val);
    }

    int leaf(Node *root) const {
        if (!root)
            return 0;
        if (!root->left && !root->right)
            return 1;
        return leaf(root->left) + leaf(root->right);
    }

    int max_node(Node *root) {
        if (!root)
            return 0;
        if (!root->left && !root->right) {
            return root->data;
        }
        return max_node(root->right);
    }

    int min_node(Node *root) {
        if (!root)
            return 0;
        if (!root->left && !root->right) {
            return root->data;
        }
        return min_node(root->left);
    }

    Node *remove(Node *node, const T &v) {
        if (!node)
            return nullptr;

        if (v < node->data) {
            node->left = remove(node->left, v);
        } else if (v > node->data) {
            node->right = remove(node->right, v);
        } else {

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

        return node;
    }

    void min_dist(Node *&node, Node *&prev = nullptr, int &res = INT_MAX) {
        if (!node)
            return;
        min_dist(node->left, prev, res);
        if (prev) {
            res = min(res, abs(node->data - prev->data));
        }
        prev = node;
        min_dist(node->right, prev, res);
    }

    void small_sumk(Node *root, int &k, int &res = 0) {
        if (!root)
            return;
        small_sumk(root->left, k, res);
        if (k > 0) {
            res += root->data;
            k--;
        }
        small_sumk(root->right, k, res);
    }
    void k_largest(Node *root, int &k, int &res) {
        if (!root)
            return;
        k_largest(root->right, k, res);
        if (k > 0) {
            res = root->data;
            k--;
        }
        k_largest(root->left, k, res);
    }
    template <class Iter> Node *build_pre(Iter &it, Iter end, T mn, T mx) {
        if (it == end)
            return nullptr;
        if (*it <= mn || *it >= mx)
            return nullptr;
        Node *node = new Node(*it);
        ++it;
        node->left = build_pre(it, end, mn, *it);
        node->right = build_pre(it, end, *it, mx);
        return node;
    }

    template <class Iter> Node *build_preorder(Iter &it, Iter end, T mn, T mx) {
        if (it == end)
            return nullptr;

        if (*it <= mn || *it >= mx)
            return nullptr;

        Node *node = new Node(*it);
        ++it;

        node->left = build_preorder(it, end, mn, node->data);
        node->right = build_preorder(it, end, node->data, mx);

        return node;
    }

    int depth(Node *node, const T &v, int res = 0) {
        if (!node)
            return 0;
        if (node->data == v) {
            return res;
        }
        if (v <= node->data) {
            return depth(node->left, v, res + 1);
        } else {
            return depth(node->right, v, res + 1);
        }
    }

    T k_anc(Node *node, const T &tar, int &k, T &res) {
        if (k == 0)
            return tar;
        if (!node)
            return T();

        if (node->data == tar)
            return tar;

        T found = T();

        if (tar < node->data)
            found = k_anc(node->left, tar, k, res);
        else
            found = k_anc(node->right, tar, k, res);

        if (found == tar) {
            --k;
            if (k == 0)
                return node->data;
        }

        return found;
    }

    T LCA(Node *node, T n1, T n2) {
        if (n1 == n2)
            return n1;
        if (n1 < node->data && n2 < node->data) {
            return LCA(node->left, n1, n2);
        } else if (n1 > node->data && n2 > node->data) {
            return LCA(node->right, n1, n2);
        } else {
            return node->data;
        }
    }

    void range(Node *node, const T &l, const T &r) {
        if (!node)
            return;
        if (l < node->data && r < node->data) {
            range(node->left, l, r);
        } else if (l > node->data && l > node->data) {
            range(node->right, l, r);
        } else if (l <= node->data && r >= node->data) {
            bool first = 1;
            inorder(node, first);
        }
    }

    bool dead_node(Node *node, T lower, T upper) {
        if (!node)
            return 0;
        if (!node->left && !node->right) {
            if (abs(lower - node->data) == 1 && abs(upper - node->data) == 1) {
                return 1;
            } else {
                return 0;
            }
        }
        return dead_node(node->left, lower, node->data) ||
               dead_node(node->right, node->data, upper);
    }

    void merge_pri(const BST &tree) {
        if (!tree.root || !root)
            return;
        stack<Node *> s;
        vector<T> vec1;
        vector<T> vec2;
        vec1.reserve(this->len);
        vec2.reserve(this->len);
        Node *curr = root;
        s.push(curr);
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            vec1.push_back(curr->data);
            curr = curr->right;
        }
        curr = tree.root;

        while (!s.empty()) {
            s.pop();
        }
        s.push(curr);
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            vec2.push_back(curr->data);
            curr = curr->right;
        }
        int i = 0;
        int j = 0;
        while (i < this->len && j < this->len) {
            if (vec1[i] < vec2[j]) {
                cout << vec1[i] << " ";
                ++i;
            } else if (vec1[i] > vec2[j]) {
                cout << vec2[j] << " ";
                ++j;
            } else {
                cout << vec1[i] << " " << vec2[j];
                ++i;
                ++j;
            }
        }
    }

  public:
    BST() : root(nullptr), len(0) {
    }

    BST(initializer_list<T> list) : root(nullptr), len(0) {
        for (const T &v : list)
            insert(v);
    }

    template <class Container> BST(const Container &c) : root(nullptr), len(0) {
        for (const T &v : c)
            insert(v);
    }

    template <class Cont, class Iter> BST(const Cont &c) {
        if (c.size() != 0) {
            Iter b = c.begin();
            root = build_pre(b, c.end(), numeric_limits<T>::lowest(),
                             numeric_limits<T>::max());
            len = c.size();
        }
    }

    BST(const BST &tree) : root(nullptr), len(0) {
        if (!tree.empty()) {
            queue<Node *> q;
            q.push(tree.root);
            while (!q.empty()) {
                for (int i = 0; i < q.size(); ++i) {
                    Node *curr = q.front();
                    q.pop();
                    insert(curr->data);
                    if (curr->left)
                        q.push(curr->left);
                    if (curr->right)
                        q.push(curr->right);
                }
            }
        }
    }

    BST(BST &&other) noexcept : root(other.root), len(other.len) {
        other.len = 0;
        other.root = nullptr;
    }

    BST &operator=(const BST<T> &other) {
        if (this != &other) {
            if (!other.empty()) {
                queue<Node *> q;
                q.push(other.getroot());
                while (!q.empty()) {
                    for (int i = 0; i < q.size(); ++i) {
                        Node *curr = q.front();
                        q.pop();
                        insert(curr->data);
                        if (curr->left)
                            q.push(curr->left);
                        if (curr->right)
                            q.push(curr->right);
                    }
                }
            }
        }
        return *this;
    }

    BST &operator=(BST &&other) noexcept {
        if (this != &other) {
            this->root = other.root;
            len = other.len;
            other.root = nullptr;
            other.len = 0;
        }
        return *this;
    }

    void insert(const T &v) {
        insert(root, v);
    }

    bool search(const T &v) const {
        return search(root, v);
    }

    void inorder() const {
        bool first = true;
        inorder(root, first);
        cout << '\n';
    }

    void preorder() const {
        bool first = true;
        preorder(root, first);
        cout << '\n';
    }

    void postorder() const {
        bool first = true;
        postorder(root, first);
        cout << '\n';
    }

    void levelorder() const {
        bool first = true;
        levelorder(root, first);
        cout << '\n';
    }

    bool empty() const {
        return root == nullptr;
    }

    ~BST() {
        clear(root);
    }

    int height() const {
        return height(root);
    }
    int height_node(const T &v) const {
        return height_node(root, v);
    }

    int leaf() const {
        return leaf(root);
    }

    int min_node() {
        return min_node(root);
    }

    int max_node() {
        return max_node(root);
    }

    void remove(const T &v) {
        root = remove(root, v);
    }

    void min_dist() {
        Node *pre = nullptr;
        int res = INT_MAX;
        min_dist(root, pre, res);
        cout << res;
    }

    void small_sumk(int &k) {
        int res = 0;
        small_sumk(root, k, res);
        cout << res << " ";
    }

    void k_largest(int &k) const {
        int res = 0;
        k_largest(root, k, res);
        cout << res << " ";
    }

    int depth(const T &v) {
        return depth(root, v);
    }

    void k_anc(const T &v, int &k) {
        T res = T();
        cout << k_anc(root, v, k, res);
    }

    T LCA(const T &n1, const T &n2) {
        return LCA(root, n1, n2);
    }

    void range(const T &n1, const T &n2) {
        range(root, n1, n2);
    }

    bool dead_node() {

        return dead_node(root, 0, INT_MAX);
    }

    void merge(const BST &tree) {
        merge_pri(tree);
    }
};

#endif