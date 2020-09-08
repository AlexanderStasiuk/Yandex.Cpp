#include <date.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>


void Date::SetYear(int _year) {
    year_ = _year;
};

int Date::GetYear() const {
    return year_;
};

void Date::SetMonth(int _month) {
    if (_month >= 1 && _month <= 12) {
        month_ = _month;
    } else {
        throw invalid_argument("Month value is invalid: " + to_string(_month));
    }
};

int Date::GetMonth() const {
    return month_;
};

void Date::SetDay(int _day) {
        if (_day >= 1 && _day <= 31) {
        day_ = _day;
    } else {
        throw invalid_argument("Day value is invalid: " + to_string(_day));
    }
};

int Date::GetDay() const {
    return day_;
};

bool operator <(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
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

ostream& operator <<(ostream& os, const Date& date) {
    os <<   setw(4) << setfill('0') << date.GetYear() << '-'
            << setw(2) << setfill('0') << date.GetMonth() << '-'
            << setw(2) << setfill('0') << date.GetDay();
    return os;
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay();
}

bool operator!=(const Date& lhs, const Date& rhs) 
{ 
    return !(lhs == rhs); 
}

bool operator<=(const Date& lhs, const Date& rhs) 
{ 
    return (lhs < rhs) || (lhs == rhs); 
}

bool operator>(const Date& lhs, const Date& rhs) 
{ 
    return (lhs != rhs) && !(lhs < rhs); 
}

bool operator>=(const Date& lhs, const Date& rhs) 
{ 
    return (lhs > rhs) || (lhs == rhs); 
}