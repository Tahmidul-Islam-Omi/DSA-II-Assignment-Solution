#include <bits/stdc++.h>

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
};

template <typename Key, typename Value>

class MAP
{
private:
    Node<Key, Value> *Root;

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
            root->right->color = 'R';
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
                    root->color = 'R';
                    root->parent->left->color = 'R';

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
                    root->color = 'R';
                    root->parent->right->color = 'R';

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

    void inorderTraversalHelper(Node<Key, Value> *node)
    {
        if (node != NULL)
        {
            inorderTraversalHelper(node->left);
            cout << node->key << " => " << node->value << endl;
            inorderTraversalHelper(node->right);
        }
    }

public:
    MAP()
    {
        Root = NULL;
        lr = false;
        rr = false;
        lrr = false;
        rlr = false;
    }

    void insert(Key key, Value value)
    {

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

    void inorderTraversal()
    {
        inorderTraversalHelper(Root);
    }
};

