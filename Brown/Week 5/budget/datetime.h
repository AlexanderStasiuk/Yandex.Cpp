#pragma once

#include <ctime>
#include <string>

class Date {
public:
	Date() = default;

    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

	Date& FromString(const std::string& str_date);

	time_t AsTimeStamp() const;

	static long long ComputeDaysDiff(const Date& date_from, const Date& date_to);

	static size_t GetIndexFromDay(const Date& date);

private:
	int year_, month_, day_;

	friend void TestReadDate();

    friend std::ostream& operator<<(std::ostream& input, const Date& date);

	friend bool operator !=(const Date& lhs, const Date& rhs);
};


std::istream& operator>>(std::istream& input, Date& date);


std::ostream& operator<<(std::ostream& input, const Date& date);