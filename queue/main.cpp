#include<iostream>
#include"./queue.h"
#include"./queue.cpp"
using std::cout;
using std::endl;
int main(){
    xie::queue<int>q;
    q.full(10,20);
    while (!q.empty())
    {
        cout<<q.dequeue()<<endl;
    }
}