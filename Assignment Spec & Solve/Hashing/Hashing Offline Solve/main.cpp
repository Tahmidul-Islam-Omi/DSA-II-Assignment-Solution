#include "hash.h"
using namespace std;
#define seed1 1010

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
    srand(seed1);

    int HashTableSize = 5000;
    int chainLength = 10;
    HashTable1 ht(HashTableSize , chainLength);

    for(int i=1; i<= 10000; i++) {
        string word = randomWordGenerator();
        ht.insert(word);
    }

    cout << ht.getCollisonCount() << endl;
    cout << ht.getAvgProbeCount() << endl;
    //ht.deleteRehashTesting();
}