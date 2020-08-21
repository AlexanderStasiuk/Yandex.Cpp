#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

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

struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop == "") {
        os << "No stop";
    } else {
        // cout << "Stop " << r.stop << ": ";
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
        // cout << endl;
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<string> order;
    map<string, vector<string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    bool first = true;
    if (r.bus == "") {
        os << "No bus";
    } else {
        
        for (const string& stop: r.order)  {
            if (first) {
                first = false;
            } else {
                os << endl;
            }
            os << "Stop " << stop << ": ";
            for (const string& bus: r.stops.at(stop)) {
                os << bus << " ";
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    bool first = true;
    if (r.buses.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus_item : r.buses) {
            if (first) {
                first = false;
            } else {
                os << endl;
            }
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse buses_response;
        if (stops_to_buses.count(stop)>0) {
            buses_response.stop = stop;
            buses_response.buses = stops_to_buses.at(stop);
        }
        return buses_response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse stops_response;
        if (buses_to_stops.count(bus)>0) {
            stops_response.bus = bus;
            for (const string& stop : buses_to_stops.at(bus)) {
                stops_response.order.push_back(stop);
                if (stops_to_buses.at(stop).size() == 1) {
                    stops_response.stops[stop].push_back("no interchange");
                } else {
                    for (const string& other_bus : stops_to_buses.at(stop)) {
                        if (bus != other_bus) {
                            stops_response.stops[stop].push_back(other_bus);
                        }
                    }
                }
            }
        }
        return stops_response;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse all_response;
        all_response.buses = buses_to_stops;
        return all_response;
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}