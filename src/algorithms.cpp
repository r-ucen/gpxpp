#include "gpxpp/algorithms.h"
#include <cmath>
#include <numbers>

namespace gpxpp {
    double haversineDistance(Latitude lat1, Longitude lon1, Latitude lat2, Longitude lon2) {
        constexpr double r { 6'371 }; // Average radius of the Earth in kilometers

        const double deltaLat { toRadians(lat2.value - lat1.value) };
        const double deltaLon { toRadians(lon2.value - lon1.value) };

        const double haversineOfCentralAngle {
            std::pow(std::sin(deltaLat / 2.0), 2)
            + std::cos(toRadians(lat1.value))
            * cos(toRadians(lat2.value))
            * std::pow(std::sin(deltaLon / 2.0), 2) };

        const double centralAngle { 2.0 * std::asin(std::sqrt(haversineOfCentralAngle)) };

        return r * centralAngle;
    }

    double toRadians(const double value) {
        return value * (std::numbers::pi / 180);
    }
}
