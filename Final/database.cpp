//
// Created by F-Mir on 3/30/2024.
//

#include "database.h"

// TODO: Check static functions suppressing
void Database::Add(const Date &date, const string &event) { // NOLINT(*-convert-member-functions-to-static)
    // TODO: implement function
    // use `insert` method
    // event may contain spaces, so use `get line` method
    (void) date;
    (void) event;
}

// TODO: Check static functions suppressing
void Database::Print(ostream &ostream) const { // NOLINT(*-convert-member-functions-to-static)
    //  TODO: implement function
    // date should be sorted
    // events for one day should be sorted in adding order
    (void) ostream;
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