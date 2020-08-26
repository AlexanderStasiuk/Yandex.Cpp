#include <query.h>

istream& operator >> (istream& is, Query& q) {
    q.stops.clear();

    uint __count;
    string __buffer;
    string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        cin >> __count;
        for (int i=0; i<__count; i++) {
            cin >> __buffer;
            q.stops.push_back(__buffer);
        }
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}