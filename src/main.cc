#include <stdio.h>
#include "algo_bitmap.h"
#include "algo_linklist.hpp"

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

    algo::LinkList<int> l;

    return 0;
}
/* EOF */