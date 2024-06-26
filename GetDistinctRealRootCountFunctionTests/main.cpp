#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x: s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x: s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv: m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

[[maybe_unused]] void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
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

int GetDistinctRealRootCount(double a, double b, double c) {
    if (abs(a) < 0.0000001)
    {
        if (abs(b) < 0.0000001)
        {
            return 0;
        }
        return 1;
    }
    auto discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        return 2;
    } else if (abs(discriminant) < 0.000001) {
        return 1;
    } else return 0;
}

int main() {
    TestRunner runner;
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(1, 5, 4), 2);
    }, "different factors, two roots");
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(1, 3, 2.25), 1);
    }, "different factors, one root");
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(2, 1, 4), 0);
    }, "different factors, no roots");
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(10, 10, 10), 0);
    }, "the same factors, no roots");
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(0, 5, 4), 1);
    }, "zero a, one root");
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(0, 0, 4), 0);
    }, "zero a and b, no roots");
    runner.RunTest([]() {
        AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1);
    }, "zero a and c, one root");
    return 0;
}
