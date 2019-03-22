/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.22
 */

#ifndef __ALGO_LRU_CACHE_HPP
#define __ALGO_LRU_CACHE_HPP

#include <list>
#include <unordered_map>
#include <utility>
#include <functional>

namespace algo {
    template <class K, class V>
    class LRUCache {
    public:
        // using ReleaseCallback = std::function<void (const V& v)>;
        typedef void ReleaseCallback(const V& v);

        LRUCache(std::size_t capacity, ReleaseCallback* callback = nullptr);
        ~LRUCache();

        LRUCache(const LRUCache&) = delete;
        LRUCache& operator= (const LRUCache&) = delete;

        void Put(const K& k, const V& v);
        bool Get(const K& k, V& v);
        bool Erase(const K& k);
        void ClearAll();
        std::size_t Size() const;

    private:
        std::size_t      cap_;
        ReleaseCallback* callback_;
        std::list<std::pair<K, V> >  data_;
        typedef typename std::list< std::pair<K, V> >::iterator Iterator;
        std::unordered_map<K, Iterator> map_;
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
    void LRUCache<K, V>::Put(const K& k, const V& v)
    {
        auto it = map_.find(k);
        if (it != map_.end()) {
            if (callback_ != nullptr) {
                // callback_(it->second->second);
            }

            it->second->second = v;
            data_.splice(data_.begin(), data_, it->second);
        }
        else {
            if (data_.size() >= cap_) {
                auto tmp = data_.rbegin()->first;
                data_.erase(map_[tmp]);
                map_.erase(tmp);
            }

            data_.push_front(std::make_pair(k, v));
            map_[k] = data_.begin();
        }
    }

    template <class K, class V>
    bool LRUCache<K, V>::Get(const K& k, V& v)
    {
        auto it = map_.find(k);
        if (it != map_.end()) {
            v = it->second->second;
            data_.splice(data_.begin(), data_, it->second);
            return true;
        }

        return false;
    }

    template <class K, class V>
    bool LRUCache<K, V>::Erase(const K &k)
    {
        auto it = map_.find(k);
        if (it != map_.end()) {

            data_.erase(it->second);
            map_.erase(it);
            return true;
        }
        return false;
    }

    template <class K, class V>
    void LRUCache<K, V>::ClearAll()
    {
        if (callback_ != nullptr) {
            auto it = data_.begin();
            for (it; it != data_.end(); ++it) {
                callback_(it->second);
            }
        }

        data_.clear();
        map_.clear();
    }

    template <class K, class V>
    std::size_t LRUCache<K, V>::Size() const
    {
        return data_.size();
    }

}
#endif // __ALGO_LRU_CACHE_HPP
/* EOF */
