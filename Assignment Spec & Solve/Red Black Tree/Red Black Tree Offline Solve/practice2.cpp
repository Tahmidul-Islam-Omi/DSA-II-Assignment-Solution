#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("input.txt"); // Replace "your_filename.txt" with your actual file name

    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    string line;

    while (std::getline(inputFile, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            cout << word << " ";
        }

        cout << endl;
    }

    inputFile.close(); // Close the file after reading

    return 0;
}
