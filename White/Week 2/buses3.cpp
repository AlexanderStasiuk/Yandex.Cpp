#include <iostream>
#include <map>
#include <set>
using namespace std;


int main() {
    string stop;
    map<set<string>, int> buses;
    set<string> current_route;
    int current_number = 1;


    int n;
    cin >> n;
    int count;
    for (int i=0; i<n; i++) {
        cin >> count;
        for (int j=0; j<count; j++) {
            cin >> stop;
            current_route.insert(stop);
        }
        if (buses.count(current_route) == 0) {
            buses[current_route] = current_number;
            cout << "New bus " << current_number << endl;
            current_number++;
        } else {
            cout << "Already exists for " << buses[current_route] << endl;
        }
        current_route.clear();
    }

	return 0;
}