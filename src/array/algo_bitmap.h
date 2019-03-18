/**
 *
 * @Author: jiangmingfu
 * @Date  : 2019.03.17
 */

#ifndef __ALGO_BITMAP_H__
#define __ALGO_BITMAP_H__

#include <cstdint>

namespace algo {

    class Bitmap {
    public:
        class Iterator;

        Bitmap();
        Bitmap(std::size_t bit_num);
        ~Bitmap();

        Bitmap(const Bitmap&) = delete;
        Bitmap& operator = (const Bitmap&) = delete;

        Bitmap(Bitmap&& obj);
        Bitmap& operator = (Bitmap&& obj);

        bool SetAll();
        bool ResetAll();

        bool SetBit(std::size_t bit);
        bool ResetBit(std::size_t bit);

        uint8_t TestBit(std::size_t bit) const;

        std::size_t BitNum() const;

        Iterator Begin();
        Iterator Begin() const;

        Iterator End();
        Iterator End() const;

        class Iterator {
        public:
            Iterator(uint32_t* ptr, std::size_t bit_cap, std::size_t offset);
            ~Iterator() = default;

            uint8_t operator *() const;
            void operator ++();

            bool operator == (const Iterator& obj) const;
            bool operator != (const Iterator& obj) const;

        private:
            uint32_t*   ptr_;
            std::size_t bit_cap_;
            std::size_t offset_;
        };

    protected:
        static constexpr std::size_t DefaultCapacity() { return 256; }
        uint32_t* AllocateMemory(uint32_t num);
        void      DeallocateMemory(uint32_t* ptr);

    private:
        std::size_t bit_num_;
        std::size_t bit_cap_;
        uint32_t* ptr_;
    };
}

#endif // __ALGO_BITMAP_H__
/* EOF */
