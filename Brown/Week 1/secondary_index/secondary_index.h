#pragma once

#include <unordered_map>
#include <map>
#include <string>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

class Database {
public:
    bool Put(const Record& record) {
        if (ids.find(record.id) != ids.end()) {
            return false;
        }

        auto [it, __inserted] = storage.insert({ 
            record.id, record
        });

        const Record* ptr = &(it->second);
        auto timestamp_iter = timestamp_index.insert({record.timestamp, ptr});
        auto karma_iter = karma_index.insert({record.karma, ptr});
        auto user_iter = user_index.insert({record.user, ptr});

        ids.insert({ 
            record.id, { timestamp_iter, karma_iter, user_iter }
        });
        
        return true;
    }

    const Record* GetById(const string& id) const {
        auto it = ids.find(id);
        if (it == ids.end()) {
            return nullptr;
        }
        return &(storage.at(id));
    }
    
    bool Erase(const string& id) {
        auto it = ids.find(id);
        if (it == ids.end()) {
            return false;
        }
        auto& ids_data = it->second;
        timestamp_index.erase(ids_data.timestamp_iter);
        karma_index.erase(ids_data.karma_iter);
        user_index.erase(ids_data.user_iter);
        storage.erase(id);
        ids.erase(it);
        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto it_begin = timestamp_index.lower_bound(low);
        auto it_end = timestamp_index.upper_bound(high);
        for (auto it = it_begin; it != it_end; ++it) {
            if (!callback(*it->second)) {
                break;
            }
        }
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto it_begin = karma_index.lower_bound(low);
        auto it_end = karma_index.upper_bound(high);
        for (auto it = it_begin; it != it_end; ++it) {
            if (!callback(*it->second)) {
                break;
            }
        }
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto [it_begin, it_end] = user_index.equal_range(user);
        for (auto it = it_begin; it != it_end; ++it) {
            if (!callback(*it->second)) {
                break;
            }
        }
    }

private:

    unordered_map<string, Record> storage;
    

    template<typename Type>
    using Index = multimap<Type, const Record*>;

    struct IndexVector {
        Index<int>::iterator timestamp_iter;
        Index<int>::iterator karma_iter;
        Index<string>::iterator user_iter;
    };
    
    map<string, IndexVector> ids;
    Index<int> timestamp_index;
    Index<int> karma_index;
    Index<string> user_index;
};