#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;


int main() {
    int n;
    cin >> n;

    string command;
    string word, word2;

    map<string, set<string>> m;


    for (int i=0; i<n; i++) {
        cin >> command;
        if (command == "ADD") {
            cin >> word >> word2;
            m[word].insert(word2);
            m[word2].insert(word);
        } else if (command == "CHECK") {
            cin >> word >> word2;
            if (m[word].count(word2) > 0 || m[word2].count(word) > 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (command == "COUNT") {
            cin >> word;
            cout << m[word].size() << endl;
        }
    }

	return 0;
}