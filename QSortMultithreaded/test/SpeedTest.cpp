//
// Created by Mikhail Kiselyov on 01.04.2023.
//

#include <gtest/gtest.h>
#include <random>
#include <quicksort_single.h>
#include <quicksort_multi.h>


class SuiteName : public ::testing::Test {
    static int *rand_arr(size_t n) {
        std::mt19937 rng(std::random_device{}());

        std::uniform_int_distribution<int> dist(0, 1000000);

        int *a = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = dist(rng);
        return a;
    }

protected:
    void SetUp() final {
        n = 5000000;
        a = rand_arr(n);
        b = new int[n];
        std::memcpy(b, a, n);
    }

    void TearDown() final {
        delete[] a;
        delete[] b;
    }


    int *a{}, *b{}, n{};
};


TEST_F(SuiteName, TimeTest) {
    struct timespec start{}, stop{};
    double secs_multi, secs_single;

    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort_multi(a, n, 4);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    secs_multi = (double) (stop.tv_nsec - start.tv_nsec) / 1000000000 + (double) (stop.tv_sec - start.tv_sec);

    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort_multi(b, n);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    secs_single = (double) (stop.tv_nsec - start.tv_nsec) / 1000000000 + (double) (stop.tv_sec - start.tv_sec);

    ASSERT_LT(secs_multi, secs_single);
}


TEST_F(SuiteName, SortTestMulti) {
    quicksort_multi(a, n, 2);
    for (int i = 1; i < n; i++) {
        ASSERT_LE(a[i-1], a[i]);
    }
}
