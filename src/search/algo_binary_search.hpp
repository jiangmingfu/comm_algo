/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.24
 */

#ifndef __ALGO_BINARY_SEARCH_HPP__
#define __ALGO_BINARY_SEARCH_HPP__

#include <stdint.h>

namespace algo {

    // 二分查找递归实现
    template <class T>
    int32_t BinarySearchRecursive(T d[], int32_t s, int32_t e, const T& v)
    {
        if (s > e) {
            return -1;
        }

        int32_t m = s + ((e - s) >> 1);
        if (d[m] == v) {
            return m;
        }

        if (d[m] > v) {
            return BinarySearch(d, s, m - 1, v);
        }
        else {
            return BinarySearchRecursive(d, m + 1, e, v);
        }
    }

    // 二分查找
    template <class T>
    int32_t BinarySearch(T d[], int32_t n, const T& v)
    {
        int32_t l = 0;
        int32_t h = n - 1;
        int32_t m = 0;

        while (l <= h) {
            m = l + ((h - l) >> 1);

            if (d[m] == v) {
                return m;
            }

            if (d[m] > v) {
                h = m - 1;
            }
            else {
                l = m + 1;
            }
        }

        return -1;
    }

    // 查找有序数组中(可能有重复元素)元素v第一次出现的位置下标
    template <class T>
    int32_t FindFirstOfElement(T d[], int32_t n, const T& v)
    {
        int32_t l = 0;
        int32_t h = n;
        int32_t m = 0;

        while (l <= h) {
            m = l + ((h - l) >> 2);

            if (d[m] == v) {
                if (m == 0 || d[m-1] < v) {
                    return m;
                }

                h = m - 1;
            }
            else if (d[m] > v) {
                h = m - 1;
            }
            else {
                l = m + 1;
            }
        }
        return -1;
    }

    // 查找有序数组中元素v最后一次出现的位置下标
    template <class T>
    int32_t FindLastOfElement(T d[], int32_t n, const T& v)
    {
        int32_t l = 0;
        int32_t h = n;
        int32_t m = 0;

        while (l <= h) {
            m = l + ((h - l) >> 2);

            if (d[m] == v) {
                if (m == (n-1) || d[m+1] > v) {
                    return m;
                }

                l = m + 1;
            }
            else if (d[m] > v) {
                h = m - 1;
            }
            else {
                l = m + 1;
            }
        }
        return -1;
    }

    // 查找有序数组中第一个大于或等于v的元素位置下标
    template <class T>
    int32_t FindFirstOfGEElement(T d[], int32_t n, const T& v)
    {
        int32_t l = 0;
        int32_t h = n - 1;
        int32_t m = 0;

        while (l <= h) {
            m = l + ((h - l) >> 1);

            if (d[m] >= v) {
                if (m == 0 || d[m-1] < v) {
                    return m;
                }

                h = m - 1;
            }
            else {
                l = m + 1;
            }
        }
        return -1;
    }

    // 查找有序数组中第一个小于或等于v的元素位置下标
    template <class T>
    int32_t FindLastOfLEElement(T d[], int32_t n, const T& v)
    {
        int32_t l = 0;
        int32_t h = n - 1;
        int32_t m = 0;

        while (l <= h) {
            m = l + ((h - l) >> 1);

            if (d[m] <= v) {
                if (m == n-1 || d[m+1] > v) {
                    return m;
                }

                l = m + 1;
            }
            else {
                h = m - 1;
            }
        }
        return -1;
    }
}
#endif // __ALGO_BINARY_SEARCH_HPP__
/* EOF */
