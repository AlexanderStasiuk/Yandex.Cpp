#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

struct DateOfBearth {
    int day;
    int month;
    int year;
};

struct Student {
    string first_name;
    string last_name;
    DateOfBearth birthday;
};


int main() {

    map<int, Student> list;

    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        Student student;
        cin >> student.first_name >> student.last_name;
        DateOfBearth birthday;
        cin >> birthday.day >> birthday.month >> birthday.year;
        student.birthday = birthday;
        list[i+1] = student;
    }


    int m;
    cin >> m;
    string command;
    int param;

    for (int i=0; i<m; i++) {
        cin >> command >> param;
        if ((command == "name" || command == "date") && param > 0  && param <= 10000) {
            if (list.count(param) == 0){
                cout << "bad request";
            } else if (command == "name") {
                cout << list[param].first_name << ' ' << list[param].last_name;
            } else if (command == "date") {
                cout << list[param].birthday.day << '.' 
                << list[param].birthday.month << '.' << list[param].birthday.year;
            }
        } else {
            cout << "bad request";
        }
        cout << endl;
    }

    return 0;
}