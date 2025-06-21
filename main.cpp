#include "tinystl/array.h"
#include "tinystl/avl_tree.h"
#include "tinystl/binary_tree.h"
#include "tinystl/hashtable.h"
#include "tinystl/list.h"
#include "tinystl/queue.h"

#include <cstdlib>
#include <iostream>
using namespace xie;

int main() {
  std::cout << "Hello world" << std::endl;
  array<int> a(10, 100);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ",";
  }

  std::cout << std::endl;

  for (size_t i = 0; i < 10; i++) {
    a.push(2 * i);
  }
  std::cout << std::endl;

  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ",";
  }
  std::cout << std::endl;

  a.delete_at(9);
  a.delete_at(8);
  a.delete_at(7);
  a.delete_at(6);
  a.delete_at(5);
  a.delete_at(4);
  a.delete_at(3);

  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ",";
  }
  std::cout << std::endl;

  hashtable<int, int> ht;
  ht.add(10, 0);
  std::cout << (ht.exists(10) ? "存在10" : "不存在10") << std::endl;

  for (size_t i = 0; i < 100; i++) {

    ht.add(i, 2 * i);
  }
  std::cout << ht.get(30) << std::endl;

  ht.remove(10);

  // #include "tinystl/binary_tree.h"
  // #include "tinystl/avl_tree.h"
  // #include "tinystl/list.h"
  // #include "tinystl/queue.h"
  binary_tree<int> bt;
  avl_tree<int> avl;
  list<int> list;
  queue<int> q;

  return 0;
}
