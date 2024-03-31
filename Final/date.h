//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATE_H
#define YELLOW_BELT_DATE_H

#pragma once

#include <chrono>
#include <iostream>

using namespace std;
using Days = chrono::duration<int64_t, ratio<86400>>;
using TimePoint = chrono::time_point<chrono::system_clock, Days>;

class Date {
public:
    Date();

    // TODO: Might be it's needed to remove attribute
    [[maybe_unused]] Date(uint16_t year, uint16_t month, uint16_t date);

private:
    const TimePoint _date;
};

Date ParseDate(istream &is);

// TestParseDate()
// TODO: Check 0-1-1
// TODO: Check 9999-12-31
// TODO: Check 2017-11-07, 0-2-31

ostream& operator<<(ostream &os, const Date& date);

#endif //YELLOW_BELT_DATE_H