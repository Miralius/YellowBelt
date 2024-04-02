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
        AssertEqual(entries.front(), "2017-11-07 big sport event",
                    "Database checks 'Add 2017-11-07 big sport event' work");
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
        AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n",
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
    {
        // Generalized check #1
        // Add 2017-11-21 Tuesday
        // Add 2017-11-20 Monday
        // Add 2017-11-21 Weekly meeting
        // Print
        // Find event != "Weekly meeting"
        // Last 2017-11-30
        // Del date > 2017-11-20
        // Last 2017-11-30
        // Last 2017-11-01

        // Result:
        // 2017-11-20 Monday
        // 2017-11-21 Tuesday
        // 2017-11-21 Weekly meeting
        // 2017-11-20 Monday
        // 2017-11-21 Tuesday
        // Found 2 entries
        // 2017-11-21 Weekly meeting
        // Removed 2 entries
        // 2017-11-20 Monday
        // No entries

        Database db;
        db.Add({2017, 11, 21}, "Tuesday");
        db.Add({2017, 11, 20}, "Monday");
        db.Add({2017, 11, 21}, "Weekly meeting");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "2017-11-20 Monday\n2017-11-21 Tuesday\n2017-11-21 Weekly meeting",
                    "Database generalized check #1 Print command");
        const auto nonWeeklyMeetingEvents = db.FindIf(
                [](const Date &, const string &event) { return event != "Weekly meeting"; });
        AssertEqual(nonWeeklyMeetingEvents.size(), 2u, "Database generalized check #1 Find entry count command");
        AssertEqual(nonWeeklyMeetingEvents.at(0), "2017-11-20 Monday",
                    "Database generalized check #1 Find command the first entry");
        AssertEqual(nonWeeklyMeetingEvents.at(1), "2017-11-21 Tuesday",
                    "Database generalized check #1 Find command the second entry");
        const auto lastEntryFirstRequest = db.Last({2017, 11, 30});
        AssertEqual(lastEntryFirstRequest, "2017-11-21 Weekly meeting",
                    "Database generalized check #1 Last command the first request");
        AssertEqual(db.RemoveIf([](const Date &date, const string &) { return date > Date{2017, 11, 20}; }), 2,
                    "Database generalized check #1 Del command");
        const auto lastEntrySecondRequest = db.Last({2017, 11, 30});
        AssertEqual(lastEntrySecondRequest, "2017-11-20 Monday",
                    "Database generalized check #1 Last command the second request");
        bool noEntriesForThirdRequest = false;
        try {
            const auto firstResult = db.Last({2016, 11, 1});
        }
        catch (const invalid_argument &) {
            noEntriesForThirdRequest = true;
        }
        Assert(noEntriesForThirdRequest, "Database generalized check #1 Last command the third request (no entries)");
    }
    {
        // Generalized check #2
        // Add 2017-11-05 holiday
        // Add 2017-11-07 after Party ^_^ "← here's space!!!"
        // Find date < 2017-11-06
        // Del event != "holiday"
        // Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event"
        // Add 2017-05-01 sport event
        // Add 2017-01-01 sport event
        // Add 2017-07-01 sport event
        // Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event"
        // Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")
        // Add 0-1-1 sport event
        // Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")

        // Result
        // 2017-11-05 holiday
        // Found 1 entries
        // Removed 1 entries
        // Found 0 entries
        // 2017-01-01 sport event
        // 2017-05-01 sport event
        // Found 2 entries
        // Removed 0 entries
        // Removed 1 entries

        Database db;
        db.Add({2017, 11, 5}, "holiday");
        db.Add({2017, 11, 7}, "after Party ^_^ ");
        const auto firstFindResult = db.FindIf(
                [](const Date &date, const string &) { return date < Date{2017, 11, 6}; });
        AssertEqual(firstFindResult.size(), 1u, "Database generalized check #2 Find command the first request (size)");
        AssertEqual(firstFindResult.at(0), "2017-11-05 holiday",
                    "Database generalized check #2 Find command the first request");
        AssertEqual(db.RemoveIf([](const Date &, const string &event) { return event != "holiday"; }), 1,
                    "Database generalized check #2 Del command the first request");
        const auto secondFindResult = db.FindIf([](const Date &date, const string &event) {
            return date >= Date{2017, 1, 1} and date < Date{2017, 7, 1} and event == "sport event";
        });
        Assert(secondFindResult.empty(), "Database generalized check #2 Find command the second request");
        db.Add({2017, 5, 1}, "sport event");
        db.Add({2017, 1, 1}, "sport event");
        db.Add({2017, 7, 1}, "sport event");
        const auto thirdFindResult = db.FindIf([](const Date &date, const string &event) {
            return date >= Date{2017, 1, 1} and date < Date{2017, 7, 1} and event == "sport event";
        });
        AssertEqual(thirdFindResult.size(), 2u, "Database generalized check #2 Find command the third request (size)");
        AssertEqual(thirdFindResult.at(0), "2017-01-01 sport event",
                    "Database generalized check #2 Find command the third request (the first entry)");
        AssertEqual(thirdFindResult.at(1), "2017-05-01 sport event",
                    "Database generalized check #2 Find command the third request (the second entry)");
        AssertEqual(db.RemoveIf([](const Date &date, const string &event) {
            return date < Date{2017, 1, 1} and (event == "holiday" or event == "sport event");
        }), 0, "Database generalized check #2 Del command the second request");
        db.Add({0, 1, 1}, "sport event");
        AssertEqual(db.RemoveIf([](const Date &date, const string &event) {
            return date < Date{2017, 1, 1} and (event == "holiday" or event == "sport event");
        }), 1, "Database generalized check #2 Del command the third request");
    }
}