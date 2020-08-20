#include <iostream>
#include <map>
using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
    if (m.count(k) > 0) {
        return m[k];
    }
    throw runtime_error("Haven't this key!");
}

int main() {
    try {
        map<int, string> m = {{0, "value"}};
        string& item = GetRefStrict(m, 1);
        item = "newvalue";
        cout << m[0] << endl; // выведет newvalue
    } catch (runtime_error& e) {
        cout << "Exception: " << e.what() << endl;
    }
}