/*
#include "include/hashMap.hpp"

template <typename Key, typename Value, typename Hash, typename KeyEqual>
struct HashMap<Key, Value, Hash, KeyEqual>::Node {
        Key key;
        Value value;
        Node *next;
        Node(const Key &k, const Value &v, Node *n)
            : key(k),
              value(v),
              next(n) {}
};

template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::HashMap(size_t initBucket, double maxL)
    : buckets(initBucket, nullptr),
      bucketCount(initBucket),
      maxLoad(maxL),
      elementCount(0),
      hash(Hash()),
      keyEqual(KeyEqual()) {}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::~HashMap() {
    clear();
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
size_t HashMap<Key, Value, Hash, KeyEqual>::computeBucketIndex(const Key &key) {
    return hash(key) % bucketCount;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::rehash(size_t newBucketCount) {
    std::vector<Node *> newBuckets(newBucketCount, nullptr);
    for (size_t i = 0; i < bucketCount; ++i) {
        Node *node = buckets[i];
        while (node) {
            Node *next = node->next;
            size_t idx = hash(node->key) % newBucketCount;
            node->next = newBuckets[idx];
            newBuckets[idx] = node;
            node = next;
        }
    }
    buckets = std::move(newBuckets);
    bucketCount = newBucketCount;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::insert(const Key &key,
                                                 const Value &value) {

    if (static_cast<double>(elementCount + 1) / bucketCount > maxLoad) {
        rehash(bucketCount * 2);
    }
    size_t idx = computeBucketIndex(key);
    Node *node = buckets[idx];
    while (node) {
        if (keyEqual(node->key, key)) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    // new element is new head
    Node *newNode = new Node(key, value, buckets[idx]);
    buckets[idx] = newNode;
    ++elementCount;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashMap<Key, Value, Hash, KeyEqual>::erase(const Key &key) {
    size_t idx = computeBucketIndex(key);
    Node *node = buckets[idx];
    Node *prev = nullptr;
    while (node) {
        if (keyEqual(node->key, key)) {
            if (prev)
                prev->next = node->next;
            else
                buckets[idx] = node->next;
            delete node;
            --elementCount;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
Value *HashMap<Key, Value, Hash, KeyEqual>::find(const Key &key) {
    size_t idx = computeBucketIndex(key);
    Node *node = buckets[idx];
    while (node) {
        if (keyEqual(node->key, key))
            return &node->value;
        node = node->next;
    }
    return nullptr;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashMap<Key, Value, Hash, KeyEqual>::contains(const Key &key) {
    return find(key) != nullptr;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::clear() {
    for (size_t i = 0; i < bucketCount; ++i) {
        Node *node = buckets[i];
        while (node) {
            Node *next = node->next;
            delete node;
            node = next;
        }
        buckets[i] = nullptr;
    }
    elementCount = 0;
}
*/
