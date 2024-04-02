//
// Created by F-Mir on 3/30/2024.
//

#include "database.h"

void Database::Add(const Date &date, const string &event) {
    auto sequentialEntriesIt = _sequentialEntries.find(date);
    auto uniqueEntriesIt = _uniqueEntries.find(date);
    if (sequentialEntriesIt != _sequentialEntries.end() and uniqueEntriesIt != _uniqueEntries.end())
    {
        auto& uniqueEntries = uniqueEntriesIt->second;
        if (uniqueEntries.count(event) == 0)
        {
            sequentialEntriesIt->second.push_back(event);
            uniqueEntries.insert(event);
        }
    }
    else
    {
        _sequentialEntries[date].push_back(event);
        _uniqueEntries[date].insert(event);
    }
}

void Database::Print(ostream &ostream) const {
    for (const auto& [date, entries] : _sequentialEntries)
    {
        for (const auto& entry : entries)
        {
            ostream << date << ' ' << entry << '\n';
        }
    }
}

string Database::Last(const Date &date) const {
    const auto afterLastIt = _sequentialEntries.upper_bound(date);
    if (afterLastIt == _sequentialEntries.cbegin())
    {
        throw invalid_argument("No entries found");
    }
    const auto lastIt = prev(afterLastIt);
    return to_string(lastIt->first) + ' ' + lastIt->second.back();
}