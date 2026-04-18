#ifndef _AVL_TREE_XIE
#define _AVL_TREE_XIE
#include <iostream>
#include <math.h>
namespace leexxq {
static constexpr int _MAX_HEIGHT_DIFFERENCE = 2;
template <class T> class avl_tree {
private:
  struct TreeNode {
    T data;
    int height;
    TreeNode *left;
    TreeNode *right;
    TreeNode(const T &value, TreeNode *_left, TreeNode *_right, int _height = 0)
        : data(value), height(_height), left(_left), right(_right) {}
  };
  TreeNode *root;
  void clear(TreeNode *node);
  void Insert(const T &value, TreeNode *&node);
  size_t Get_node_count(TreeNode *node) const;
  TreeNode *Get_min_node(TreeNode *node) const {
    if (node == nullptr)
      throw "二叉搜索树没有结点";
    if (node->left == nullptr)
      return node;
    else
      return Get_min_node(node->left);
  }
  TreeNode *Get_max_node(TreeNode *node) const {
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
  int Get_height(TreeNode *&node); // 结点为空为-1
  int Get_depth(const T &value, TreeNode *&node);
  void Delete_node(TreeNode *&node, const T &value);
  void Print_values(TreeNode *node) const;
  void One_left_rotate(TreeNode *&node); // 单旋转
  void One_right_rotate(TreeNode *&node);
  void Two_left_rotate(TreeNode *&node); // 双旋转
  void Two_right_rotate(TreeNode *&node);
  void Balance(TreeNode *&node); // 平衡二叉树
public:
  avl_tree() : root(nullptr) {}
  void insert(const T &value) { Insert(value, root); }
  void delete_node(const T &value) { Delete_node(root, value); }
  int height(const T &value) { return Get_height(Find_node(value, root)); }
  int depth(const T &value) { return Get_depth(value, root); }
  void print_tree() const { Print_values(root); }
  ~avl_tree();
};

template <class T> avl_tree<T>::~avl_tree() { clear(root); }
template <class T> void avl_tree<T>::clear(TreeNode *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
  node = nullptr;
}
template <class T> size_t avl_tree<T>::Get_node_count(TreeNode *node) const {
  if (node == nullptr)
    return 0;
  else
    return Get_node_count(node->left) + Get_node_count(node->right) + 1;
}
template <class T> int avl_tree<T>::Get_height(TreeNode *&node) {
  return node == nullptr ? -1 : node->height;
}
template <class T> int avl_tree<T>::Get_depth(const T &value, TreeNode *&node) {
  if (node == nullptr)
    return -1;
  else if (value > node->data)
    return Get_depth(value, node->right) + 1;
  else if (value < node->data)
    return Get_depth(value, node->left) + 1;
  else {
    return 0;
  }
}
template <class T> void avl_tree<T>::Print_values(TreeNode *node) const {
  if (node != nullptr) {
    Print_values(node->left);
    std::cout << node->data << std::endl;
    Print_values(node->right);
  }
}
template <class T>
void avl_tree<T>::Delete_node(TreeNode *&node, const T &value) {
  if (node == nullptr)
    return;
  else if (value > node->data)
    return Delete_node(node->right, value);
  else if (value < node->data)
    return Delete_node(node->left, value);
  else {
    if (node->right != nullptr && node->left != nullptr) {
      node->data = Get_min_node(node->right)->data; // 两个儿子
      Delete_node(node->right, node->data);
    } else {
      TreeNode *t = node;
      node = (node->right != nullptr) ? node->right : node->left; // 只有一个儿子
      delete t;
    }
  }
  Balance(node);
}
template <class T> void avl_tree<T>::Insert(const T &value, TreeNode *&node) {
  if (node == nullptr) {
    node = new TreeNode(value, nullptr, nullptr);
  } else if (value > node->data)
    Insert(value, node->right);
  else if (value < node->data)
    Insert(value, node->left);
  else {
    return;
  }
  Balance(node);
}
template <class T> void avl_tree<T>::One_left_rotate(TreeNode *&node) {
  TreeNode *t = node;
  node = node->left;
  t->left = node->right;
  node->right = t;
  t->height = std::max(Get_height(t->left), Get_height(t->right)) + 1;
  node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;
}
template <class T> void avl_tree<T>::One_right_rotate(TreeNode *&node) {
  TreeNode *t = node;
  node = node->right;
  t->right = node->left;
  node->left = t;
  t->height = std::max(Get_height(t->left), Get_height(t->right)) + 1;
  node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;
}
template <class T> void avl_tree<T>::Two_right_rotate(TreeNode *&node) {
  One_left_rotate(node->right);
  One_right_rotate(node);
}
template <class T> void avl_tree<T>::Two_left_rotate(TreeNode *&node) {
  One_right_rotate(node->left);
  One_left_rotate(node);
}
template <class T> void avl_tree<T>::Balance(TreeNode *&node) {
  if (node == nullptr)
    return;
  if (Get_height(node->left) - Get_height(node->right) >=
      _MAX_HEIGHT_DIFFERENCE) {
    if (Get_height(node->left->left) >= Get_height(node->left->right)) {
      One_left_rotate(node);

    } else {
      Two_left_rotate(node);
    }
  } else if (Get_height(node->right) - Get_height(node->left) >=
             _MAX_HEIGHT_DIFFERENCE) {
    if (Get_height(node->right->left) <= Get_height(node->right->right)) {
      One_right_rotate(node);
    } else {
      Two_right_rotate(node);
    }
  }
  node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;
}
} // namespace xie
#endif
