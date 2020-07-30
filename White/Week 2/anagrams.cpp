#include <iostream>
#include <map>
#include <string>
using namespace std;


bool isAnagram(const string& word1, const string& word2) {
    if (word1.size() != word2.size()) {
        return false;
    }
    
    map<char, int> dict1;
    map<char, int> dict2;
    for (int i = 0; i<word1.size(); i++) {
        dict1[word1[i]]++;
        dict2[word2[i]]++;
    }
    
    if (dict1 == dict2) {
        return true;
    } else {
        return false;
    }
}


int main() {
    int n;
    cin >> n;

    string word1;
    string word2;

    for (int i=0; i<n; i++) {
        cin >> word1 >> word2;
        if (isAnagram(word1, word2) == true) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

	return 0;
}