#include <cstdlib>
#include "algo_allocator.h"

namespace algo {

    void* Allocator::AllocateMem(std::size_t obj_num, std::size_t each_size_in_byte)
    {
        if (obj_num == 0 || each_size_in_byte == 0) {
            return nullptr;
        }

        return std::calloc(obj_num, each_size_in_byte);
    }

    void  Allocator::DeallocateMem(void* ptr)
    {
        if (ptr != nullptr) {
            std::free(ptr);
        }
    }
}

/* EOF */