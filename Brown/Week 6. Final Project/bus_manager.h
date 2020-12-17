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

            auto lengthByData = routes_.at(routeNumber).lengthByRealRoads();
        
            if (!lengthByData) {
                auto routeLength = computeRouteLengthByRealRoads(routeNumber);
                routes_.at(routeNumber).setRouteLengthByRealRoads(routeLength);
                auto lengthByCoordinates = computeRouteEuqlidianDistance(routeNumber);
                auto curvature = routeLength / lengthByCoordinates;
                routes_.at(routeNumber).setCurvature(curvature);
            }

            out_stream << "Bus " << routeNumber << ": " << stops
                        << " stops on route, " << uniqueStops << " unique stops, "
                        << *routes_.at(routeNumber).lengthByRealRoads() << " route length, "
                        << *routes_.at(routeNumber).curvature() << " curvature";
        } else {
            out_stream << "Bus " << routeNumber << ": not found";
        }

        return out_stream.str();
    }

    std::string stationInfo(const std::string& stationName) {
        std::ostringstream out_stream;
        if (stations_.count(stationName)) {
            const auto& buses = stations_.at(stationName).buses_;
            if (buses.empty()) {
                out_stream << "Stop " << stationName << ": no buses";
            } else {
                out_stream << "Stop " << stationName << ": buses";
                for (const auto& bus : buses) {
                    out_stream << " " << bus;
                }
            }
        } else {
            out_stream << "Stop " << stationName << ": not found";
        }
        return out_stream.str();
    }


private:
    std::unordered_map<std::string, Station> stations_;
    std::unordered_map<std::string, Route> routes_;

    double computeRouteEuqlidianDistance(std::string routeNumber) {
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

    size_t computeRouteLengthByRealRoads(const std::string& routeNumber) const {
        const auto stationsNames = routes_.at(routeNumber).stationNames();
        size_t length = 0;
        
        for (size_t i = 0; i < stationsNames.size() - 1; ++i) {
            const auto& first = stations_.at(stationsNames[i]);
            const auto& second = stations_.at(stationsNames[i + 1]);

            if (first.distanceToStations_.count(second.name_)) {
                length += first.distanceToStations_.at(second.name_);
            } else {
                length += second.distanceToStations_.at(first.name_);
            }
        }

        if (!routes_.at(routeNumber).isRing()) {
            for (size_t i = stationsNames.size() - 1; i > 0; --i) {
                const auto& first = stations_.at(stationsNames[i]);
                const auto& second = stations_.at(stationsNames[i - 1]);
                if (first.distanceToStations_.count(second.name_)) {
                    length += first.distanceToStations_.at(second.name_);
                } else {
                    length += second.distanceToStations_.at(first.name_);
                }
            }
        }

        return length;
    }
};