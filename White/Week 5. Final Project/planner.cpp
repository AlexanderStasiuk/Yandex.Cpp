#include<iostream>
#include<istream>
#include<sstream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<iomanip>
#include <ctype.h>
using namespace std;

class Date {
public:
    // ------------------- Setter and getter for Year -------------------
    void SetYear(int _year) {
        year = _year;
    }
    int GetYear() const {
        return year;
    };
    // ------------------- Setter and getter for Month -------------------
    void SetMonth(int _month) {
        if (_month >= 1 && _month <= 12) {
            month = _month;
        } else {
            throw invalid_argument("Month value is invalid: " + to_string(_month));
        }
    }
    int GetMonth() const {
        return month;
    };
    // ------------------- Setter and getter for Day -------------------
    void SetDay(int _day) {
         if (_day >= 1 && _day <= 31) {
            day = _day;
        } else {
            throw invalid_argument("Day value is invalid: " + to_string(_day));
        }
    }
    int GetDay() const {
        return day;
    };

private:
    int year;
    int month;
    int day;
};

void EnsureNextSymbol(istream& s, bool last) {
    char c;
    if (last == false) {
        s >> c;
        if (c != '-') {
            throw exception();
        } 
    } else if (s >> c) {
        throw exception();
    }
}

void CheckNextSymbol(istream& s, bool year) {
    if (year == true) {
        if (!isdigit(s.peek()) && (char(s.peek()) != '-') && (char(s.peek()) != '+')) {
            throw exception();
        }
    } else {
        if (!isdigit(char(s.peek())) && (char(s.peek()) != '+')){
            throw exception();
        }
    }
    
}

istream& operator >>(istream& s, Date& date) {
    Date _date;
    int year, month, day;
    CheckNextSymbol(s, true);
    s >> year;
    EnsureNextSymbol(s, false);
    CheckNextSymbol(s, false);
    s >> month;
    EnsureNextSymbol(s, false);
    CheckNextSymbol(s, false);
    s >> day;
    EnsureNextSymbol(s, true);
    _date.SetYear(year);
    _date.SetMonth(month);
    _date.SetDay(day);
    date = _date;
    return s;
}

bool operator <(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
};

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        database[date].insert(event);
    };
    bool DeleteEvent(const Date& date, const string& event) {
        if (database.count(date) > 0) {
            if (database.at(date).find(event) != database.at(date).end()) {
                database.at(date).erase(event);
                if (database.at(date).size() == 0) {
                    database.erase(date);
                }
                return true;
            }
        }
        return false;
    };
    int  DeleteDate(const Date& date) {
        int number_of_events = 0;
        if (database.count(date) > 0) {
            number_of_events = database.at(date).size();
            database.erase(date);
        }
        return number_of_events;
    };

    void Find(const Date& date) const {
        if (database.count(date) > 0) {
            for (const string& event: database.at(date)) {
                cout << event << endl;
            }
        }
    };
    
    void Print() const {
        for (auto& [date, set_of_events]: database) {
            for (const string& event: set_of_events) {
                cout << setw(4) << setfill('0') << date.GetYear() << '-'
                << setw(2) << setfill('0') << date.GetMonth() << '-'
                << setw(2) << setfill('0') << date.GetDay() << " ";        
                cout << event << endl;
            }
        }
    };
private:
    map<Date, set<string>> database;
};

bool ReadDate(stringstream& _stream, Date& date) {
    string str_date;
    _stream >> str_date;
    stringstream _str_date_stream(str_date);
    try {
        _str_date_stream >> date;
        return true;
    } catch (invalid_argument& ex) {
        cout << ex.what() << endl;
    } catch (exception&) {
        cout << "Wrong date format: " + str_date << endl;
    }
    return false;
}

int main() {
    Database db;
        
    string command;
    string command_type;
    Date date;
    string event;

    while (getline(cin, command)) {
        if (command == "") {
            continue;
        }

        stringstream _stream(command);
        _stream >> command_type;

        if (command_type == "Add") {
            if (ReadDate(_stream, date)) {
                _stream >> event;
                db.AddEvent(date, event);
            }
        } else if (command_type == "Del") {
            if (ReadDate(_stream, date)) {
                if (_stream >> event) {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                } else {
                    int number_deleted = db.DeleteDate(date);
                    cout << "Deleted " << to_string(number_deleted) + " events" << endl;
                }
            }
        } else if (command_type == "Find") {
            if (ReadDate(_stream, date)) {
                db.Find(date);
            }
        } else if (command_type == "Print") {
            db.Print();
        } else {
            cout << "Unknown command: " + command_type << endl;
        }
    }

    return 0;
}