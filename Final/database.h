//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATABASE_H
#define YELLOW_BELT_DATABASE_H

#pragma once

#include "date.h"

#include <vector>
#include <map>
#include <list>

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
    map<Date, list<string>> _entries;
};

void TestDatabase();

#endif //YELLOW_BELT_DATABASE_H