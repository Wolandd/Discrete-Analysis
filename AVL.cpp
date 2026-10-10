#include <iostream>
#include <algorithm>

struct Node {
    int key;
    int height;

    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

int height(Node* v) {
    if (v == nullptr) {
        return 0;
    }
    return v->height;
}

void updateHeight(Node* v) {
    if (v == nullptr) {
        return;
    }
    v->height = 1 + std::max(height(v->left), height(v->right));
}

int getBalance(Node* v) {
    if (v == nullptr) {
        return 0;
    }
    return height(v->left) - height(v->right);
}

Node* rotateRight(Node* p) {
    Node* x = p->left;
    Node* B = x->right;

    x->right = p;
    p->left = B;

    updateHeight(p);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* p) {
    Node* x = p->right;
    Node* B = x->left;

    x->left = p;
    p->right = B;

    updateHeight(p);
    updateHeight(x);

    return x;
}

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    
    if (root->key > key) {
        root->left = insert(root->left, key);
    }
    else if (root->key < key) {
        root->right = insert(root->right, key);
    }
    else {
        return root; //одинаковые не вставляем
    }
    
    updateHeight(root);
    int balance = getBalance(root);

    if (balance == 2) {
        if (key < root->left->key) {
            return rotateRight(root);
        }
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance == -2) {
        if (key > root->right->key) {
            return rotateLeft(root);
        }
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

Node* minNode(Node* root) {
    if (root->left != nullptr) {
        root = minNode(root->left);
    }
    return root;
}

Node* remove(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = remove(root->left, key);
    }
    else if (key > root->key) {
        root->right = remove(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        Node* successor = minNode(root->right);
        root->key = successor->key;

        root->right = remove(root->right, successor->key);
    }
    
    if (root == nullptr) {
        return root;
    }

    updateHeight(root);
    int balance = getBalance(root);

    if (balance == 2 && getBalance(root->left) == 0) {
        return rotateLeft(root);
    }
    else if (balance == -2 && getBalance(root->right) == 0) {
        return rotateRight(root);
    }
    else if (balance == 2 && getBalance(root->left) == 1) {
        root = rotateRight(root);
    }
    else if (balance == 2 && getBalance(root->left) == -1) {
        root->left = rotateLeft(root->left);
        root = rotateRight(root);
    }
    else if (balance == -2 && getBalance(root->right) == -1) {
        root = rotateLeft(root);
    }
    else if (balance == -2 && getBalance(root->right) == 1) {
        root->right = rotateRight(root->right);
        root = rotateLeft(root);
    }
    return root;
}

int main()
{
    //AVL
}
