#pragma once

#include <istream>
#include <ostream>

using namespace std;

class Date {
public:
    Date() : year_(1), month_(1), day_(1) {};
    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {};
    void SetYear(int _year);
    int GetYear() const;
    void SetMonth(int _month);
    int GetMonth() const;
    void SetDay(int _day);
    int GetDay() const;
private:
    int year_;
    int month_;
    int day_;
};



ostream& operator <<(ostream& os, const Date& date);
istream& operator >>(istream& s, Date& date);
bool operator <(const Date& lhs, const Date& rhs);
bool operator ==(const Date& lhs, const Date& rhs);
bool operator !=(const Date& lhs, const Date& rhs);
bool operator <=(const Date& lhs, const Date& rhs);
bool operator >(const Date& lhs, const Date& rhs);
bool operator >=(const Date& lhs, const Date& rhs);

Date ParseDate(istream& is);