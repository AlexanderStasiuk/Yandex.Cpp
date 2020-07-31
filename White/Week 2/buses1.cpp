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
    string newCountryName;
    map<string, vector<string>> busStops;
    map<string, vector<string>> stopBuses;


    int n;
    cin >> n;
    string command;
    for (int i=0; i<n; i++) {
        cin >> command;
        if (command == "NEW_BUS") {
            cin >> bus >> stopCount;
            for (int j=0; j<stopCount; j++) {
                cin >> stop;
                stopBuses[stop].push_back(bus);
                busStops[bus].push_back(stop);
            }
        } else if (command == "BUSES_FOR_STOP") {
            cin >> stop;
            if (stopBuses.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (string bus: stopBuses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
            }
        } else if (command == "STOPS_FOR_BUS") {
            cin >> bus;
            if (busStops.count(bus) == 0) {
                cout << "No bus" << endl;
            } else {
                for (string stop: busStops[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stopBuses[stop].size() == 1) {
                        cout << "no interchange" << endl;
                    } else {
                        for (string busDetal: stopBuses[stop]) {
                            if (busDetal != bus) {
                                cout << busDetal << " ";
                            }
                        }
                        cout << endl;
                    }
                }
            }
        } else if (command == "ALL_BUSES") {
            AllBuses(busStops);
        }
    }

	return 0;
}