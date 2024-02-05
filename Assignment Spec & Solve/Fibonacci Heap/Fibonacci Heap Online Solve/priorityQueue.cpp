#include <bits/stdc++.h>
#include "fibonacciHeap.cpp"

using namespace std;

template <typename Key, typename Value>

class PriorityQueue
{
    Node<Key, Value> *Heap;
    FibonacciHeap<int, int> FH;

public:
    Node<Key, Value> *make_heap()
    {
        Heap = FH.HeapInitialization();
        return Heap;
    }

    bool is_empty(Node<int, int> *heap)
    {
        if (heap == NULL)
        {
            cout << "Heap is Empty" << endl;
        }

        else
        {
            cout << "Heap is not Empty" << endl;
        }
    }

    void insert(Node<int, int> *heap, Key key, Value value)
    {
        FH.insertion(key, value);
    }

    void print(Node<int, int> *heap)
    {
        FH.display();
        cout << endl;

        //cout << FH.getH()->child->key << endl;
    }

    void extract_max(Node<int, int> *heap)
    {
        cout << "Max Value is (" << FH.getH()->key << "," << FH.getH()->value << ")" << endl;
        FH.Extract_max();
    }

    void increase_key(Node<int, int> *heap, Value value, Key new_key)
    {
        FH.Increase_key(value, new_key);
    }

    void Delete(Node<int, int> *heap, Value value)
    {
        FH.deletion(value);
    }

    void find_max(Node<int, int> *heap)
    {
        cout << "Max Value is (" << FH.getH()->key << "," << FH.getH()->value << ")" << endl;
    }

    void test() {

    }
};

int main()
{
    PriorityQueue<int, int> pq;
    Node<int, int> *Heap;
    Heap = pq.make_heap();

    pq.insert(Heap, 23, 5);
    pq.insert(Heap, 19, 3);
    pq.insert(Heap, 70, 1);
    pq.insert(Heap, 39, 8);
    pq.insert(Heap, 47, 2);
    pq.insert(Heap, 49, 15);

    pq.print(Heap);

    pq.extract_max(Heap);

    pq.print(Heap);
}