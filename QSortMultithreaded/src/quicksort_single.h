//
// Created by Mikhail Kiselyov on 28.03.2023.
//

#ifndef CPP_HW_QUICKSORTTHREADED_H
#define CPP_HW_QUICKSORTTHREADED_H

#include <iterator>
#include <algorithm>
#include <functional>


template<typename RandomAccessIterator,
        typename Order>
void quicksort(RandomAccessIterator first, RandomAccessIterator last, Order order) {
    if (last - first > 1) {
        RandomAccessIterator split = std::partition(first + 1, last, std::bind(order, std::placeholders::_1, *first));
        std::iter_swap(first, split - 1);
        quicksort(first, split - 1, order);
        quicksort(split, last, order);
    }
}

template<typename RandomAccessIterator>
void quicksort(RandomAccessIterator first, RandomAccessIterator last) {
    quicksort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}


#endif //CPP_HW_QUICKSORTTHREADED_H
