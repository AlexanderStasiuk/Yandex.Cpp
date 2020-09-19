#include "airline_ticket.h"
#include "test_runner.h"

#include <iomanip>
#include <numeric>

using namespace std;

#define UPDATE_FIELD(ticket, field, values) if (values.find(#field) != end(values)) {    \
                                                istringstream is(values.at(#field));     \
                                                is >> ticket.field;                     \
                                            }


bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator==(const Time& lhs, const Time& rhs) {
    return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

bool operator <(const Date& lhs, const Date& rhs) {
    if (lhs.year == rhs.year) {
        if (lhs.month == rhs.month) {
            return lhs.day < rhs.day;
        }
        return lhs.month < rhs.month;
    }
    return lhs.year < rhs.year;
}

bool operator <(const Time& lhs, const Time& rhs) {
    if (lhs.hours == rhs.hours) {
        return lhs.minutes < rhs.minutes;
    }
    return lhs.hours < rhs.hours;
}

ostream& operator <<(ostream& os, const Time& time) {
    os  << setw(2) << setfill('0') << time.hours << ':'
        << setw(2) << setfill('0') << time.minutes;
    return os;
}

ostream& operator <<(ostream& os, const Date& date) {
    os <<   setw(4) << setfill('0') << date.year << '-'
            << setw(2) << setfill('0') << date.month << '-'
            << setw(2) << setfill('0') << date.day;
    return os;
}

istream& operator >>(istream& s, Date& date) {
    s >> date.year;
    s.ignore();
    s >> date.month;
    s.ignore();
    s >> date.day;
    return s;
}

istream& operator >>(istream& s, Time& time) {
    s >> time.hours;
    s.ignore();
    s >> time.minutes;
    return s;
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
