#ifndef SKIPLIST_BSKIPLIST_H
#define SKIPLIST_BSKIPLIST_H
#include <vector>
#include <memory>

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
    class SkipList {
    public:
        SkipList(int);
        ~SkipList();
        void insert(K key, V value);
        void remove(K key);
        int search(K key);
        void print();

    private:
        int curr_level_;
        int maxLevel_;
        std::shared_ptr<Node<K, V>> header_;
    };
}

#endif //SKIPLIST_BSKIPLIST_H
