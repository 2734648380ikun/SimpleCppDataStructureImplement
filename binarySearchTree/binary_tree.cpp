#include"binary_tree.h"
#include<iostream>
namespace xie
{
    template<class T>
    binary_tree<T>::~binary_tree(){
        clear(root);
    }
    template<class T>  
    void binary_tree<T>::clear(TreeNode* node){
        if(node!=nullptr){
            clear(node->left);
            clear(node->right);
            delete node;
        }
        node=nullptr;
    }
    template<class T>
    void binary_tree<T>::Delete_node(TreeNode*& node){
        if(node!=nullptr){
            if(node->right!=nullptr&&node->left!=nullptr){
                node->data=node->right->data;//两个儿子
                Delete_node(node->right);
            }else{
                TreeNode* t=node;
                node=(node->right!=nullptr)?node->right:node->left;//只有一个儿子
                delete t;
            }
        }
    }
    template<class T>
    void binary_tree<T>::Print_values(TreeNode* node)const{
        if(node!=nullptr){
            Print_values(node->left);
            std::cout<<node->data<<std::endl;
            Print_values(node->right);
        }
    }
    template<class T>
    void binary_tree<T>::Insert(const T& value,TreeNode*&node){

            if(node==nullptr){
                node=new TreeNode(value,nullptr,nullptr);
            }
            else if(value>node->data) Insert(value,node->right);
            else if(value<node->data) Insert(value,node->left);
            else{
            }
    }
    template<class T>
    size_t binary_tree<T>::Get_node_count(TreeNode* node)const{
        if(node==nullptr) return 0;
        else return Get_node_count(node->left)+Get_node_count(node->right)+1;
    }
    template<class T>
    int binary_tree<T>::Get_height(TreeNode* node){
        if(node==nullptr) return -1;
        else return std::max(Get_height(node->left),Get_height(node->right))+1;
    }
}// namespace xie
