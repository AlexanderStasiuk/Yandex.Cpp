#pragma once

#include "station.h"

#include <cmath>
#include <string>
#include <vector>
#include <string_view>

std::vector<std::string> splitBy(std::string_view str, const std::string& sep = " ") {
    std::vector<std::string> result;
    while (!str.empty()) {
        auto pos = str.find(sep);
        result.push_back(std::string(str.substr(0, pos)));
        str.remove_prefix(pos != str.npos ? pos + sep.size() : str.size());
    }
    return result;
}

const int EARTH_RADIUS = 6371000;
const double PI = 3.1415926535;

double degToRad(double deg) {
  return deg * PI / 180;
}

double computeDistance(const Station& lhs, const Station& rhs) {
    auto lhsRadLat = degToRad(lhs.lat_);
    auto lhsRadLon = degToRad(lhs.lon_);
    auto rhsRadLat = degToRad(rhs.lat_);
    auto rhsRadLon = degToRad(rhs.lon_);

    return  acos(sin(lhsRadLat) * sin(rhsRadLat) +
            cos(lhsRadLat) * cos(rhsRadLat) *
            cos(fabs(lhsRadLon - rhsRadLon))) * EARTH_RADIUS;
}