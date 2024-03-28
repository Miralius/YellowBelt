#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2
#include "Person.h"
#endif

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

[[maybe_unused]] void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

int main() {
    TestRunner runner;
    runner.RunTest([]() {
        Person person;
        person.ChangeFirstName(1965, "Polina");
        AssertEqual(person.GetFullName(1900), "Incognito");
    }, "FullName before the first record with first name");
    runner.RunTest([]() {
        Person person;
        person.ChangeLastName(1965, "Polina");
        AssertEqual(person.GetFullName(1900), "Incognito");
    }, "FullName before the first record with last name");
    runner.RunTest([]() {
        Person person;
        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1966, "Sergeeva");
        AssertEqual(person.GetFullName(1900), "Incognito");
    }, "FullName before the first record with first and last name");
    runner.RunTest([]() {
        Person person;
        person.ChangeFirstName(1965, "Polina");
        AssertEqual(person.GetFullName(1965), "Polina with unknown last name");
    }, "Only first name in the same year");
    runner.RunTest([]() {
        Person person;
        person.ChangeLastName(1967, "Sergeeva");
        AssertEqual(person.GetFullName(1967), "Sergeeva with unknown first name");
    }, "Only last name in the same year");
    runner.RunTest([]() {
        Person person;
        person.ChangeFirstName(1965, "Polina");
        AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
    }, "Only first name after the record with first name");
    runner.RunTest([]() {
        Person person;
        person.ChangeLastName(1965, "Sergeeva");
        AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
    }, "Only last name after the record with last name");
    runner.RunTest([]() {
        Person person;
        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
    }, "Only first name between the record with first name and the record with last name");
    runner.RunTest([]() {
        Person person;
        person.ChangeFirstName(1967, "Polina");
        person.ChangeLastName(1965, "Sergeeva");
        AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
    }, "Only last name between the record with last name and the record with first name");
    runner.RunTest([]() {
        Person person;
        person.ChangeLastName(1967, "Sergeeva");
        person.ChangeFirstName(1965, "Polina");
        AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
    }, "Full name after two records");
    runner.RunTest([]() {
        Person person;
        person.ChangeLastName(1967, "Sergeeva");
        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Volkova");
        person.ChangeFirstName(1965, "Apolinar");
        AssertEqual(person.GetFullName(1967), "Apolinar Volkova");
    }, "Two records with the same year");
    runner.RunTest([]() {
        Person person;
        person.ChangeLastName(1967, "Sergeeva");
        person.ChangeFirstName(1965, "Polina");
        person.ChangeFirstName(1970, "Apolinar");
        person.ChangeLastName(1968, "Volkova");
        AssertEqual(person.GetFullName(1900), "Incognito");
        AssertEqual(person.GetFullName(1965), "Polina with unknown last name");
        AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
        AssertEqual(person.GetFullName(1968), "Polina Volkova");
        AssertEqual(person.GetFullName(1970), "Apolinar Volkova");
    }, "Full name with several records");
    return 0;
}
