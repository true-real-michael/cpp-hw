//
// Created by Mikhail Kiselyov on 28.03.2023.
//

#ifndef QSORT_QUICKSORT_MULTI_H
#define QSORT_QUICKSORT_MULTI_H

#include <iterator>
#include <algorithm>
#include <functional>
#include <thread>
#include <vector>



void quicksort_multi(int* first, int* last,
                     size_t nThreads,
                     size_t &nThreadsBusy,
                     std::mutex &mutx) {
    if (last - first > 1) {
        auto split = std::partition(first + 1, last, std::bind(std::less<int>(), std::placeholders::_1, *first));
        std::iter_swap(first, split - 1);

        if (nThreadsBusy < nThreads) {
            mutx.lock();
            nThreadsBusy++;
            mutx.unlock();
            std::thread subthread(quicksort_multi, first, split - 1, nThreads, std::ref(nThreadsBusy), std::ref(mutx));

            quicksort_multi(split, last, nThreads, nThreadsBusy, mutx);

            subthread.join();
            mutx.lock();
            nThreadsBusy--;
            mutx.unlock();
        } else {
            quicksort_multi(first, split - 1, nThreads, nThreadsBusy, mutx);
            quicksort_multi(split, last, nThreads, nThreadsBusy, mutx);
        }

    }
}

void quicksort_multi(int* first, int* last, size_t nThreads = 4) {
    std::vector<std::thread> threads(nThreads);
    size_t nThreadsBusy = 1;
    std::mutex mutx;

    quicksort_multi(first,
                    last,
                    nThreads,
                    nThreadsBusy,
                    mutx);
}


//template<typename T>
//int naive_quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
//    auto const sz = end - begin;
//    if (sz <= 1) return 0;
//
//    auto pivot = begin + sz/2;
//    auto const pivot_v = *pivot;
//
//    std::swap(*pivot, *(end - 1));
//    auto p = std::partition(begin, end, [&](const T& a) { return a < pivot_v; } );
//    std::swap(*p, *(end - 1));
//
//    if (sz > 4096) {
//        auto left = std::async(std::launch::async, [&]() {
//            return naive_quick_sort(begin, p);
//        });
//        naive_quick_sort(p + 1, end);
//    } else {
//        naive_quick_sort(begin, p);
//        naive_quick_sort(p + 1, end);
//    }
//    return 0;
//}
//
//template <typename T>
//void quick_sort(std::vector<T>& arr) {
//    naive_quick_sort(arr.begin(), arr.end());
//}


#endif //QSORT_QUICKSORT_MULTI_H
