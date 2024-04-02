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
#include <set>

using namespace std;

class Database {

public:
    void Add(const Date &date, const string &event);

    void Print(ostream &ostream) const;

    [[nodiscard]] string Last(const Date &date) const;

    template<typename Predicate>
    [[nodiscard]] int RemoveIf(Predicate &&predicate) {
        int result{};
        auto sequentialEntriesIt = _sequentialEntries.begin();
        auto uniqueEntriesIt = _uniqueEntries.begin();
        for (; sequentialEntriesIt != _sequentialEntries.end() and uniqueEntriesIt != _uniqueEntries.end();) {
            const auto onlyEventPredicate = [&dateEvent = uniqueEntriesIt->first, &predicate](const auto &event) {
                return predicate(dateEvent, event);
            };
            auto &sequentialEntries = sequentialEntriesIt->second;
            auto &uniqueEntries = uniqueEntriesIt->second;
            const int deletedCount = erase_if(uniqueEntries, onlyEventPredicate);
            result += deletedCount;
            if (uniqueEntries.empty()) {
                uniqueEntriesIt = _uniqueEntries.erase(uniqueEntriesIt);
                sequentialEntriesIt = _sequentialEntries.erase(sequentialEntriesIt);
            } else {
                if (deletedCount) {
                    sequentialEntries.erase(remove_if(sequentialEntries.begin(), sequentialEntries.end(),
                                                      onlyEventPredicate), sequentialEntries.end());
                }
                ++uniqueEntriesIt;
                ++sequentialEntriesIt;
            }
        }
        return result;
    }

    template<typename Predicate>
    [[nodiscard]] vector<string> FindIf(Predicate &&predicate) const {
        vector<string> result;
        for (const auto &[date, entries]: _sequentialEntries) {
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
                } else {
                    begin = resultIt;
                }
            }
        }
        return result;
    }

private:
    template<class Set, typename Predicate>
    int erase_if(Set &set, Predicate &&predicate) {
        int old_size = set.size();
        for (auto first = set.begin(), last = set.end(); first != last;) {
            if (predicate(*first))
                first = set.erase(first);
            else
                ++first;
        }
        return old_size - set.size();
    }

    map<Date, vector<string>> _sequentialEntries;
    map<Date, set<string>> _uniqueEntries;
};

void TestDatabase();

#endif //YELLOW_BELT_DATABASE_H