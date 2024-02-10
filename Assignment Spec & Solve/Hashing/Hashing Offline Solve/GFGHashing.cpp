#include <iostream>
#include <list>
#include <vector>

// Define a class for the HashTable
class HashTable
{
private:
    // Define the size of the hash table array
    static const int hashGroups = 10;
    // Define a vector of lists to represent the hash table
    std::vector<std::list<std::pair<int, int>>> table;

public:
    // Constructor to initialize the hash table
    HashTable()
    {
        table.resize(hashGroups);
    }

    // Hash function to map keys to indices in the hash table
    int hashFunction(int key)
    {
        return key % hashGroups;
    }

    // Insert a key-value pair into the hash table
    void insert(int key, int value)
    {
        int index = hashFunction(key);
        for (auto &kv : table[index])
        {
            if (kv.first == key)
            {
                // Key already exists, update the value
                kv.second = value;
                return;
            }
        }
        // Key doesn't exist, add a new key-value pair
        table[index].emplace_back(key, value);
    }

    // Retrieve the value associated with a key from the hash table
    int get(int key)
    {
        int index = hashFunction(key);
        for (auto &kv : table[index])
        {
            if (kv.first == key)
            {
                // Key found, return the associated value
                return kv.second;
            }
        }
        // Key not found
        return -1; // or any suitable default value
    }

    // Delete a key-value pair from the hash table
    void remove(int key)
    {
        int index = hashFunction(key);
        table[index].remove_if([key](std::pair<int, int> kv)
                               { return kv.first == key; });
    }
};

// Main function to test the hash table
int main()
{
    HashTable ht;

    // Insert some key-value pairs
    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(11, 30); // Will be placed in the same bucket as key 1

    // Retrieve values using keys
    std::cout << "Value for key 1: " << ht.get(1) << std::endl;
    std::cout << "Value for key 2: " << ht.get(2) << std::endl;
    std::cout << "Value for key 11: " << ht.get(11) << std::endl;

    // Remove a key-value pair
    ht.remove(2);

    // Try to retrieve the removed value
    std::cout << "Value for key 2 after removal: " << ht.get(2) << std::endl; // Should output -1

    return 0;
}
