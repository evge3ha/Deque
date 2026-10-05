#pragma once

#include <deque>

template<class T, class Comp>
inline std::deque<T> Merge(const std::deque<T>& half1,
                           const std::deque<T>& half2,
                           const Comp& comparator) {
    std::deque<T> result{};
    auto left_it  = half1.begin();
    auto right_it = half2.begin();

    while (left_it != half1.end() && right_it != half2.end()) {
        if (comparator(*left_it, *right_it)) {
            result.push_back(*left_it);
            ++left_it;
        } else {
            result.push_back(*right_it);
            ++right_it;
        }
    }

    result.insert(result.end(), left_it, half1.end());
    result.insert(result.end(), right_it, half2.end());

    return result;
}

template<class T, class Comp>
inline std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <=1) {
        return src;
    }

    const int mid = src.size() / 2;
    const std::deque<T> left_sorted  = MergeSort<T, Comp>({src.begin(), src.begin() + mid}, comparator);
    const std::deque<T> right_sorted = MergeSort<T, Comp>({src.begin() + mid, src.end()}, comparator);

    return Merge(left_sorted, right_sorted, comparator);
}
