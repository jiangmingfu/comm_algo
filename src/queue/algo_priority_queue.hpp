/**
 *
 *  @Author jiangmingfu
 *  @Date   2019.04.01
 */

#ifndef __ALGO_PRIORITY_QUEUE_HPP__
#define __ALGO_PRIORITY_QUEUE_HPP__

#include "algo_heap_sort.hpp"

namespace algo {

    // 优先级队列
    template <class T, class Comparator>
    class PriorityQueue {
    public:
        PriorityQueue(int32_t capacity);
        ~PriorityQueue() = default;

        PriorityQueue(const PriorityQueue&) = delete;
        PriorityQueue& operator= (const PriorityQueue& ) = delete;

        bool Push(const T& v);
        T*   Top();
        void Pop();
        int32_t Size() const;

    private:
        BinaryHeap<T, Comparator> heap_;
    };

    template <class T, class Comparator>
    PriorityQueue<T, Comparator>::PriorityQueue(int32_t capacity)
    : heap_(capacity)
    {
    }

    template <class T, class Comparator>
    bool PriorityQueue<T, Comparator>::Push(const T& v)
    {
        return heap_.Insert(v);
    }

    template <class T, class Comparator>
    T* PriorityQueue<T, Comparator>::Top()
    {
        return heap_.Top();
    }

    template <class T, class Comparator>
    void PriorityQueue<T, Comparator>::Pop()
    {
        heap_.PopTop();
    }

    template <class T, class Comparator>
    int32_t PriorityQueue<T, Comparator>::Size() const
    {
        return heap_.Size();
    }

}
#endif // __ALGO_PRIORITY_QUEUE_HPP__
/* EOF */
