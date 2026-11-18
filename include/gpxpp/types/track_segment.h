#pragma once
#include <vector>

#include "gpxpp/types/track_point.h"

namespace gpxpp {
    struct TrackSegment {
        std::vector<TrackPoint> points {};
    };

    inline std::ostream& operator<< (std::ostream& out, const TrackSegment& tp) {
        out << "\tSegment: " << std::endl;
        for (const auto& p : tp.points) {
            out << p;
        }
        return out;
    }
}
