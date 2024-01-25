#include <iostream>
#include <vector>
using namespace std;

// Structure of a Binary Tree Node
struct Node {
    int data;
    struct Node* left, *right;
    Node(int v)
    {
        data = v;
        left = right = NULL;
    }
};

// Function to print tree structure in the format "parent(child1, child2)"
void printTreeStructure(struct Node* node)
{
    if (node == NULL)
        return;

    cout << node->data;

    if (node->left || node->right) {
        cout << "(";
        if (node->left)
            printTreeStructure(node->left);
        if(node->left == NULL) {
            cout << " ";
        }
        cout << ",";
        if (node->right)
            printTreeStructure(node->right);

        if(node->right == NULL) {
            cout << " ";
        }
        cout << ")";
    }
}

// Driver code
int main()
{
    struct Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    // Function call
    cout << "Tree structure in the format: ";
    printTreeStructure(root);
    cout << endl;

    return 0;
}
 