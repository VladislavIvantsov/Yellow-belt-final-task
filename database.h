#pragma once

#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include "date.h"

using namespace std;

class Database {
private:
    map<Date, set<string>> unique_events;
    map<Date, vector<string>> ordered_events;
public:
    void Add(const Date &date, const string &event);

    void Print(ostream &stream) const;

    template<class Func>
    vector<string> FindIf(Func func) const {
        vector<string> result;
        for (auto it_date = this->ordered_events.begin(); it_date != this->ordered_events.end(); ++it_date) {
            Date date = (*it_date).first;
            auto predicate = [date, func](const string &event) {
                return func(date, event);
            };
            for (auto it_event = find_if((*it_date).second.begin(), (*it_date).second.end(), predicate);
                 it_event != (*it_date).second.end();
                 it_event = find_if(next(it_event), (*it_date).second.end(), predicate)) {
                stringstream ss;
                ss << date << " " << *it_event;
                result.push_back(ss.str());
            }
        }
        return result;
    }

    string Last(const Date &date) const;


    template<class Func>
    int RemoveIf(Func func) {
        int result = 0;
        map<Date, vector<string>> new_ordered_events;
        map<Date, set<string>> new_unique_events;
        for (auto it_date = this->ordered_events.begin(); it_date != this->ordered_events.end(); ++it_date) {
            Date date = (*it_date).first;
            auto predicate = [date, func](const string &event) {
                return func(date, event);
            };
            auto it_event = stable_partition((*it_date).second.begin(), (*it_date).second.end(), predicate);

            if (it_event != (*it_date).second.end()) {
                new_ordered_events[date] = vector<string>{it_event, (*it_date).second.end()};
                new_unique_events[date] = set<string>{it_event, (*it_date).second.end()};
                result += (*it_date).second.size() - new_ordered_events[date].size();
            } else {
                result += (*it_date).second.size();
            }
        }
        this->ordered_events = new_ordered_events;
        this->unique_events = new_unique_events;
        return result;
    }
};