//
// Created by Mikhail Kiselyov on 28.03.2023.
//

#include "quicksort_multi.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

#include <sys/time.h>

using namespace std;


template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> v) {
    for (const auto &e: v) os << e << ' ';
    return os;
}


int *rand_arr(size_t n) {
    std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<int> dist(0, 1000000);

    int *a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = dist(rng);
    return a;
}


int main() {
    int n = 10000000;
    auto a = rand_arr(n);
    auto b = rand_arr(n);

    struct timespec start, stop;
    double secs;

    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort_multi(a, n, 3);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    secs = (double) (stop.tv_nsec - start.tv_nsec) / 1000000000 + (double) (stop.tv_sec - start.tv_sec);
    cout << secs << endl;

    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort_multi(b, n);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    secs = (double) (stop.tv_nsec - start.tv_nsec) / 1000000000 + (double) (stop.tv_sec - start.tv_sec);
    cout << secs << endl;

    delete a;
    delete b;

    return 0;
}