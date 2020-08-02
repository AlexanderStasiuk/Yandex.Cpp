#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;


bool func(int i,int j) { 
    return (abs(i)<abs(j));
}


int main() {
    int n;
    cin >> n;
    
    vector<int> v;
    int i_in;
    for (int i=0; i<n; i++) {
        cin >> i_in;
        v.push_back(i_in);
    }

    sort(begin(v), end(v), func);

    for (auto i: v) {
        cout << i << " ";
    }

	return 0;
}