/*
 *  @Author jiangmingfu
 *  @Date   2019.3.18
 */

#ifndef __ALGO_DOUBLE_CIRCULAR_LIST_HPP__
#define __ALGO_DOUBLE_CIRCULAR_LIST_HPP__

#include "algo_allocator.h"

namespace algo {

    // 双向循环链表
    template <class T>
    class DoubleCircularList {
    public:
        struct Node;
        class Iterator;

        DoubleCircularList();
        ~DoubleCircularList();

        Node* InsertTail(const T& v);
        Node* InsertHead(const T& v);
        Node* InsertAfter(Node& node, const T& v);
        Node* InsertBefore(Node& node, const T& v);

        Node* Find(const T& v) const;
        void  Delete(Node* node);
        void  DeleteAll();

        Iterator Begin();
        Iterator Begin() const;

        Iterator End();
        Iterator End() const;

        Iterator RBegin();
        Iterator RBegin() const;

        Iterator REnd();
        Iterator REnd() const;

    protected:
        Node* CreateHeadNode();
        void  DeleteHeadNode();
        Node* AllocateNode(const T& v);
        void  DeallocateNode(Node* ptr);

    private:
        Node* guard_;
    };

    template <class T>
    struct DoubleCircularList<T>::Node {
        T     v;
        Node* next;
        Node* pre;

        Node()
        : v(T())
        , next(nullptr)
        , pre(nullptr)
        {}
    };

    template <class T>
    class DoubleCircularList<T>::Iterator {
    public:
        Iterator(Node* node, bool is_forward)
        : node_(node)
        , is_forward_(is_forward)
        {}

        ~Iterator() = default;

        T& operator* ()
        {
            return node_->v;
        }

        const T& operator* () const
        {
            return node_->v;
        }

        void operator++ ()
        {
            if (is_forward_) {
                node_ = node_->next;
            }
            else {
                node_ = node_->pre;
            }
        }

        bool operator == (const Iterator& obj) const
        {
            if (node_ == obj.node_ && is_forward_ == obj.is_forward_) {
                return true;
            }
            return false;
        }

        bool operator != (const Iterator& obj) const
        {
            return !(*this == obj);
        }

    private:
        Node* node_;
        bool is_forward_;
    };

    template <class T>
    DoubleCircularList<T>::DoubleCircularList()
    {
        guard_ = CreateHeadNode();
    }

    template <class T>
    DoubleCircularList<T>::~DoubleCircularList()
    {
        DeleteAll();
        DeleteHeadNode();
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::InsertTail(const T& v)
    {
       return InsertBefore(*guard_, v);
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::InsertHead(const T& v)
    {
        return InsertAfter(*guard_, v);
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::InsertAfter(Node& node, const T& v)
    {
        Node* new_node = AllocateNode(v);
        new_node->next = guard_->next;
        new_node->pre = guard_;

        node.next->pre = new_node;
        node.next = new_node;

        return new_node;
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::InsertBefore(Node& node, const T& v)
    {
        Node* new_node = AllocateNode(v);
        new_node->next = guard_;
        new_node->pre = guard_->pre;

        node.pre->next = new_node;
        node.pre = new_node;

        return new_node;
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::Find(const T& v) const
    {
        Node* node = guard_->next;

        while (node != guard_) {
            if (node->v == v) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    template <class T>
    void DoubleCircularList<T>::Delete(Node* node)
    {
        node->pre->next = node->next;
        node->next->pre = node->pre;

        delete node;
    }

    template <class T>
    void DoubleCircularList<T>::DeleteAll()
    {
        Node* node = guard_->next;
        while (node != guard_) {
            node = node->next;
            delete node->pre;
        }
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::Begin()
    {
        return Iterator(guard_->next, true);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::Begin() const
    {
        return Iterator(guard_->next, true);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::End()
    {
        return Iterator(guard_, true);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::End() const
    {
        return Iterator(guard_, true);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::RBegin()
    {
        return Iterator(guard_->pre, false);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::RBegin() const
    {
        return Iterator(guard_->pre, false);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::REnd()
    {
        return Iterator(guard_, false);
    }

    template <class T>
    typename DoubleCircularList<T>::Iterator DoubleCircularList<T>::REnd() const
    {
        return Iterator(guard_, false);
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::CreateHeadNode()
    {
        Node* node = AllocateNode(T());
        node->pre = node;
        node->next = node;
        return  node;
    }

    template <class T>
    void DoubleCircularList<T>::DeleteHeadNode()
    {
        if (guard_ != nullptr) {
            DeallocateNode(guard_);
            guard_ = nullptr;
        }
    }

    template <class T>
    typename DoubleCircularList<T>::Node* DoubleCircularList<T>::AllocateNode(const T& v)
    {
        Node* ptr = Allocator::AllocateObj<Node>();
        if (ptr != nullptr) {
            ptr->v = v;
        }
        return ptr;
    }

    template <class T>
    void DoubleCircularList<T>::DeallocateNode(Node* ptr)
    {
        if (ptr != nullptr) {
            Allocator::DeallocateObj(ptr);
        }
    }
}
#endif // __ALGO_DOUBLE_CIRCULAR_LIST_HPP__
/* EOF */
