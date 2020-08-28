#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto border1 = begin(elements) + elements.size()/3;
    auto border2 = border1 + elements.size()/3;

    MergeSort(begin(elements), border1);
    MergeSort(border1, border2);
    MergeSort(border2, end(elements));

    vector<typename RandomIt::value_type> __temp__;

    merge(begin(elements), border1, border1, border2, back_inserter(__temp__));
    merge(begin(__temp__), end(__temp__), border2, end(elements), range_begin);
}


int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}