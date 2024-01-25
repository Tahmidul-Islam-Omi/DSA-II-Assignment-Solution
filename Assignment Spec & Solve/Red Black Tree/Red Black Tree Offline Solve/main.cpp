#include "map.cpp"
#include<bits/stdc++.h>
using namespace std;

int main()
{

    MAP<int, string> mp;

    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    string line;

    int i=1;

    while (getline(inputFile, line)) {
        cout << "Cmd " << i << ": "  ;
        i++;
        istringstream iss(line);
        string command;
        iss >> command;

        if(command == "Clr") {
            if(mp.empty()) {
                cout << "unsuccessful" << endl;
            }

            else {
                cout << "successful" << endl;
                MAP<int, string> mp;
            }
        }

        if( command == "Em" ) {
            if(mp.empty()) {
                cout << "yes" << endl;
            }

            else {
                cout << "no" << endl;
            }
        }

        if(command == "S") {
            cout << mp.sizeofTree() << endl;
        }

        if(command == "Itr") {
            mp.inorderTraversal();
        }

        if(command == "F") {

            // Input Error

            int key ;
            //string value;
            //iss >> key >> value;
            iss >> key;


            if (mp.found(key)) {
                cout << key << " " << "found" << endl;
            }

            else {
                cout << key << " " << "not found" << endl;
            }

        }

        if(command == "I") {
            int key ;
            string value;
            iss >> key >> value;
            mp.insert(key, value);
            mp.printTree();
            cout << endl;
        }

        if(command == "E") {
            int key;
            iss >> key;
            cout << endl;
        }

    }

    inputFile.close();

    return 0;
}