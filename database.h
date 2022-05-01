#pragma once

#include "date.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <utility>

struct Record
{
    const Date date;
    const string event;
};

ostream& operator<<(ostream& os, const Record& record);

class Database
{
private:
    map<Date, vector<string>> records;
    set<pair<Date, string>> uniq_events;
public:
    void Add(const Date& date, const string& event);

    void Print(ostream& os) const;

    template <class Predicate>
    int RemoveIf(Predicate predicate) {
        //cerr << "comand: Del " << endl;
        int counter = 0;
        vector<Date> to_erase;
        for(auto & record: records) {
            auto date = record.first;
            auto& events = record.second;
            auto it = stable_partition(begin(events), end(events), 
                [date, predicate](const string & event) { return !predicate(date, event); } );
            
            auto it2 = it;

            while(it2 != end(events)) {
                uniq_events.erase(make_pair(date, *it2));
                ++it2;
                ++counter;
            }
            //counter += end(events) - it;
            events.erase(it, events.end());

            if (begin(events) == end(events)) {
                to_erase.push_back(date);
            }
        }
        for (auto date: to_erase) {
            records.erase(date);
        }

        return counter;
    }

    template <class Predicate>
    vector<Record> FindIf(Predicate predicate) const {
        //cerr << "comand: FindIf " << endl;
        vector<Record> new_records;
        for(auto const& [date, events]: records) {
            for (auto& event: events) {
                if (predicate(date, event) == true) {
                    Record rec = {date, event};
                    new_records.push_back(rec);
                }
            }
        }
        return new_records;
}

    Record Last(const Date& date) const;
};
