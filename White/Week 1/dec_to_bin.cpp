#include <iostream>
#include <vector>

using namespace std;


int main() {
	int n;
	vector<int> items;

	cin >> n;

	do  {
		items.push_back(n % 2);
		n = n / 2;
	} while (n>0);

	for (int i = items.size() - 1; i>=0; i--) {
		cout << items[i];
	}

	return 0;
}
