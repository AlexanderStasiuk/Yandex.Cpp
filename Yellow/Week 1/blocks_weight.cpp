#include <iostream>
#include <vector>
using namespace std;

uint64_t block_capacity(vector<uint> size) {
    uint64_t capacity = 1;
    for (const uint& i: size) {
        capacity *= i;
    }
    return capacity;
}

uint64_t block_weight(int64_t capacity, uint density) {
    return capacity*density;
}

int main() {
    uint n, density;
    cin >> n >> density;
    vector<vector<uint>> a(n);
    for (size_t i=0; i<n; i++) {
        a[i] = vector<uint>(3);
        for (uint& item: a[i]) {
            cin >> item;
        }
    }

    uint64_t sum_weights = 0;
    for (const vector<uint>& size: a) {
        sum_weights += block_weight(block_capacity(size), density);
    }

    cout << sum_weights;
	return 0;
}