#include <bits/stdc++.h>
using namespace std;

template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    Node *parent;
    Node *child;
    Node *left;
    Node *right;
    int degree;
    char marked;
    char C;
};

template <typename Key, typename Value>
class FibonacciHeap
{
    int nodes;
    Node<Key, Value> *H;

public:
    void insert(Key key, Value value);
    void MakeHeap();
    Node<Key, Value> *meld(Node<Key, Value> *H1, Node<Key, Value> *H2);
    void ExtractMax();
    void Consolidate(Node<Key, Value> *H1);
};

template <typename Key, typename Value>
void FibonacciHeap<Key, Value>::MakeHeap()
{
    Node<Key, Value> *node;
    node = NULL;
    H = node;
}

template <typename Key, typename Value>
void FibonacciHeap<Key, Value>::insert(Key key, Value value)
{
    Node<Key, Value> *node = new Node;
    node->key = key;
    node->value = value;

    node->degree = 0;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->child = NULL;
    node->mark = 'W';
    node->C = 'N';

    node->left = node;
    node->right = node;

    if (H != NULL)
    {
        (H->left)->right = node;
        node->right = H;
        node->left = H->left;
        H->left = node;

        if (node->key > H->key)
        {
            H = node;
        }
    }

    else
    {
        H = node;
    }

    nodes++;
}

template <typename Key, typename Value>
Node<Key, Value> *FibonacciHeap<Key, Value>::meld(Node<Key, Value> *H1, Node<Key, Value> *H2)
{
    Node<Key, Value> *node;
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

// template <typename Key, typename Value>
// Node<Key, Value> *FibonacciHeap<Key, Value>::ExtractMax(Node<Key, Value> *H1) {
//     Node<Key, Value> *p;
//     Node<Key, Value> *ptr;
//     Node<Key, Value> *node = H1;

//     p = node;
//     ptr = node;

//     // Heap is Empty, so
//     if (node == NULL) {
//         return node;
//     }

//     Node<Key, Value> *child = NULL;
//     Node<Key, Value> *np;

//     if (node->child != NULL) {
//         child = node->child;
//     }

//     // traversing in the child list
//     if (child != NULL)
//     {
//         ptr = child;
//         np = child->right;

//         while (np != ptr) {
//             // add to the root list
//             (H1->left)->right = child;
//             child->right = H1;
//             child->left = H1->left;
//             H1->left = child;

//             // if found , then updated
//             if (child->key > H1->key) {
//                 H1 = child;
//             }

//             child->parent = NULL;
//             child = np;

//         }
//     }

//     // delete the minimum node
//     (node->left)->right = node->right;
//     (node->right)->left = node->left;
//     H1 = node->right;

//     // Heap is empty
//     if (node == node->right && node->child == NULL) {
//         H = NULL;
//     }

//     // Heap is not empty, so consolidate
//     else
//     {
//         H1 = node->right;
//         Consolidate(H1);
//     }

//     nodes--;
//     return p;
// }

template <typename Key, typename Value>
void Consolidate()
{
    int temp1;
    float temp2 = (log(nodes)) / (log(2));
    int temp3 = temp2;

    struct Node<Key, Value> *arr[temp3 + 1];

    for (int i = 0; i <= temp3; i++)
    {
        arr[i] = NULL;
    }

    Node<Key, Value> *ptr1 = H;
    Node<Key, Value> *ptr2;
    Node<Key, Value> *ptr3;

    Node<Key, Value> *ptr4 = ptr1;
    do
    {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;

        while (arr[temp1] != NULL)
        {
            ptr2 = arr[temp1];

            if (ptr1->key > ptr2->key)
            {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }

            if (ptr2 == H)
            {
                H = ptr1;
            }

            Fibonnaci_link(ptr2, ptr1);

            if (ptr1->right == ptr1)
            {
                H = ptr1;
            }

            arr[temp1] = NULL;
            temp1++;
        }

        arr[temp1] = ptr1;
        ptr1 = ptr1->right;

    } while (ptr1 != H);

    H = NULL;

    for (int j = 0; j <= temp3; j++)
    {
        if (arr[j] != NULL)
        {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];

            if (H != NULL)
            {
                (H->left)->right = arr[j];
                arr[j]->right = H;
                arr[j]->left = H->left;
                H->left = arr[j];
                if (arr[j]->key > H->key)
                {
                    H = arr[j];
                }
            }

            else
            {
                H = arr[j];
            }

            if (H == NULL)
            {
                H = arr[j];
            }

            else if (arr[j]->key > H->key)
            {
                H = arr[j];
            }
        }
    }
}

template <typename Key, typename Value>
void Extract_max()
{
    if (H == NULL)
    {
        cout << "Heap is empty" << endl;
    }

    else
    {
        Node<Key, Value> *temp = H;
        node *pntr;
        pntr = temp;
        Node<Key, Value> *x = NULL;
        if (temp->child != NULL)
        {

            x = temp->child;
            do
            {
                pntr = x->right;
                (H->left)->right = x;
                x->right = H;
                x->left = H->left;
                H->left = x;

                if (x->key > H->key)
                {
                    H = x;
                }

                x->parent = NULL;
                x = pntr;

            } while (pntr != temp->child);
        }

        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        H = temp->right;

        if (temp == temp->right && temp->child == NULL)
        {
            H = NULL;
        }

        else
        {
            H = temp->right;
            Consolidate();
        }

        no_of_nodes--;
    }
}

template <typename Key, typename Value>
void Cut(struct Node<Key, Value> *found, struct Node<Key, Value> *temp)
{
    if (found == found->right) {
        temp->child = NULL;
    }

    (found->left)->right = found->right;
    (found->right)->left = found->left;

    if (found == temp->child) {
        temp->child = found->right;
    }

    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = 'B';
}

template <typename Key, typename Value>
void Cascase_cut(struct Node<Key, Value> *temp)
{
    Node<Key, Value> *ptr5 = temp->parent;

    if (ptr5 != NULL)
    {
        if (temp->mark == 'W')
        {
            temp->mark = 'B';
        }
        else
        {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}

int main()
{
    


    return 0;
}