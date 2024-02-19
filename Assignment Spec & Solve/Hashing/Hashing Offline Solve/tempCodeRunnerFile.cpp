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

    int HashTableSize = 5000;
    int chainLength = 5;
    HashTable1 ht(HashTableSize , chainLength);

    vector<string> words(10000);

    for(int i=1; i<= 10000; i++) {
        string word = randomWordGenerator();
        words.push_back(word);
        ht.insert(word);
    }

    cout << ht.getCollisonCount() << endl;
    cout << ht.getAvgProbeCount() << endl;
}