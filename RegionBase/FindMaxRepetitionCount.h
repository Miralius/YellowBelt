#include <limits>
#include <algorithm>
#include <set>
#include <vector>
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2
#include "Region.h"
#endif

bool operator==(const Region &lhs, const Region &rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) ==
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

bool operator<(const Region &lhs, const Region &rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
    // It's a terrible solution but it works!
    if (regions.empty())
    {
        return 0;
    }
    const auto regionSet = set<Region>(regions.cbegin(), regions.cend());
    int maxRepetitionCount = numeric_limits<int>::min();
    for (const auto &region: regionSet) {
        maxRepetitionCount = max(maxRepetitionCount,
                                 static_cast<int>(count(regions.cbegin(), regions.cend(), region)));
    }
    return maxRepetitionCount;
}