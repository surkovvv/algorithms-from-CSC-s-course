#include <iostream>
#include <vector>
int N = 0;
int M = 0;

/* Первая строка - n и m - кол-во отрезков и точек для проверки
Затем идет n строк вида a_i, b_i - концы отрезков
После идет строка с m точками
Для каждой из них нужно вывести, скольким отрезкам она принадлежит
*/

// в общем случае, хочется вернуть пару <j,k>, где j - индекс начала элементов
std::pair<size_t, size_t> partition(int*& array, size_t l, size_t r) {
    // 1) выбрать опорный элемент и обменять его с самым левым
    std::swap(array[l], array[(l + r + 1) / 2]);
    // 2) i, j
    size_t i = l + 1, j = l, k = 1;
    for (; i < r + 1; i++) {
        if (array[i] < array[l]) {
            j++;
            if (j != i)
                std::swap(array[j], array[i]);
        }
        else if (array[i] == array[l]) {
            k++;
            size_t pos;
            pos = std::max(int(l + k - 1), 1);
            //size_t pos = std::max(int(j - l - k + 1), int(l + k - 1));
            std::swap(array[j + 1], array[pos]);
            if (i != j + 1)
                std::swap(array[pos], array[i]);
            j++;
        }
        /*for (size_t t = 0; t <= r; t++)
            std::cout << array[t] << ' ';
        std::cout << '\n'; */
    }
    for (size_t p = 0; p < k; p++)
        std::swap(array[p + l], array[j - p]);
    return std::make_pair(j - k + 1, j);
}

void quick_sort(int*& array, int l, int r) {
    if (r <= l)
        return;
    std::pair<size_t, size_t> eq_elem = partition(array, l, r);
    size_t less = eq_elem.first;
    size_t more = eq_elem.second;
    quick_sort(array, l, less - 1);
    quick_sort(array, more + 1, r);
}

// индекс первого числа массива, большего x (или индекс + 1)
// TODO переписать итеративно
void bin_search_less_and_eq(int* array, size_t size, int x) {
    int l = 0, r = size - 1;
    while (l <= r) {
        size_t m = (l + r) / 2;
        if (array[m] <= x) {
            size_t i = m;
            while (array[i] <= x && i < r)
                i++;
            if (array[i] <= x)
                N = r - l + 1;
            else
                N = i;
            return;
        } else
            r = m - 1;
    }
    N = 0;
}

void bin_search_less_only(int* array, size_t size, int x){
    int l = 0, r = size - 1;
    while (l <= r) {
        size_t m = (l + r) / 2;
        if (array[m] < x) {
            size_t i = m;
            while (array[i] < x && i < r)
                i++;
            if (array[i] < x)
                M = r - l + 1;
            else
                M = i;
            return;
        } else
            r = m - 1;
    }
    M = 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    int* left_coordinates = new int[n];
    int* right_coordinates = new int[n];
    int* coordinates_to_check = new int[m];
    std::vector<int> answer; // [m]
    for (size_t i = 0; i < n; i++)
        std::cin >> left_coordinates[i] >> right_coordinates[i];
    for (size_t j = 0; j < m; j++)
        std::cin >> coordinates_to_check[j];
    quick_sort(left_coordinates, 0, n - 1);
    quick_sort(right_coordinates, 0, n - 1);
    for (size_t j = 0; j < m; j++){
        bin_search_less_and_eq(left_coordinates, n, coordinates_to_check[j]);
        bin_search_less_only(right_coordinates, n, coordinates_to_check[j]);
        answer.push_back(N - M);
        N = M = 0;
    }
    for (auto x : answer)
        std::cout << x << ' ';
    return 0;
}
