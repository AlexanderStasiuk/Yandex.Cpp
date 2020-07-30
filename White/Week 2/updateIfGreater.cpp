#include <iostream>
using namespace std;


void UpdateIfGreater(int first, int& second) {
    if (first > second) {
        second = first;
    }
}


int main() {
    int a = 8;
    int b = 6;
	UpdateIfGreater(a, b);
    cout << a << b;
	return 0;
}