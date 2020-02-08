#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
private:
    int _year;
    int _month;
    int _day;

    int Validate(const int &value, const int &left, const int &right, const string &his);

public:
    Date() : _year(1), _month(1), _day(1) {}

    Date(const int &year, const int &month, const int &day)
            : _year(year),
              _month(Validate(month, 1, 12, "Month")),
              _day(Validate(day, 1, 31, "Day")) {}

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;
};

ostream &operator<<(ostream &stream, const Date &date);

Date ParseDate(istream &stream);

bool operator<(const Date &lhs, const Date &rhs);