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
    unordered_map<Value, Node<Key, Value> *> mp;

public:
    int getNodeCount()
    {
        return nodes;
    }

    Node<Key, Value> *getH()
    {
        return H;
    }

    Node<Key, Value> *HeapInitialization()
    {
        Node<Key, Value> *node;
        node = NULL;
        H = node;
        nodes = 0;

        return H;
    }

    void insertion(Key key, Value value)
    {
        Node<Key, Value> *node = new Node<Key, Value>();
        node->key = key;
        node->value = value;

        mp[value] = node;

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

    void meld(FibonacciHeap<Key, Value> H1, int cnt)
    {

        if (H != NULL)
        {
            (H->left)->right = H1;
            H1->right = H;
            H1->left = H->left;
            H->left = H1;

            if (H1->key > H->key)
            {
                H = H1;
            }
        }

        else
        {
            H = H1;
        }
        nodes += cnt;
    }

    // void Fibonnacci_link(Node<Key, Value> *node2, Node<Key, Value> *node1)
    // {
    //     // Deletion node2 bcz it is added in node1
    //     (node2->left)->right = node2->right;
    //     (node2->right)->left = node2->left;

    //     // if only one node left

    //     if (node1->right == node1)
    //     {
    //         H = node1;
    //     }

    //     node2->left = node2;
    //     node2->right = node2;
    //     node2->parent = node1;

    //     if (node1->child == NULL)
    //     {
    //         node1->child = node2;
    //     }

    //     // linking child & node2
    //     node2->right = node1->child;
    //     node2->left = (node1->child)->left;
    //     ((node1->child)->left)->right = node2;
    //     (node1->child)->left = node2;

    //     // Update node1's child to be the maximum among its children

    //     if (node2->key > (node1->child)->key)
    //     {
    //         node1->child = node2;
    //     }

    //     node1->degree++;
    // }

    void Fibonnacci_link(Node<Key, Value> *node2, Node<Key, Value> *node1)
    {
        // Deletion node2 bcz it is added in node1
        (node2->left)->right = node2->right;
        (node2->right)->left = node2->left;

        // if only one node left

        if (node1->right == node1)
        {
            H = node1;
        }

        node2->left = node2;
        node2->right = node2;
        node2->parent = node1;

        if (node1->child == NULL)
        {
            node1->child = node2;
        }

        // linking child & node2
        node2->right = node1->child;
        node2->left = (node1->child)->left;
        ((node1->child)->left)->right = node2;
        (node1->child)->left = node2;

        // Update node1's child to be the maximum among its children

        if (node2->key > (node1->child)->key)
        {
            node1->child = node2;
        }

        node1->degree++;
    }

    // void Consolidate()
    // {
    //     int temp1;

    //     // maximum degree a node can have
    //     float temp2 = (log(nodes)) / (log(2));
    //     int temp3 = temp2;

    //     Node<Key, Value> *arr[temp3 + 1];

    //     for (int i = 0; i <= temp3; i++)
    //     {
    //         arr[i] = NULL;
    //     }

    //     Node<Key, Value> *node1 = H;
    //     Node<Key, Value> *node2;
    //     Node<Key, Value> *node3;

    //     Node<Key, Value> *node4 = node1;
    //     do
    //     {
    //         node4 = node4->right;
    //         temp1 = node1->degree;

    //         while (arr[temp1] != NULL)
    //         {
    //             // previous value saved
    //             node2 = arr[temp1];

    //             if (node1->key < node2->key)
    //             {
    //                 // swapping
    //                 node3 = node1;
    //                 node1 = node2;
    //                 node2 = node3;
    //             }

    //             if (node2 == H)
    //             {
    //                 H = node1;
    //             }

    //             Fibonnacci_link(node2, node1);

    //             arr[temp1] = NULL;
    //             temp1++;
    //         }

    //         arr[temp1] = node1;
    //         node1 = node1->right;

    //     } while (node1 != H);

    //     H = NULL;

    //     for (int j = 0; j <= temp3; j++)
    //     {
    //         if (arr[j] != NULL)
    //         {
    //             if (H != NULL)
    //             {
    //                 (H->left)->right = arr[j];
    //                 arr[j]->right = H;
    //                 arr[j]->left = H->left;
    //                 H->left = arr[j];
    //                 if (arr[j]->key > H->key)
    //                 {
    //                     H = arr[j];
    //                 }
    //             }

    //             else
    //             {
    //                 H = arr[j];
    //             }
    //         }
    //     }
    // }

    void Consolidate()
    {
        int temp1;

        // maximum degree a node can contain
        float temp2 = (log(nodes)) / (log(2));
        int temp3 = temp2;

        Node<Key, Value> *arr[temp3 + 1];

        for (int i = 0; i <= temp3; i++)
        {
            arr[i] = NULL;
        }

        Node<Key, Value> *node1 = H;
        Node<Key, Value> *node2;
        Node<Key, Value> *node3;

        Node<Key, Value> *node4 = node1;
        do
        {
            node4 = node4->right;
            temp1 = node1->degree;

            while (arr[temp1] != NULL)
            {
                // previous value saved
                node2 = arr[temp1];

                if (node1->key < node2->key)
                {
                    // swapping
                    node3 = node1;
                    node1 = node2;
                    node2 = node3;
                }

                if (node2 == H)
                {
                    H = node1;
                }

                Fibonnacci_link(node2, node1);

                arr[temp1] = NULL;
                temp1++;
            }

            arr[temp1] = node1;
            node1 = node1->right;

        } while (node1 != H);

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
        // If found is the only node in its child list
        if (IncreNode == IncreNode->right)
        {
            Parent->child = NULL;
        }

        // // Unlink found from its siblings
        (IncreNode->left)->right = IncreNode->right;
        (IncreNode->right)->left = IncreNode->left;

        // If found is the child of temp, update temp's child pointer
        if (IncreNode == Parent->child)
        {
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
        Node<Key, Value> *node5 = Parent->parent;

        if (node5 != NULL)
        {
            // If temp is not marked, mark it as 'B' (black)
            if (Parent->marked == 'W')
            {
                Parent->marked = 'B';
            }
            else
            {
                // If temp is marked, perform a cut and recursively perform cascading cut on its parent
                Cut(Parent, node5);
                Cascase_cut(node5);
            }
        }
    }

    void Increase_key(Value value, Key new_key)
    {
        if (H == NULL)
        {
            cout << "The Heap is Empty" << endl;
            return;
        }

        if (mp[value] == NULL)
        {
            cout << "Value is not found" << endl;
            return;
        }

        Node<Key, Value> *found = mp[value];

        Node<Key, Value> *temp = found->parent;

        found->key = new_key;

        if (temp != NULL && found->key > temp->key)
        {
            Cut(found, temp);
            Cascase_cut(temp);
        }

        if (found->key > H->key)
        {
            H = found;
        }
    }

    void deletion(Value value)
    {
        if (H == NULL)
        {
            cout << "Heap is Empty" << endl;
        }

        else
        {

            Increase_key(value, 10000000);
            Extract_max();
        }
    }

    void displayHelper()
    {
        while (!q.empty())
        {

            Node<Key, Value> *temp = q.front();
            q.pop();

            cout << "(" << temp->key << "," << temp->value << ")";

            Node<Key, Value> *childList = temp->child;
            Node<Key, Value> *childtemp = childList;

            if (childList != NULL)
            {
                cout << " -> ";
            }

            if (childList != NULL)
            {

                do
                {
                    cout << "(" << childList->key << "," << childList->value << ")"
                         << " , ";

                    if (childList->child != NULL)
                    {
                        q.push(childList);
                    }

                    childList = childList->right;

                } while (childList != childtemp && childList->right != NULL);
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

        do
        {
            cout << "Tree " << treeNum << ": ";
            q.push(node);
            displayHelper();
            node = node->right;
            treeNum++;
        } while (node != H && node->right != NULL);
    }

    void DDisplay()
    {
        Node<Key, Value> *node = H;
        if (node == NULL)
            cout << "The Heap is Empty" << endl;

        else
        {
            cout << "The root nodes of Heap are: " << endl;
            do
            {
                cout << node->key;
                q.push(node);
                node = node->right;
                if (node != H)
                {
                    cout << "-->";
                }
            } while (node != H && node->right != NULL);
            cout << endl
                 << "The heap has " << nodes << " nodes" << endl
                 << endl;
        }
    }
};

// int main()
// {
//     FibonacciHeap<int, int> FH;
//     FH.HeapInitialization();

//     FH.insertion(23, 12);
//     FH.insertion(17, 1);
//     FH.insertion(10, 90);
//     FH.insertion(12, 99);

//     FH.Extract_max();

//     FH.insertion(19, 2);

//     FH.Extract_max();

//     FH.insertion(20, 11);
//     FH.insertion(21, 27);
//     FH.insertion(29, 3);

//     FH.Extract_max();

//     FH.display();

//     FH.DDisplay();
// }