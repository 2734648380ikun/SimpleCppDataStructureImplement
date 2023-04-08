#include"array.h"
#include"array.cpp"
#include<iostream>
using std::cout;
using std::endl;
int main(){
    auto A=xie::array<int>(40);
    cout<<A.capacity()<<","<<A.size()<<endl;
    auto B=xie::array<int>(A);//默认构造
    cout<<B.capacity()<<","<<B.size()<<endl;
    auto C=xie::array<int>(xie::array<int>(12));//移动构造
    cout<<C.capacity()<<","<<C.size()<<endl;
    cout<<A.is_empty()<<endl;
    C.push(10);
    C.push(10);
    C.push(30);
    C.push(10);
    C.push(10);
    C.push(30);
    C.push(10);
    C.push(10);
    C.push(30);
    cout<<C.capacity()<<","<<C.size()<<endl;
    return 0;
}