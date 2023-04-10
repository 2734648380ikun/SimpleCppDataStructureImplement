#ifndef _BINARY_TREE_XIE
#define _BINARY_TREE_XIE
#include"../array/array.cpp"
#include<math.h>
#include<memory>
namespace xie
{
    template<class T>
    class binary_tree
    {
    private:
        struct TreeNode
        {
            T data;
            TreeNode* left;
            TreeNode* right;
            TreeNode(const T&value,TreeNode*_left,TreeNode*_right):data(value),left(_left),right(_right){}
        };
        TreeNode* root;
        void clear(TreeNode* node);
        void Insert(const T& value,TreeNode*&node);
        void Print_values(TreeNode* node)const;
        size_t Get_node_count(TreeNode* node)const;
        TreeNode*& Get_min_node(TreeNode* node)const{
            if(node==nullptr) throw "二叉搜索树没有结点";
            if(node->left==nullptr) return node->data;
            else return Get_min(node->left);
        }
        TreeNode*& Get_max_node(TreeNode* node)const{
            if(node==nullptr) throw "二叉搜索树没有结点";
            if(node->right==nullptr) return node->data;
            else return Get_max(node->right);
        }
        TreeNode*& Find_node(const T& value,TreeNode*&node){
            if(node==nullptr) return node;
            else if(value>node->data) return Find_node(value,node->right);
            else if(value<node->data) return Find_node(value,node->left);
            else{
                return node;
            }
        }
        int Get_height(TreeNode* node);
        void Delete_node(TreeNode*&node);
    public:
        binary_tree():root(nullptr){}
        ~binary_tree();
        void insert(const T& value){return Insert(value,root);}// 往树上插值
        size_t get_node_count()const{return Get_node_count(root);} // 查找树上的节点数
        void print_values()const{Print_values(root);} // 从小到大打印树中节点的值
        bool is_in_tree(const T& value){return Find_node(value,root)!=nullptr;} // 如果值存在于树中则返回 true
        int get_height(const T& value){return Get_height(Find_node(value,root));} // 返回节点所在的高度（如果只有一个节点，那么高度则为0，没有该节点为-1）
        T get_min()const{return Get_min_node(root)->data;} // 返回树上的最小值
        T get_max()const{return Get_max_node(root)->data;} // 返回树上的最大值
        //bool is_binary_search_tree(const TreeNode*&  t)const;//判断是否是二插搜索树
        void delete_value(const T&value){Delete_node(Find_node(value,root));}//删除树上的值
    };
} // namespace xie




#endif