#include<iostream>
#include<math.h>
#include"binary_tree.cpp"
int main(){
    xie::binary_tree<int> bt;
    bt.insert(50);
    bt.insert(40);
    bt.insert(7);
    bt.insert(5);
    bt.insert(4);
    bt.insert(20);
    bt.print_values();
    std::cout<<"---------"<<bt.get_node_count()<<"----------"<<bt.get_height(50)<<std::endl;
    bt.delete_value(20);
    bt.delete_value(7);
    bt.delete_value(40);
    bt.print_values();
    std::cout<<"---------"<<bt.get_node_count()<<"----------"<<bt.get_height(50)<<std::endl;
    return 0;
}