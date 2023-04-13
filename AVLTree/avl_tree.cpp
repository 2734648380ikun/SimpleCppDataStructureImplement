#include"avl_tree.h"
namespace xie
{
    template<class T>
    avl_tree<T>::~avl_tree(){
        clear(root);
    }
    template<class T>  
    void avl_tree<T>::clear(TreeNode* node){
        if(node!=nullptr){
            clear(node->left);
            clear(node->right);
            delete node;
        }
        node=nullptr;
    }
    template<class T>
    size_t avl_tree<T>::Get_node_count(TreeNode* node)const{
        if(node==nullptr) return 0;
        else return Get_node_count(node->left)+Get_node_count(node->right)+1;
    }
    template<class T>
    int avl_tree<T>::Get_height(TreeNode*&node){
        return node==nullptr?-1:node->height;
    }
    template<class T>
    int avl_tree<T>::Get_depth(const T&value,TreeNode*&node){
        if(node==nullptr) return -1;
        else if(value>node->data) return Get_depth(value,node->right)+1;
        else if(value<node->data) return Get_depth(value,node->left)+1;
        else{
            return 0;
        }
    }
    template<class T>
    void avl_tree<T>::Print_values(TreeNode* node)const{
        if(node!=nullptr){
            Print_values(node->left);
            std::cout<<node->data<<std::endl;
            Print_values(node->right);
        }
    }
    template<class T>
    void avl_tree<T>::Delete_node(TreeNode*& node,const T& value){
        if(node==nullptr) return;
        else if(value>node->data) return Delete_node(node->right,value);
        else if(value<node->data) return Delete_node(node->left,value);
        else{
            if(node->right!=nullptr&&node->left!=nullptr){
                node->data=Get_min_node(node->right)->data;//两个儿子
                Delete_node(node->right,node->data);
            }else{
                TreeNode* t=node;
                node=(node->right!=nullptr)?node->right:node->left;//只有一个儿子
                delete t;
            }
        }
        Balance(node);
    }
    template<class T>
    void avl_tree<T>::Insert(const T& value,TreeNode*&node){
        if(node==nullptr){
            node=new TreeNode(value,nullptr,nullptr);
        }
        else if(value>node->data) Insert(value,node->right);
        else if(value<node->data) Insert(value,node->left);
        else{
            return;
        }
        Balance(node);
    }
    template<class T>
    void avl_tree<T>::One_left_rotate(TreeNode*&node){
        TreeNode*t=node;
        node=node->left;
        t->left=node->right;
        node->right=t;
        t->height=std::max(Get_height(t->left),Get_height(t->right))+1;
        node->height=std::max(Get_height(node->left),Get_height(node->right))+1;
    }
    template<class T> 
    void avl_tree<T>::One_right_rotate(TreeNode*&node){
        TreeNode*t=node;
        node=node->right;
        t->right=node->left;
        node->left=t;
        t->height=std::max(Get_height(t->left),Get_height(t->right))+1;
        node->height=std::max(Get_height(node->left),Get_height(node->right))+1;
    }
    template<class T>
    void avl_tree<T>::Two_right_rotate(TreeNode*&node){
        One_left_rotate(node->right);
        One_right_rotate(node);
    }
    template<class T>
    void avl_tree<T>::Two_left_rotate(TreeNode*&node){
        One_right_rotate(node->left);
        One_left_rotate(node);
    }
    template<class T>
    void avl_tree<T>::Balance(TreeNode*&node){
        if(node==nullptr) return;
        if(Get_height(node->left)-Get_height(node->right)>=_MAX_HEIGHT_DIFFERENCE){
            if(Get_height(node->left->left)>=Get_height(node->left->right)){
                One_left_rotate(node);

            }else{
                Two_left_rotate(node);
            }
        }else if(Get_height(node->right)-Get_height(node->left)>=_MAX_HEIGHT_DIFFERENCE){
            if(Get_height(node->right->left)<=Get_height(node->right->right)){
                One_right_rotate(node);
            }else{
                Two_right_rotate(node);
            }
        }
        node->height=std::max(Get_height(node->left),Get_height(node->right))+1;
    }
} // namespace xie
