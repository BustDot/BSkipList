#include "SkipList.h"

namespace BSkipList {
template <typename K, typename V>
void SkipList<K, V>::insert(K key, V value) {
  std::scoped_lock lock(mutex_);
  auto cur = header_;
  NodeVec<K, V> update(max_level_, nullptr);

  for (int i = curr_level_; i >= 0; i--) {
    while (cur->forward_[i] != nullptr && cur->forward_[i]->GetKey() < key) {
      cur = cur->forward_[i];
    }
    update[i] = cur;
  }
  cur = cur->forward_[0];

  // If the key already exists, update the value
  if (cur != nullptr && cur->GetKey() == key) {
    cur->value_ = value;
    return;
  }

  int level = getRandLevel();
  if (level > curr_level_) {
    for (int i = curr_level_ + 1; i < level; i++) {
      update[i] = header_;
    }
    curr_level_ = level;
  }

  auto insert_node = std::make_shared<Node<K, V>>(key, value, level);
  for (int i = 0; i < level; i++) {
    insert_node->forward_[i] = update[i]->forward_[i];
    update[i]->forward_[i] = insert_node;
  }
  size_++;
}

template <typename K, typename V>
void SkipList<K, V>::remove(K key) {}

template <typename K, typename V>
bool SkipList<K, V>::exist(K key) {
  return false;
}

template <typename K, typename V>
int SkipList<K, V>::size() const {
  return size_;
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
