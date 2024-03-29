#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix);

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
    auto length = distance(range_begin, range_end);

    const auto less_it_value = [] (const auto& lhs, const auto& rhs)
    {
        return lhs[0] < rhs;
    };

    const auto less_value_it = [] (const auto& lhs, const auto& rhs)
    {
        return lhs < rhs[0];
    };

    while (length > 0)
    {
        auto half_length = length / 2;
        auto range_middle = range_begin + half_length;
        if (less_it_value(*range_middle, prefix))
        {
            range_begin = next(range_middle);
            length -= ++half_length;
        }
        else if (less_value_it(prefix, *range_middle))
            length = half_length;
        else
        {
            range_end = range_begin + length;
            const auto left = lower_bound(range_begin, range_middle, prefix, less_it_value);
            const auto right = upper_bound(next(range_middle), range_end, prefix, less_value_it);
            return { left, right };
        }
    }
    return { range_begin, range_begin };
}

int main() {
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
         (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
         (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}