//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_DATABASE_H
#define YELLOW_BELT_DATABASE_H

#pragma once

#include "date.h"

#include <vector>
#include <map>
#include <algorithm>

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
        vector<string> result;
        for (const auto& [date, entries]: _entries)
        {
            const auto onlyEventPredicate = [&dateEvent = date, &predicate] (const auto& event)
            {
                return predicate(dateEvent, event);
            };
            auto begin = entries.cbegin();
            const auto end = entries.cend();
            while (begin != end)
            {
                const auto resultIt = find_if(begin, end, onlyEventPredicate);
                if (resultIt != end)
                {
                    result.emplace_back(to_string(date) + ' ' + *resultIt);
                    begin = next(resultIt);
                }
            }
        }
        return result;
    }

private:
    map<Date, vector<string>> _entries;
};

void TestDatabase();

#endif //YELLOW_BELT_DATABASE_H