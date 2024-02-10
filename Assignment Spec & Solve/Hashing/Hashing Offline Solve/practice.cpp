#include<bits/stdc++.h>
using namespace std;

unsigned int fnv1a(const char* data) {
    unsigned int hash = 2166136261; // FNV offset basis
    while (*data) {
        hash ^= *data++;
        hash *= 16777619; // FNV prime
    }
    return hash % 1000;
}

unsigned int djb2(const char* data) {
    unsigned int hash = 5381;
    int c;
    while ((c = *data++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % 1000;
}


int main() {
    cout << fnv1a("Omi") << endl;
    cout << fnv1a("Lubna") << endl;
    cout << fnv1a("Zarif") << endl;

    cout << djb2("Omi") << endl;
    cout << djb2("Lubna") << endl;
    cout << djb2("Zarif") << endl;
}

// #include <iostream>
// #include <list>

// // Define the size of the array of linked lists
// const int arraySize = 10;

// int main() {
//     // Declare an array of pointers to lists
//     std::list<int>* array[arraySize];

//     // Initialize each element of the array with a new linked list
//     for (int i = 0; i < arraySize; ++i) {
//         array[i] = new std::list<int>;
//     }

//     // Add some elements to the linked lists
//     array[0]->push_back(1);
//     array[0]->push_back(2);
//     array[1]->push_back(3);
//     array[2]->push_back(4);

//     // Access elements in the linked lists
//     std::cout << "Elements in array[0] linked list:" << std::endl;
//     for (int elem : *array[0]) {
//         std::cout << elem << " ";
//     }
//     std::cout << std::endl;

//     std::cout << "Elements in array[1] linked list:" << std::endl;
//     for (int elem : *array[1]) {
//         std::cout << elem << " ";
//     }
//     std::cout << std::endl;

//     // Don't forget to free memory
//     for (int i = 0; i < arraySize; ++i) {
//         delete array[i];
//     }

//     return 0;
// }
