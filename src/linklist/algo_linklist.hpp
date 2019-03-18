/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.17
 */

#ifndef __ALGO_LINKLIST_HPP__
#define __ALGO_LINKLIST_HPP__

#include "algo_allocator.h"

namespace algo {
    template <class T>
    class LinkList {
    public:
        struct Node;
        class Iterator;

        LinkList();
        ~LinkList();

        Node* InsertTail(const T& node);
        Node* InsertHead(const T& node);
        Node* InsertAfter(const Node& node, const T& d);
        Node* InsertBefore(const Node& node, const T& d);

        bool IsEmpty() const;
        bool Delete(const T& d);
        bool DeleteAll();

        Node* Find(const T& d) const;

        // 获取反向第k个节点
        Node* GetReserveNThNode(std::size_t k) const;

        // 获取中间节点
        Node* GetMiddleNode() const;

        // 链表倒置
        bool Reverse();

        // 是否包含环
        bool IsContainLoop() const;

        Iterator Begin();
        Iterator Begin() const;

        Iterator End();
        Iterator End() const;

    protected:
        Node* AllocateNode(const T& d);
        void  DeallocateNode(Node* node);

    private:
        Node* guard_;
    };

    template <class T>
    struct LinkList<T>::Node {
        T     d;
        Node* next;

        Node()
        : d(T())
        , next(nullptr)
        {}
    };

    template <class T>
    class LinkList<T>::Iterator {
    public:
        Iterator(Node* node)
                : cursor_(node)
        {}

        ~Iterator() = default;

        T& operator * ()
        {
            return cursor_->d;
        }

        const T& operator * () const
        {
            return cursor_->d;
        }

        void operator ++ ()
        {
            cursor_ = cursor_->next;
        }

        bool operator == (const Iterator& obj) const
        {
            return cursor_ == obj.cursor_;
        }

        bool operator != (const Iterator& obj) const
        {
            return cursor_ != obj.cursor_;
        }

    private:
        Node* cursor_;
    };

    template <class T>
    LinkList<T>::LinkList()
    {
        guard_ = AllocateNode(T());
    }

    template <class T>
    LinkList<T>::~LinkList()
    {
        DeleteAll();
        DeallocateNode(guard_);
        guard_ = nullptr;
    }

    template <class T>
    bool LinkList<T>::IsEmpty() const
    {
        return guard_->next == nullptr;
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::InsertTail(const T& d)
    {
        Node* p = guard_;

        while (p->next != nullptr) {
            p = p->next;
        }
        return InsertAfter(p, d);
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::InsertHead(const T& d)
    {
        return InsertAfter(guard_, d);
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::InsertAfter(const Node& node, const T& d)
    {
        Node* p = AllocateNode(d);
        p->next = node.next;
        node.next = p;
        return p;
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::InsertBefore(const Node& node, const T& d)
    {
        Node* p = guard_;
        while (p->next != &node) {
            p = p->next;
        }

        if (p->next == nullptr) {
            return nullptr;
        }

        Node* new_node = AllocateNode(d);
        new_node->next = node;
        p->next = new_node;
        return new_node;
    }

    template <class T>
    bool LinkList<T>::Delete(const T& d)
    {
        Node* p = guard_->next;
        Node* temp = nullptr;
        while (p != nullptr) {
            if (p->d == d) {
                temp = p;
                p = p->next;

                DeallocateNode(temp);
            }
            else {
                p = p->next;
            }
        }
        return true;
    }

    template <class T>
    bool LinkList<T>::DeleteAll()
    {
        Node* p = guard_->next;
        Node* tmp = nullptr;
        while (p != nullptr) {
            tmp = p;
            p = p->next;
            DeallocateNode(tmp);
        }
        return true;
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::Find(const T& d) const
    {
        Node* p = guard_->next;
        while (p != nullptr) {
            if (p->d == d) {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::GetReserveNThNode(std::size_t k) const
    {
        std::size_t i = 0;

        Node* cursor = guard_->next;

        while(cursor != nullptr) {
            if (i == k) {
                break;
            }

            ++i;
            cursor = cursor->next;
        }

        if (cursor == nullptr) {
            return nullptr;
        }

        Node* result = guard_->next;
        while(cursor->next != nullptr) {
            cursor = cursor->next;
            result = result->next;
        }
        return result;
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::GetMiddleNode() const
    {
        Node* slow = guard_->next;
        Node* fast = guard_->next;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    template <class T>
    bool LinkList<T>::Reverse()
    {
        Node* p = guard_->next;
        guard_->next = nullptr;

        Node* tmp = nullptr;
        while (p != nullptr) {
            tmp = p;
            p = p->next;
            InsertAfter(guard_, tmp);
        }
        return true;
    }

    template <class T>
    bool LinkList<T>::IsContainLoop() const
    {
        Node* slow = guard_;
        Node* fast = guard_;

        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow) {
                return true;
            }
        }
        return false;
    }


    template <class T>
    typename LinkList<T>::Iterator LinkList<T>::Begin()
    {
        return Iterator(guard_);
    }

    template <class T>
    typename LinkList<T>::Iterator LinkList<T>::Begin() const
    {
        return Iterator(guard_);
    }

    template <class T>
    typename LinkList<T>::Iterator LinkList<T>::End()
    {
        return Iterator(nullptr);
    }

    template <class T>
    typename LinkList<T>::Iterator LinkList<T>::End() const
    {
        return Iterator(nullptr);
    }

    template <class T>
    typename LinkList<T>::Node* LinkList<T>::AllocateNode(const T& d)
    {
        Node* p = Allocator::AllocateObj<Node>();
        if (p != nullptr) {
            p->d = d;
        }
        return p;
    }

    template <class T>
    void LinkList<T>::DeallocateNode(Node* node)
    {
        if (node != nullptr) {
            Allocator::DeallocateMem(node);
        }
    }
}

#endif // __ALGO_LINKLIST_HPP__
/* EOF */
