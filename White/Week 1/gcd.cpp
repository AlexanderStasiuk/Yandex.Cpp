#include <iostream>

using namespace std;

// gcd - greatest common divisor

int main() {
	int a;
	int b;

	cin >> a >> b;

	while ((a != 0) && (b != 0)) {
		if (a > b) {
			a = a % b;
		} else {
			b = b % a;
		}
	}

	cout << a+b;

	return 0;
}
