#ifndef _QUEUE_XIE
#define _QUEUE_XIE
#include "list.h"
#include <memory>
namespace leexxq {
template <class T> class queue {
  using link_ptr = leexxq::link<T> *;

private:
  link_ptr head;
  link_ptr tail;

public:
  queue() : head(nullptr), tail(nullptr) {}
  queue(const queue<T> &q) = delete;
  queue<T> &operator=(const queue<T> &q) = delete;
  queue(const queue<T> &&q)
      : head(std::move(q.head)), tail(std::move(q.tail)) {}
  queue<T> &operator=(const queue<T> &&q) {
    tail = q.tail;
    head = q.head;
  }
  ~queue();
  void enqueue(const T &value); // —— 在可容的情况下添加元素到尾部
  T dequeue();                  // —— 删除最早添加的元素并返回其值
  bool empty() const { return head == nullptr; }
  void full(const size_t &num, const T &value); // —— 填充队列
};
template <class T> queue<T>::~queue() {
  while (head != nullptr) {
    link<T> *t = head;
    head = head->next;
    delete t;
  }
}
template <class T> inline void queue<T>::enqueue(const T &value) {
  if (head == nullptr) {
    head = new link<T>(value);
    tail = head;
  } else {
    tail->next = new link<T>(value);
    tail = tail->next;
  }
}
template <class T> inline T queue<T>::dequeue() {
  T value;
  if (head != nullptr) {
    link_ptr t = head->next;
    value = head->data;
    delete head;
    head = t;
  }
  return value;
}
template <class T>
inline void queue<T>::full(const size_t &num, const T &value) {
  for (size_t i = 0; i < num; ++i) {
    enqueue(value);
  }
}

} // namespace xie
#endif
