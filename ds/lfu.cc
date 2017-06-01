/**
 *  LFU
 *  ===
 *
 *  Cache: Least frequently used in O(1) time (if no map conflicts & rehashing).
 *
 *  head_                                     tail_
 *    |                                         |
 *    v                                         v
 *  | prev_; LinkedHashSet; next_; | | | | | | | |
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <unordered_map>
#include <list>

template <typename K> class freq;

template <typename K>
class freq_node {
public:
    freq_node(int f, freq_node *prev, freq_node *next)
        : f_(f), prev_(prev), next_(next)  { /* nop */ }
    ~freq_node() { /* nop */ }

    // No copy and move.
    freq_node(const freq_node&) = delete;
    freq_node& operator=(const freq_node&) = delete;
    freq_node(freq_node&&) = delete;
    freq_node& operator=(freq_node&&) = delete;

    friend freq<K>;

    void
    add_key(K k)
    {
        kq_.emplace_front(k);
        kis_.emplace(k, kq_.begin());
    }

    void
    remove_key(K k)
    {
        auto it = kis_[k];
        kis_.erase(k);
        kq_.erase(it);
    }

    void
    remove_last_key()
    {
        auto it = kq_.begin();
        kis_.erase(*it);
        kq_.erase(it);
    }
private:
    int f_;
    freq_node<K> *prev_;
    freq_node<K> *next_;
    // list + unordered_map = LinkedHashSet in Java.
    std::list<K> kq_;   // emplace_front() + pop_back() for convenience of using
                        // std::list<K>::begin()
    // Key-iterator store.
    std::unordered_map<K, typename std::list<K>::iterator> kis_;
};

template <typename K>
class freq {
public:
    freq() : head_(NULL), tail_(NULL) { /* nop */ };
    ~freq() { /* nop */ }

    // No copy and move.
    freq(const freq&) = delete;
    freq& operator=(const freq&) = delete;
    freq(freq&&) = delete;
    freq& operator=(freq&&) = delete;

    void
    add_last(K k)
    {
        if (tail_ == NULL) head_ = tail_ = new freq_node<K>(1, NULL, NULL);
        if (tail_->f_ != 1) {
            auto temp = new freq_node<K>(1, tail_, NULL);
            tail_->next_ = temp;
            tail_ = temp;
        }
        tail_->add_key(k);
        kfs_.emplace(k, tail_);
    }

    void
    inc(K k)
    {
        kfs_.erase(k);
        auto n = kfs_[k];
        n->remove_key(k);

        if (head_ == n) {
            auto temp = new freq_node<K>(n->f_ + 1, NULL, head_);
            head_->prev_ = temp;
            head_ = temp;
            kfs_.emplace(k, head_);
            head_->add_key(k);
        } else if (n->prev_->f_ != n->f_ + 1) {
            auto temp = new freq_node<K>(n->f_ + 1, n->prev_, n);
            n->prev_ = temp;
            n->prev_->next_ = temp;
            kfs_.emplace(k, temp);
            temp->add_key(k);
        } else {
            kfs_.emplace(k, n->prev_);
            n->prev_->add_key(k);
        }

        if (n->kq_.empty()) {
            if (n == tail_) {
                tail_ = n->prev_;
                tail_->next_ = NULL;
            } else {
                n->prev_->next_ = n->next_;
                n->next_->prev_ = n->prev_;
            }
            delete n;
        }
    }

    void
    remove_last()
    {
        if (tail_->kq_.size() > 1) tail_->remove_last_key();
        else {
            tail_ = tail_->prev_;
            delete tail_->next_;
            tail_->next_ = NULL;
        }
    }
private:
    freq_node<K> *head_;
    freq_node<K> *tail_;
    std::unordered_map<K, freq_node<K>*> kfs_;   // key-frequency store
};

template <typename K, typename V>
class lfu {
public:
    lfu() : capacity_(2) { /* nop */ }
    explicit lfu(int capacity) : capacity_(capacity) { /* nop */ }
    ~lfu() { /* nop */ }

    // No copy and move.
    lfu(const lfu&) = delete;
    lfu& operator=(const lfu&) = delete;
    lfu(lfu&&) = delete;
    lfu& operator=(lfu&&) = delete;

    unsigned size() const { return siz_; }

    V
    get(K k)
    {
        V v = kvs_[k];
        fq_.inc(k);
        return v;
    }

    void
    set(K k, V v)
    {
        auto q = kvs_.find(k);

        if (q == kvs_.end()) {
            fq_.add_last(k);
            kvs_.emplace(k, v);
        } else kvs_[k] = v;

        if (siz_ + 1 == capacity_) fq_.remove_last();
        else ++siz_;
    }
private:
    unsigned siz_{0};
    unsigned capacity_;
    std::unordered_map<K, V> kvs_;  // key-value store
    freq<K> fq_;                    // frequency queue
};

int
main(int argc, const char *argv[])
{
    lfu<int, int> cache{4};

    cache.set(1, 42);
    cache.set(2, 3);
    cache.set(3, 4);
    cache.set(4, 5);

    std::cout << cache.get(1) << std::endl;

    // cache.set(5, 6);
    // std::cout << cache.get(2) << std::endl; // now {2: 3} has gone

    // cache.get(6);

    return 0;
}
