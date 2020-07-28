#include <iostream>
#include <string>

using namespace std;

int main() {
	string x;
	string y;
	string z;

	cin >> x >> y >> z;

	string min = x;

	if (y < min) {
		min = y;
	}
	if (z < min) {
		min = z;
	}


	cout << min;
	return 0;
}