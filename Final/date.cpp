//
// Created by F-Mir on 3/30/2024.
//

#include "date.h"

#include <iomanip>

Date::Date(const uint16_t year, const uint16_t month, const uint16_t day)
        : _year(year), _month(month), _day(day) {}

uint16_t Date::GetYear() const {
    return _year;
}

uint16_t Date::GetMonth() const {
    return _month;
}

uint16_t Date::GetDay() const {
    return _day;
}

Date ParseDate(istream &is) {
    uint16_t year;
    is >> year;
    is.ignore(1); // ignore '-'

    uint16_t month;
    is >> month;
    is.ignore(1); // ignore '-'

    uint16_t day;
    is >> day;

    return {year, month, day};
}

ostream &operator<<(ostream &os, const Date &date) {
    return os << setfill('0') << setw(4) << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2)
              << date.GetDay();
}