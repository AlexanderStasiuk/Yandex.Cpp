#include <iostream>
#include <vector>
#include <string>
using namespace std;


void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (string item: source) {
        destination.push_back(item);
    }
    source.clear();
}


int main() {
    vector<string> a = {"ewew1", "2"};
    vector<string> b = {"3", "345"};
	MoveStrings(a, b);
    for (auto i: a) {
        cout << i << " ";
    }
    cout << endl;
    for (auto i: b) {
        cout << i << " ";
    }
	return 0;
}