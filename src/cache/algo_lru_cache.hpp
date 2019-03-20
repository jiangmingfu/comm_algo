/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.20
 */

#ifndef __ALGO_LRU_CACHE_HPP
#define __ALGO_LRU_CACHE_HPP

#include <functional>
#include <unordered_map>
#include <list>

namespace algo {
    template <class K, class V>
    class LRUCache {
    public:
        using ReleaseCallback = std::function<void (V* v)>();

        LRUCache(std::size_t capacity, ReleaseCallback* callback = nullptr);
        ~LRUCache();

        LRUCache(const LRUCache&) = delete;
        LRUCache& operator= (const LRUCache&) = delete;

        void Put(const K& k, V* v);
        bool Get(const K& k, V** v);
        void ClearAll();
        std::size_t Size() const;

    private:
        void Remove(const K& k);

    private:
        std::size_t      cap_;
        ReleaseCallback* callback_;
        std::unordered_map<K, V*> data_;
        std::list<typename std::unordered_map<K, V*>::iterator> list_;
    };

    template <class K, class V>
    LRUCache<K, V>::LRUCache(std::size_t item_size, LRUCache<K, V>::ReleaseCallback* callback)
    : cap_(item_size)
    ,callback_(callback)
    {

    }

    template <class K, class V>
    LRUCache<K, V>::~LRUCache()
    {
        ClearAll();
    }

    template <class K, class V>
    void LRUCache<K, V>::Put(const K& k, V* v)
    {
        if (data_.count(k) > 0) {
            if (callback_ != nullptr) {
                callback_(data_[k]);
            }
            data_[k] = v;
        }
        else {
            if (data_.size() >= cap_) {

            }
        }
    }

    template <class K, class V>
    bool LRUCache<K, V>::Get(const K& k, V** v)
    {
        if (data_.count(k) > 0) {
            *v = data_[k];
            return true;
        }
        return false;
    }

    template <class K, class V>
    void LRUCache<K, V>::Remove(const K& k)
    {
        if (data_.count(k) > 0) {
            if (callback_) {
                callback_(data_[k]);
            }
            list_.erase(data_.find(k));
        }
    }

    template <class K, class V>
    void LRUCache<K, V>::ClearAll()
    {
        if (callback_ != nullptr) {

        }
    }

    template <class K, class V>
    std::size_t LRUCache<K, V>::Size() const
    {
        return data_.size();
    }

}
#endif // __ALGO_LRU_CACHE_HPP
/* EOF */
