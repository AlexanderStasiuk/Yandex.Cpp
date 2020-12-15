#pragma once

#include <string>
#include <set>

struct Station {
    std::string name_ = "";
    double lat_ = 0.0;
    double lon_ = 0.0;
    std::set<std::string> buses_ = {};
};