#include <stdio.h>
#include "algo_bitmap.h"
#include "algo_linklist.hpp"
#include "algo_double_circular_list.hpp"
#include "algo_merge_sort.hpp"

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

    return 0;
}
/* EOF */