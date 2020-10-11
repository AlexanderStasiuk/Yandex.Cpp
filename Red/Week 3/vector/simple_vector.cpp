// #include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() {
        data = nullptr;
        end_ = data;
        capacity = 0;
    }
    explicit SimpleVector(size_t size) {
        data = new T[size];
        end_ = data + size;
        capacity = size;
    }
    ~SimpleVector() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() { return data; }
    T* end() { return end_;}

    const T* begin() const { return data; }
    const T* end() const { return end_;}

    size_t Size() const {
        return end_ - data;
    }
    size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if (Capacity() == Size()) {
            if (capacity == 0) {
              capacity = 1;
            } else {
              capacity = 2*Capacity();
            }
            T* new_segment = new T[capacity];
            CopyData(data, new_segment);
            delete[] data;
            data = new_segment;
        }
        data[index_of_last_element] = value; 
        index_of_last_element ++;
        end_ = data + index_of_last_element;  
    }

private:
    T* data;
    T* end_;
    size_t capacity = 0;
    size_t index_of_last_element = 0;

    void CopyData(T* &from, T* &to) {
      T* from_ = from;
      T* to_ = to;
        while (from_ != end_) {
            *to_ = *from_;
            from_++;
            to_++;
        }
    }
};

void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}
