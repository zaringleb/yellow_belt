#pragma once

#include <sstream>

using namespace std;

class Date
{
private:
    int _year, _month, _day;
public:
    Date(int year, int month, int day);
    Date();
    ostream& print(ostream& os) const;
    istream& read(istream& is);
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
};

ostream& operator<<(ostream& os, const Date& dt);

istream& operator>>(istream& is, Date& dt);

Date ParseDate(istream& is);

void TestDatePrint();
void TestDatePrintLeadingNulls();
void TestDateRead();
void TestDateReadLeadingNulls();
void TestDateComparision();
void TestParseDate();
void TestParseEvent();