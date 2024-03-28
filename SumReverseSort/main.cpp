#include "sum_reverse_sort.h"
#include "../TestRunner/TestRunner.h"

int main()
{
    TestRunner runner;
    runner.RunTest([]() {
        AssertEqual(Sum(2, 2), 4, "Sum(2, 2) != 4");
        AssertEqual(Reverse("glavryba"), "abyrvalg", R"(Reverse("glavryba") != "abyrvalg")");
        vector<int> example = {1, 8, 4, 8};
        Sort(example);
        AssertEqual(example, vector<int>({1, 4, 8 ,9}), "example != {1, 4, 8 ,8}");
    }, "SumReverseSort tests");

    return 0;
}