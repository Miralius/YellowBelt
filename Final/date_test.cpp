//
// Created by F-Mir on 4/1/2024.
//
#include "date.h"
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2

#include "../TestRunner/TestRunner.h"

#else
#include "test_runner.h"
#endif

#include <sstream>

void TestParseDate() {
    {
        istringstream is("0-1-1");
        AssertEqual(ParseDate(is), Date(0, 1, 1), "Parse date 0-1-1");
    }
    {
        istringstream is("9999-12-31");
        AssertEqual(ParseDate(is), Date(9999, 12, 31), "Parse date 9999-12-31");
    }
    {
        istringstream is("2017-11-07");
        AssertEqual(ParseDate(is), Date(2017, 11, 7), "Parse date 2017-11-07");
    }
    {
        istringstream is("0-2-31");
        AssertEqual(ParseDate(is), Date(0, 2, 31), "Parse date 0-2-31");
    }
}