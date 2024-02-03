#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int value;
    Node *Child;
    Node *right;

    Node(int value)
    {
        this->value = value;
        Child = NULL;
        right = NULL;
    }
};

queue<Node *> q;

void displayHelper(Node *root)
{

    while (!q.empty())
    {

        Node* temp = q.front();
        q.pop();

        cout << temp->value ;

        Node *childList = temp->Child;

        if(childList != NULL) {
            cout << " -> ";
        }

        while (childList != NULL)
        {
            cout << childList->value << ",";

            if (childList->Child != NULL)
            {
                q.push(childList);
            }

            childList = childList->right;
        }

        cout << endl;
    }
}

int main()
{

    // Heap
    //     45----------23--------12
    //    /  \        /  \
    //   10   7      4    9
    //  /  \
    // 3    5

    Node *root = new Node(45);

    Node *node1 = new Node(23);
    Node *node2 = new Node(12);

    root->right = node1;
    node1->right = node2;

    Node *child1 = new Node(10);
    child1->right = new Node(7);

    root->Child = child1;

    Node *node3 = new Node(3);
    Node *node4 = new Node(5);
    node3->right = node4;

    child1->Child = node3;

    Node *node5 = new Node(4);
    Node *node6 = new Node(9);
    node5->right = node6;

    node1->Child = node5;
    
    Node *temp = root;

    int treeNum = 1;

    while (temp != NULL)
    {
        cout << "Tree " << treeNum << ": ";
        q.push(temp);
        displayHelper(temp);
        temp = temp->right;
        treeNum++;
    }
}