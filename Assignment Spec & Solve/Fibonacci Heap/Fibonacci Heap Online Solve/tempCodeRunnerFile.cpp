    void meld(Node<int, int> *heap1, Node<int, int> *heap2)
    {
        // assuming heap1 is existing heap
        FibonacciHeap<int, int> FH3 ;
        FH3.Node = heap2; 
        int cnt = FH3.getNodeCount();
        FH.meld(FH3, cnt);
    }