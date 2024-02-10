#include <bits/stdc++.h>
using namespace std;

class HashTable1
{
private:
    int hashSize;
    vector<list<pair<string, int>>> table;
    int ValueCount;

public:
    HashTable1(int size)
    {
        this->hashSize = nextPrime(size);
        table.resize(hashSize);
        ValueCount = 0;
    }

    // fnv1a hash function

    int hashFunction(string str)
    {
        unsigned int hash = 2166136261; // FNV offset basis
        // Iterate over each character in the string
        for (char ch : str)
        {
            hash ^= ch;
            hash *= 16777619; // FNV prime
        }
        // Return the hash value modulo hashSize
        return hash % hashSize;
    }

    void insert(string key)
    {
        // Key doesn't exist, so add it
        if (find(key) == -1)
        {
            int index = hashFunction(key);
            table[index].emplace_back(key, ++ValueCount);
        }
    }

    int find(string key)
    {
        int index = hashFunction(key);

        for (auto x : table[index])
        {
            if (x.first == key)
            {
                // Key found,so return the associated value
                return x.second;
            }
        }

        return -1; // key not found so return -1
    }

    bool remove(string key)
    {
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                return true;
            }
        }

        return false;
    }

    bool isPrime(long long num)
    {
        if (num <= 1)
        {
            return false;
        }

        if (num == 2)
        {
            return true;
        }

        if (num % 2 == 0)
        {
            return false;
        }

        int root = sqrt(num);

        for (long long i = 3; i <= root; i += 2)
        {
            if (num % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    long long nextPrime(long long num)
    {
        while (true)
        {
            if (isPrime(num))
            {
                return num;
            }

            num++;
        }
    }
};