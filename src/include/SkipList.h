#ifndef SKIPLIST_BSKIPLIST_H
#define SKIPLIST_BSKIPLIST_H
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <vector>

namespace BSkipList {

template <typename K, typename V>
class Node {
 public:
  Node(const K key, const V value, int level) : key_(key), value_(value), level_(level), forward_(level, nullptr) {}

  K GetKey() const { return key_; }

  V GetValue() const { return value_; }

  void SetValue(V value) { value_ = value; }

  /** Store the pointers to the next nodes in each level */
  std::vector<std::shared_ptr<Node<K, V>>> forward_;

 private:
  K key_;
  V value_;
  /** The level of the node */
  int level_;
};

template <typename K, typename V>
using NodeVec = std::vector<std::shared_ptr<Node<K, V>>>;

template <typename K, typename V>
class SkipList {
 public:
  explicit SkipList(int max_level, double skiplist_p)
      : curr_level_(0),
        max_level_(max_level),
        header_(std::make_shared<Node<K, V>>(K(), V(), max_level)),
        size_(0),
        SKIPLIST_P(skiplist_p),
        mt_(std::random_device{}()),
        dis_(0, 0xFFFF){};
  void insert(K, V);
  void remove(K key);
  bool find(K key, V &value);
  int size() const;
  void Print() const;

 private:
  int getRandLevel();

  double SKIPLIST_P;
  int curr_level_;
  int max_level_;
  std::shared_ptr<Node<K, V>> header_;
  int size_;
  std::mutex mutex_;
  /** Random number generator */
  std::mt19937 mt_;
  std::uniform_int_distribution<int> dis_;
};

/** Template implementation can't write in a seperated file */

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
  // Reach the bottom level
  cur = cur->forward_[0];

  // If the key already exists, update the value
  if (cur != nullptr && cur->GetKey() == key) {
    cur->SetValue(value);
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
void SkipList<K, V>::remove(K key) {
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
  if (cur != nullptr && cur->GetKey() == key) {
    for (int i = 0; i <= curr_level_; i++) {
      if (update[i]->forward_[i] != cur) {
        break;
      }
      update[i]->forward_[i] = cur->forward_[i];
    }
    while (curr_level_ > 0 && header_->forward_[curr_level_] == nullptr) {
      curr_level_--;
    }
    size_--;
  }
}

template <typename K, typename V>
bool SkipList<K, V>::find(K key, V &value) {
  std::scoped_lock lock(mutex_);
  auto cur = header_;
  for (int i = curr_level_; i >= 0; i--) {
    while (cur->forward_[i] != nullptr && cur->forward_[i]->GetKey() < key) {
      cur = cur->forward_[i];
    }
  }
  cur = cur->forward_[0];
  if (cur != nullptr && cur->GetKey() == key) {
    value = cur->GetValue();
    return true;
  }
  return false;
}

template <typename K, typename V>
int SkipList<K, V>::size() const {
  return size_;
}

template <typename K, typename V>
void SkipList<K, V>::Print() const {
  std::cout << "\n*****Skip List*****"
            << "\n";
  for (int i = 0; i <= curr_level_; i++) {
    auto node = header_->forward_[i];
    std::cout << "Level " << i << ": ";
    while (node != nullptr) {
      std::cout << node->GetKey() << ": " << node->GetValue() << "; ";
      node = node->forward_[i];
    }
    std::cout << std::endl;
  }
}

template <typename K, typename V>
int SkipList<K, V>::getRandLevel() {
  int level = 1;
  while (dis_(mt_) < SKIPLIST_P * 0xFFFF && level <= max_level_) {
    level++;
  }
  return level;
}

}  // namespace BSkipList

#endif  // SKIPLIST_BSKIPLIST_H
