#include <vector>
#include <iostream>
#include <map>

using namespace std;

template<typename T>
T Sqr(const T& value);

template<typename F, typename S>
pair<F, S> Sqr(const pair<F, S>& inputPair);

template<typename T>
vector<T> Sqr(const vector<T>& inputVector);

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& inputMap);


template<typename T>
T Sqr(const T& value)
{
    return value * value;
}

template<typename F, typename S>
pair<F, S> Sqr(const pair<F, S>& inputPair)
{
    return make_pair(Sqr(inputPair.first), Sqr(inputPair.second));
}

template<typename T>
vector<T> Sqr(const vector<T>& inputVector)
{
    vector<T> result;
    result.reserve(inputVector.size());
    for (const auto& value : inputVector)
    {
        result.emplace_back(Sqr(value));
    }
    return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& inputMap)
{
    map<K, V> result;
    for (const auto& [key, value] : inputMap)
    {
        result[key] = Sqr(value);
    }
    return result;
}

int main()
{
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}