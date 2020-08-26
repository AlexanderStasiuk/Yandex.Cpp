#include <bus_manager.h>


void BusManager :: AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager :: GetBusesForStop(const string& stop) const {
    BusesForStopResponse buses_response;
    if (stops_to_buses.count(stop)>0) {
        buses_response.stop = stop;
        buses_response.buses = stops_to_buses.at(stop);
    }
    return buses_response;
}

StopsForBusResponse BusManager :: GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager :: GetAllBuses() const {
    AllBusesResponse all_response;
    all_response.buses = buses_to_stops;
    return all_response;
}