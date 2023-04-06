#include"list.h"
#include"list.cpp"
#include<iostream>
using std::cout;
using std::endl;
void printfList(const xie::list<int>& l){
    int n=l.size();
    for(int i=0;i<n;++i){
        cout<<"--"<<l[i]<<"--"<<endl;
    }
}
int main(){
    xie::list<int> l;
    for(int i=0;i<10;++i){
        l.push_back(i);
    }
    l.reverse();
    cout<<l.pop_front()<<endl;
    printfList(l);
    return 0;
}