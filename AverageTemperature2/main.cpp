#include <iostream>
#include <vector>
#include <numeric>

int main() {
    u_int32_t N;
    std::cin >> N;
    std::vector<int> temperatures;
    temperatures.reserve(N);
    for (u_int32_t i = 0; i < N; ++i) {
        int temperature;
        std::cin >> temperature;
        temperatures.push_back(temperature);
    }

    auto averageTemperature = std::accumulate(temperatures.cbegin(), temperatures.cend(), 0LL) /
                              static_cast<int64_t>(temperatures.size());

    std::vector<u_int32_t> highAverageTemperatureIndexes;
    for (u_int32_t i = 0; i < temperatures.size(); ++i)
    {
        if (temperatures.at(i) > averageTemperature)
        {
            highAverageTemperatureIndexes.push_back(i);
        }
    }

    std::cout << highAverageTemperatureIndexes.size() << '\n';
    for (const auto index : highAverageTemperatureIndexes)
    {
        std::cout << index << ' ';
    }

    return 0;
}