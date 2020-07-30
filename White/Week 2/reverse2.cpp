#include <iostream>
#include <vector>
using namespace std;


vector<int> Reversed(const vector<int>& v) {
    vector<int> res;
    int lastIndex = v.size() - 1;
    for (int i=0; i<v.size(); i++) {
        res.push_back(v[lastIndex-i]);
    }
    return res;
}


int main() {
    vector<int> a = {1, 4, 5, 3, 2};
	a = Reversed(a);
    for (auto i: a) {
        cout << i << " ";
    }
	return 0;
}