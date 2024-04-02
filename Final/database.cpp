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

// TODO: Check static functions suppressing
std::string Database::Last(const Date &date) const { // NOLINT(*-convert-member-functions-to-static)
    //  TODO: implement function
    // use lower_bound(date)
    // use THE LAST added event for the date
    // if date < database's dates -> no entries
    (void) date;
    return {};
}