#pragma once

#include <date.h>

#include <map>
#include <set>
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>
#include <utility>

using namespace std;

class SingleEvent {
public:
    SingleEvent(const Date& date, const string& event = "")
        : date_(date), event_(event) {};
    Date GetDate() const {return date_;}
    string GetEvent() const {return event_;}
private:
    const Date date_;
    const string event_;
};

ostream& operator<<(ostream& os, const SingleEvent& single_event);


class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;
    SingleEvent Last(const Date& date) const;

    template<class Predicate>
    int RemoveIf(Predicate p) { 
        int count = 0;
        vector<Date> clean;

        for (auto& [date, events] : database_) {
            count += events.RemoveIf(date, p);
            if (events.IsEmpty()) {
                clean.push_back(date);
            }
        }
        for (const auto& date : clean) {
            database_.erase(date);
        }

        return count;
    }

    template<class Predicate>
    vector<SingleEvent> FindIf(Predicate p) const { 
        vector<SingleEvent> res;

        for (const auto& item : database_) {
            auto events = item.second.Events();
            for (const auto& event : events) {
                if (p(item.first, event)) {
                    res.emplace_back(item.first, event);
                }
            }
        }

        return res;
    }

private:
    class Events_ {
    public:
        void Add(const string& event);
        void Print(ostream& os, const Date& date) const;
        bool Contains(const string& event) const;
        bool IsEmpty() const;
        string Last() const;
        const vector<string>& Events()const;

        template <typename Predicate>
        int RemoveIf(const Date& date, Predicate p) {
            auto it = stable_partition(begin(full_history_), end(full_history_), [&](const string& elem) {
                return !p(date, elem);
            });

            if (it == end(full_history_)) {
                return 0;
            }
    
            int count = 0;

            for (auto it_next = it; it_next != end(full_history_); it_next++) {
                unique_list_.erase(*it_next);
                count++;
            }

            full_history_.erase(it, end(full_history_));

            return count;
        }
    private:
        vector<string> full_history_;
        set<string> unique_list_;
    };

    map<Date, Events_> database_;
};