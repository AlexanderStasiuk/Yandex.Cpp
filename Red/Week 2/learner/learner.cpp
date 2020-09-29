#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

#include "profile.h"

using namespace std;

class Learner {
private:
    set<string> dict;
public:
    int Learn(const vector<string>& words) {
        LOG_DURATION("Learn");
        int start = dict.size();
        for (const auto& word : words) {
            dict.insert(word);
        }
        return dict.size()-start;
    }

  vector<string> KnownWords() {
    return vector<string> (begin(dict), end(dict));
  }
};

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
