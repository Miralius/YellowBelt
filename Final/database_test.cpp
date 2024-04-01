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

#include <sstream>

void TestDatabase() {
    {
        // Check for add:
        // Add 2017-11-07 big sport event

        Database db;
        db.Add({2017, 11, 7}, "big sport event");
        const auto entries = db.FindIf([](const Date &date, const string &) {
            return date == Date{2017, 11, 7};
        });
        Assert(entries.size() == 1, "Database 'found 1 entries' after adding");
        AssertEqual(entries.front(), "big sport event", "Database checks 'Add 2017-11-07 big sport event' work");
    }
    {
        // Check for del:
        // Add 2017-06-01 1st of June
        // Add 2017-07-08 8th of July
        // Add 2017-07-08 Someone's birthday
        // Del date == 2017-07-08

        // Result:
        // stdout "Removed 2 entries"

        Database db;
        db.Add({2017, 6, 1}, "1st of June");
        db.Add({2017, 7, 8}, "8th of July");
        db.Add({2017, 7, 8}, "Someone's birthday");
        AssertEqual(db.RemoveIf([](const Date &date, const string &) {
            return date == Date{2017, 7, 8};
        }), 2, "Database checks 'Del date == 2017-07-08' where there are 2 entries will be deleted");
    }
    {
        // Check for del (everything is removed):
        // Add 2017-06-01 1st of June
        // Add 2017-07-08 8th of July
        // Add 2017-07-08 Someone's birthday
        // Del

        // Result:
        // stdout "Removed 3 entries"

        Database db;
        db.Add({2017, 6, 1}, "1st of June");
        const auto dateExample = Date(2017, 7, 8);
        db.Add(dateExample, "8th of July");
        db.Add(dateExample, "Someone's birthday");
        AssertEqual(db.RemoveIf([](const Date &, const string &) {
            return true;
        }), 3, "Database checks 'Del' where there are 3 entries, and everything is removed");
    }
    {
        // Check for print:
        // Add 2017-01-01 Holiday
        // Add 2017-03-08 Holiday
        // Add 2017-1-1 New Year
        // Add 2017-1-1 New Year

        // Result
        // 2017-01-01 Holiday
        // 2017-01-01 New Year
        // 2017-03-08 Holiday

        Database db;
        db.Add({2017, 1, 1}, "Holiday");
        db.Add({2017, 3, 8}, "Holiday");
        db.Add({2017, 1, 1}, "New Year");
        db.Add({2017, 1, 1}, "New Year");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday",
                    "Database 'Print' checking");
    }
    {
        // Check for Find
        // Add 2017-01-01 Holiday
        // Add 2017-03-08 Holiday
        // Add 2017-01-01 New Year
        // Find event != "working day"
        // Add 2017-05-09 Holiday

        // Result:
        // 2017-01-01 Holiday
        // 2017-01-01 New Year
        // 2017-03-08 Holiday
        // Found 3 entries

        Database db;
        db.Add({2017, 1, 1}, "Holiday");
        db.Add({2017, 3, 8}, "Holiday");
        db.Add({2017, 1, 1}, "New Year");
        const auto nonWorkingDayEvents = db.FindIf([](const Date &, const string &event) {
            return event != "working day";
        });
        db.Add({2017, 5, 9}, "Holiday");
        AssertEqual(nonWorkingDayEvents.size(), 3u, "Database 'Find' count checking");
        AssertEqual(nonWorkingDayEvents.at(0), "2017-01-01 Holiday", "Database 'Find' the first record checking");
        AssertEqual(nonWorkingDayEvents.at(1), "2017-01-01 New Year", "Database 'Find' the second record checking");
        AssertEqual(nonWorkingDayEvents.at(2), "2017-03-08 Holiday", "Database 'Find' the third record checking");
    }
    {
        // Check for Find (empty condition)
        // Add 2017-01-01 Holiday
        // Add 2017-03-08 Holiday
        // Add 2017-01-01 New Year
        // Find
        // Add 2017-05-09 Holiday

        // Result:
        // 2017-01-01 Holiday
        // 2017-01-01 New Year
        // 2017-03-08 Holiday
        // Found 3 entries

        Database db;
        db.Add({2017, 1, 1}, "Holiday");
        db.Add({2017, 3, 8}, "Holiday");
        db.Add({2017, 1, 1}, "New Year");
        const auto nonWorkingDayEvents = db.FindIf([](const Date &, const string &) {
            return true;
        });
        db.Add({2017, 5, 9}, "Holiday");
        AssertEqual(nonWorkingDayEvents.size(), 3u, "Database 'Find' empty condition checking");
        AssertEqual(nonWorkingDayEvents.at(0), "2017-01-01 Holiday",
                    "Database 'Find (empty condition)' the first record checking");
        AssertEqual(nonWorkingDayEvents.at(1), "2017-01-01 New Year",
                    "Database 'Find (empty condition)' the second record checking");
        AssertEqual(nonWorkingDayEvents.at(2), "2017-03-08 Holiday",
                    "Database 'Find (empty condition)' the third record checking");
    }
    {
        // Check for Last
        // Add 2017-01-01 New Year
        // Add 2017-03-08 Holiday
        // Add 2017-01-01 Holiday
        // Last 2016-12-31
        // Last 2017-01-01
        // Last 2017-06-01
        // Add 2017-05-09 Holiday

        // Result:
        // No entries
        // 2017-01-01 Holiday
        // 2017-03-08 Holiday

        Database db;
        db.Add({2017, 1, 1}, "New Year");
        db.Add({2017, 3, 8}, "Holiday");
        db.Add({2017, 1, 1}, "Holiday");
        bool noEntriesForFirstRequest = false;
        try {
            const auto firstResult = db.Last({2016, 12, 31});
        }
        catch (const invalid_argument &) {
            noEntriesForFirstRequest = true;
        }
        const auto secondResult = db.Last({2017, 1, 1});
        const auto thirdResult = db.Last({2017, 6, 1});
        db.Add({2017, 5, 9}, "Holiday");
        Assert(noEntriesForFirstRequest, "Database 'Last' the first request (2016-12-31) no result checking");
        AssertEqual(secondResult, "2017-01-01 Holiday",
                    "Database 'Last' the second record request (2017-01-01) checking");
        AssertEqual(thirdResult, "2017-03-08 Holiday",
                    "Database 'Last' the first record request (2017-03-08) checking");
    }
}