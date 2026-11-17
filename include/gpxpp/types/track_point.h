#pragma once
#include <chrono>
#include <optional>

#include "gpxpp/types/coordinates.h"

namespace gpxpp {
    struct TrackPoint {
        Latitude lat {};
        Longitude lon {};
        std::optional<double> elevation {};
        std::optional<std::chrono::sys_seconds> time {};
    };
}
