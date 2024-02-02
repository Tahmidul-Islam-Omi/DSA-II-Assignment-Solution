#include <bits/stdc++.h>
using namespace std;

template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    Node *parent;
    Node *child;
    Node *prev;
    Node *next;
    int degree;
    bool marked;
    bool C;
};

template <typename Key, typename Value>
class FibonacciHeap
{
    int nodes;
    Node<Key, Value> *H;

public:
    Node<Key, Value> *insert(Key key, Value value);
    Node<Key, Value> *MakeHeap();
    Node<Key, Value> *meld(Node<Key, Value> *H1 , Node<Key, Value> *H2);
    Node<Key, Value> *ExtractMax (Node<Key, Value> *H1);
    void Consolidate(Node<Key, Value> *H1);

};

template <typename Key, typename Value>
Node<Key, Value> *FibonacciHeap<Key, Value>::MakeHeap()
{
    Node<Key, Value>* node;
    node = NULL;
    return node;
}

template <typename Key, typename Value>
Node<Key, Value> *FibonacciHeap<Key, Value>::insert(Key key, Value value)
{
    Node<Key, Value> *node = new Node;
    node->key = key;
    node->value = value;

    node->degree = 0;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->child = NULL;
    node->mark = false;
    node->C = false;

    if (H != NULL)
    {
        (H->left)->right = x;
        node->right = H;
        node->left = H->left;
        H->left = node;

        if (node->key > H->key) {
            H = node;
        }
    }

    else {
        H = node;
    }

    nodes++;
    return H;
}

template <typename Key, typename Value>
Node<Key, Value> *FibonacciHeap<Key, Value>::meld(Node<Key, Value> *H1, Node<Key, Value> *H2)
{
    Node<Key, Value> * node;
    H = H1;

    // merging root lists
    (H->left)->right = H2;
    (H2->left)->right = H;

    // updating pointers of node
    node = H->left;
    H->left = H2->left;
    H2->left = node;

    return H;
}


template <typename Key, typename Value>
Node<Key, Value> *FibonacciHeap<Key, Value>::ExtractMax(Node<Key, Value> *H1) {
    Node<Key, Value> *p;
    Node<Key, Value> *ptr;
    Node<Key, Value> *node = H1;

    p = node;
    ptr = node;

    // Heap is Empty, so
    if (node == NULL) {
        return node;
    }

    Node<Key, Value> *child = NULL;
    Node<Key, Value> *np;


    if (node->child != NULL) {
        child = node->child;
    }

    // traversing in the child list
    if (child != NULL)
    {
        ptr = child;
        np = child->right;

        while (np != ptr) {
            // add to the root list
            (H1->left)->right = child;
            child->right = H1;
            child->left = H1->left;
            H1->left = child;

            // if found , then updated
            if (child->key > H1->key) {
                H1 = child;
            }

            child->parent = NULL;
            child = np;

        }
    }

    // delete the minimum node
    (node->left)->right = node->right;
    (node->right)->left = node->left;
    H1 = node->right;

    // Heap is empty
    if (node == node->right && node->child == NULL) {
        H = NULL;
    }

    // Heap is not empty, so consolidate
    else
    {
        H1 = node->right;
        Consolidate(H1);
    }

    nodes--;
    return p;
}


