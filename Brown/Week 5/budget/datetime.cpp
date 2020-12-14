#include <datetime.h>

#include <sstream>


Date& Date::FromString(const std::string& str_date)
{
	std::stringstream buff;

    for (const char& ch : str_date) {
		ch == '-' ? buff << ' ' : buff << ch;
    }

	buff >> year_ >> month_ >> day_;

	return *this;
}


time_t Date::AsTimeStamp() const {
	std::tm t;
	t.tm_sec = 0;
	t.tm_min = 0;
	t.tm_hour = 0;
	t.tm_mday = day_;
	t.tm_mon = month_ - 1;
	t.tm_year = year_ - 1900;
	t.tm_isdst = 0;
	return mktime(&t);
}


long long Date::ComputeDaysDiff(const Date& date_from, const Date& date_to) {
	const time_t timestamp_to = date_to.AsTimeStamp();
	const time_t timestamp_from = date_from.AsTimeStamp();
	const auto SECONDS_IN_DAY = 60 * 60 * 24;
	
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}


size_t Date::GetIndexFromDay(const Date& date) {
	return static_cast<size_t>(ComputeDaysDiff(Date(2000, 1, 1), date));
}


std::istream& operator>>(std::istream& input, Date& date) {
	std::string str_date;
	input >> str_date;

	date = Date().FromString(str_date);

	return input;
}


std::ostream& operator<<(std::ostream& input, const Date& date) {
	input << date.year_ << "-" << date.month_ << "-" <<
		date.day_;

	return input;
}


bool operator!=(const Date& lhs, const Date& rhs) {
	return lhs.year_ != rhs.year_ ||
		lhs.month_ != rhs.month_ ||
		lhs.day_ != rhs.day_;
}