#include "hash.h"
using namespace std;

string randomWordGenerator() {

    int wordLength = rand() % 6 + 5;

    string letters = "abcdefghijklmnopqrstuvwxyz";

    string word = "";

    for(int i=1; i<= wordLength; i++) {
        word += letters[ rand() % 26];
    }

    return word;

}

int main()
{
    srand(time(NULL));

    int HashTableSize =1000;
    HashTable1 ht(HashTableSize);

    for(int i=1; i<= HashTableSize-2; i++) {
        ht.insert(randomWordGenerator());
    }

    ht.insert("Omi");
    ht.insert("BUET");

    ht.remove("Omi");

    cout << ht.find("Omi") << endl;

}