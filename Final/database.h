//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATABASE_H
#define YELLOW_BELT_DATABASE_H

#pragma once

#include "date.h"

#include <vector>

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
    [[nodiscard]] vector<string> FindIf(Predicate &&predicate) {
        // TODO: implement function
        // Empty condition makes function equal to Print
        (void) predicate;
        return {};
    }
private:
    // TODO: It seems the best way to keep records is map<Date, list/vector<string>(or pair<set<string>, string>)>
};

void TestDatabase();

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