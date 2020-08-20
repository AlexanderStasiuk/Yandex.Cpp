#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

template <typename First, typename Second> 
pair<First, Second> operator *(const pair<First, Second>& p1, const pair<First, Second>& p2);

template <typename T>
vector<T> operator * (const vector<T>& v1, const vector<T>& v2);

template <typename Key, typename Value>
map<Key, Value> operator * (const map<Key, Value>& m1, const map<Key, Value>& m2);


// Pair
template <typename First, typename Second>
pair<First, Second> operator * (const pair<First, Second>& p1, const pair<First, Second>& p2) {
    First f = p1.first * p1.first;
    Second s = p2.second * p2.second;
    return make_pair(f, s);
}

// Vector
template <typename T>
vector<T> operator * (const vector<T>& v1, const vector<T>& v2) {
    vector<T> result;
    for (int i=0; i<v1.size(); i++) {
        result.push_back(v1[i]*v2[i]);
    }
    return result;
}

// Map
template <typename Key, typename Value>
map<Key, Value> operator * (const map<Key, Value>& m1, const map<Key, Value>& m2) {
    map<Key, Value> result;
    for (auto [key, value]: m1) {
        result[key] = value*m2.at(key);
    }
    return result;
}


template <typename T>
T Sqr(T x) {
    return x*x;
}

int main() {
    cout << Sqr(3) << endl;

    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2.2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}