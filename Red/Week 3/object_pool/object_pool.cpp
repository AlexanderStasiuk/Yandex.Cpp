#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        T* obj;
        if (free.size() == 0) {
            obj = new T;
        } else {
            obj = free.front();
            free.pop();
        }
        busy.insert(obj);
        return obj;
    }
    T* TryAllocate() {
        if (free.size() == 0) {
            return nullptr;
        }
        return Allocate();
    }

    void Deallocate(T* object) {
        auto it = busy.find(object);
        if (it == end(busy)) {
            throw invalid_argument("There isn't");
        }
        free.push(*it);
        busy.erase(it);
    }

    ~ObjectPool() {
        while (!free.empty())
        {
            delete free.front();
            free.pop();
        } 
        for (auto item: busy) {
            delete item;
        }
    }

private:
    queue<T*> free;
    set<T*> busy;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
