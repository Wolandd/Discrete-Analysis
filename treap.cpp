#include <iostream>
#include <random>
#include <cstdint>

std::mt19937 rng(std::random_device{}());

struct Node {
    int key;
    int prior;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        prior = rng();
        left = nullptr;
        right = nullptr;
    }
};

Node* search(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key > root->key) {
        return search(root->right, key);
    }
    else if (key < root->key) {
        return search(root->left, key);
    }
    else { 
        return root; 
    }
}

void split(Node* t, int key, Node*& left, Node*& right) {
    if (t == nullptr) {
        left = right = nullptr;
        return;
    }

    if (key <= t->key) { //key -> right
        split(t->left, key, left, t->left);
        right = t;
    }
    else {
        split(t->right, key, t->right, right);
        left = t;
    }
}

Node* merge(Node* a, Node* b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }

    if (a->prior > b->prior) {
        a->right = merge(a->right, b);
        return a;
    }
    else {
        b->left = merge(a, b->left);
        return b;
    }
}

Node* insert(Node* root, int key) {
    Node* l;
    Node* r;
    Node* x = new Node(key);
    split(root, key, l, r);
    return merge(merge(l, x), r);
}

Node* remove(Node* root, int key) {
    Node *l, *r, *x;
    split(root, key, l, r);
    split(r, key + 1, x, r);
    delete x;
    return merge(l, r);
}

int main()
{
    
}
