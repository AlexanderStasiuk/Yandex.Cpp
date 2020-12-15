#include "route.h"

#include <set>

Route::Route(const std::string& routeNumber, bool isRing, std::vector<std::string> stationNames)
    : number_(routeNumber),
    isRing_(isRing),
    stationNames_(move(stationNames)),
    length_() {};

size_t Route::stationsCount() const {
    size_t result;
    if (isRing_) {
        result = stationNames_.size();
    } else {
        result = stationNames_.size() + stationNames_.size() - 1;
    }
    return result;
}

size_t Route::uniqueStationsCount() const {
    std::set<std::string> uniqueStations(stationNames_.begin(), stationNames_.end());
    return uniqueStations.size();
}

std::optional<double> Route::routeLength() const { return length_; }

const std::vector<std::string>& Route::stationNames() const { return stationNames_; }

bool Route::isRing() const { return isRing_; }

std::string Route::routeNumber() const { return number_; }

void Route::setLength(double length) { length_.emplace(length); }