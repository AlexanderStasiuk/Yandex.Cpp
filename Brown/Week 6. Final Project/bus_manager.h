#pragma once

#include "station.h"
#include "route.h"
#include "utils.h"

// #include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

class BusManager {
public:
    BusManager(std::unordered_map<std::string, Station> stations, std::unordered_map<std::string, Route> routes)
      : stations_(move(stations)), routes_(move(routes)) {}

    std::string routeInfo(const std::string& routeNumber) {
        std::ostringstream out_stream;

        if (routes_.count(routeNumber)) {
            auto stops = routes_.at(routeNumber).stationsCount();
            auto uniqueStops = routes_.at(routeNumber).uniqueStationsCount();
            auto routeLength = routes_.at(routeNumber).routeLength();
            if (!routeLength) {
                auto length = computeRouteLength(routeNumber);
                routes_.at(routeNumber).setLength(length);
            } 
            out_stream << "Bus " << routeNumber << ": " << stops
                        << " stops on route, " << uniqueStops << " unique stops, "
                        << *routes_.at(routeNumber).routeLength() << " route length";
        } else {
            out_stream << "Bus " << routeNumber << ": not found";
        }

    return out_stream.str();
  }

private:
    std::unordered_map<std::string, Station> stations_;
    std::unordered_map<std::string, Route> routes_;

    double computeRouteLength(std::string routeNumber) {
        auto stationNames = routes_.at(routeNumber).stationNames();
        double length = 0.0;
        for (size_t i = 0; i < stationNames.size() - 1; ++i) {
            const auto& first = stations_.at(stationNames[i]);
            const auto& second = stations_.at(stationNames[i + 1]);
            length += computeDistance(first, second);
        }

        if (!routes_.at(routeNumber).isRing()) {
            length *= 2;
        }

        return length;
    }
};