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
        int result{};
        for (auto mapIt = _entries.begin(); mapIt != _entries.end();) {
            const auto onlyEventPredicate = [&dateEvent = mapIt->first, &predicate](const auto &event) {
                return predicate(dateEvent, event);
            };
            auto &entries = mapIt->second;
            const auto last = remove_if(entries.begin(), entries.end(), onlyEventPredicate);
            result += distance(last, entries.end());
            if (last == entries.begin()) {
                mapIt = _entries.erase(mapIt);
            } else {
                entries.erase(last, entries.end());
                ++mapIt;
            }
        }
        return result;
    }

    template<typename Predicate>
    [[nodiscard]] vector<string> FindIf(Predicate &&predicate) {
        vector<string> result;
        for (const auto &[date, entries]: _entries) {
            const auto onlyEventPredicate = [&dateEvent = date, &predicate](const auto &event) {
                return predicate(dateEvent, event);
            };
            auto begin = entries.cbegin();
            const auto end = entries.cend();
            while (begin != end) {
                const auto resultIt = find_if(begin, end, onlyEventPredicate);
                if (resultIt != end) {
                    result.emplace_back(to_string(date) + ' ' + *resultIt);
                    begin = next(resultIt);
                }
                else
                {
                    begin = resultIt;
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