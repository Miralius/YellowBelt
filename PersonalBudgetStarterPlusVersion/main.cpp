#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>

using namespace std;
using Days = chrono::duration<int64_t, ratio<86400>>;
using TimePoint = chrono::time_point<chrono::system_clock, Days>;

TimePoint GetTimePointFromString(const string &dateString) {
    std::tm time = {};
    strptime(dateString.c_str(), "%Y-%m-%d", &time);
    return chrono::ceil<Days>(chrono::system_clock::from_time_t(mktime(&time)));
}

class PersonalFinances {
public:
    PersonalFinances()
            : _finances(vector<unsigned long long>(getIndex(_maxDate) + 1)) {
    }

    void Earn(const TimePoint &date, unsigned cash) {
        _finances[getIndex(date)] += cash;
    }

    void ComputeIncomes()
    {
        partial_sum(_finances.cbegin(), _finances.cend(), _finances.begin());
    }

    [[nodiscard]] unsigned long long GetIncomeBetweenDates(const TimePoint &from, const TimePoint &to) const {
        auto indexFrom = getIndex(from);
        auto indexTo = getIndex(to);
        return indexFrom > 0 ? _finances[indexTo] - _finances[indexFrom - 1] : _finances[indexTo];
    }

private:
    [[nodiscard]] unsigned getIndex(const TimePoint &date) const {
        return chrono::duration_cast<Days>(date - _minDate).count();
    }

    const TimePoint _minDate = GetTimePointFromString("1700-01-01");
    const TimePoint _maxDate = GetTimePointFromString("2099-12-31");
    vector<unsigned long long> _finances;
};

int main() {
    PersonalFinances finances;

    int E;
    cin >> E;
    for (auto i = 0; i < E; ++i) {
        string date;
        cin >> date;
        auto timePoint = GetTimePointFromString(date);
        unsigned cash;
        cin >> cash;
        finances.Earn(timePoint, cash);
    }
    finances.ComputeIncomes();

    int Q;
    cin >> Q;
    for (auto i = 0; i < Q; ++i) {
        string from;
        cin >> from;
        auto fromTimePoint = GetTimePointFromString(from);
        string to;
        cin >> to;
        auto toTimePoint = GetTimePointFromString(to);
        cout << finances.GetIncomeBetweenDates(fromTimePoint, toTimePoint) << '\n';
    }

    return 0;
}