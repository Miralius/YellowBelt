//
// Created by F-Mir on 3/30/2024.
//

#include "date.h"

Date::Date()
        : _date(TimePoint()) {}

// TODO: Might be it's needed to remove attribute
[[maybe_unused]] Date::Date(const uint16_t year, const uint16_t month, const uint16_t date)
        : _date([](const uint16_t year, const uint16_t month, const uint16_t date) {
    // TODO: implement lambda function
    (void) year;
    (void) month;
    (void) date;
    return TimePoint();
}(year, month, date)) {}

Date ParseDate(istream &is) {
    // TODO: implement function;
    (void) is;
    return {};
}

ostream& operator<<(ostream &os, const Date& date)
{
    // TODO: implement function;
    // date out for 0-1-1 should be 0001-01-1
    (void)os;
    (void)date;
    return os;
}