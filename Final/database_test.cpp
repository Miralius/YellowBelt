//
// Created by F-Mir on 4/1/2024.
//
#include "main.h"
#include "database.h"
#include "condition_parser.h"
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2

#include "../TestRunner/TestRunner.h"

#else
#include "test_runner.h"
#endif

#include <sstream>

void TestDatabase() {
    {
        Database db;
        istringstream is("Add 2017-11-07 big sport event");
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        db.Add(date, event);

        is = istringstream("date == 2017-11-07");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };

        const auto entries = db.FindIf(predicate);
        Assert(entries.size() == 1, "Database 'found 1 entries' after adding");
        AssertEqual(*entries.cbegin(), "big sport event", "Database checks 'Add 2017-11-07 big sport event' work");
    }
}