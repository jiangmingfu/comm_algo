/**
 *
 * @Author jiangmingfu
 * @Date  2019.04.01
 */


#ifndef __ALGO_HEAP_SORT_HPP__
#define __ALGO_HEAP_SORT_HPP__

#include <stdint.h>
#include <functional>
#include "algo_allocator.h"

namespace algo {

    // 堆排序
    template <class T, class Comparator>
    class BinaryHeap {
    public:
        BinaryHeap(int32_t capacity);
        ~BinaryHeap();

        BinaryHeap(const BinaryHeap&) = delete;
        BinaryHeap& operator= (const BinaryHeap&) = delete;

        // 从后往前建堆，从上往下调整
        bool CreateHeap(T* d, int32_t n);

        // 从前往后建堆，从下往上调整
        bool CreateHeap2(T* d, int32_t n);
        bool Insert(const T& v);
        T* Top() const;
        void PopTop();
        void UpdateTop(const T& v);

        int32_t Size() const;

    protected:
        void AdjustHeapDown(int32_t i, int32_t k);
        void AdjustHeapUp(int32_t i, int32_t k);

    private:
        T* ptr_;
        int32_t num_;
        int32_t capacity_;
        Comparator comp_;
    };

    template <class T, class Comparator>
    BinaryHeap<T, Comparator>::BinaryHeap(int32_t capacity)
    : ptr_(nullptr)
    , num_(0)
    , capacity_(0)
    {
        ptr_ = Allocator::AllocateMultiObjs(capacity);
        capacity_ = capacity;
        num_ = 0;
    }

    template <class T, class Comparator>
    BinaryHeap<T, Comparator>::~BinaryHeap()
    {
        if (ptr_ != nullptr) {
            Allocator::DeallocMultiObjs(ptr_);
            ptr_ = nullptr;
        }
    }

    template <class T, class Comparator>
    bool BinaryHeap<T, Comparator>::CreateHeap(T* d, int32_t n)
    {
        if (n > capacity_) {
            return false;
        }

        for (int i = 0; i < n; ++i) {
            ptr_[i] = d[i];
        }
        num_ = n;

        for (int i = (n - 1)/2; i >= 0; --i) {
            AdjustHeapDown(i, num_ - 1);
        }
    }

    template <class T, class Comparator>
    bool BinaryHeap<T, Comparator>::CreateHeap2(T* d, int32_t n)
    {
        if (n > capacity_) {
            return false;
        }

        num_ = 0;
        for (int32_t i = 0; i < n; ++i) {
            Insert(d[i]);
        }
        return true;
    }

    template <class T, class Comparator>
    bool BinaryHeap<T, Comparator>::Insert(const T& v)
    {
        if (num_ < capacity_) {
            ptr_[num_++] = v;
            AdjustHeapUp(num_ - 1, 0);
            return true;
        }
        return false;
    }

    template <class T, class Comparator>
    T* BinaryHeap<T, Comparator>::Top() const
    {
        if (num_ > 0) {
            return &ptr_[0];
        }
        return nullptr;
    }

    template <class T, class Comparator>
    void BinaryHeap<T, Comparator>::PopTop()
    {
        ptr_[0] = ptr_[num_-1];
        --num_;
        AdjustHeapDown(0, num_ - 1);
    }

    template <class T, class Comparator>
    void BinaryHeap<T, Comparator>::UpdateTop(const T& v)
    {
        ptr_[0] = v;
        AdjustHeapDown(0, num_ - 1);
    }

    template <class T, class Comparator>
    void BinaryHeap<T, Comparator>::AdjustHeapDown(int32_t i, int32_t k)
    {
        if (i <= k) {
            int max_id = i;
            if ((2*i + 1) <= k && comp_(ptr_[i], ptr_[2*i+1]) < 0) {
                max_id = 2*i + 1;
            }

            if ((2*i+2) <= k && comp_(ptr_[max_id], ptr_[2*i+2]) < 0) {
                max_id = 2*i + 2;
            }

            if (i != max_id) {
                std::swap(ptr_[i], ptr_[max_id]);
                AdjustHeapDown(max_id, k);
            }
        }
    }

    template <class T, class Comparator>
    void BinaryHeap<T, Comparator>::AdjustHeapUp(int32_t i, int32_t k)
    {
        if (i >= k) {
            int parent_id = (i-1)/2;
            if (parent_id >= k && comp_(parent_id, ptr_[i]) < 0) {
                std::swap(ptr_[parent_id], ptr_[i]);
                AdjustHeapUp(parent_id, k);
            }
        }
    }

    template <class T, class Comparator>
    int32_t BinaryHeap<T, Comparator>::Size() const
    {
        return num_;
    }
}

#endif // __ALGO_HEAP_SORT_HPP__
/* EOF */