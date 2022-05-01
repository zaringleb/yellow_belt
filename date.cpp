#include "date.h"

#include <iostream>
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day) {
    _year = year;
    _month = month;
    _day = day;
}

Date::Date() {}

ostream& Date::print(ostream& os) const {
    char null_symbol = '0';
    os 
        << setfill(null_symbol) << setw(4) << _year
        << "-" << setfill(null_symbol) << setw(2) << _month
        << "-" << setfill(null_symbol) << setw(2) << _day;
    return os;
}

ostream& operator<<(ostream& os, const Date& dt)
{ return dt.print(os); }

istream& Date::read(istream& is) {
    is >> _year;
    if (is.get() != '-') {
        throw logic_error("Invalid date format");
    }
    is >> _month;
    if (is.get() != '-') {
        throw logic_error("Invalid date format");
    }
    is >> _day;

    
    return is;
}

istream& operator>>(istream& is, Date& dt)
{ return dt.read(is); }

Date ParseDate(istream& is) {
    Date d;
    is >> d;
    return d;
}

bool Date::operator<(const Date& other) const {
    return tie(_year, _month, _day) < tie(other._year, other._month, other._day);
}

bool Date::operator<=(const Date& other) const {
    return tie(_year, _month, _day) <= tie(other._year, other._month, other._day);
}

bool Date::operator>(const Date& other) const {
    return tie(_year, _month, _day) > tie(other._year, other._month, other._day);
}

bool Date::operator>=(const Date& other) const {
    return tie(_year, _month, _day) >= tie(other._year, other._month, other._day);
}

bool Date::operator==(const Date& other) const {
    return tie(_year, _month, _day) == tie(other._year, other._month, other._day);
}

bool Date::operator!=(const Date& other) const {
    return tie(_year, _month, _day) != tie(other._year, other._month, other._day);
}