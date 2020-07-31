#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;


void AllBuses(const map<string, vector<string>>& busStops) {
    if (busStops.size() == 0) {
        cout << "No buses" << endl;
    } else {
        for (auto [key, value]: busStops) {
            cout << "Bus " << key << ": ";
            for (string stop: value) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }
}

void About(map<string, string>& list, string country) {
    if (list.count(country) == 0) {
        cout << "Country " << country << " doesn't exist";
    } else {
        cout << "Country " << country << " has capital " << list[country];
    }
    cout << endl;
}


int main() {
    string bus;
    string stop;
    int stopCount;
    vector<string> route;
    map<vector<string>, int> buses;


    int n;
    cin >> n;
    int count;
    for (int i=0; i<n; i++) {
        cin >> count;
        for (int j=0; j<count; j++) {
            cin >> stop;
            route.push_back(stop);
        }
        if (buses.count(route) == 0) {
            buses[route] = buses.size()+1;
            cout << "New bus " << buses.size() << endl;
        } else {
            cout << "Already exists for " << buses[route] << endl;
        }
        route.clear();
    }

	return 0;
}