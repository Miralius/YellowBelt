//
// Created by F-Mir on 3/30/2024.
//

#include "date.h"

#include <iomanip>

Date::Date(const uint16_t year, const uint16_t month, const uint16_t day)
        : _year(year), _month(month), _day(day) {}

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
    return os << setfill('0') << setw(4) << date._year << '-' << setw(2) << date._month << '-' << setw(2) << date._day;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return tie(lhs._year, lhs._month, lhs._day) < tie(rhs._year, rhs._month, rhs._day);
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return !(lhs > rhs);
}

bool operator>(const Date &lhs, const Date &rhs) {
    return tie(lhs._year, lhs._month, lhs._day) > tie(rhs._year, rhs._month, rhs._day);
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return !(lhs < rhs);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return !(lhs != rhs);
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return tie(lhs._year, lhs._month, lhs._day) != tie(rhs._year, rhs._month, rhs._day);
}