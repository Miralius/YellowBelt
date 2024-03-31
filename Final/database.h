//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOWBELT_DATABASE_H
#define YELLOWBELT_DATABASE_H


#include "date.h"
#include <set>

using namespace std;

class Database {

public:
    void Add(const TimePoint &date, const string &event);
    void Print(ostream &ostream) const;
    [[nodiscard]] string Last(const TimePoint &date) const;

    template <typename Predicate>
    [[nodiscard]] int RemoveIf(Predicate&& predicate)
    {
        // mock function
        (void)predicate;
        return {};
    }

    template <typename Predicate>
    [[nodiscard]] set<string> FindIf(Predicate&& predicate)
    {
        // mock function
        (void)predicate;
        return {};
    }
};


#endif //YELLOWBELT_DATABASE_H
