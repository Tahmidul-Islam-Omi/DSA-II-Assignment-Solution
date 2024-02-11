#include <bits/stdc++.h>
using namespace std;

class HashTable1
{
private:
    int hashSize;
    vector<list<pair<string, int>>> table;
    int ValueCount;
    int collisonCount;
    int probeCount;
    int chainLength;
    int currSize;

public:
    HashTable1(int size, int chainLength)
    {
        this->hashSize = nextPrime(size);
        table.resize(hashSize);
        this->chainLength = chainLength;
        ValueCount = 0;
        collisonCount = 0;
        currSize = 0;
        probeCount = 1;
    }

    void setHashSize(int size)
    {
        this->hashSize = size;
    }

    void ResetcollisonCount()
    {
        collisonCount = 0;
    }

    void ResetCurrSize()
    {
        currSize = 0;
    }

    void ResetProbeCount() {
        probeCount = 1;
    }

    int getCollisonCount()
    {
        return collisonCount;
    }

    double getAvgProbeCount()
    {
        return (double)probeCount / (currSize );
    }

    // fnv1a hash function

    // unsigned int hashFunction(string str)
    // {
    //     unsigned int hash = 2166136261; // FNV offset basis
    //     // Iterate over each character in the string
    //     for (char ch : str)
    //     {
    //         hash ^= ch;
    //         hash *= 16777619; // FNV prime
    //     }
    //     // Return the hash value modulo hashSize
    //     return hash % hashSize;
    // }

    unsigned int hashFunction(string str)
    {
        unsigned int hash = 5381;
        
        for(char ch : str)
        {
            hash = ((hash << 5) + hash) + ch; // hash * 33 + c
        }

        return hash % hashSize;
    }

    unsigned int auxHash(string str)
    {
        unsigned int hash = 0;
        for (char ch : str)
        {
            hash += ch; // Simply summing up the ASCII values of characters
        }
        return hash % hashSize;
    }

    // Separate chaining implementation
    // void insertHelper(string key, int value)
    // {
    //     int index = hashFunction(key);
    //     currSize++;

    //     if (table[index].empty())
    //     {
    //         table[index].emplace_back(key, value);
    //     }

    //     else
    //     {
    //         collisonCount++;
    //         probeCount += table[index].size() - 1;
    //         table[index].emplace_back(key, value);
    //     }

    //     if (currSize % 100 == 0 && currMaxChainLength() > chainLength)
    //     {
    //         Rehash("insertRehash");
    //     }
    // }

    // Double Hashing Implementation

    // void insertHelper(string key, int value)
    // {
    //     int index = hashFunction(key);
    //     currSize++;

    //     if (table[index].empty())
    //     {
    //         table[index].emplace_back(key, value);
    //     }

    //     else
    //     {
    //         int index1 = auxHash(key);
    //         index = doubleHash(index, index1);
    //         collisonCount++;

    //         if (index != -1)
    //         {
    //             table[index].emplace_back(key, value);
    //         }
    //     }

    //     if (currSize % 100 == 0 && currMaxChainLength() > chainLength)
    //     {
    //         Rehash("insertRehash");
    //     }
    // }

    // Custom probing Implementation

    void insertHelper(string key, int value)
    {
        int index = hashFunction(key);
        currSize++;

        if (table[index].empty())
        {
            table[index].emplace_back(key, value);
        }

        else
        {
            int index1 = auxHash(key);
            index = customProbing(index, index1);
            collisonCount++;

            if (index != -1)
            {
                table[index].emplace_back(key, value);
            }
        }

        if (currSize % 100 == 0 && currMaxChainLength() > chainLength)
        {
            Rehash("insertRehash");
        }
    }

    int customProbing(int k, int k1)
    {

        // Here i denotes probeCount
        for (int i = 1; i <= 100; i++)
        {
            int index = (k + 5 * i * k1 + 7 * i * i) % hashSize;

            if (table[index].empty())
            {
                probeCount += i;
                return index;
            }
        }

        return -1;
    }

    int doubleHash(int k, int k1)
    {

        // Here i denotes probeCount
        for (int i = 1; i <= 100; i++)
        {
            int index = (k + i * k1) % hashSize;

            if (table[index].empty())
            {
                probeCount += i;
                return index;
            }
        }

        return -1;
    }

    void insert(string key)
    {
        // Key doesn't exist, so add it
        if (find(key) == -1)
        {
            insertHelper(key, ++ValueCount);
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

    void remove(string key)
    {
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                cout << "Removed Successfully" << endl;
                currSize--;

                if (currSize % 100 == 0 && currMaxChainLength() < 0.8 * chainLength)
                {
                    Rehash("DeleteRehash");
                }

                return;
            }
        }

        cout << "Oops! not found" << endl;
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

    void Rehash(string str)
    {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Rehashing is triggered" << endl;
        cout << "Average Probe Count: " << getAvgProbeCount() << endl;
        cout << "Load Factor:- " << currSize / hashSize << endl;
        cout << "Maximum Chain Length: " << currMaxChainLength() << endl;
        cout << "----------------------------------------------------------------" << endl;

        // insertRehash
        if (str == "insertRehash")
        {
            int newSize = nextPrime(2 * hashSize);
            setHashSize(newSize);

            ResetcollisonCount();
            ResetCurrSize();
            ResetProbeCount();

            vector<list<pair<string, int>>> newtable = table;
            table.clear();

            for (int i = 0; i < newtable.size(); i++)
            {
                for (auto it : newtable[i])
                {
                    insertHelper(it.first, it.second);
                }
            }
        }

        // deleteRehash
        else
        {
            int newSize = nextPrime(hashSize / 2);
            setHashSize(newSize);

            ResetcollisonCount();
            ResetCurrSize();

            vector<list<pair<string, int>>> newtable = table;
            table.clear();

            for (int i = 0; i < newtable.size(); i++)
            {
                for (auto it : newtable[i])
                {
                    insertHelper(it.first, it.second);
                }
            }
        }

        cout << "----------------------------------------------------------------" << endl;
        cout << "Rehashing is triggered" << endl;
        cout << "Average Probe Count: " << getAvgProbeCount() << endl;
        cout << "Load Factor:- " << currSize / hashSize << endl;
        cout << "Maximum Chain Length: " << currMaxChainLength() << endl;
        cout << "----------------------------------------------------------------" << endl;
    }

    int currMaxChainLength()
    {
        int length = -1;

        for (int i = 0; i < hashSize; i++)
        {
            length = max(length, distance(table[i].begin(), table[i].end()));
        }

        return length;
    }
};