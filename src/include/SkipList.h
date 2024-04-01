#ifndef SKIPLIST_BSKIPLIST_H
#define SKIPLIST_BSKIPLIST_H
#include <memory>
#include <mutex>
#include <random>
#include <vector>

namespace BSkipList {

template <typename K, typename V>
class Node {
 public:
  Node(const K key, const V value, int level) : key_(key), value_(value), level_(level), forward_(level, nullptr) {}

  K getKey() const { return key_; }

  V getValue() const { return value_; }

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
        SKIPLIST_P(skiplist_p),
        mt_(std::random_device{}()),
        dis_(0, 0xFFFF){};
  void insert(K, V);
  void remove(K key);
  bool exist(K key);

 private:
  int getRandLevel();

  double SKIPLIST_P;
  int curr_level_;
  int max_level_;
  std::shared_ptr<Node<K, V>> header_;
  std::mutex mutex_;
  /** Random number generator */
  std::mt19937 mt_;
  std::uniform_int_distribution<int> dis_;
};

}  // namespace BSkipList

#endif  // SKIPLIST_BSKIPLIST_H
