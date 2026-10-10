#include <iostream>

enum Color {
    R, B
};

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* par; //parent
};

Node* NIL;

void initNIL() {
    NIL = new Node;
    NIL->color = B;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->par = NIL;
}
Node* createNode(Node* par, int key) {
    Node* x = new Node;
    x->key = key;
    x->color = R;
    x->left = NIL;
    x->right = NIL;
    x->par = par;
    return x;
}
 
void rightRotate(Node*& root, Node* p);
void leftRotate(Node*& root, Node* p);

void fixupInsert(Node* x) {
    if (x->par == NIL) { //root
        x->color = B;
        return;
    }
    else if (x->par->color == B) {
        return;
    }
    
    Node* p = x->par;
    Node* g = p->par;
    
    if (g->left == p) {
        Node* u = g->right;
        if (u->color == R) {
            u->color = B;
            p->color = B;
            g->color = R;
            fixupInsert(g);
        }
        else {
            if (p->left == x) { //LL
                p->color = B;
                g->color = R;
                rightRotate(g);
            }
            else { //LR
                leftRotate(p);
                p->color = B;
                g->color = R;
                rightRotate(g);
            }
        }
    }
    else {
        Node* u = g->left;
        if (u->color == R) {
            u->color = B;
            p->color = B;
            g->color = R;
            fixupInsert(g);
        }
        else {
            if (p->right == x) { //RR
                p->color = B;
                g->color = R;
                leftRotate(g);
            }
            else { //RL
                rightRotate(p);
                p->color = B;
                g->color = R;
                leftRotate(g);
            }
        }
    }
}

Node* insert(Node* root, int key) {
    if (root == NIL) {
        root = createNode(NIL, key);
        root->color = B;
        return root;
    }
    if (key < root->key) {
        if (root->left == NIL) {
            root->left = createNode(root, key);
            if (root->color == R) {
                fixupInsert(root->left);
            }
        }
        else {
            root->left = insert(root->left, key);
        }

    }
    else if (key > root->key) {
        if (root->right == NIL) {
            root->right = createNode(root, key);
            if (root->color == R) {
                fixupInsert(root->right);
            }
        }
        else {
            root->right = insert(root->right, key);
        }
    }
    else {
        return root; //без одинаковых
    }

    return root;
}

Node* search(Node* root, int key);

void transplant(Node*& root, Node* u, Node* v) {
    if (u->par == NIL) {
        root = v;
        v->par = NIL;
        return;
    }
    else if (u->par->left == u) {
        u->par->left = v;
    }
    else {
        u->par->right = v;
    }
    v->par = u->par;
}

Node* findMinimum(Node* v) {
    while (v->left != NIL) {
        v = v->left;
    }
    return v;
}

void deleteFixup(Node*& root, Node* x) { 
    while (x != root && x->color == B) {
        Node* p = x->par;
        if (p->left == x) {
            Node* w = p->right; // w != NIL условие нужно добавить
            if (w->color == R) {
                p->color = R;
                w->color = B;
                leftRotate(root, p);
                w = x->par->right;
            }
            
            if (w->left->color == B && w->right->color == B) {
                w->color = R;
                x = p;
            }
            else {
                if (w->right->color == B) { //Neer->color == R
                    w->color = R;
                    w->left->color = B;
                    rightRotate(root, w);
                    w = x->par->right;
                }
                w->color = p->color;
                p->color = B;
                w->right->color = B;
                leftRotate(root, p);
                x = root;
            }
        }
        else {
            //симметрично
        }
    }
    x->color = B;
}

void remove(Node*& root, int key) {
    Node* z = search(root, key);
    if (z == NIL) {
        return;
    }

    Node* x;
    Color deleteColor = z->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else { 
        Node* successor = findMinimum(z->right);
        z->key = successor->key;
        deleteColor = successor->color;

        x = successor->right;
        transplant(root, successor, x);
        z = successor;
        
    }
    delete z;
    if (deleteColor == B) {
        deleteFixup(root, x);
    }
}


int main()
{
    //RBT
    initNIL();
    Node* root = new Node;
    root = NIL;
}
