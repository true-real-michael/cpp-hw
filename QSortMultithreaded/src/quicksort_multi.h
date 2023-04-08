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


#include <algorithm>
#include <mutex>
#include <thread>


void _quicksort(int *array, size_t size, size_t &nThreadsBusy, size_t nThreads, std::mutex &mtx) {
    if (size <= 1) {
        return;
    }

    int pivot = array[size / 2];

    size_t i = 0;
    size_t j = size - 1;

    while (i <= j) {
        while (array[i] < pivot) {
            i++;
        }

        while (array[j] > pivot) {
            j--;
        }

        if (i <= j) {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    if (nThreadsBusy < nThreads) {
        mtx.lock();
        nThreadsBusy++;
        mtx.unlock();

        std::thread thr(_quicksort, array, j + 1, std::ref(nThreadsBusy), nThreads, std::ref(mtx));
        _quicksort(array + i, size - i, nThreadsBusy, nThreads, mtx);

        thr.join();
        mtx.lock();
        nThreadsBusy--;
        mtx.unlock();
    } else {
        _quicksort(array + i, size - i, nThreadsBusy, nThreads, mtx);
        _quicksort(array, j + 1, nThreadsBusy, nThreads, mtx);
    }
}


void quicksort_multi(int *array, size_t size, size_t nThreads = 1) {
    size_t nThreadsBusy = 1;
    std::mutex mtx;
    _quicksort(array, size, nThreadsBusy, nThreads, mtx);
}


#endif //QSORT_QUICKSORT_MULTI_H
