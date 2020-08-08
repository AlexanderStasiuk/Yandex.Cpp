#include<iostream>
using namespace std;


bool EnsureEqual(const string& a, const string& b) {
    if (a != b) {    
        throw runtime_error(a + " != " + b);
    }
    return true;
}

int main() {
  try {
    EnsureEqual("C++ White", "C++ White");
    EnsureEqual("C++ White", "C++ Yellow");
  } catch (runtime_error& e) {
    cout << e.what() << endl;
  }
  return 0;
}