#include <iostream>
#include <map>
#include <string>
using namespace std;


void Dump(const map<string, string>& list) {
    if (list.size() == 0) {
        cout << "There are no countries in the world";
    } else {
        for (auto [key, value]: list) {
            cout << key << "/" << value << " ";
        }
    }
    cout << endl;
}

void About(map<string, string>& list, string country) {
    if (list.count(country) == 0) {
        cout << "Country " << country << " doesn't exist";
    } else {
        cout << "Country " << country << " has capital " << list[country];
    }
    cout << endl;
}

void Rename(map<string, string>& list, string oldCountryName, string newCountryName) {
    if (list.count(newCountryName)!=0 || list.count(oldCountryName)==0 || oldCountryName==newCountryName){
        cout << "Incorrect rename, skip";
    } else {
        cout << "Country " << oldCountryName << " with capital " <<
        list[oldCountryName] << " has been renamed to " << newCountryName;
        list[newCountryName] = list[oldCountryName];
        list.erase(oldCountryName);
    }
    cout << endl;
}

void ChangeCapital(map<string, string>& list, string country, string newCapital) {
    if (list.count(country) == 0){
        cout << "Introduce new country " << country << " with capital " << newCapital;
    } else if (list[country] == newCapital) {
        cout << "Country " << country << " hasn't changed its capital";
    } else {
        cout << "Country " << country << " has changed its capital from " 
        << list[country] << " to " << newCapital;
    }
    list[country] = newCapital;
    cout << endl;
}


int main() {
    string country;
    string newCapital;
    string oldCountryName;
    string newCountryName;
    map<string, string> countries;


    int n;
    cin >> n;
    string command;
    for (int i=0; i<n; i++) {
        cin >> command;
        if (command == "CHANGE_CAPITAL") {
            cin >> country >> newCapital;
            ChangeCapital(countries, country, newCapital);
        } else if (command == "RENAME") {
            cin >> oldCountryName >> newCountryName;
            Rename(countries, oldCountryName, newCountryName);
        } else if (command == "ABOUT") {
            cin >> country;
            About(countries, country);
        } else if (command == "DUMP") {
            Dump(countries);
        }
    }

	return 0;
}