#include "date.h"

using namespace std;


int Date::Validate(const int &value, const int &left, const int &right, const string &his) {
    if (value < left || value > right) {
        throw invalid_argument(his + " value is invalid: " + to_string(value));
    }
    return value;
}

int Date::GetYear() const {
    return this->_year;
}

int Date::GetMonth() const {
    return this->_month;
}

int Date::GetDay() const {
    return this->_day;
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2)
           << date.GetDay();
    return stream;
}

Date ParseDate(istream &stream) {
    string input;
    stream >> input;
    stringstream ss(input);
    int day, year, month;
    if (!(ss >> year) || ss.peek() != '-') {
        throw invalid_argument("Wrong date format: " + input);
    }
    ss.ignore(1);
    if (!(ss >> month) || ss.peek() != '-') {
        throw invalid_argument("Wrong date format: " + input);
    }
    ss.ignore(1);
    if (!(ss >> day) || ss.peek() != EOF) {
        throw invalid_argument("Wrong date format: " + input);
    }
    return Date(year, month, day);
}

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    }
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() < rhs.GetMonth()) {
            return true;
        }
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() < rhs.GetDay()) {
                return true;
            }
        }
    }
    return false;
}
