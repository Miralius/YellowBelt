#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector<string> result;
    {
        auto wordBeginIt = s.cbegin();
        auto endWordIt = s.cbegin();
        while (endWordIt != s.cend()) {
            endWordIt = find_if(endWordIt, s.cend(), [](const auto &letter) {
                return letter == ' ';
            });
            result.emplace_back(wordBeginIt, endWordIt);
            if (endWordIt != s.cend())
            {
                wordBeginIt = ++endWordIt;
            }
        }
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}