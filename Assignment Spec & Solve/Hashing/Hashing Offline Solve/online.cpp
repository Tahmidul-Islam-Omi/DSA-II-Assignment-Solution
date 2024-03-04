#include<bits/stdc++.h>
#include"hash.h"

using namespace std;

bool validateWord(string word, int m, int n ) {
    int arr[4];
    memset(arr, 0, sizeof(arr));

    int cnt = 0;

    for(int i=m; i<=n; i++) {

        if(word[i] == 'A') {
            arr[0]++;
        }

        if(word[i] == 'C') {
            arr[1]++;
        }

        if(word[i] == 'T') {
            arr[2]++;
        }

        if(word[i] == 'G') {
            arr[3]++;
        }
    }

}

int main() {
    int l,k;
    cin >> l >> k;

    string word;
    cin >> word;

    HashTable1 ht(100 , 10);

    for(int i=0; i<l-(k-1); i++) {
        string str = word.substr(i,k);
        ht.insert(str , 1);
    }

    ht.print();
}