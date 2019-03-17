/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.17
 */

#ifndef __ALGO_LINKLIST_HPP__
#define __ALGO_LINKLIST_HPP__

#include <set>
#include "algo_allocator.h"

namespace algo {
    template <class T>
    class LinkList {
    public:
        struct Node {
            T     d;
            Node* next;

            Node()
            : d(T())
            , next(nullptr)
            {}
        };

    public:
        class Iterator;

        LinkList();
        ~LinkList();

        Node* InsertTail(const T& node);
        Node* InsertHead(const T& node);
        Node* InsertAfter(const Node& node, const T& d);
        Node* InsertBefore(const Node& node, const T& d);

        bool Delete(const T& d);
        bool DeleteAll();

        Node* Find(const T& d) const;

        bool Reserve();
        bool IsContainLoop() const;
        bool IsPalindrome();

        Iterator Begin();
        Iterator Begin() const;

        Iterator End();
        Iterator End() const;

        class Iterator {
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

    protected:
        Node* AllocateNode(const T& d);
        void  DeallocateNode(Node* node);

    private:
        Node* guard_;
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
    bool LinkList<T>::Reserve()
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
        std::set<void*> visits;

        Node* p = guard_->next;
        while (p != nullptr) {
            if (visits.count((void*)p) > 0) {
                return true;
            }
            visits.insert((void*)p);
            p = p->next;
        }
        return false;
    }

    template <class T>
    bool LinkList<T>::IsPalindrome()
    {
        Node* slow = guard_;
        Node* fast = guard_;


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