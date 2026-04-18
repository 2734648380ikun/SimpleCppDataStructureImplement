#include "tinystl/array.h"
#include "tinystl/avl_tree.h"
#include "tinystl/binary_tree.h"
#include "tinystl/hashtable.h"
#include "tinystl/list.h"
#include "tinystl/queue.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace leexxq;

namespace {

void expect(bool condition, const std::string &message) {
  if (!condition) {
    std::cerr << "[FAILED] " << message << std::endl;
    std::exit(1);
  }
}

void test_array() {
  array<int> arr;
  expect(arr.is_empty(), "array should start empty");

  for (int i = 0; i < 20; ++i) {
    arr.push(i);
  }

  expect(arr.size() == 20, "array size after push should be 20");
  expect(arr.capacity() >= 32, "array should grow capacity");
  expect(arr[0] == 0 && arr[19] == 19, "array should keep push order");
  expect(arr.find(11) == 11, "array find existing value");
  expect(arr.find(999) == -1, "array find missing value");

  array<size_t> removed = arr.remove(5);
  expect(removed.size() == 1 && removed[0] == 5, "array remove index tracking");
  expect(arr.size() == 19, "array size after remove");
  expect(arr.find(5) == -1, "array remove target value");
}

void test_list() {
  list<int> l;
  expect(l.empty(), "list should start empty");

  l.push_front(2);
  l.push_front(1);
  l.push_back(3);

  expect(l.size() == 3, "list size after push");
  expect(l.front() == 1, "list front value");
  expect(l.back() == 3, "list back value");
  expect(l[1] == 2, "list index access");

  expect(l.insert(2, 99), "list insert in middle");
  expect(l.size() == 4 && l[2] == 99 && l[3] == 3, "list insert result");
  expect(l.erase(2), "list erase in middle");
  expect(l.size() == 3 && l[2] == 3, "list erase result");
  expect(!l.erase(100), "list erase out of range");

  expect(l.remove_value(2), "list remove existing value");
  expect(!l.remove_value(200), "list remove missing value");
  expect(l.size() == 2 && l[0] == 1 && l[1] == 3, "list remove value result");

  l.reverse();
  expect(l[0] == 3 && l[1] == 1, "list reverse");
  expect(l.value_n_from_end(0) == 1, "list nth from end (0)");
  expect(l.value_n_from_end(1) == 3, "list nth from end (1)");

  expect(l.pop_front() == 3, "list pop_front value");
  expect(l.size() == 1 && l.front() == 1, "list pop_front result");
}

void test_queue() {
  queue<int> q;
  expect(q.empty(), "queue should start empty");

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  expect(!q.empty(), "queue should be non-empty after enqueue");

  expect(q.dequeue() == 1, "queue dequeue first");
  expect(q.dequeue() == 2, "queue dequeue second");
  expect(q.dequeue() == 3, "queue dequeue third");
  expect(q.empty(), "queue should be empty after draining");

  q.full(3, 7);
  expect(q.dequeue() == 7, "queue full + dequeue first");
  expect(q.dequeue() == 7, "queue full + dequeue second");
  expect(q.dequeue() == 7, "queue full + dequeue third");
  expect(q.empty(), "queue should be empty after full/dequeue");

  q.enqueue(42);
  expect(q.dequeue() == 42, "queue enqueue/dequeue after reset");
}

void test_hashtable() {
  hashtable<int, int> ht;
  const size_t initial_capacity = ht.capacity();
  expect(ht.size() == 0, "hashtable should start empty");

  ht.add(1, 10);
  ht.add(8, 80);
  ht.add(15, 150);

  expect(ht.size() == 3, "hashtable size after add");
  expect(ht.exists(1) && ht.exists(8) && ht.exists(15),
         "hashtable exists for inserted keys");
  expect(ht.get(8) == 80, "hashtable get existing key");

  expect(ht.remove(8), "hashtable remove existing key");
  expect(!ht.exists(8), "hashtable removed key should not exist");
  expect(!ht.remove(999), "hashtable remove missing key");

  for (int i = 100; i < 130; ++i) {
    ht.add(i, i * 2);
  }

  expect(ht.capacity() > initial_capacity, "hashtable should rehash/grow");
  expect(ht.exists(127) && ht.get(127) == 254, "hashtable value after rehash");
}

void test_binary_tree() {
  binary_tree<int> tree;
  const int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
  for (int v : values) {
    tree.insert(v);
  }

  expect(tree.get_node_count() == 9, "binary_tree node count");
  expect(tree.is_in_tree(6), "binary_tree contains existing value");
  expect(!tree.is_in_tree(2), "binary_tree missing value");
  expect(tree.get_min() == 1, "binary_tree min value");
  expect(tree.get_max() == 14, "binary_tree max value");
  expect(tree.get_height(8) == 3, "binary_tree root height");
  expect(tree.get_height(42) == -1, "binary_tree missing node height");

  tree.delete_value(13);
  expect(!tree.is_in_tree(13), "binary_tree delete leaf node");
  expect(tree.get_node_count() == 8, "binary_tree node count after delete");
}

void test_avl_tree() {
  avl_tree<int> tree;
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);

  expect(tree.depth(2) == 0, "avl_tree root depth after rotation");
  expect(tree.depth(1) == 1 && tree.depth(3) == 1,
         "avl_tree child depths after rotation");
  expect(tree.height(2) == 1, "avl_tree root height");
  expect(tree.height(1) == 0 && tree.height(3) == 0,
         "avl_tree leaf heights");
  expect(tree.height(42) == -1, "avl_tree missing node height");

  tree.delete_node(1);
  expect(tree.height(1) == -1, "avl_tree delete leaf node");
}

} // namespace

int main() {
  test_array();
  test_list();
  test_queue();
  test_hashtable();
  test_binary_tree();
  test_avl_tree();

  std::cout << "All tests passed." << std::endl;
  return 0;
}
