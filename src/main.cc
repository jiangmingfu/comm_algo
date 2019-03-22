#include <stdio.h>

#include <list>
#include <string>
#include <stdint.h>

#include "algo_bitmap.h"
#include "algo_linklist.hpp"
#include "algo_double_circular_list.hpp"
#include "algo_merge_sort.hpp"
#include "algo_lru_cache.hpp"

int main()
{

    algo::Bitmap bitmap(64);

    bitmap.ResetAll();
    bitmap.SetBit(1);
    bitmap.SetBit(63);

    algo::Bitmap::Iterator it = bitmap.Begin();
    while (it != bitmap.End()) {
        if (*it > 0) {
            printf("1");
        }
        else {
            printf("0");
        }
        ++it;
    }

    printf("\nhello comm_algo.\n");

    algo::DoubleCircularList<int> dcl;

    for (int i = 0; i < 2; ++i) {
        dcl.InsertHead(i);
    }

    algo::DoubleCircularList<int>::Iterator it2 = dcl.Begin();
    while (it2 != dcl.End()) {
        printf("%d ", *it2);
        ++it2;
    }
    printf("\n");

    int d[] = {56, 23, 54, 23, 1, 67, 90, 21, 33};
    algo::MergeSort(d, sizeof(d)/sizeof(d[0]));
    for (int i = 0; i < sizeof(d)/sizeof(d[0]); ++i) {
        printf("%d ", d[i]);
    }
    printf("\n");

    algo::LRUCache<std::string, int > cache(5);

    cache.Put("one", 1);
    cache.Put("two", 2);
    cache.Put("three", 3);
    cache.Put("four", 4);
    cache.Put("five", 5);

    cache.Put("six", 6);

    int v;
    if (cache.Get("one", v)) {
        printf("one: %d\n", v);
    }
    else {
        printf("one: not found .\n");
    }

    return 0;
}
/* EOF */