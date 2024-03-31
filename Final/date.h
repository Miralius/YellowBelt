//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATE_H
#define YELLOW_BELT_DATE_H

#pragma once

#include <chrono>
#include <iostream>

using namespace std;
using TimePoint = chrono::time_point<chrono::system_clock>; // TODO: may be it's needed to use Days duration

class Date {
public:
    Date();

    // TODO: Might be it's needed to remove attribute
    [[maybe_unused]] Date(uint16_t year, uint16_t month, uint16_t date);

private:
    const TimePoint _date;
};

Date ParseDate(istream &is);

#endif //YELLOW_BELT_DATE_H