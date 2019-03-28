/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.28
 */

#ifndef __ALGO_BINARY_SEARCH_TREE_HPP__
#define __ALGO_BINARY_SEARCH_TREE_HPP__

#include <stdint.h>
#include <stack>
#include "algo_allocator.h"

namespace algo {

    // 二叉搜索树
    template <class T, class Comparator>
    class BSTree {
    public:
        struct Node;
        struct Iterator;

        BSTree();
        ~BSTree();

        BSTree(const BSTree&) = delete;
        BSTree& operator= (const BSTree&) = delete;

        bool Insert(const T& v);
        Node* Find(const T& v) const;
        bool Erase(const T& v);

        bool IsEmpty() const;
        bool GetLargest(T& v) const;
        bool GetSmallest(T& v) const;

    protected:
        Node* CreateNode(const T& v);
        void  DeleteNode(Node* ptr);

    private:
        Node* head_;
        const Comparator comp_;
    };

    template <class T, class Comparator>
    struct BSTree<T, Comparator>::Node {
        T v;
        Node* lchild;
        Node* rchild;

        Node()
        : v()
        , lchild(nullptr)
        , rchild(nullptr)
        {
        }

        bool IsLeaf() const {
            return (lchild == nullptr && rchild == nullptr);
        }
    };

    template <class T, class Comparator>
    BSTree<T, Comparator>::BSTree()
    : head_(nullptr)
    {
    }

    template <class T, class Comparator>
    BSTree<T, Comparator>::~BSTree()
    {
        Node* p = head_;
        Node* tmp = nullptr;

        std::stack<Node*> stack;

        if (head_ != nullptr) {
            stack.push(head_);
        }

        while(!stack.empty()) {
            Node* n = stack.top();
            stack.pop();

            if (n->lchild != nullptr) {
                stack.push(n->lchild);
            }

            if (n->rchild != nullptr) {
                stack.push(n->rchild);
            }

            Allocator::DeallocateObj(n);
        }
    }

    template <class T, class Comparator>
    bool BSTree<T, Comparator>::Insert(const T& v)
    {
        if (head_ == nullptr) {
            head_ = CreateNode(v);
        }
        else {
            Node* p = head_;
            while (true) {
                if (comp_(p->v, v) == 0) {
                    return true;
                }

                if (comp_(p->v, v) > 0) {
                    if (p->lchild != nullptr) {
                        p = p->lchild;
                    }
                    else {
                        p->lchild = CreateNode(v);
                        break;
                    }
                }
                else {
                   if (p->rchild != nullptr) {
                       p = p->rchild;
                   }
                   else {
                       p->lchild = CreateNode(v);
                       break;
                   }
                }
            } // while
        }
        return true;
    }

    template <class T, class Comparator>
    typename  BSTree<T, Comparator>::Node*
    BSTree<T, Comparator>::Find(const T& v) const
    {
        Node* p = head_;
        while (p != nullptr) {
            if (comp_(p->v, v) == 0) {
                return p;
            }

            if (comp_(p->v, v) > 0) {
                p = p->lchild;
            }
            else {
                p = p->rchild;
            }
        }
        return nullptr;
    }

    template <class T, class Comparator>
    bool BSTree<T, Comparator>::Erase(const T& v)
    {
        Node* p = head_;
        Node* parent = nullptr;

        while (p != nullptr) {

            if (comp_(p->v, v) == 0) {
                break;
            }

            parent = p;
            if (comp_(p->v, v) > 0) {
                p = p->lchild;
            }
            else {
                p = p->rchild;
            }
        }

        if (p == nullptr) {
            return false;
        }

        if (parent == nullptr) {
            DeleteNode(p);
            head_ = nullptr;
        }
        else {

            if (p->lchild == nullptr && p->rchild == nullptr) { // leaf
                DeleteNode(p);

                if (comp_(parent->v, v) > 0) {
                    parent->lchild = nullptr;
                }
                else {
                    parent->rchild = nullptr;
                }
                return true;
            }
            else {
                if (p->lchild != nullptr) { // left branch

                    Node* tmp = p->lchild;
                    parent = p;
                    while (tmp->rchild != nullptr) {
                        parent = tmp;
                        tmp = tmp->rchild;
                    }
                    p->v = tmp->v;

                    if (parent == p) {
                        p->lchild = nullptr;
                    }
                    else {
                        parent->rchild = nullptr;
                    }
                    DeleteNode(tmp);
                }
                else {
                    Node* tmp = p->rchild;
                    parent = p;
                    while (tmp->lchild != nullptr) {
                        parent = tmp;
                        tmp = tmp->lchild;
                    }
                    p->v = tmp->v;

                    if (parent == p) {
                        p->rchild = nullptr;
                    }
                    else {
                        parent->lchild = nullptr;
                    }
                    DeleteNode(tmp);
                }
            }
        }
    }

    template <class T, class Comparator>
    bool BSTree<T, Comparator>::IsEmpty() const
    {
        return (head_ == nullptr);
    }

    template <class T, class Comparator>
    bool BSTree<T, Comparator>::GetLargest(T& v) const
    {
        if (head_ == nullptr) {
            return false;
        }

        Node* p = head_;
        while (p->rchild != nullptr) {
            p = p->rchild;
        }

        v = p->v;
        return true;
    }

    template <class T, class Comparator>
    bool BSTree<T, Comparator>::GetSmallest(T& v) const
    {
        if (head_ == nullptr) {
            return false;
        }

        Node* p = head_;
        while (p->lchild != nullptr) {
            p = p->lchild;
        }

        v = p->v;
        return true;
    }

    template <class T, class Comparator>
    typename  BSTree<T, Comparator>::Node*
    BSTree<T, Comparator>::CreateNode(const T& v)
    {
        Node* node = Allocator::AllocateObj<Node>();
        node->lchild = node->rchild = nullptr;
        node->v = v;
        return node;
    }

    template <class T, class Comparator>
    void BSTree<T, Comparator>::DeleteNode(Node* ptr)
    {
        if (ptr != nullptr) {
            Allocator::DeallocateObj(ptr);
        }
    }
}
#endif // __ALGO_BINARY_SEARCH_TREE_HPP__
/* EOF */
