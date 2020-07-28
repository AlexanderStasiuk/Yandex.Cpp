#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float a;
	float b;
	float c;

	cin >> a >> b >> c;

	if (a == 0 && b == 0) {
		cout << "";
	}
	if (a == 0 && b != 0) {
		cout << (-1*c)/b;
	}
	if (a != 0) {
        if ((b*b-4*a*c) == 0) {
            cout << ((-1*b) - sqrt(b*b-4*a*c))/(2*a);
        }
        if ((b*b-4*a*c) < 0) {
            cout << "";
        } 
        if ((b*b-4*a*c) > 0) {
            cout << ((-1*b) - sqrt(b*b-4*a*c))/(2*a) << " " << ((-1*b) + sqrt(b*b-4*a*c))/(2*a);
        }

	}

	return 0;
}
