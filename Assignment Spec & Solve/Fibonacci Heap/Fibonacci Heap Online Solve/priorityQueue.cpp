#include <bits/stdc++.h>
#include "fibonacciHeap.cpp"

using namespace std;

template <typename Key, typename Value>

class PriorityQueue
{
    Node<Key, Value> *Heap;
    FibonacciHeap<int, int> FH;
    FibonacciHeap<int, int> FH3 ;

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
    }

    void rootListprint(Node<int, int> *heap)
    {

        FH.rootListDisplay();
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

    // void meld(Node<int, int> *heap1, Node<int, int> *heap2)
    // {
    //     // assuming heap1 is existing heap
    //     FH3.H = heap2; 
    //     int cnt = FH3.getNodeCount();
    //     FH.meld(FH3, cnt);
    // }

};

int main()
{

        // pq.insert(Heap, 10, 10);
    // pq.insert(Heap, 20, 20);
    // pq.insert(Heap, 30, 30);
    // pq.insert(Heap, 40, 40);
    // pq.insert(Heap, 50, 50);
    // pq.insert(Heap, 60, 60);

    // pq.extract_max(Heap);


    // pq.extract_max(Heap);

    // pq.rootListprint(Heap);

    // pq.Delete(Heap , 60);

    // pq.find_max(Heap);

    // pq.is_empty(Heap);

    // pq.rootListprint(Heap);

    // pq.increase_key(Heap , 10 , 100);

    // pq.extract_max(Heap);

    // pq.rootListprint(Heap);

    PriorityQueue<int, int> pq;
    Node<int, int> *Heap;
    Heap = pq.make_heap();


    for(int i=1000; i<=3000; i++) {
        pq.insert(Heap, i, 2*i);

        if(i % 100 == 0) {
            pq.extract_max(Heap);
        }
    }

    pq.rootListprint(Heap);

    // PriorityQueue<int, int> pq1;
    // Node<int, int> *Heap1;
    // Heap1 = pq1.make_heap();

    // for(int i=4000; i<=3000; i++) {
    //     pq1.insert(Heap1, i, 3*i);

    //     if(i % 100 == 0) {
    //         pq1.extract_max(Heap1);
    //     }
    // }

    // // //pq.meld(Heap , Heap1);

    // pq1.rootListprint(Heap1);

}