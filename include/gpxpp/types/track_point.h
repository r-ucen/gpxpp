#pragma once
#include <chrono>
#include <optional>

#include "gpxpp/types/coordinates.h"

namespace gpxpp {
    struct TrackPoint {
        Latitude m_lat {};
        Longitude m_lon {};
        std::optional<double> m_elevation {};
        std::optional<std::chrono::sys_seconds> m_time {};
    };
}
