#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

void Assert(bool b, const string& hint) {
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

bool IsPalindrom(const string& str) {
    auto begin = str.cbegin();
    auto end = str.cend();
    if (begin == end or begin == --end)
    {
        return true;
    }
    while (begin != str.cend())
    {
        if (*begin != *end)
        {
            return false;
        }
        ++begin;
        --end;
    }
    return true;
}

int main() {
    TestRunner runner;
    runner.RunTest([]() {
        Assert(IsPalindrom(""), "Empty string");
    }, "Empty string");
    runner.RunTest([]() {
        Assert(IsPalindrom("a"), "a");
        Assert(IsPalindrom(" "), "space char");
        Assert(IsPalindrom("\n"), "enter char");
        Assert(IsPalindrom("0"), "digit");
    }, "One letter string");
    runner.RunTest([]() {
        Assert(IsPalindrom("aca"), "only letters");
        Assert(!IsPalindrom("abc"), "non-palindrome");
        Assert(IsPalindrom("ab ba"), "palindrome with one space");
        Assert(!IsPalindrom(" ab ba"), "palindrome with space on the front");
        Assert(!IsPalindrom("ab ba "), "palindrome with space on the back");
        Assert(IsPalindrom("a1 b\nb 1a"), "chars with spaces");
    }, "Odd letter count");
    runner.RunTest([]() {
        Assert(IsPalindrom("acca"), "only letters");
        Assert(!IsPalindrom("abcd"), "non-palindrome");
        Assert(IsPalindrom("ab  ba"), "palindrome with in-between spaces");
        Assert(!IsPalindrom(" abc cba"), "palindrome with space on the front");
        Assert(!IsPalindrom("abc cba "), "palindrome with space on the back");
        Assert(IsPalindrom("a1 b\n\nb 1a"), "chars with spaces");
    }, "Even letter count");
    return 0;
}