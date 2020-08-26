#include <responses.h>
#include <iostream>

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop == "") {
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

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