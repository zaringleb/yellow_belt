
#include "date.h"
#include "test_runner.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

void TestDatePrint() {
  Date d = {2022, 10, 20};
  stringstream ss;
  ss << d;
  AssertEqual<string>(ss.str(), "2022-10-20", "1");
}

void TestDatePrintLeadingNulls() {
  Date d = {1, 1, 1};
  stringstream ss;
  ss << d;
  AssertEqual<string>(ss.str(), "0001-01-01", "1");
}

void TestDateRead() {
  stringstream ss_in, ss_out;
  ss_in << "2022-10-20";

  Date d;
  ss_in >> d;
  ss_out << d;
  AssertEqual<string>(ss_out.str(), "2022-10-20", "1");
}

void TestDateReadLeadingNulls() {
  stringstream ss_in, ss_out;
  ss_in << "0001-01-01";

  Date d;
  ss_in >> d;
  ss_out << d;
  AssertEqual<string>(ss_out.str(), "0001-01-01", "1");
}

void TestDateComparision() {
  Assert(Date(2022, 1, 5) < Date(2022, 1, 6), "1");
  Assert(Date(2022, 1, 7) < Date(2022, 2, 6), "2");
  Assert(Date(2022, 12, 30) < Date(2023, 1, 1), "3");
  AssertEqual(Date(2022, 1, 5) < Date(2022, 1, 5), false, "4");

  Assert(Date(2022, 1, 5) <= Date(2022, 1, 6), "5");
  Assert(Date(2022, 1, 7) <= Date(2022, 2, 6), "6");
  Assert(Date(2022, 12, 30) <= Date(2023, 1, 1), "7");
  Assert(Date(2022, 1, 5) <= Date(2022, 1, 5), "8");

  Assert(Date(2022, 1, 6) > Date(2022, 1, 5), "9");
  Assert(Date(2022, 2, 6) > Date(2022, 1, 7), "10");
  Assert(Date(2023, 1, 1) > Date(2022, 12, 30), "11");
  AssertEqual(Date(2022, 1, 5) > Date(2022, 1, 5), false, "12");

  Assert(Date(2022, 1, 6) >= Date(2022, 1, 5), "13");
  Assert(Date(2022, 2, 6) >= Date(2022, 1, 7), "14");
  Assert(Date(2023, 1, 1) >= Date(2022, 12, 30), "15");
  Assert(Date(2022, 1, 5) >= Date(2022, 1, 5), "16");

  Assert(Date(2022, 1, 5) == Date(2022, 1, 5), "17");
  AssertEqual(Date(2022, 1, 5) == Date(2022, 1, 6), false, "18");
  AssertEqual(Date(2022, 1, 5) == Date(2022, 2, 5), false, "19");
  AssertEqual(Date(2022, 1, 5) == Date(2023, 1, 5), false, "20");

  AssertEqual(Date(2022, 1, 5) != Date(2022, 1, 5), false, "21");
  Assert(Date(2022, 1, 5) != Date(2022, 1, 6), "22");
  Assert(Date(2022, 1, 5) != Date(2022, 2, 5), "23");
  Assert(Date(2022, 1, 5) != Date(2023, 1, 5), "24");
}

void TestParseDate() {
  stringstream ss;
  ss << "2022-10-20";
  AssertEqual(ParseDate(ss), Date(2022, 10, 20), "1");
}
