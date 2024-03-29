#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // 1. Если диапазон содержит меньше 2 элементов, выйти из функции
    if (distance(range_begin, range_end) < 2) {
        return;
    }
    // 2. Создать вектор, содержащий все элементы текущего диапазона
    vector<typename RandomIt::value_type> sorted(range_begin, range_end);
    // 3. Разбить вектор на 3 равные части
    auto a_third = distance(sorted.begin(), sorted.end()) / 3;
    auto first_part_range_begin = sorted.begin();
    auto first_part_range_end = sorted.begin() + a_third;
    auto second_part_range_begin = first_part_range_end;
    auto second_part_range_end = second_part_range_begin + a_third;
    auto third_part_range_begin = second_part_range_end;
    auto third_part_range_end = sorted.end();
    // 4. Вызвать функцию MergeSort от каждой части вектора.
    MergeSort(first_part_range_begin, first_part_range_end);
    MergeSort(second_part_range_begin, second_part_range_end);
    MergeSort(third_part_range_begin, third_part_range_end);
    // 5. Слить первые две трети вектора с помощью алгоритма merge,
    // сохранив результат во временный вектор с помощью back_inserter
    vector<typename RandomIt::value_type> temp_vector;
    merge(first_part_range_begin, first_part_range_end, second_part_range_begin, second_part_range_end,
          back_inserter(temp_vector));
    // 6. Слить временный вектор из предыдущего пункта с последней третью вектора из п. 4,
    // записав полученный отсортированный диапазон вместо исходного.
    merge(temp_vector.cbegin(), temp_vector.cend(), third_part_range_begin, third_part_range_end, range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x: v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}