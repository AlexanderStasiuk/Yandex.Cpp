#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Напишите реализацию функции,
    // не копируя сортируемые элементы
    if (range_end - range_begin <= 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto border1 = begin(elements) + elements.size()/3;
    auto border2 = border1 + elements.size()/3;

    MergeSort(move(begin(elements)), move(border1));
    MergeSort(move(border1), move(border2));
    MergeSort(move(border2), move(end(elements)));

    vector<typename RandomIt::value_type> __temp__;

    merge(
        make_move_iterator(begin(elements)), make_move_iterator(border1),
        make_move_iterator(border1), make_move_iterator(border2), back_inserter(__temp__));
    merge(
        make_move_iterator(begin(__temp__)), make_move_iterator(end(__temp__)),
        make_move_iterator(border2), make_move_iterator(end(elements)), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
