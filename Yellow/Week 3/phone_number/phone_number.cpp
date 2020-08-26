#include<phone_number.h>
#include<string>
#include <iostream>
#include <sstream>

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream input_stream(international_number);

  char first_symbol = input_stream.get();
  getline(input_stream, country_code_, '-');
  getline(input_stream, city_code_, '-');
  getline(input_stream, local_number_);

  if (first_symbol != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Incorrect value in constructor: " + international_number);
  }
};

string PhoneNumber :: GetCountryCode() const {
    return country_code_;
};

string PhoneNumber :: GetCityCode() const {
    return city_code_;
};

string PhoneNumber :: GetLocalNumber() const {
    return local_number_;
};

string PhoneNumber :: GetInternationalNumber() const {
    return  '+' + country_code_ +
            '-' + city_code_ +
            '-' + local_number_;
};