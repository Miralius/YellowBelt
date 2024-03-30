//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOWBELT_DATE_H
#define YELLOWBELT_DATE_H
#include <chrono>
#include <iostream>

using namespace std;
using TimePoint = chrono::time_point<chrono::system_clock>;


class Date {
public:
};

TimePoint ParseDate(istream& is);

#endif //YELLOWBELT_DATE_H
