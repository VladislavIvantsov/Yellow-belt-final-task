#include "database.h"

using namespace std;

void Database::Add(const Date &date, const string &event) {
    if (!event.empty()) {
        auto insert_result = this->unique_events[date].insert(event);
        if (insert_result.second) {
            this->ordered_events[date].push_back(event);
        }
    }
}

void Database::Print(ostream &stream) const {
    for (auto it_date = this->ordered_events.begin(); it_date != this->ordered_events.end(); ++it_date) {
        for (auto it_event = (*it_date).second.begin(); it_event != (*it_date).second.end(); ++it_event) {
            stream << (*it_date).first << " " << *it_event << endl;
        }
    }
}

string Database::Last(const Date &date) const {
    if (this->ordered_events.empty()) {
        return "No entries";
    }
    auto upper_bound = this->ordered_events.upper_bound(date);
    if (upper_bound == this->ordered_events.begin()) {
        return "No entries";
    }
    upper_bound--;
    stringstream ss;
    ss << upper_bound->first << " " << (upper_bound->second.back());
    return ss.str();
}