#include <iostream>
#include <vector>
using namespace std;


vector<int> moreThanAverage(vector<int> v) {
    int sum = 0;
    for (auto item: v) {
        sum += item;
    }
    int average = sum/v.size();

    vector<int> res;
    for (int i=0; i<v.size(); i++) {
        if (v[i] > average) {
            res.push_back(i);
        }
    }

    return res;
}


int main() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (int& item: a) {
        cin >> item;
    }
	vector<int> res = moreThanAverage(a);
    cout << res.size() << endl;
    for (auto i: res) {
        cout << i << " ";
    }
	return 0;
}