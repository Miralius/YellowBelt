//
// Created by F-Mir on 3/30/2024.
//

#include "date.h"

Date::Date()
        : _date(TimePoint()) {}

// TODO: Might be it's needed to remove attribute
[[maybe_unused]] Date::Date(const uint16_t year, const uint16_t month, const uint16_t day)
        : _date([](const uint16_t year, const uint16_t month, const uint16_t day) {
    tm time = {};
    FillTmStruct(time, year, month, day);
    return chrono::time_point_cast<Days>(chrono::system_clock::from_time_t(mktime(&time)));
}(year, month, day)) {}

void FillTmStruct(tm &time, uint16_t year, uint16_t month, uint16_t day) {
    time.tm_year = year - 1900;
    time.tm_mon = month;
    time.tm_mday = day;
}

Date ParseDate(istream &is) {
    // TODO: implement function;
    (void) is;
    return {};
}

ostream &operator<<(ostream &os, const Date &date) {
    // TODO: implement function;
    // date out for 0-1-1 should be 0001-01-1
    (void) os;
    (void) date;
    return os;
}