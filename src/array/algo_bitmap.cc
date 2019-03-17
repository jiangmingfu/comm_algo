#include <string.h>
#include "algo_bitmap.h"
#include "algo_allocator.h"

namespace algo {
    Bitmap::Bitmap()
    : bit_num_(0)
    {
        bit_cap_ = DefaultCapacity();
        ptr_ = AllocateMemory(bit_cap_ >> 5);
    }

    Bitmap::Bitmap(std::size_t bit_num)
    : bit_num_(bit_num)
    {
        std::size_t align = 32;
        if ((bit_num & (align - 1)) != 0) {
            bit_cap_ = (bit_num | (align - 1)) + 1;
        }
        else {
            bit_cap_ = bit_num;
        }

        ptr_ = AllocateMemory(bit_cap_ >> 5);
    }

    Bitmap::~Bitmap()
    {
        if (ptr_ != nullptr) {
            DeallocateMemory(ptr_);
            ptr_ = nullptr;
        }
    }

    Bitmap::Bitmap(Bitmap&& obj)
    {
        ptr_ = obj.ptr_;
        bit_cap_ = obj.bit_cap_;
        bit_num_ = obj.bit_num_;

        obj.ptr_ = nullptr;
        obj.bit_cap_ = 0;
        obj.bit_num_ = 0;
    }

    Bitmap& Bitmap::operator = (Bitmap&& obj)
    {
        if (this != &obj) {
            DeallocateMemory(ptr_);

            ptr_ = obj.ptr_;
            bit_cap_ = obj.bit_cap_;
            bit_num_ = obj.bit_num_;

            obj.ptr_ = nullptr;
            obj.bit_cap_ = 0;
        }

        return *this;
    }

    bool Bitmap::SetAll()
    {
        memset(ptr_, 255, bit_cap_ >> 3);
        return true;
    }

    bool Bitmap::ResetAll()
    {
        memset(ptr_, 0, bit_cap_ >> 3);
        return true;
    }

    bool Bitmap::SetBit(std::size_t bit)
    {
        if (bit >= bit_num_) {
            return false;
        }

        ptr_[bit>>5] |= (1U << (bit & (32 - 1)));
        return true;
    }

    bool Bitmap::ResetBit(std::size_t bit)
    {
        if (bit >= bit_num_) {
            return false;
        }

        ptr_[bit>>5] &= ~(1U << (bit & (32 -1)));
        return true;
    }


    uint8_t Bitmap::TestBit(std::size_t bit) const
    {
        if (bit >= bit_num_) {
            // TODO: index overflow
            return 0;
        }

        return (ptr_[bit>>5] & (1U << (bit & (32 - 1)))) > 0 ? 1 : 0;
    }

    std::size_t Bitmap::BitNum() const
    {
        return bit_num_;
    }

    uint32_t* Bitmap::AllocateMemory(uint32_t num)
    {
        return (uint32_t*)Allocator::AllocateMem(num, sizeof(uint32_t));
    }

    void Bitmap::DeallocateMemory(uint32_t* ptr)
    {
        if (ptr != nullptr) {
            Allocator::DeallocateMem(ptr);
        }
    }

    Bitmap::Iterator Bitmap::Begin()
    {
        return Iterator(ptr_, bit_cap_, 0);
    }

    Bitmap::Iterator Bitmap::Begin() const
    {
        return Iterator(ptr_, bit_cap_, 0);
    }

    Bitmap::Iterator Bitmap::End()
    {
        return Iterator(ptr_, bit_cap_, bit_num_);
    }

    Bitmap::Iterator Bitmap::End() const
    {
        return Iterator(ptr_, bit_cap_, bit_num_);
    }

    Bitmap::Iterator::Iterator(uint32_t* ptr, std::size_t bit_cap, std::size_t offset)
    : ptr_(ptr)
    , bit_cap_(bit_cap)
    , offset_(offset)
    {

    }


    uint8_t Bitmap::Iterator::operator *() const
    {
        return (ptr_[offset_>>5] & (1U << (offset_ & (32 - 1)))) > 0 ? 1: 0;
    }

    void Bitmap::Iterator::operator ++()
    {
        ++offset_;
    }

    bool Bitmap::Iterator::operator == (const Iterator& obj) const
    {
        return (ptr_ == obj.ptr_ && bit_cap_ == obj.bit_cap_ && offset_ == obj.offset_);
    }

    bool Bitmap::Iterator::operator != (const Iterator& obj) const
    {
        return !(*this == obj);
    }
}

/* EOF */