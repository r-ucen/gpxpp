#pragma once
#include <optional>
#include <string>
#include <vector>

#include "gpxpp/types/track_segment.h"

namespace gpxpp {
    struct Track {
        std::optional<std::string> m_name {};
        std::optional<std::string> m_description {};
        std::optional<std::string> m_type {};
        std::vector<TrackSegment> m_segments {};
    };
}
