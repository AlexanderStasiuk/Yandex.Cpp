#include <iostream>
#include <vector>
#include <string>
using namespace std;


void handleCommand(vector<bool>& queue, string command, int value) {
    if (command == "COME") {
        queue.resize(queue.size()+value, false);
    };
    if (command == "WORRY") {
        queue[value] = true;
    };
    if (command == "QUIET") {
        queue[value] = false;
    };

    if (command == "WORRY_COUNT") {
        int counter = 0;
        for (auto item: queue) {
            if (item == true) {
                counter++;
            }
        }
        cout << counter << endl;
    };
}


int main() {
    int n;
    cin >> n;

    string command;
    int value;
    vector<bool> queue;


    for (int i=0; i<n; i++) {
        cin >> command;
        if (command != "WORRY_COUNT") {
            cin >> value;
        } else {
            value = 0;
        }
        handleCommand(queue, command, value);
    }

	return 0;
}