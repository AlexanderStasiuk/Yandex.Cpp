#pragma once

#include <string>
#include <vector>
#include <optional>


class Route {
public:
    Route(const std::string& routeNumber, bool isRing, std::vector<std::string> stationNames);
    size_t stationsCount() const;

    size_t uniqueStationsCount() const;

    std::optional<double> routeLength() const;

    const std::vector<std::string>& stationNames() const;

    bool isRing() const;

    std::string routeNumber() const;

    void setLength(double length);

private:
    std::string number_;
    bool isRing_;
    std::vector<std::string> stationNames_;
    std::optional<double> length_;
};