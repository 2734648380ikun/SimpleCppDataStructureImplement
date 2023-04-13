#ifndef _AVL_TREE_XIE
#define _AVL_TREE_XIE
#include<math.h>
#include<iostream>
namespace xie
{
    static constexpr int _MAX_HEIGHT_DIFFERENCE=2;
    template<class T>
    class avl_tree
    {
    private:
        struct TreeNode
        {
            T data;
            int height;
            TreeNode* left;
            TreeNode* right;
            TreeNode(const T&value,TreeNode*_left,TreeNode*_right,int _height=0)
                    :data(value),height(_height),left(_left),right(_right){}
        };
        TreeNode* root;
        void clear(TreeNode* node);
        void Insert(const T& value,TreeNode*&node);
        size_t Get_node_count(TreeNode* node)const;
        TreeNode* Get_min_node(TreeNode* node)const{
            if(node==nullptr) throw "二叉搜索树没有结点";
            if(node->left==nullptr) return node;
            else return Get_min_node(node->left);
        }
        TreeNode* Get_max_node(TreeNode* node)const{
            if(node==nullptr) throw "二叉搜索树没有结点";
            if(node->right==nullptr) return node;
            else return Get_max_node(node->right);
        }
        TreeNode*& Find_node(const T& value,TreeNode*&node){
            if(node==nullptr) return node;
            else if(value>node->data) return Find_node(value,node->right);
            else if(value<node->data) return Find_node(value,node->left);
            else{
                return node;
            }
        }
        int Get_height(TreeNode*&node);//结点为空为-1
        int Get_depth(const T& value,TreeNode*& node);
        void Delete_node(TreeNode*&node,const T&value);
        void Print_values(TreeNode* node)const;
        void One_left_rotate(TreeNode*& node);//单旋转
        void One_right_rotate(TreeNode*& node);
        void Two_left_rotate(TreeNode*& node);//双旋转
        void Two_right_rotate(TreeNode*& node);
        void Balance(TreeNode*& node);//平衡二叉树
    public:
        avl_tree():root(nullptr){}
        void insert(const T& value){Insert(value,root);}
        void delete_node(const T& value){Delete_node(root,value);}
        int height(const T& value){return Get_height(Find_node(value,root));}
        int depth(const T& value){return Get_depth(value,root);}
        void print_tree()const{Print_values(root);}
        ~avl_tree();
    };
} // namespace xie
#endif