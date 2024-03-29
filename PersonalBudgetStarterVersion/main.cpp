#include <iostream>
#include <chrono>
#include <map>
#include <iomanip>

using namespace std;
using TimePoint = chrono::time_point<chrono::system_clock>;
using Days = chrono::duration<int64_t, ratio<86400>>;

TimePoint GetTimePointFromString(const string &dateString) {
    std::tm time = {};
    strptime(dateString.c_str(), "%Y-%m-%d", &time);
    return chrono::ceil<Days>(chrono::system_clock::from_time_t(mktime(&time)));
}

class PersonalFinances {
public:
    void Earn(const TimePoint &from, const TimePoint &to, unsigned cash) {
        auto cashPerDay = cash / static_cast<double>(chrono::duration_cast<Days>(to - from).count() + 1);
        for (auto timePoint = from; timePoint <= to;) {
            _finances[timePoint] += cashPerDay;
            timePoint += Days(1);
        }
    }

    [[nodiscard]] double ComputeIncome(const TimePoint &from, const TimePoint &to) const {
        double result{};
        for (auto fromTimePoint = _finances.lower_bound(from);
             fromTimePoint != _finances.upper_bound(to); ++fromTimePoint) {
            result += fromTimePoint->second;
        }
        return result;
    }

private:
    map<TimePoint, double> _finances;
};

int main() {
    int Q;
    cin >> Q;

    PersonalFinances finances;

    for (auto i = 0; i < Q; ++i) {
        string action;
        cin >> action;
        string from;
        cin >> from;
        auto fromTimePoint = GetTimePointFromString(from);
        string to;
        cin >> to;
        auto toTimePoint = GetTimePointFromString(to);
        if (action == "Earn")
        {
            unsigned cash;
            cin >> cash;
            finances.Earn(fromTimePoint, toTimePoint, cash);
        }
        else
        {
            cout << setprecision(25) << finances.ComputeIncome(fromTimePoint, toTimePoint) << '\n';
        }
    }

    return 0;
}