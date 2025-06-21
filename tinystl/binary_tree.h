#ifndef _BINARY_TREE_XIE
#define _BINARY_TREE_XIE
#include "array.h"
#include <algorithm>
#include <math.h>
#include <memory>
namespace xie {
template <class T> class binary_tree {
private:
  struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(const T &value, TreeNode *_left, TreeNode *_right)
        : data(value), left(_left), right(_right) {}
  };
  TreeNode *root;
  void clear(TreeNode *node);
  void Insert(const T &value, TreeNode *&node);
  void Print_values(TreeNode *node) const;
  size_t Get_node_count(TreeNode *node) const;
  TreeNode *&Get_min_node(TreeNode *node) const {
    if (node == nullptr)
      throw "二叉搜索树没有结点";
    if (node->left == nullptr)
      return node;
    else
      return Get_min_node(node->left);
  }
  TreeNode *&Get_max_node(TreeNode *node) const {
    if (node == nullptr)
      throw "二叉搜索树没有结点";
    if (node->right == nullptr)
      return node;
    else
      return Get_max_node(node->right);
  }
  TreeNode *&Find_node(const T &value, TreeNode *&node) {
    if (node == nullptr)
      return node;
    else if (value > node->data)
      return Find_node(value, node->right);
    else if (value < node->data)
      return Find_node(value, node->left);
    else {
      return node;
    }
  }
  int Get_height(TreeNode *node);
  void Delete_node(TreeNode *&node);

public:
  binary_tree() : root(nullptr) {}
  ~binary_tree();
  void insert(const T &value) { return Insert(value, root); } // 往树上插值
  size_t get_node_count() const {
    return Get_node_count(root);
  } // 查找树上的节点数
  void print_values() const { Print_values(root); } // 从小到大打印树中节点的值
  bool is_in_tree(const T &value) {
    return Find_node(value, root) != nullptr;
  } // 如果值存在于树中则返回 true
  int get_height(const T &value) {
    return Get_height(Find_node(value, root));
  } // 返回节点所在的高度（如果只有一个节点，那么高度则为0，没有该节点为-1）
  T get_min() const { return Get_min_node(root)->data; } // 返回树上的最小值
  T get_max() const { return Get_max_node(root)->data; } // 返回树上的最大值
  // bool is_binary_search_tree(const TreeNode*&  t)const;//判断是否是二插搜索树
  void delete_value(const T &value) {
    Delete_node(Find_node(value, root));
  } // 删除树上的值
};

template <class T> binary_tree<T>::~binary_tree() { clear(root); }
template <class T> void binary_tree<T>::clear(TreeNode *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
  node = nullptr;
}
template <class T> void binary_tree<T>::Delete_node(TreeNode *&node) {
  if (node != nullptr) {
    if (node->right != nullptr && node->left != nullptr) {
      node->data = node->right->data; // 两个儿子
      Delete_node(node->right);
    } else {
      TreeNode *t = node;
      node =
          (node->right != nullptr) ? node->right : node->left; // 只有一个儿子
      delete t;
    }
  }
}
template <class T> void binary_tree<T>::Print_values(TreeNode *node) const {
  if (node != nullptr) {
    Print_values(node->left);
    std::cout << node->data << std::endl;
    Print_values(node->right);
  }
}
template <class T>
void binary_tree<T>::Insert(const T &value, TreeNode *&node) {

  if (node == nullptr) {
    node = new TreeNode(value, nullptr, nullptr);
  } else if (value > node->data)
    Insert(value, node->right);
  else if (value < node->data)
    Insert(value, node->left);
  else {
  }
}
template <class T> size_t binary_tree<T>::Get_node_count(TreeNode *node) const {
  if (node == nullptr)
    return 0;
  else
    return Get_node_count(node->left) + Get_node_count(node->right) + 1;
}
template <class T> int binary_tree<T>::Get_height(TreeNode *node) {
  if (node == nullptr)
    return -1;
  else
    return std::max(Get_height(node->left), Get_height(node->right)) + 1;
}
} // namespace xie

#endif
