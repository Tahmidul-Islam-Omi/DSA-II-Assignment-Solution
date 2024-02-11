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

    int HashTableSize =20000;
    int chainLength = 20;
    HashTable1 ht(HashTableSize , chainLength);

    for(int i=1; i<= HashTableSize; i++) {
        ht.insert(randomWordGenerator());
    }

    cout << ht.getCollisonCount() << endl;
    cout << ht.getAvgProbeCount() << endl;
}