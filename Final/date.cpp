//
// Created by F-Mir on 3/30/2024.
//

#include "date.h"

#include <iomanip>

Date::Date()
        : _date(TimePoint()) {}

Date::Date(const uint16_t year, const uint16_t month, const uint16_t day)
        : _date([](const uint16_t year, const uint16_t month, const uint16_t day) {
    tm time = {};
    FillTmStruct(time, year, month, day);
    return chrono::time_point_cast<Days>(chrono::system_clock::from_time_t(mktime(&time)));
}(year, month, day)) {}

TimePoint Date::GetTimePoint() const {
    return _date;
}

void FillTmStruct(tm &time, uint16_t year, uint16_t month, uint16_t day) {
    time.tm_year = year - 1900;
    time.tm_mon = month;
    time.tm_mday = day;
}

Date ParseDate(istream &is) {
    uint16_t year;
    is >> year;
    is.ignore(1);
    uint16_t month;
    is >> month;
    is.ignore(1);
    uint16_t day;
    is >> day;
    return {year, month, day};
}

ostream &operator<<(ostream &os, const Date &date) {
    const time_t time_t = chrono::system_clock::to_time_t(date.GetTimePoint());
    const tm tm = *localtime(&time_t);
    os << setfill('0') << setw(4) << tm.tm_year << '-' << setw(2) << tm.tm_mon << '-' << tm.tm_mday;
    return os;
}