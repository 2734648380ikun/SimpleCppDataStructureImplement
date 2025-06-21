#ifndef _HASHTABLE_XIE
#define _HASHTABLE_XIE
#include "array.h"
#include <memory>
namespace xie {
constexpr size_t _MIN_HASHTABLE = 7;
template <class T_key, class T_value> class hashtable {
private:
  enum EntryType { ACTIVE, DELETED, EMPTY };
  struct object {
    T_value value;
    T_key key;
    EntryType info;
    object() : info(EMPTY) {}
    object(const object &ob) : value(ob.value), key(ob.key), info(ob.info) {}
    object &operator=(const object &ob) {
      value = ob.value;
      key = ob.key;
      info = ob.info;
      return *this;
    }
  };
  array<object> _hashtable;
  size_t size_table;
  size_t find(const T_key &key) const;
  void rehash();

public:
  hashtable() : _hashtable(array<object>()), size_table(0) {
    _hashtable.resize(_MIN_HASHTABLE);
  }
  hashtable(const hashtable<T_key, T_value> &hb)
      : _hashtable(array<object>(hb._hashtable)), size_table(hb.size_table) {}
  ~hashtable() = default;
  size_t hash(const T_key &key) const { return key % capacity(); }
  size_t capacity() const { return _hashtable.size(); }
  size_t size() const { return size_table; }
  void add(const T_key &key, const T_value &value);
  bool exists(const T_key &key) const;
  T_value &get(const T_key &key) const;
  bool remove(const T_key &key);
};

template <class T_key, class T_value>
size_t hashtable<T_key, T_value>::find(const T_key &key) const {
  size_t currentPos = hash(key);
  while (_hashtable[currentPos].info != EMPTY &&
         _hashtable[currentPos].key != key) {
    size_t offset = 1;
    currentPos += offset;
    currentPos %= _hashtable.size();
  }
  return currentPos;
}
template <class T_key, class T_value>
void hashtable<T_key, T_value>::add(const T_key &key, const T_value &value) {
  size_t pos = find(key);
  _hashtable[pos].info = ACTIVE;
  _hashtable[pos].key = key;
  _hashtable[pos].value = value;
  ++size_table;
  rehash();
}
template <class T_key, class T_value>
bool hashtable<T_key, T_value>::exists(const T_key &key) const {
  size_t pos = find(key);
  object t = _hashtable.at(pos);
  return t.info == ACTIVE;
}
template <class T_key, class T_value>
inline T_value &hashtable<T_key, T_value>::get(const T_key &key) const {
  size_t pos = find(key);
  return _hashtable[pos].value;
}
template <class T_key, class T_value>
bool hashtable<T_key, T_value>::remove(const T_key &key) {
  if (!exists(key))
    return false;
  size_t pos = find(key);
  _hashtable.at(pos).info = DELETED;
  --size_table;
  return true;
}

template <class T_key, class T_value> void hashtable<T_key, T_value>::rehash() {
  if (2 * size_table >= capacity()) {
    array<object> t = _hashtable;
    _hashtable = array<object>(object(), capacity() * 2);
    _hashtable.resize(capacity());
    size_table = 0;
    for (size_t i = 0; i < t.size(); ++i) {
      if (t[i].info == ACTIVE) {
        add(t[i].key, t[i].value);
      }
    }
  }
}
} // namespace xie

#endif
