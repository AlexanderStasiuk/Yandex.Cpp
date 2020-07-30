#include <iostream>
#include <vector>
using namespace std;


void Swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}


void Reverse(vector<int>& v) {
    int lastIndex = v.size() - 1;
    for (int i=0; i<(v.size())/2; i++) {
        Swap(v[i], v[lastIndex-i]);
    }
}


int main() {
    vector<int> a = {1, 4, 5, 3, 2};
	Reverse(a);
    for (auto i: a) {
        cout << i << " ";
    }
	return 0;
}