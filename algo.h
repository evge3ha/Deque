#pragma once

#include <deque>

template<class T, class Comp>
inline std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> sort{};
    int x{}, y{};

    while(half1.size() > x && half2.size() > y) {
        if(comparator(half1[x], half2[y])) {
            sort.push_back(half1[x]);
            x++;
        } else {
            sort.push_back(half2[y]);
            y++;
        }
    }

    while(x < half1.size()) {
        sort.push_back(half1[x]);
        ++x;
    }

    while(y < half2.size()) {
        sort.push_back(half2[y]);
        ++y;
    }

    return sort;
}

template<class T, class Comp>
inline std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if(src.size() <=1) {
        return src;
    }

    const int mid = src.size() / 2;
    const std::deque<T> left_sorted  = MergeSort<T, Comp>({src.begin(), src.begin() + mid}, comparator);
    const std::deque<T> right_sorted = MergeSort<T, Comp>({src.begin() + mid, src.end()}, comparator);

    return Merge(left_sorted, right_sorted, comparator);
}
