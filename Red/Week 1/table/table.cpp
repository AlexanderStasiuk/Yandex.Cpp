#include "test_runner.h"

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Реализуйте здесь шаблонный класс Table

template <typename T>
class Table {
private:
    vector<vector<T>> data;

public:
    Table(size_t rows, size_t columns) {
        Resize(rows, columns);
    }

    const vector<T>& operator [] (size_t idx) const {
        return data[idx];
    }

    vector<T>& operator [] (size_t idx) {
        return data[idx];
    }

    void Resize(size_t rows, size_t columns) {
        data.resize(rows);
        for (auto& item : data) {
            item.resize(columns);
        }
    }

    pair<size_t, size_t> Size() const {
        if (!data.empty() && !data[0].empty()) {
            return {data.size(), data[0].size()};
        }

        return  {0, 0};
    }

};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
