#include <iostream>
#include <vector>
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


vector<string> PalindromFilter(vector<string> words, int len) {
	vector<string> result;
	for (string word: words) {
		if (IsPalindrom(word) == true && word.size() >= len) {
			result.push_back(word);
		}
	}
	return result;
}


int main() {
	for (string a: PalindromFilter({"sds", "sdf", "sdffs", "dsdsd"}, 2)){
		cout << a << " ";
	}
	return 0;
}