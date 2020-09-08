#include <database.h>

void Database::Add(const Date& date, const string& event)
{  
    auto it = database_.find(date);
    if (it != database_.end()) {
        auto& events = it->second;
        if (events.Contains(event))
            return;
        events.Add(event);
    }
    else {
        database_[date].Add(event);
    }
}

void Database::Print(ostream& os) const {
    for (const auto& [date, events]: database_) {
        events.Print(os, date);
    }
};

SingleEvent Database::Last(const Date& date) const {
    if (database_.empty())
        throw invalid_argument("Empty database");

    auto it = database_.lower_bound(date);

    if (it == database_.cbegin() && date < it->first)
        throw invalid_argument("No entries for requested date");

    if (it == database_.cend() || it->first != date)
        it = prev(it);

    return SingleEvent(it->first, it->second.Last());
} 

// ----------------- Events_ class implementations -----------------

void Database::Events_::Add(const string& event) {
    full_history_.push_back(event);
    unique_list_.insert(event);          
}

void Database::Events_::Print(ostream& os, const Date& date) const {
    for (const auto& event : full_history_) {
        os << date << " " << event << endl;
    }
}

bool Database::Events_::IsEmpty() const {
    return full_history_.empty(); 
}

bool Database::Events_::Contains(const string& event) const {
    return unique_list_.count(event) != 0;
}
        
const vector<string>& Database::Events_::Events() const { 
    return full_history_; 
}

string Database::Events_::Last() const { 
    return full_history_.back(); 
}

// ----------------- SingleEvent class implementations -----------------

ostream& operator<<(ostream& os, const SingleEvent& single_event)
{
    os << single_event.GetDate() << " " << single_event.GetEvent();
    return os;
}