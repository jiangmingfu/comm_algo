#include <stdio.h>

#include <list>
#include <string>
#include <stdint.h>

#include "algo_bitmap.h"
#include "algo_linklist.hpp"
#include "algo_double_circular_list.hpp"
#include "algo_merge_sort.hpp"
#include "algo_lru_cache.hpp"
#include "algo_quick_sort.hpp"
#include "algo_bubble_sort.hpp"
#include "algo_binary_search.hpp"
#include "algo_circular_array.hpp"

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

    int d[] = {56, 23, 54, 23, 1, 67, 90, 21, 33, 100, 232, 23, 1232, 34,578, 12, 8976,
               12,56, 9650, 34, 586, 123, 589, 596, 23, 12, 65, 768, 98, 0, 7, 9};
//    algo::MergeSort(d, sizeof(d)/sizeof(d[0]));
//    for (int i = 0; i < sizeof(d)/sizeof(d[0]); ++i) {
//        printf("%d ", d[i]);
//    }
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

    algo::QuickSort(d, sizeof(d)/sizeof(d[0]));
    // algo::InsertSort(d, sizeof(d)/sizeof(d[0]));
    for (int i = 0; i < sizeof(d)/sizeof(d[0]); ++i) {
        printf("%d ", d[i]);
    }

    int32_t data[] = {1, 2, 5, 5, 5, 7, 10, 10, 12, 15, 16, 16};
    int32_t l = sizeof(data)/sizeof(data[0]);
    int p = algo::BinarySearch(data, l, 1);
    printf("\n10: %d\n", p);

    p = algo::FindFirstOfElement(data, l, 10);
    printf("\n10: %d\n", p);

    p = algo::FindLastOfElement(data, l, 10);
    printf("\n10: %d\n", p);

    p = algo::FindFirstOfGEElement(data, l, 10);
    printf("\n10: %d\n", p);

    p = algo::FindLastOfLEElement(data, l, 10);
    printf("\n10: %d\n", p);

    algo::CircularArray<int>  a(100);

    a.Push(1);
    int vv = 0;
    a.Pop(vv);
    printf("vv = %d\n", vv);
    return 0;
}
/* EOF */