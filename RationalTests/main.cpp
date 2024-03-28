#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
// The #if is needed for stepik check system submitting if we use the whole file
#if __GNUC__ == 13 && __GNUC_MINOR__ == 2
#include "Rational.h"
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
        Rational fraction;
        AssertEqual(fraction.Numerator(), 0);
        AssertEqual(fraction.Denominator(), 1);
    }, "Default ctor with zero value");
    runner.RunTest([]() {
        Rational fraction(4, 6);
        AssertEqual(fraction.Numerator(), 2);
        AssertEqual(fraction.Denominator(), 3);
    }, "Reduced fraction");
    runner.RunTest([]() {
        Rational fraction(4, -6);
        AssertEqual(fraction.Numerator(), -2);
        AssertEqual(fraction.Denominator(), 3);
    }, "Reduced negative fraction");
    runner.RunTest([]() {
        Rational fraction(-4, -6);
        AssertEqual(fraction.Numerator(), 2);
        AssertEqual(fraction.Denominator(), 3);
    }, "Reduced positive fraction");
    runner.RunTest([]() {
        Rational fraction(-0, -7);
        AssertEqual(fraction.Numerator(), 0);
        AssertEqual(fraction.Denominator(), 1);
    }, "Zero fraction");
    return 0;
}