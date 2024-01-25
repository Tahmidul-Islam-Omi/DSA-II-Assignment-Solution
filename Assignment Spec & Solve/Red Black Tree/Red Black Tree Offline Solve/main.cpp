#include "map.cpp"
#include<bits/stdc++.h>
using namespace std;

int main()
{

    MAP<int, string> mp;

    mp.insert(100, "hello");
    mp.insert(21, "world");
    mp.insert(3, "Omi");

    mp.inorderTraversal(); 

    return 0;

}