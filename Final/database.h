//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATABASE_H
#define YELLOW_BELT_DATABASE_H

#pragma once

#include "date.h"
#include <set>

using namespace std;

class Database {

public:
    void Add(const Date &date, const string &event);

    void Print(ostream &ostream) const;

    [[nodiscard]] string Last(const Date &date) const;

    template<typename Predicate>
    [[nodiscard]] int RemoveIf(Predicate &&predicate) {
        // TODO: implement function
        // Empty condition erase whole database
        (void) predicate;
        return {};
    }

    template<typename Predicate>
    [[nodiscard]] set<string> FindIf(Predicate &&predicate) {
        // TODO: implement function
        // Empty condition makes function equal to Print
        (void) predicate;
        return {};
    }
private:
    // TODO: It seems the best way to keep records is map<Date, list/vector<string>(or pair<set<string>, string>)>
};

void TestDatabase();

// Add 2017-06-01 1st of June
// Add 2017-07-08 8th of July
// Add 2017-07-08 Someone's birthday
// TODO: del without condition

// TODO: Check for print:
// Add 2017-01-01 Holiday
// Add 2017-03-08 Holiday
// Add 2017-1-1 New Year
// Add 2017-1-1 New Year
// Print
// stdout:
// 2017-01-01 Holiday
// 2017-01-01 New Year
// 2017-03-08 Holiday

// TODO: check for Find
// Add 2017-01-01 Holiday
// Add 2017-03-08 Holiday
// Add 2017-01-01 New Year
// Find event != "working day"
// Add 2017-05-09 Holiday
// stdout:
// 2017-01-01 Holiday
// 2017-01-01 New Year
// 2017-03-08 Holiday
// Found 3 entries
// TODO: Find with empty condition

// TODO: check for Last
// Add 2017-01-01 New Year
// Add 2017-03-08 Holiday
// Add 2017-01-01 Holiday
// Last 2016-12-31
// Last 2017-01-01
// Last 2017-06-01
// Add 2017-05-09 Holiday
// stdout:
// No entries
// 2017-01-01 Holiday
// 2017-03-08 Holiday

// TODO: Generalized check #1
// Add 2017-11-21 Tuesday
// Add 2017-11-20 Monday
// Add 2017-11-21 Weekly meeting
// Print
// Find event != "Weekly meeting"
// Last 2017-11-30
// Del date > 2017-11-20
// Last 2017-11-30
// Last 2017-11-01
// stdout:
// 2017-11-20 Monday
// 2017-11-21 Tuesday
// 2017-11-21 Weekly meeting
// 2017-11-20 Monday
// 2017-11-21 Tuesday
// Found 2 entries
// 2017-11-21 Weekly meeting
// Removed 2 entries
// 2017-11-20 Monday
// No entries

// TODO: Generalized check #2
// Add 2017-11-05 holiday
// Add 2017-11-07 after Party ^_^  // TODO: (← here's space!!!)
// Find date < 2017-11-06
// Del event != "holiday"
// Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event"
// Add 2017-05-01 sport event
// Add 2017-01-01 sport event
// Add 2017-07-01 sport event
// Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event"
// Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")
// Add 0-1-1 sport event
// Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")
// stdout
// 2017-11-05 holiday
// Found 1 entries
// Removed 1 entries
// Found 0 entries
// 2017-01-01 sport event
// 2017-05-01 sport event
// Found 2 entries
// Removed 0 entries
// Removed 1 entries

#endif //YELLOW_BELT_DATABASE_H