#ifndef _LIST_XIE
#define _LIST_XIE
#include <memory>
namespace xie {
template <class T> struct link {
  T data;
  link<T> *next;
  link() : next(nullptr) {}
  link(const T &value) : data(value), next(nullptr) {}
  link(link<T> *l) : next(l) {}
  link(const T &value, link<T> *l) : data(value), next(l) {}
  link(const link<T> &&l) noexcept
      : data(std::move(l.data)), next(std::move(l.next)) {}
};
template <class T> class list {
private:
  link<T> *head;

public:
  explicit list() : head(nullptr) {}
  list(const link<T> *lk) : head(new link<T>()) {}
  list(const list<T> &l) = delete;
  list &operator=(const list &l) = delete;
  list(const list<T> &&l) noexcept : head(l.head) {}
  T &operator[](const size_t &index) const { return at(index); }
  ~list();
  size_t size() const noexcept;
  bool empty() const noexcept { return size() == 0; }
  link<T> *find(const size_t &index) const;
  T &at(const size_t &index) const;
  void push_front(const T &value);        // —— 添加元素到链表的首部
  T pop_front();                          // —— 删除首部元素并返回其值
  void push_back(const T &value);         // —— 添加元素到链表的尾部
  T pop_back();                           // —— 删除尾部元素并返回其值
  T &front() const { return head->data; } // —— 返回首部元素的值
  T &back() const;                        // —— 返回尾部元素的值
  bool
  insert(const size_t &index,
         const T
             &value); // —— 插入值到指定的索引，并把当前索引的元素指向到新的元素
  bool erase(const size_t &index); // —— 删除指定索引的节点
  size_t
  value_n_from_end(const size_t &index) const; // —— 返回倒数第 n 个节点的值
  void reverse();                              // —— 逆序链表
  bool remove_value(const T &value); // —— 删除链表中指定值的第一个元素
};

template <class T> list<T>::~list() {
  while (head != nullptr) {
    link<T> *t = head;
    head = head->next;
    delete t;
  }
}
template <class T> inline T &list<T>::at(const size_t &index) const {
  link<T> *t = head;
  for (size_t i = 0; i < index; ++i) {
    if (t != nullptr)
      t = t->next;
    else
      throw "越界！";
  }
  return t->data;
}
template <class T> inline size_t list<T>::size() const noexcept {
  size_t len = 0;
  link<T> *t = head;
  while (t != nullptr) {
    ++len;
    t = t->next;
  }
  return len;
}
template <class T> inline void list<T>::push_front(const T &value) {
  link<T> *t = head;
  head = new link<T>(value, t);
}
template <class T> inline T list<T>::pop_front() {
  link<T> *t = head;
  T value = t->data;
  if (!t)
    throw "链表无节点";
  else {
    head = head->next;
    delete t;
  }
  return value;
}
template <class T> inline void list<T>::push_back(const T &value) {
  link<T> *t = head;
  if (t != nullptr) {
    while (t->next != nullptr) {
      t = t->next;
    }
    t->next = new link<T>(value);
  } else {
    push_front(value);
  }
}
template <class T> inline T list<T>::pop_back() {
  link<T> *t = head;
  link<T> *t1 = head;
  while (t && t->next != nullptr) {
    t1 = t;
    t = t->next;
  }
  return t1->data;
}
template <class T> inline T &list<T>::back() const {
  link<T> *t = head;
  while (t && t->next != nullptr) {
    t = t->next;
  }
  return t->data;
}
template <class T> inline link<T> *list<T>::find(const size_t &index) const {
  link<T> *t = head;
  for (size_t i = 0; i < index; ++i) {
    if (!t->next)
      return nullptr;
    t = t->next;
  }
  return t;
}
template <class T>
inline bool list<T>::insert(const size_t &index, const T &value) {
  link<T> *t = head;
  if (index == 0)
    push_front(value);
  else {
    t = find(index - 1);
    if (!t)
      return false;
    link<T> *t1 = t->next;
    t->next = new link<T>(value);
    t->next->next = t1;
  }
  return true;
}
template <class T> inline bool list<T>::erase(const size_t &index) {
  link<T> *t = head;
  if (index == 0)
    pop_front();
  else {
    t = find(index - 1);
    if (t == nullptr || t->next == nullptr)
      return false;
    link<T> *t1 = t->next;
    if (t1) {
      t->next = t1->next;
      delete t1;
    }
  }
  return true;
}
template <class T> inline void list<T>::reverse() {
  link<T> *t = head;
  if (t != nullptr && t->next != nullptr) {
    link<T> *t1 = t->next;
    while (t1 != nullptr) {
      link<T> *t2 = t1->next;
      t1->next = t;
      t = t1;
      t1 = t2;
    }
    head->next = nullptr;
    head = t;
  }
}
template <class T>
inline size_t list<T>::value_n_from_end(const size_t &index) const {
  return at(size() - index - 1);
}
template <class T> inline bool list<T>::remove_value(const T &value) {
  link<T> *t = head;
  size_t i = 0;
  while (t != nullptr) {
    if (t->data == value) {
      erase(i);
      return true;
    }
    t = t->next;
    ++i;
  }
  return false;
}

} // namespace xie

#endif
