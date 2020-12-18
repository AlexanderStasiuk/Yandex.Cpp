#pragma once

#include "station.h"
#include "route.h"
#include "utils.h"
#include "bus_manager.h"

#include <string_view>
#include <iostream>
#include <string>
#include <unordered_map>


std::unordered_map<std::string, size_t> parseDistanceToStation(std::string_view str, char sep = ',') {
    std::unordered_map<std::string, size_t> result;
    while (!str.empty()) {
        auto pos = str.find('m');
        size_t distance = stoull(std::string(str.substr(0, pos)));
        str.remove_prefix(pos + 5);

        pos = str.find(sep);
        std::string stationName = std::string(str.substr(0, pos));

        str.remove_prefix(pos != str.npos ? pos + 2 : str.size());
        result.emplace(move(stationName), distance);
    }

    return result;
}



Station buildStation(const std::map<std::string, Json::Node>& reqMap) {
    Station station;
    station.name_ = reqMap.at("name").AsString();
    station.lat_ = reqMap.at("latitude").AsDouble();
    station.lon_ = reqMap.at("longitude").AsDouble();
    const auto& distancesToStations = reqMap.at("road_distances").AsMap();
    for (const auto& elem : distancesToStations) {
        station.distanceToStations_.emplace(elem.first, elem.second.AsInt());
    }

    return station;
}

Route buildRoute(const std::map<std::string, Json::Node>& reqMap) {
    auto routeNumber = reqMap.at("name").AsString();
    auto isRing = reqMap.at("is_roundtrip").AsBool();
    const auto& stations = reqMap.at("stops").AsArray();
    std::vector<std::string> stationNames;
    for (const auto& station : stations) {
        stationNames.push_back(station.AsString());
    }

    return Route(routeNumber, isRing, std::move(stationNames));
}

BusManager buildDataBase(const std::vector<Json::Node>& requests) {
    std::unordered_map<std::string, Station> stations;
    std::unordered_map<std::string, Route> routes;

    for (const auto& req : requests) {
        const auto& reqMap = req.AsMap();
        const auto& requestType = reqMap.at("type").AsString();
        if (requestType == "Stop") {
            auto station = buildStation(reqMap);
            if (stations.count(station.name_)) {
                stations[station.name_].lat_ = station.lat_;
                stations[station.name_].lon_ = station.lon_;
                stations[station.name_].distanceToStations_ = move(station.distanceToStations_);
                stations[station.name_].name_ = std::move(station.name_);
            } else {
                stations[station.name_] = std::move(station);
            }
        } else if (requestType == "Bus") {
            auto busRoute = buildRoute(reqMap);
            auto routeNumber = busRoute.routeNumber();
            for (const auto& stationName : busRoute.stationNames()) {
                stations[stationName].buses_.insert(routeNumber);
            }
            routes.insert({routeNumber, std::move(busRoute)});
        }
    }

    return {stations, routes};
}

std::string parseRequest(std::string_view str) {
    auto pos = str.find_first_of(" ");
    return std::string(str.substr(++pos));
}

void processRequests(BusManager& manager,
                     const std::vector<Json::Node>& requests,
                     std::ostream& outStream = std::cout) {
    outStream.precision(6);
    outStream << "[";
    for (size_t i = 0; i < requests.size(); ++i) {
        const auto& reqMap = requests[i].AsMap();
        const auto& type = reqMap.at("type").AsString();
        outStream << "{";
        outStream << "\"request_id\": " << reqMap.at("id").AsInt() << ", ";
        if (type == "Bus") {
            const auto routeInfo = manager.routeInfo(reqMap.at("name").AsString());
            if (routeInfo.count("error_message")) {
                outStream << "\"error_message\": "
                        << "\"" << routeInfo.at("error_message").AsString() << "\"";
            } else {
                outStream << "\"route_length\": "
                        << routeInfo.at("route_length").AsInt() << ", ";
                outStream << "\"curvature\": " << routeInfo.at("curvature").AsDouble()
                        << ", ";
                outStream << "\"stop_count\": " << routeInfo.at("stop_count").AsInt()
                        << ", ";
                outStream << "\"unique_stop_count\": "
                        << routeInfo.at("unique_stop_count").AsInt();
            }

        } else if (type == "Stop") {
            const auto stationInfo = manager.stationInfo(reqMap.at("name").AsString());
            if (stationInfo.count("error_message")) {
                outStream << "\"error_message\": "
                        << "\"" << stationInfo.at("error_message").AsString() << "\"";
            } else {
                outStream << "\"buses\": [";
                const auto& buses = stationInfo.at("buses").AsArray();
                for (size_t i = 0; i < buses.size(); ++i) {
                    if (i < buses.size() - 1) {
                        outStream << "\"" << buses[i].AsString() << "\", ";
                    } else {
                        outStream << "\"" << buses[i].AsString() << "\"";
                    }
                }
                outStream << "]";
            }
        }

        if (i < requests.size() - 1) {
            outStream << "}, ";
        } else {
            outStream << "}";
        }
    }

    outStream << "]";
}