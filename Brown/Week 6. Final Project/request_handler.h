#pragma once

#include "station.h"
#include "route.h"
#include "utils.h"
#include "bus_manager.h"

#include <string_view>
#include <iostream>



Station buildStation(std::string_view str) {
    Station station;
    str.remove_prefix(str.find_first_not_of(" "));

    auto pos = str.find_first_of(":");
    station.name_ = str.substr(0, pos);

    str.remove_prefix(pos + 2);
    pos = str.find_first_of(",");
    station.lat_ = stod(std::string(str.substr(0, pos)));

    pos = str.find_first_of(" ");
    str.remove_prefix(++pos);
    station.lon_ = stod(std::string(str.substr(0)));

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
        if (requestType == "Stop") {
            std::string strToParse;
            getline(inStream, strToParse);
            auto station = buildStation(strToParse);
            stations[station.name_] = std::move(station);
        } else if (requestType == "Bus") {
            std::string strToParse;
            getline(inStream, strToParse);
            auto busRoute = buildRoute(strToParse);
            routes.insert({busRoute.routeNumber(), std::move(busRoute)});
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
        std::string strToParse;
        getline(inStream, strToParse);
        if (strToParse.empty()) {
            getline(inStream, strToParse);
        }
        outStream << manager.routeInfo(parseRequest(strToParse)) << std::endl;
    }
}