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



Station buildStation(std::string_view str) {
    Station station;
    str.remove_prefix(str.find_first_not_of(' '));

    auto pos = str.find_first_of(':');
    station.name_ = str.substr(0, pos);

    str.remove_prefix(pos + 2);
    pos = str.find_first_of(',');
    station.lat_ = stod(std::string(str.substr(0, pos)));

    pos = str.find_first_of(' ');
    str.remove_prefix(++pos);

    pos = str.find_first_of(',');
    if (pos != str.npos) {
        station.lon_ = stod(std::string(str.substr(0, pos)));
        str.remove_prefix(pos + 2);
        station.distanceToStations_ = move(parseDistanceToStation(str));
    } else {
        station.lon_ = stod(std::string(str.substr(0)));
    }

    return station;
}

Route buildRoute(std::string_view str) {
    str.remove_prefix(str.find_first_not_of(" "));

    auto pos = str.find_first_of(":");
    std::string routeNumber = std::string(str.substr(0, pos));

    str.remove_prefix(pos + 2);

    std::string separator;
    bool isRing;
    pos = str.find("-");
    if (pos != str.npos) {
        separator = " - ";
        isRing = false;
    } else {
        separator = " > ";
        isRing = true;
    }
    auto stationNames = splitBy(str, separator);

    return Route(routeNumber, isRing, std::move(stationNames));
}

BusManager buildDataBase(std::istream& inStream = std::cin) {
    std::unordered_map<std::string, Station> stations;
    std::unordered_map<std::string, Route> routes;

    int requestCnt = 0;
    inStream >> requestCnt;
    for (int i = 0; i < requestCnt; ++i) {
        std::string requestType;
        inStream >> requestType;
        std::string strToParse;
        getline(inStream, strToParse);
        if (requestType == "Stop") {
            auto station = buildStation(strToParse);
            if (stations.count(station.name_)) {
                stations[station.name_].lat_ = station.lat_;
                stations[station.name_].lon_ = station.lon_;
                stations[station.name_].distanceToStations_ = move(station.distanceToStations_);
                stations[station.name_].name_ = std::move(station.name_);
            } else {
                stations[station.name_] = std::move(station);
            }
        } else if (requestType == "Bus") {
            auto busRoute = buildRoute(strToParse);
            auto routeNumber = busRoute.routeNumber();
            for (const auto& stopName : busRoute.stationNames()) {
                stations[stopName].buses_.insert(routeNumber);
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
                     std::istream& inStream = std::cin,
                     std::ostream& outStream = std::cout) {
    outStream.precision(6);
    int requestCnt = 0;
    inStream >> requestCnt;
    for (int i = 0; i < requestCnt; ++i) {
        std::string requestType;
        inStream >> requestType;
        std::string strToParse;
        getline(inStream, strToParse);
        if (requestType == "Bus") {
            outStream << manager.routeInfo(parseRequest(strToParse)) << std::endl;
        } else if (requestType == "Stop") {
            outStream << manager.stationInfo(parseRequest(strToParse)) << std::endl;
        }
    }
}