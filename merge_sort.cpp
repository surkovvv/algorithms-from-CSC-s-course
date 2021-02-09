#include <iostream>
long inverse = 0;

void merge(long*& array, int left, int mid, int right) {
    long* merged = new long[right - left];
    size_t it1 = 0, it2 = 0;
    while (left + it1 < mid && mid + it2 < right){
        if (array[left + it1] <= array[mid + it2]){
            merged[it1 + it2] = array[left + it1];
            it1++;
        }
        else{
            merged[it1 + it2] = array[mid + it2];
            inverse += mid - it1 - left;
            it2++;
        }
    }
    while (left + it1 < mid){
        merged[it1 + it2] = array[left + it1];
        it1++;
    }
    while (mid + it2 < right){
        merged[it1 + it2] = array[mid + it2];
        it2++;
    }
    for (size_t i = 0; i < it1+it2; i++)
        array[left + i] = merged[i];
}

void mergesort(long* &A, int l, int r) {
    if (l + 1 >= r)
        return;
    size_t mid = (l + r) / 2;
    mergesort(A, l, mid);
    mergesort(A, mid , r);
    merge(A, l, mid, r);
}

int main() {
    int n;
    std::cin >> n;
    long *array = new long[n];
    for (size_t i = 0; i < n; i++)
        std::cin >> array[i];
    mergesort(array, 0, n);
    for (size_t i = 0; i < n; i++)
        std::cout << array[i] << ' ';
    std::cout << '\n' << inverse;
    return 0;
}
