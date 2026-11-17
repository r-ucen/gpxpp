#pragma once
#include <vector>

#include "track_point.h"

namespace gpxpp {
    class TrackSegment {
    public:
        std::vector<TrackPoint>& getPoints() { return m_points; }
        [[nodiscard]] const std::vector<TrackPoint>& getPoints() const { return m_points; }

        void setPoints(std::vector<TrackPoint> points) { m_points = std::move(points); }
    private:
        std::vector<TrackPoint> m_points {};
    };
}
