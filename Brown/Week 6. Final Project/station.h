#pragma once

#include <string>
#include <set>
#include <unordered_map>

struct Station {
    std::string name_ = "";
    double lat_ = 0.0;
    double lon_ = 0.0;
    std::set<std::string> buses_ = {};
    std::unordered_map<std::string, size_t> distanceToStations_ = {};
};