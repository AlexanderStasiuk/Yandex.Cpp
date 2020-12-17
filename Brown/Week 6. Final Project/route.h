#pragma once

#include <string>
#include <vector>
#include <optional>


class Route {
public:
    Route(const std::string& routeNumber, bool isRing, std::vector<std::string> stationNames);
    size_t stationsCount() const;

    size_t uniqueStationsCount() const;

    std::optional<size_t> lengthByRealRoads() const;

    std::optional<double> curvature() const;


    const std::vector<std::string>& stationNames() const;

    bool isRing() const;

    std::string routeNumber() const;

    void setRouteLengthByRealRoads(size_t length);

    void setCurvature(double curvature);

private:
    std::string number_;
    bool isRing_;
    std::vector<std::string> stationNames_;
    std::optional<size_t> length_;
    std::optional<double> curvature_;
};