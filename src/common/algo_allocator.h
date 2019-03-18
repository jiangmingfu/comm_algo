
/**
 *  @Author: jiangmingfu
 *  @Date  : 2019.03.17
 */

#ifndef __ALGO_ALLOCATOR_H__
#define __ALGO_ALLOCATOR_H__

#include <stdint.h>

namespace algo {

    //  memory allocate
    class Allocator {
    public:
        static void* AllocateMem(std::size_t obj_num, std::size_t each_size_in_byte);
        static void  DeallocateMem(void* ptr);

        template <class T>
        static T* AllocateObj()
        {
            return new T();
        }

        template <class T>
        static void DeallocateObj(T* obj_ptr)
        {
            if (obj_ptr != nullptr) {
                delete obj_ptr;
            }
        }

        template <class T>
        static T* AllocateMultiObjs(std::size_t obj_num)
        {
            return new T [obj_num];
        }

        template <class T>
        static void DeallocMultiObjs(T* objs_ptr)
        {
            if (objs_ptr != nullptr) {
                delete [] objs_ptr;
            }
        }

    };
}

#endif // __ALGO_ALLOCATOR_H__
/* EOF */