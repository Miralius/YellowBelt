#include <sstream>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const std::string &international_number) {
    stringstream numberStream(international_number);
    char sign;
    numberStream >> sign;
    if (sign != '+')
    {
        throw invalid_argument("");
    }
    getline(numberStream, country_code_, '-');
    getline(numberStream, city_code_, '-');
    numberStream >> local_number_;
    if (!numberStream)
    {
        throw invalid_argument("");
    }
}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + '-' + city_code_ + '-' + local_number_;
}