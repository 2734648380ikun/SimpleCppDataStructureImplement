#include"avl_tree.cpp"
#include"../array/array.cpp"
#include<iostream>
#include<ctime>
#include<random>
#define test_nums 7
int main(){
    xie::avl_tree<int>at;
    std::default_random_engine e;
    std::uniform_int_distribution<int> randnum(0,100);
    xie::array<int> arr;
    e.seed(time(0));
    for(int i=0;i<test_nums;i++){
        auto r=randnum(e);
        at.insert(r);
        arr.push(r);
    }
    std::cout<<"-----print-----"<<std::endl;
    at.print_tree();
    // for(int i=0;i<test_nums;i++){
    //     std::cout<<at.depth(arr[i])<<"--"<<arr[i]<<std::endl;
    // }
    std::uniform_int_distribution<int> randnum2(0,test_nums-1);
    for(int i=0;i<test_nums/2;i++){
        auto t=randnum2(e);
        at.delete_node(arr[t]);
        std::cout<<"delete:"<<arr[t]<<std::endl;
    }
    std::cout<<"-----print-----"<<std::endl;
    at.print_tree();
    std::cout<<"---------------"<<std::endl;
    for(int i=0;i<test_nums;i++){
        std::cout<<at.depth(arr[i])<<"--"<<arr[i]<<std::endl;
    }
    return 0;
}