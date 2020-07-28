#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float N, A, B, X, Y;

	cin >> N >> A >> B >> X >> Y;

	if (N <= A) {
		cout << N;
	} else if (N > A && N <= B) {
        cout << N*(1-X/100);
    } else if (N > A && N > B) {
        cout << N*(1-Y/100);
    }

	return 0;
}