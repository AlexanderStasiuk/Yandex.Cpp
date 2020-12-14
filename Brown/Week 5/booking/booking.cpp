#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
using namespace std;



struct DayBookingsInfo {
    int room_count = 0;
    map<int, int> clients;
};

struct BookingItem {
    explicit BookingItem (
        const int64_t& t, const string& h, const int& c, const int& r
    ) : time(t), hotel(h), client_id(c), room_count(r) {}
    string hotel;
    int64_t time;
    int client_id;
    int room_count;
};

class Hotels {
private:
    queue<BookingItem> bookings_;
    map<string, DayBookingsInfo> stats;
    int64_t most_old_time = - 10^18 - 1;

    void AddRecord(int64_t time, string hotel, int client_id, int room_count) {
        BookingItem new_booking (time, hotel, client_id, room_count);
        bookings_.push(new_booking);
        stats[hotel].clients[client_id] += 1;
        stats[hotel].room_count += room_count;
    }

    void Update(int64_t time) {
        while(bookings_.front().time <= (time-86400) && !bookings_.empty()) {
            auto curr_ellement = bookings_.front();
            stats[curr_ellement.hotel].room_count -= curr_ellement.room_count;
            stats[curr_ellement.hotel].clients[curr_ellement.client_id] -= 1;
            if (stats[curr_ellement.hotel].clients[curr_ellement.client_id] == 0) {
                stats[curr_ellement.hotel].clients.erase(curr_ellement.client_id);
            }
            most_old_time = curr_ellement.time;
            bookings_.pop();
        }
    }
public:
    void Book(int64_t time, string hotel_name, int client_id, int room_count) {
        if (stats.count(hotel_name) == 0) {
            stats[hotel_name] = DayBookingsInfo();
        } 
        AddRecord(time, hotel_name, client_id, room_count);
        Update(time);
    }

    int Clients(string hotel_name) {
        return stats[hotel_name].clients.size();
    }

    int Rooms(string hotel_name) {
        return stats[hotel_name].room_count;
    }

};

int main()
{
    Hotels hotels;
    int Q;
    cin >> Q;
    for(int i=0; i<Q; i++) {
        string comm;
        cin >> comm;
        if (comm=="BOOK") {
            int client_id, room_count;
            int64_t time;
            string hotel_name;
            cin >> time >> hotel_name >> client_id >> room_count;
            hotels.Book(time, hotel_name, client_id, room_count);
        } else if (comm=="CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.Clients(hotel_name) << endl;
        }
        else if (comm=="ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.Rooms(hotel_name) << endl;
        }
    }
    return 0;
}