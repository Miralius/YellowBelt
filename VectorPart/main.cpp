#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    const auto firstNegativeIt = find_if(numbers.cbegin(), numbers.cend(), [] (const auto& number)
    {
        return number < 0;
    });
    for_each(reverse_iterator(firstNegativeIt), numbers.crend(), [] (const auto& number)
    {
        cout << number << ' ';
    });
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}