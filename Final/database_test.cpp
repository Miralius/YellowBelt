//
// Created by F-Mir on 4/1/2024.
//
#include "main.h"
#include "database.h"
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2

#include "../TestRunner/TestRunner.h"

#else
#include "test_runner.h"
#endif

void TestDatabase() {
    {
        Database db;
        const auto dateExample = Date(2017, 11, 7);
        db.Add(dateExample, "big sport event");
        const auto entries = db.FindIf([&dateExample](const Date &date, const string &) {
            return date == dateExample;
        });
        Assert(entries.size() == 1, "Database 'found 1 entries' after adding");
        AssertEqual(*entries.cbegin(), "big sport event", "Database checks 'Add 2017-11-07 big sport event' work");
    }
    {
        Database db;
        db.Add({2017, 6, 1}, "1st of June");
        const auto dateExample = Date(2017, 7, 8);
        db.Add(dateExample, "8th of July");
        db.Add(dateExample, "Someone's birthday");
        AssertEqual(db.RemoveIf([&dateExample](const Date &date, const string &) {
            return date == dateExample;
        }), 2, "Database checks 'Del date == 2017-07-08' where there are 2 entries will be deleted");
    }
    {
        Database db;
        db.Add({2017, 6, 1}, "1st of June");
        const auto dateExample = Date(2017, 7, 8);
        db.Add(dateExample, "8th of July");
        db.Add(dateExample, "Someone's birthday");
        AssertEqual(db.RemoveIf([](const Date &, const string &) {
            return true;
        }), 3, "Database checks 'Del' where there are 3 entries, and everything is removed");
    }
}