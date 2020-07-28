#include <iostream>
using namespace std;


int Factorial(int x) {
	if (x<1) {
		return 1;
	}
	int result = 1;
	for (int i=1; i<=x; i++){
		result *= i;
	}
	return result;
}


int main() {
	int x;
	cin >> x;

	cout << Factorial(x);

	return 0;
}