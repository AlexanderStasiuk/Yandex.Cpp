#include <iostream>
#include <vector>
using namespace std;


vector<uint> moreThanAverage(const vector<int>& v) {
    int64_t sum = 0;
    for (const int& item: v) {
        sum += item;
    }
    int average = sum/(static_cast<int>(v.size()));

    vector<uint> res;
    for (uint i=0; i<v.size(); i++) {
        if (v[i] > average) {
            res.push_back(i);
        }
    }

    return res;
}


int main() {
    uint n;
    cin >> n;
    vector<int> a(n);

    for (int& item: a) {
        cin >> item;
    }
	vector<uint> res = moreThanAverage(a);
    cout << res.size() << endl;
    for (const uint& i: res) {
        cout << i << " ";
    }
	return 0;
}