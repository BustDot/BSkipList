#include "SkipList.h"

namespace BSkipList {
template <typename K, typename V>
void SkipList<K, V>::insert(K key, V value) {
  std::scoped_lock lock(mutex_);
}

template <typename K, typename V>
void SkipList<K, V>::remove(K key) {}

template <typename K, typename V>
bool SkipList<K, V>::exist(K key) {
  return false;
}

template <typename K, typename V>
int SkipList<K, V>::getRandLevel() {
  int level = 1;
  while (dis_(mt_) < SKIPLIST_P * 0xFFFF && level < max_level_) {
    level++;
  }
  return level;
}
}  // namespace BSkipList
