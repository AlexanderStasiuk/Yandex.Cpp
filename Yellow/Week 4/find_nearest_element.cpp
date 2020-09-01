#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

#include <iterator>
#include <set>

set<int>::const_iterator FindNearestElement(const set<int>& numbers,
                                            int border) {
  const auto first = numbers.lower_bound(border);

  if (first == numbers.begin()) {
    return first;
  }

  const auto last = prev(first);
  if (first == numbers.end()) {
    return last;
  }

  const bool is_left = (border - *last <= *first - border);
  return is_left ? last : first;
}


int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}