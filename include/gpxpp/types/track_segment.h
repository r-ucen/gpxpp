#pragma once
#include <vector>

#include "gpxpp/types/track_point.h"

namespace gpxpp {
    struct TrackSegment {
        std::vector<TrackPoint> points {};
    };
}
