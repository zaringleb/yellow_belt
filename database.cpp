#include "database.h"
#include <algorithm>
#include <exception>

ostream& operator<<(ostream& os, const Record& record)
{
    os << record.date << " " << record.event;
    return os;
}


void Database::Add(const Date& date, const string& event) {
    //cerr << "comand: Add " << date << " " << event << endl;
    auto p = make_pair(date, event);
    if (uniq_events.find(p) == uniq_events.end()) {
        records[date].push_back(event);
        uniq_events.insert(p);
    }
}

void Database::Print(ostream& os) const {
    //cerr << "comand: Print " << endl;
    for(auto const& [date, events]: records) {
        for (const string& event: events) {
            os << date << " " << event << endl;
        }
    }
}

Record Database::Last(const Date& date) const {
    //cerr << "comand: Last " << date << endl;
    auto it = records.upper_bound(date);
    if (it == records.begin()) {
        throw invalid_argument("no records before this date");
    }
    --it;

    const auto & events = it->second;
    Record rec = {it->first, events[events.size() - 1]};
    return rec;
}