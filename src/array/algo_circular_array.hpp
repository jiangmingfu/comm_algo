/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.24
 */

#ifndef __ALGO_CIRCULAR_ARRAY_HPP__
#define __ALGO_CIRCULAR_ARRAY_HPP__

#include <stdint.h>
#include "algo_util.h"
#include "algo_allocator.h"

namespace algo {

    // 循环数组<此处使用了无符号数反转的trick>
    template <class T>
    class CircularArray {
    public:
        class Iterator;

        CircularArray(uint32_t max_elem_num);
        ~CircularArray();

        CircularArray(const CircularArray& ) = delete;
        CircularArray(CircularArray&& o);

        CircularArray& operator= (const CircularArray& ) = delete;
        CircularArray& operator= (CircularArray&& o);

        bool Push(const T& v);
        bool Pop(T& v);
        uint32_t Size() const;
        bool IsEmpty() const;
        bool IsFull()  const;
        bool Clear();

        Iterator Begin();
        const Iterator Begin() const;

        Iterator End();
        const Iterator End() const;

    protected:
        uint32_t GetRealIndex(uint32_t idx) const {
            return (idx & (cap_ - 1));
        }

    private:
        T* ptr_;
        uint32_t cap_;
        uint32_t in_idx_;
        uint32_t out_idx_;
    };

    template <class T>
    class CircularArray<T>::Iterator {
    public:
        Iterator(T* ptr, uint32_t cap, uint32_t idx)
        : ptr_(ptr)
        , cap_(cap)
        , idx_(idx)
        {

        }

        Iterator() = default;

        T& operator* ()
        {
            return ptr_[idx_ & (cap_ - 1)];
        }

        const T&operator * () const
        {
            return ptr_[idx_ & (cap_ - 1)];
        }

        void operator ++ ()
        {
            ++idx_;
        }

        bool operator == (const Iterator& o) const
        {
            if (ptr_ == o.ptr_ && cap_ == o.cap_ && idx_ == o.idx_) {
                return true;
            }
            return false;
        }

        bool operator != (const Iterator& o) const
        {
            return !(*this == o);
        }

    private:
        T* ptr_;
        uint32_t cap_;
        uint32_t idx_;
    };

    template <class T>
    CircularArray<T>::CircularArray(uint32_t max_elem_num)
    : ptr_(nullptr)
    , in_idx_(0)
    , out_idx_(0)
    {
        cap_ = Util::RoundUpPowerOfTwo(max_elem_num);
        ptr_ = Allocator::AllocateMultiObjs<T>(cap_);
    }

    template <class T>
    CircularArray<T>::~CircularArray()
    {
        if (ptr_ != nullptr) {
            Allocator::DeallocMultiObjs(ptr_);
            ptr_ = nullptr;
        }
    }

    template <class T>
    CircularArray<T>::CircularArray(CircularArray<T>&& o)
    {
        ptr_ = o.ptr_;
        cap_ = o.cap_;
        in_idx_ = o.in_idx_;
        out_idx_ = o.out_idx_;

        o.ptr_ = nullptr;
        o.cap_ = o.in_idx_ = o.out_idx_ = 0;
    }

    template <class T>
    CircularArray<T>& CircularArray<T>::operator= (CircularArray<T>&& o)
    {
        if (this == &o) {
            return *this;
        }

        if (ptr_ != nullptr) {
            Allocator::DeallocMultiObjs(ptr_);
        }

        ptr_ = o.ptr_;
        cap_ = o.cap_;
        in_idx_ = o.in_idx_;
        out_idx_ = o.out_idx_;

        o.ptr_ = nullptr;
        o.cap_ = o.in_idx_ = o.out_idx_ = 0;
        return *this;
    }

    template <class T>
    bool CircularArray<T>::Push(const T& v)
    {
        if (IsFull()) {
            return false;
        }

        ptr_[GetRealIndex(in_idx_++)] = v;
        return true;
    }

    template <class T>
    bool CircularArray<T>::Pop(T& v)
    {
        if (IsEmpty()) {
            return false;
        }

        v = ptr_[GetRealIndex(out_idx_++)];
        return true;
    }

    template <class T>
    uint32_t CircularArray<T>::Size() const
    {
        return (in_idx_ - out_idx_);
    }

    template <class T>
    bool CircularArray<T>::IsEmpty() const
    {
        return (in_idx_ == out_idx_);
    }

    template <class T>
    bool CircularArray<T>::IsFull()  const
    {
        return (in_idx_ + 1 == out_idx_);
    }

    template <class T>
    bool CircularArray<T>::Clear()
    {
        in_idx_ = out_idx_ = 0;
        return true;
    }

    template <class T>
    typename CircularArray<T>::Iterator CircularArray<T>::Begin()
    {
        return Iterator(ptr_, cap_, out_idx_);
    }

    template <class T>
    const typename CircularArray<T>::Iterator CircularArray<T>::Begin() const
    {
        return Iterator(ptr_, cap_, out_idx_);
    }

    template <class T>
    typename CircularArray<T>::Iterator CircularArray<T>::End()
    {
        return Iterator(ptr_, cap_, in_idx_);
    }

    template <class T>
    const typename CircularArray<T>::Iterator CircularArray<T>::End() const
    {
        return Iterator(ptr_, cap_, in_idx_);
    }
}
#endif // __ALGO_CIRCULAR_ARRAY_HPP__
/* EOF */
