#include <set>
#include <iostream>

using namespace std;

set<int>::const_iterator FindNearestElement(
        const set<int> &numbers,
        int border);
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

set<int>::const_iterator FindNearestElement(
        const set<int> &numbers,
        int border) {
    auto result = numbers.lower_bound(border);
    auto minValue = abs(border - *result);
    while (result != numbers.cbegin())
    {
        const auto newMinValue = abs(border - *(prev(result)));
        if (newMinValue > minValue)
        {
            break;
        }
        minValue = newMinValue;
        --result;
    }
    return result;
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}