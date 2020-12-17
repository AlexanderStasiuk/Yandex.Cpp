#include "route.h"

#include <set>
#include <optional>


Route::Route(const std::string& routeNumber, bool isRing, std::vector<std::string> stationNames)
    : number_(routeNumber),
    isRing_(isRing),
    stationNames_(move(stationNames)),
    length_(),
    curvature_() {};

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

std::optional<size_t> Route::lengthByRealRoads() const { return length_; }

std::optional<double> Route::curvature() const { return curvature_; }


const std::vector<std::string>& Route::stationNames() const { return stationNames_; }

bool Route::isRing() const { return isRing_; }

std::string Route::routeNumber() const { return number_; }

void Route::setRouteLengthByRealRoads(size_t length) { length_.emplace(length); }

void Route::setCurvature(double curvature) { curvature_.emplace(curvature); }