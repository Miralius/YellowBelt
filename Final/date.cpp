//
// Created by F-Mir on 3/30/2024.
//

#include "date.h"

// TODO: Might be it's needed to remove attribute
[[maybe_unused]] Date::Date(const uint16_t year, const uint16_t month, const uint16_t day)
        : _year(year), _month(month), _day(day) {}

Date ParseDate(istream &is) {
    // TODO: implement function;
    (void) is;
    return {0, 0, 0};
}

ostream &operator<<(ostream &os, const Date &date) {
    // TODO: implement function;
    // date out for 0-1-1 should be 0001-01-1
    (void) os;
    (void) date;
    return os;
}