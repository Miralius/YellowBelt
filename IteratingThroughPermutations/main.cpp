#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> permutations(N);
    iota(permutations.begin(), permutations.end(), 1);
    reverse(permutations.begin(), permutations.end());
    do
    {
        for (int x : permutations) {
            cout << x << " ";
        }
        cout << '\n';
    }
    while (prev_permutation(permutations.begin(), permutations.end()));
    return 0;
}