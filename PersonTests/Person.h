#pragma once

#include <string>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstNames.insert_or_assign(year, first_name);
    }
    void ChangeLastName(int year, const string& last_name) {
        lastNames.insert_or_assign(year, last_name);
    }
    string GetFullName(int year) {
        auto recentFirstName = firstNames.upper_bound(year);
        auto recentLastName = lastNames.upper_bound(year);
        if (recentFirstName != firstNames.cbegin() and recentLastName != lastNames.cbegin())
        {
            return (--recentFirstName)->second + ' ' + (--recentLastName)->second;
        }
        else if (recentFirstName != firstNames.cbegin())
        {
            return (--recentFirstName)->second + " with unknown last name";
        }
        else if (recentLastName != lastNames.cbegin())
        {
            return (--recentLastName)->second + " with unknown first name";
        }
        else
        {
            return "Incognito";
        }
    }
private:
    map<int, string> firstNames;
    map<int, string> lastNames;
};