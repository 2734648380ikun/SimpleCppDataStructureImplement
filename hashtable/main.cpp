#include"hashtable.cpp"
#include<iostream>
using std::cout;
using std::endl;
int main(){
    xie::hashtable<int,int> hb;
    cout<<hb.capacity()<<","<<hb.size()<<endl;
    for(int i=0;i<20;++i){
        hb.add(i,i*10);
    }
    cout<<hb.exists(5)<<","<<hb.get(5)<<","<<hb.capacity();
    return 0;
}