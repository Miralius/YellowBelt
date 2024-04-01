//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATE_H
#define YELLOW_BELT_DATE_H

#pragma once

#include <iostream>
#include <cstdint>
#include <chrono>

using namespace std;

class Date {
public:
    Date(uint16_t year, uint16_t month, uint16_t day);

    friend ostream &operator<<(ostream &os, const Date &date);

    friend bool operator!=(const Date &lhs, const Date &rhs);

private:
    const uint16_t _year;
    const uint16_t _month;
    const uint16_t _day;
};

Date ParseDate(istream &is);

void TestParseDate();
// TODO: Check 2017-11-07, 0-2-31

#endif //YELLOW_BELT_DATE_H