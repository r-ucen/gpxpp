#pragma once
#include <optional>
#include <string>
#include <vector>

#include "gpxpp/types/track_segment.h"

namespace gpxpp {
    struct Track {
        std::optional<std::string> name {};
        std::optional<std::string> description {};
        std::optional<std::string> type {};
        std::vector<TrackSegment> segments {};
    };
}
