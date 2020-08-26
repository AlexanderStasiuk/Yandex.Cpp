#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto it = begin(s);
    auto end_it = begin(s);
    do {
        end_it = find_if(
            it, end(s),
            [](const char& c) {
                return c == ' ';
            }
        );
        result.push_back(string(it, end_it));
        it = end_it;
        it++;
    } while (end_it != end(s));
    return result;
}


int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
