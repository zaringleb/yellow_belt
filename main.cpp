#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

string ParseEvent(istream& is) {
  string event;
  getline(is >> ws, event);
  return event;
}

void TestAll();


void DoMain(istream& input, ostream& output) {
  Database db;

  for (string line; getline(input, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(output);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      output << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        output << entry << endl;
      }
      output << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          output << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          output << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
}

void TestDatabase();

int main() {
  //TestAll();

  DoMain(cin, cout);
  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestDatabase() {
  {
    ostringstream os;
    istringstream is(
      "Add 2017-06-01 1st of June\n"
      "Add 2017-07-08 8th of July\n"
      "Add 2017-07-08 Someone's birthday\n"
      "Del date == 2017-07-08\n"
      );
    DoMain(is, os);
    AssertEqual(os.str(), "Removed 2 entries\n", "1");
  }
  {
    ostringstream os;
    istringstream is(
      "Add 2017-01-01 Holiday\n"
      "Add 2017-03-08 Holiday\n"
      "Add 2017-1-1 New Year\n"
      "Add 2017-1-1 New Year\n"
      "Print\n"
      );
    DoMain(is, os);
    AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", "2");
  }
  {
    ostringstream os;
    istringstream is(
      "Add 2017-01-01 New Year\n"
      "Add 2017-03-08 Holiday\n"
      "Add 2017-01-01 Holiday\n"
      "Last 2016-12-31\n"
      "Last 2017-01-01\n"
      "Last 2017-06-01\n"
      "Add 2017-05-09 Holiday\n"
      );
    DoMain(is, os);
    AssertEqual(os.str(), "No entries\n2017-01-01 Holiday\n2017-03-08 Holiday\n", "Last test");
  }
  {
    ostringstream os;
    istringstream is(
      "Add 2017-11-17 One more event\n"
      "Add 2017-11-17 Friday\n"
      "Add 2017-11-17 Hey ho!\n"
      "Del event == \"Hey ho!\"\n"
      "Last 2017-11-17\n"
      );
    DoMain(is, os);
    AssertEqual(os.str(), "Removed 1 entries\n2017-11-17 Friday\n", "Del test");
  }
}

void TestAll() {
  TestRunner tr;

  tr.RunTest(TestDatePrint, "TestDatePrint");
  tr.RunTest(TestDatePrintLeadingNulls, "TestDatePrintLeadingNulls");
  tr.RunTest(TestDateRead, "TestDateRead");
  tr.RunTest(TestDateReadLeadingNulls, "TestDateReadLeadingNulls");
  tr.RunTest(TestDateComparision, "TestDateComparision");
  tr.RunTest(TestParseDate, "TestParseDate");

  tr.RunTest(TestParseEvent, "TestParseEvent");

  tr.RunTest(TestParseCondition, "TestParseCondition");

  tr.RunTest(TestDatabase, "TestDatabase");
}

