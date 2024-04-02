//
// Created by F-Mir on 3/30/2024.
//

#include "database.h"

void Database::Add(const Date &date, const string &event) {
    auto dateIt = _entries.find(date);
    if (dateIt != _entries.end())
    {
        auto& entries = dateIt->second;
        if (find(entries.cbegin(), entries.cend(), event) == entries.cend())
        {
            entries.push_back(event);
        }
    }
    else
    {
        _entries[date].push_back(event);
    }
}

void Database::Print(ostream &ostream) const {
    for (const auto& [date, entries] : _entries)
    {
        for (const auto& entry : entries)
        {
            ostream << date << ' ' << entry << '\n';
        }
    }
}

string Database::Last(const Date &date) const {
    const auto afterLastIt = _entries.upper_bound(date);
    if (afterLastIt == _entries.cbegin())
    {
        throw invalid_argument("No entries found");
    }
    const auto lastIt = prev(afterLastIt);
    return to_string(lastIt->first) + ' ' + lastIt->second.back();
}