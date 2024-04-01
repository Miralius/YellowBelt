//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATE_H
#define YELLOW_BELT_DATE_H

#pragma once

#include <iostream>
#include <cstdint>

using namespace std;

class Date {
public:
    // TODO: Might be it's needed to remove attribute
    [[maybe_unused]] Date(uint16_t year, uint16_t month, uint16_t day);

private:
    const uint16_t _year;
    const uint16_t _month;
    const uint16_t _day;
};

Date ParseDate(istream &is);

// TestParseDate()
// TODO: Check 0-1-1
// TODO: Check 9999-12-31
// TODO: Check 2017-11-07, 0-2-31

ostream &operator<<(ostream &os, const Date &date);

#endif //YELLOW_BELT_DATE_H