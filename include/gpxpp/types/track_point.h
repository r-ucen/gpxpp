#pragma once
#include <chrono>
#include <optional>
#include <ostream>
#include <format>

#include "gpxpp/types/coordinates.h"

namespace gpxpp {
    struct TrackPoint {
        Latitude lat {};
        Longitude lon {};
        std::optional<double> elevation {};
        std::optional<std::chrono::sys_seconds> time {};
    };

    inline std::ostream& operator<< (std::ostream& out, const TrackPoint& tp) {
        out << std::format("\t\tLat: {}, Lon: {}, Elevation: {}, Time: {}",
            tp.lat.value, tp.lon.value, tp.elevation.value_or(0), tp.time.value_or({})) << std::endl;
        return out;
    }
}
