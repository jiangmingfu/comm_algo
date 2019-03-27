/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.27
 */

#ifndef __ALGO_SKIPLIST_HPP__
#define __ALGO_SKIPLIST_HPP__

#include <stdint.h>
#include <functional>
#include <vector>
#include <time.h>
#include "algo_allocator.h"

namespace algo {

    // 跳表
    template <class Key, class Comparator>
    class Skiplist {
    public:
        struct Node;

        Skiplist(int32_t max_level);
        ~Skiplist();

        Skiplist(const Skiplist&) = delete;
        Skiplist& operator= (const Skiplist&) = delete;

        void Insert(const Key& k);
        bool IsContain(const Key& k);
        bool Erase(const Key& k);
        std::vector<Key> Range(const Key& k1, const Key& k2);

    protected:
        void FindLastLessOrEqual(const Key& k, Node* prev[]);
        void FindLastLess(const Key& k, Node* prev[]);
        Node* CreateNode(const Key& k, int level);
        int32_t RandLevel();

    private:
        static const int branch_num_ = 4;
        int max_level_;
        Node* head_;
        const Comparator comp_;
    };

    template <class Key, class Comparator>
    struct Skiplist<Key, Comparator>::Node {
        Key k;
        int32_t level;
        Node* next[0];
    };

    template <class Key, class Comparator>
    Skiplist<Key, Comparator>::Skiplist(int32_t max_level)
    : max_level_(max_level)
    {
        head_ = CreateNode(Key(), max_level);
    }

    template <class Key, class Comparator>
    Skiplist<Key, Comparator>::~Skiplist()
    {
        Node* p = head_;
        Node* tmp = nullptr;
        while (p != nullptr) {
            tmp = p->next[0];
            Allocator::DeallocateMem(p);
            p = tmp;
        }
    }

    template <class Key, class Comparator>
    void Skiplist<Key, Comparator>::Insert(const Key& k)
    {
        Node* prev[max_level_] = {0};
        FindLastLessOrEqual(k, prev);

        // repeated element
        if (comp_(prev[0]->k, k) == 0) {
            return;
        }

        int level = RandLevel();
        Node* new_node = CreateNode(k, level);

        for (int l = 0; l < level; ++l) {
            new_node->next[l] = prev[l]->next[l];
            prev[l]->next[l] = new_node;
        }
    }

    template <class Key, class Comparator>
    bool Skiplist<Key, Comparator>::IsContain(const Key& k)
    {
        Node* prev[max_level_] = {0};
        FindLastLessOrEqual(k, prev);
        return (comp_(prev[0]->k, k) == 0);
    }

    template <class Key, class Comparator>
    bool Skiplist<Key, Comparator>::Erase(const Key& k)
    {
        Node* prev2[max_level_] = {0};
        FindLastLess(k, prev2);
        if (prev2[0]->next[0] == nullptr) {
            return true;
        }

        if (prev2[0]->next[0] != nullptr && comp_(prev2[0]->next[0]->k, k) != 0) {
            return true;
        }

        Node* del_node = prev2[0]->next[0];
        int level = prev2[0]->next[0]->level;
        for (int l = 0; l < level; ++l) {
            if (prev2[l] == nullptr || prev2[l]->next[l] == nullptr) {
                prev2[l] = nullptr;
            }
            else {
                prev2[l] = prev2[l]->next[l]->next[l];
            }
        }

        Allocator::DeallocateObj(del_node);
        return true;
    }

    template <class Key, class Comparator>
    std::vector<Key> Skiplist<Key, Comparator>::Range(const Key& k1, const Key& k2)
    {
        std::vector<Key> result;
        Node* prev[max_level_] = {0};
        FindLastLess(k1, prev);

        if (prev[0] != nullptr) {
            Node* cursor = prev[0]->next[0];
            while (cursor != nullptr && comp_(cursor->k, k1) >= 0 &&
                    comp_(cursor->k, k2) <= 0) {
                result.emplace_back(cursor->k);
                cursor = cursor->next[0];
            }
        }
        return result;
    }

    template <class Key, class Comparator>
    typename Skiplist<Key, Comparator>::Node* Skiplist<Key, Comparator>::CreateNode(const Key& k, int level)
    {
        size_t len = sizeof(Node) + sizeof(Node*) * level;
        void* ptr = Allocator::AllocateMem(1, len);
        Node* node = new (ptr) Node();

        node->k = k;
        node->level = level;
        return node;
    }

    template <class Key, class Comparator>
    int32_t Skiplist<Key, Comparator>::RandLevel()
    {
        int level = 0;
        srand(time(nullptr));
        while (level < max_level_ && rand()%branch_num_ == 0) {
            ++level;
        }
        return level;
    }

    template <class Key, class Comparator>
    void Skiplist<Key, Comparator>::FindLastLessOrEqual(const Key& k, Node* prev[])
    {
        for (int level = max_level_ - 1; level >= 0; --level) {
            prev[level] = head_;
            while (prev[level]->next[level] != nullptr &&
            comp_(prev[level]->next[level]->k, k) < 0) {
                prev[level] = prev[level]->next[level];

            }
        }
    }

    template <class Key, class Comparator>
    void Skiplist<Key, Comparator>::FindLastLess(const Key& k, Node* prev[])
    {
        for (int level = max_level_ - 1; level >= 0; --level) {
            prev[level] = head_;
            while (prev[level]->next[level] != nullptr &&
                   comp_(prev[level]->next[level]->k, k) <= 0) {
                prev[level] = prev[level]->next[level];

            }
        }
    }

}
#endif // __ALGO_SKIPLIST_HPP__
/* EOF */
