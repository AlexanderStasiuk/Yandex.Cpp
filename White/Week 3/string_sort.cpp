#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;


bool func(string i,string j) { 
    for (auto& ch: i) {
        ch = tolower(ch);
    }
    for (auto& ch: j) {
        ch = tolower(ch);
    }
    return (i<j);
}


int main() {
    int n;
    cin >> n;
    
    vector<string> v;
    string i_in;

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