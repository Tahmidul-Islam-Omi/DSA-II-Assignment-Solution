#include <bits/stdc++.h>
#include "color.hpp"

using namespace std;

template <typename Key, typename Value>

class Node
{

public:
    Key key;
    Value value;
    char color;
    Node *left;
    Node *right;
    Node *parent;

    Node(Key key, Value value)
    {
        this->key = key;
        this->value = value;
        this->color = 'R';
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }

    Node<Key, Value> * uncle()
    {

        if (parent == NULL or parent->parent == NULL)
            return NULL;

        if (parent->isOnLeft())
        {
            return parent->parent->right;
        }
        else
        {
            return parent->parent->left;
        }
    }

    bool isOnLeft()
    {
        return this == parent->left;
    }

    Node<Key, Value> * sibling()
    {
        if (parent == NULL)
        {
            return NULL;
        }

        if (isOnLeft())
        {
            return parent->right;
        }

        return parent->left;
    }

    void moveDown(Node<Key, Value> * nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild()
    {
        return (left != NULL and left->color == 'R') or
               (right != NULL and right->color == 'R');
    }
};

template <typename Key, typename Value>

class MAP
{
private:
    Node<Key, Value> *Root;
    int size;

    bool lr;  // left rotation
    bool rr;  // right rotation
    bool lrr; // left right rotation
    bool rlr; // right left rotation

    Node<Key, Value> *rotateLeft(Node<Key, Value> *node)
    {
        Node<Key, Value> *x = node->right;
        Node<Key, Value> *y = x->left;
        x->left = node;
        node->right = y;
        node->parent = x;

        if (y != NULL)
        {
            y->parent = node;
        }

        return x;
    }

    Node<Key, Value> *rotateRight(Node<Key, Value> *node)
    {
        Node<Key, Value> *x = node->left;
        Node<Key, Value> *y = x->right;
        x->right = node;
        node->left = y;
        node->parent = x;

        if (y != NULL)
        {
            y->parent = node;
        }

        return x;
    }

    Node<Key, Value> *insertHelper(Node<Key, Value> *root, Key key, Value value)
    {
        bool redConflict = false;

        if (root == NULL)
        {
            return new Node<Key, Value>(key, value);
        }

        else if (key < root->key)
        {
            root->left = insertHelper(root->left, key, value);
            root->left->parent = root;

            if (Root != root)
            {
                if (root->color == 'R' && root->left->color == 'R')
                {
                    redConflict = true;
                }
            }
        }

        else
        {
            root->right = insertHelper(root->right, key, value);
            root->right->parent = root;

            if (Root != root)
            {
                if (root->color == 'R' && root->right->color == 'R')
                {
                    redConflict = true;
                }
            }
        }

        if (lr == true)
        {
            root = rotateLeft(root);
            root->color = 'B';
            root->left->color = 'R';
            lr = false;
        }

        else if (rr == true)
        {
            root = rotateRight(root);
            root->color = 'B';
            root->right->color = 'R';
            rr = false;
        }

        else if (lrr == true)
        {
            root->left = rotateLeft(root->left);
            root->left->parent = root;
            root = rotateRight(root);
            root->color = 'B';
            root->right->color = 'R';
            lrr = false;
        }

        else if (rlr == true)
        {
            root->right = rotateRight(root->right);
            root->right->parent = root;
            root = rotateLeft(root);
            root->color = 'B';
            root->left->color = 'R';
            rlr = false;
        }

        if (redConflict == true)
        {

            if (root->parent->right == root)
            {
                // right case
                if (root->parent->left == NULL || root->parent->left->color == 'B')
                {
                    // rotation occurs
                    if (root->left != NULL && root->left->color == 'R')
                    {
                        // right-left case
                        rlr = true;
                    }

                    else if (root->right != NULL && root->right->color == 'R')
                    {
                        // right-right case
                        lr = true;
                    }
                }

                else
                {
                    root->color = 'B';
                    root->parent->left->color = 'B';

                    if (root->parent != Root)
                    {
                        root->parent->color = 'R';
                    }
                }
            }

            if (root->parent->left == root)
            {
                // left case

                if (root->parent->right == NULL || root->parent->right->color == 'B')
                {
                    // rotation occurs
                    if (root->right != NULL && root->right->color == 'R')
                    {
                        // left-right case
                        lrr = true;
                    }

                    else if (root->left != NULL && root->left->color == 'R')
                    {
                        // left-left case
                        rr = true;
                    }
                }

                else
                {
                    root->color = 'B';
                    root->parent->right->color = 'B';

                    if (root->parent != Root)
                    {
                        root->parent->color = 'R';
                    }
                }
            }

            redConflict = false;
        }

        return root;
    }

    void leftRotate(Node<Key, Value> *node)
    {
        Node<Key, Value> *nParent = node->right;

        if (node == Root)
            Root = nParent;

        node->moveDown(nParent);

        node->right = nParent->left;

        if (nParent->left != NULL)
            nParent->left->parent = node;

        nParent->left = node;
    }

    void rightRotate(Node<Key, Value> *node)
    {
        Node<Key, Value> *nParent = node->left;

        if (node == Root)
            Root = nParent;

        node->moveDown(nParent);

        node->left = nParent->right;

        if (nParent->right != NULL)
            nParent->right->parent = node;

        nParent->right = node;
    }

    bool found(Node<Key, Value> *node, Key key)
    {
        if (node != NULL)
        {

            if (node->key == key)
            {
                return true;
            }

            return found(node->left, key) || found(node->right, key);
        }

        return false;
    }

    void swapColors(Node<Key, Value> *node1, Node<Key, Value> *node2)
    {
        char temp;
        temp = node1->color;
        node1->color = node2->color;
        node2->color = temp;
    }

    void swapValues(Node<Key, Value> *u, Node<Key, Value> *v)
    {
        Key temp;
        Value temp1;

        temp = u->key;
        temp1 = u->value;

        u->key = v->key;
        u->value = v->value;

        v->key = temp;
        v->value = temp1;
    }

    void fixRedRed(Node<Key, Value> *node)
    {
        if (node == Root)
        {
            node->color = 'B';
            return;
        }

        Node<Key, Value> *parent = node->parent, *grandparent = parent->parent,
                         *uncle = node->uncle();

        if (parent->color != 'B')
        {
            if (uncle != NULL && uncle->color == 'R')
            {
                parent->color = 'B';
                uncle->color = 'B';
                grandparent->color = 'R';
                fixRedRed(grandparent);
            }
            else
            {
                if (parent->isOnLeft())
                {
                    if (node->isOnLeft())
                    {
                        swapColors(parent, grandparent);
                    }
                    else
                    {
                        leftRotate(parent);
                        swapColors(node, grandparent);
                    }
                    rightRotate(grandparent);
                }
                else
                {
                    if (node->isOnLeft())
                    {
                        rightRotate(parent);
                        swapColors(node, grandparent);
                    }
                    else
                    {
                        swapColors(parent, grandparent);
                    }

                    leftRotate(grandparent);
                }
            }
        }
    }

    Node<Key, Value> *successor(Node<Key, Value> *node)
    {
        Node<Key, Value> *temp = node;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    Node<Key, Value> *BSTreplace(Node<Key, Value> *node)
    {

        if (node->left != NULL and node->right != NULL)
            return successor(node->right);

        if (node->left == NULL and node->right == NULL)
            return NULL;

        if (node->left != NULL)
            return node->left;
        else
            return node->right;
    }

    void deleteNode(Node<Key, Value> *v)
    {
        Node<Key, Value> *u = BSTreplace(v);

        bool uvBlack = ((u == NULL or u->color == 'B') and (v->color == 'B'));
        Node<Key, Value> *parent = v->parent;

        if (u == NULL)
        {

            if (v == Root)
            {

                Root = NULL;
            }
            else
            {
                if (uvBlack)
                {
                    fixDoubleBlack(v);
                }
                else
                {
                    if (v->sibling() != NULL)
                        v->sibling()->color = 'R';
                }

                if (v->isOnLeft())
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left == NULL or v->right == NULL)
        {

            if (v == Root)
            {

                v->key = u->key;
                v->value = u->value;

                v->left = v->right = NULL;
                delete u;
            }
            else
            {

                if (v->isOnLeft())
                {
                    parent->left = u;
                }
                else
                {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack)
                {

                    fixDoubleBlack(u);
                }
                else
                {

                    u->color = 'B';
                }
            }
            return;
        }

        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node<Key, Value> *x)
    {
        if (x == Root)

            return;

        Node<Key, Value> *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL)
        {

            fixDoubleBlack(parent);
        }
        else
        {
            if (sibling->color == 'R')
            {

                parent->color = 'R';
                sibling->color = 'B';
                if (sibling->isOnLeft())
                {
                    // left case
                    rightRotate(parent);
                }
                else
                {
                    // right case
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else
            {

                if (sibling->hasRedChild())
                {

                    if (sibling->left != NULL and sibling->left->color == 'R')
                    {
                        if (sibling->isOnLeft())
                        {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            // right left
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())
                        {
                            // left right
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = 'B';
                }
                else
                {
                    // 2 black children
                    sibling->color = 'R';
                    if (parent->color == 'B')
                        fixDoubleBlack(parent);
                    else
                        parent->color = 'B';
                }
            }
        }
    }

    Node<Key, Value> *search(int n)
    {
        Node<Key, Value> *temp = Root;

        while (temp != NULL)
        {
            if (n < temp->key)
            {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->key)
            {
                break;
            }
            else
            {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    void clearHelper(Node<Key, Value> *node)
    {
        if (node == NULL)
        {
            return;
        }

        clearHelper(node->left);
        clearHelper(node->right);

        delete node;
    }

public:
    MAP()
    {
        Root = NULL;
        lr = false;
        rr = false;
        lrr = false;
        rlr = false;
        size = 0;
    }

    Node<Key, Value> *getRoot()
    {
        return Root;
    }

    void insert(Key key, Value value)
    {
        size++;

        if (Root == NULL)
        {
            Root = new Node<Key, Value>(key, value);
            Root->color = 'B';
        }

        else
        {
            Root = insertHelper(Root, key, value);
        }
    }

    bool found(Key key)
    {
        return found(Root, key);
    }

    bool empty()
    {
        return size == 0;
    }

    int sizeofTree()
    {
        return size;
    }

    void setSize(int size)
    {
        this->size = size;
    }

    int getSize()
    {
        return size;
    }

    bool deleteByVal(int n)
    {

        if (Root == NULL) {
            return false;
        }

        Node<Key, Value> *v = search(n);


        if (v->key != n)
        {
            return false;
        }

        size = size - 1;
        deleteNode(v);
        
        return true;
    }

    void clear()
    {
        clearHelper(Root);

        Root = NULL;
        size = 0;
    }
};