//
// Created by Mikhail Kiselyov on 28.03.2023.
//

#include "quicksort_single.h"
#include "quicksort_multi.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;



template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> v) { for (const auto &e: v) os << e << ' '; return os; }


int main() {
    vector<int> a = {1, 3, 2, 5, 9, 4, 5};
    cout << a << endl;
    quicksort_multi(a.begin(), a.end());
    cout << a << endl;
}