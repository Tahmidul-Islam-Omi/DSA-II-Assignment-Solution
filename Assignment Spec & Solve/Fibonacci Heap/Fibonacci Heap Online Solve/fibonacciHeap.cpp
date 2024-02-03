#include <bits/stdc++.h>
using namespace std;

template <typename Key, typename Value>
class Node
{
public:
    Key key;
    Value value;
    Node *parent;
    Node *child;
    Node *left;
    Node *right;
    int degree;
    char marked;
    char C;

    Node()
    {
        parent = NULL;
        child = NULL;
        left = NULL;
        right = NULL;
        marked = 'W';
        C = 'N';
        degree = 0;
    }
};

template <typename Key, typename Value>
class FibonacciHeap
{
    int nodes;
    Node<Key, Value> *H;
    queue<Node<Key, Value> *> q;

public:
    int getNodeCount()
    {
        return nodes;
    }

    void MakeHeap()
    {
        Node<Key, Value> *node;
        node = NULL;
        H = node;
        nodes = 0;
    }

    void insert(Key key, Value value)
    {
        Node<Key, Value> *node = new Node<Key, Value>();
        node->key = key;
        node->value = value;

        node->degree = 0;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        node->child = NULL;
        node->marked = 'W';
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

    void Fibonnacci_link(Node<Key, Value> *ptr2, Node<Key, Value> *ptr1)
    {
        // Deletion ptr2 bcz it is added in ptr1
        (ptr2->left)->right = ptr2->right;
        (ptr2->right)->left = ptr2->left;

        // if only one node left

        if (ptr1->right == ptr1)
        {
            H = ptr1;
        }

        ptr2->left = ptr2;
        ptr2->right = ptr2;
        ptr2->parent = ptr1;

        if (ptr1->child == NULL)
        {
            ptr1->child = ptr2;
        }

        // linking child & ptr2
        ptr2->right = ptr1->child;
        ptr2->left = (ptr1->child)->left;
        ((ptr1->child)->left)->right = ptr2;
        (ptr1->child)->left = ptr2;

        // Update ptr1's child to be the maximum among its children

        if (ptr2->key > (ptr1->child)->key)
        {
            ptr1->child = ptr2;
        }

        ptr1->degree++;
    }

    void Consolidate()
    {
        int temp1;

        // maximum degree a node can have
        float temp2 = (log(nodes)) / (log(2));
        int temp3 = temp2;

        Node<Key, Value> *arr[temp3 + 1];

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
                // previous value saved
                ptr2 = arr[temp1];

                if (ptr1->key < ptr2->key)
                {
                    // swapping
                    ptr3 = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
                }

                if (ptr2 == H)
                {
                    H = ptr1;
                }

                Fibonnacci_link(ptr2, ptr1);

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
            }
        }
    }

    void Extract_max()
    {
        if (H == NULL)
        {
            cout << "Heap is empty" << endl;
        }

        else
        {
            Node<Key, Value> *temp = H;
            Node<Key, Value> *pntr = temp;

            Node<Key, Value> *x = NULL;

            if (temp->child != NULL)
            {

                // traversing to the root list

                x = temp->child;
                do
                {
                    // adding child into the root list
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

            // delete the max node
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            H = temp->right;

            // Heap is empty

            if (temp == temp->right && temp->child == NULL)
            {
                H = NULL;
            }

            // Heap is not empty, so consolidate
            else
            {
                H = temp->right;
                Consolidate();
            }

            nodes--;
        }
    }

    void Cut(Node<Key, Value> *IncreNode, Node<Key, Value> *Parent)
    {
        //If found is the only node in its child list
        if (IncreNode == IncreNode->right) {
            Parent->child = NULL;
        }
        
        // // Unlink found from its siblings
        (IncreNode->left)->right = IncreNode->right;
        (IncreNode->right)->left = IncreNode->left;

        // If found is the child of temp, update temp's child pointer
        if (IncreNode == Parent->child) {
            Parent->child = IncreNode->right;
        }

        Parent->degree = Parent->degree - 1;

        //  Make found a singleton circular list
        IncreNode->right = IncreNode;
        IncreNode->left = IncreNode;

        // // Insert found into the root list
        (H->left)->right = IncreNode;
        IncreNode->right = H;
        IncreNode->left = H->left;
        H->left = IncreNode;

        IncreNode->parent = NULL;

        IncreNode->marked = 'B';
    }

    // Recursive cascade cutting function
    void Cascase_cut(Node<Key, Value> *Parent)
    {
        Node<Key, Value> *ptr5 = Parent->parent;

        if (ptr5 != NULL)
        {
            // If temp is not marked, mark it as 'B' (black)
            if (Parent->marked == 'W')
            {
                Parent->marked = 'B';
            }
            else
            {
                 // If temp is marked, perform a cut and recursively perform cascading cut on its parent
                Cut(Parent, ptr5);
                Cascase_cut(ptr5);
            }
        }
    }

    void Increase_key(Value value, Key new_key)
    {
        if (H == NULL) {
            cout << "The Heap is Empty" << endl;
        }

        if (found == NULL) {
            cout << "Node not found in the Heap" << endl;
        }

        found->key = val;

        struct node *temp = found->parent;

        if (temp != NULL && found->key < temp->key)
        {
            Cut(found, temp);
            Cascase_cut(temp);
        }

        if (found->key < mini->key) {
            mini = found;
        }
    }

    void displayHelper()
    {
        while (!q.empty())
        {
            cout << "Hi" << endl;

            Node<Key, Value> *temp = q.front();
            q.pop();

            cout << "(" << temp->key << "," << temp->value << ")";

            Node<Key, Value> *childList = temp->child;

            if (childList != NULL)
            {
                cout << " -> ";
            }

            while (childList != NULL)
            {
                cout << "(" << childList->key << "," << childList->value << ")"
                     << " , ";

                if (childList->child != NULL)
                {
                    q.push(childList);
                }

                childList = childList->right;
            }

            cout << endl;
        }
    }

    void display()
    {
        Node<Key, Value> *node = H;

        if (node == NULL)
        {
            cout << "Heap is Empty!" << endl;
            return;
        }

        int treeNum = 1;

        cout << node->key << "," << node->value << endl;
        cout << node->child->key << "," << node->child->value << endl;

        // do
        // {
        //     cout << "Tree " << treeNum << ": ";
        //     q.push(node);
        //     displayHelper();
        //     node = node->right;
        //     treeNum++;
        // } while (node != H && node->right != NULL);
    }

    void DDisplay()
    {
        Node<Key, Value> *ptr = H;
        if (ptr == NULL)
            cout << "The Heap is Empty" << endl;

        else
        {
            cout << "The root nodes of Heap are: " << endl;
            do
            {
                cout << ptr->key;
                q.push(ptr);
                ptr = ptr->right;
                if (ptr != H)
                {
                    cout << "-->";
                }
            } while (ptr != H && ptr->right != NULL);
            cout << endl
                 << "The heap has " << nodes << " nodes" << endl
                 << endl;
        }
    }
};

int main()
{
    FibonacciHeap<int, int> FH;
    FH.MakeHeap();
    FH.insert(23, 12);
    FH.insert(17, 1);
    FH.insert(10, 90);

    FH.Extract_max();

    FH.display();
}


template <typename Key, typename Value>
void traverseFibonacciHeap(Node<Key, Value>* node) {
    if (node == nullptr) {
        return;
    }

    Node<Key, Value>* start = node;
    Node<Key, Value>* current = start;

    do {
        // Process the current node
        processNode(current);

        // Recursively traverse the child list of the current node
        traverseFibonacciHeap(current->child);

        // Move to the next node in the root list
        current = current->right;

    } while (current != start);
}

template <typename Key, typename Value>
void processNode(Node<Key, Value>* node) {
    // Perform any processing or print information about the node
    // For example: cout << "(" << node->key << "," << node->value << ") ";
}
