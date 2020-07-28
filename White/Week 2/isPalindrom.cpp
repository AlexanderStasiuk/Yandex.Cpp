#include <iostream>
#include <string>
using namespace std;


bool IsPalindrom(string s) {
	int numberOfSymbols = s.size() - 1;
	for (int i=0; i<=numberOfSymbols/2; i++) {
		if (s[i] != s[numberOfSymbols-i]) {
			return false;
		}
	}
	return true;
}


int main() {
	string s;
	cin >> s;

	cout << IsPalindrom(s);

	return 0;
}
