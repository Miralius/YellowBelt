#include <vector>
#include <iostream>
#include <map>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& map, const Key& key)
{
    auto it = map.find(key);
    if (it != map.end())
    {
        return it->second;
    }
    throw runtime_error("");
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}