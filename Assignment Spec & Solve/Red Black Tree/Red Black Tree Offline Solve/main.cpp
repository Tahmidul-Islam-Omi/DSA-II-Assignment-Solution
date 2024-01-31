#include "map.cpp"
#include <bits/stdc++.h>
#include "color.hpp"
using namespace std;

template <typename Key, typename Value>

void printTree(Node<Key, Value> *node , ofstream& outputFile)
{
    if (node == NULL)
    {
        return;
    }

    if (node->color == 'R')
    {
        cout << hue::red << node->key << "_" << node->value << hue::reset;
        outputFile << node->key << "_" << node->value;
    }

    if (node->color == 'B')
    {
        cout << node->key << "_" << node->value;
        outputFile << node->key << "_" << node->value;
    }

    if (node->left || node->right)
    {
        cout << "(";
        outputFile << "(";

        if (node->left)
        {
            printTree(node->left , outputFile);
        }

        cout << ",";
        outputFile << ",";

        if (node->right)
        {
            printTree(node->right , outputFile);
        }

        cout << ")";
        outputFile << ")";
    }
}

template <typename Key, typename Value>

void inorderTraversal(Node<Key, Value> *node , ofstream& outputFile)
{
    if (node != NULL)
    {
        inorderTraversal(node->left , outputFile);

        if (node->color == 'R')
        {
            cout << hue::red << node->key << " ⇒ " << node->value << hue::reset << endl;
            outputFile << node->key << " ⇒ " << node->value << endl;
        }

        if (node->color == 'B')
        {
            cout << node->key << " ⇒ " << node->value << endl;
            outputFile << node->key << " ⇒ " << node->value << endl;
        }

        inorderTraversal(node->right , outputFile);
    }
}

int main()
{

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    if (!outputFile.is_open())
    {
        cerr << "Error opening the output file!" << endl;
        return 1;
    }

    MAP<int, string> mp;

    string line;

    int i = 1;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string command;
        iss >> command;

        outputFile << "Cmd " << i << ": " << command;
        i++;

        if (command == "Clr")
        {
            if (mp.empty())
            {
                cout << "unsuccessful" << endl;
                outputFile << endl;
                outputFile << "unsuccessful" << endl;
            }

            else
            {
                mp.clear();
                cout << "successful" << endl;

                outputFile << endl;
                outputFile << "successful" << endl;
            }
        }

        if (command == "Em")
        {
            if (mp.empty())
            {
                cout << "yes" << endl;
                outputFile << endl;
                outputFile << "yes" << endl;
            }

            else
            {
                cout << "no" << endl;
                outputFile << endl;
                outputFile << "no" << endl;
            }
        }

        if (command == "S")
        {
            cout << mp.sizeofTree() << endl;
            outputFile << endl;
            outputFile << mp.sizeofTree() << endl;
        }

        if (command == "Itr")
        {
            outputFile << endl;
            inorderTraversal(mp.getRoot() , outputFile);
        }

        if (command == "F")
        {

            int key;
        
            iss >> key;

            outputFile << " " << key << endl;

            if (mp.found(key))
            {
                cout << key << " "
                     << "found" << endl;
                outputFile << key << " "
                           << "found" << endl;
            }

            else
            {
                cout << key << " "
                     << "not found" << endl;
                outputFile << key << " "
                           << "not found" << endl;
            }

        }

        if (command == "I")
        {
            int key;
            string value;
            iss >> key >> value;
            outputFile << " " << key << " " << value << endl;

            mp.insert(key, value);
            printTree(mp.getRoot() , outputFile);
            cout << endl;
            outputFile << endl;
        }

        if (command == "E")
        {
            int key;
            iss >> key;
            outputFile << " " << key << endl;\

            if ( mp.deleteByVal(key) == true ) {
                printTree(mp.getRoot() , outputFile);
                outputFile << endl;
            }

            else {
                cout << key << " " << "not found" << endl;
                outputFile << key << " " << "not found" << endl;
            }

        }

        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}