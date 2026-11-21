#pragma once
#include <ranges>
#include <vector>

#include "gpxpp/types/track.h"

namespace gpxpp {
    struct Document {
        std::vector<Track> tracks;

        auto allSegments() {
            return tracks | std::views::transform([](Track& track) -> std::vector<TrackSegment>& { return track.segments; })
            | std::views::join;
        }

        [[nodiscard]] auto allSegments() const {
            return tracks | std::views::transform([](const Track& track) -> const std::vector<TrackSegment>& { return track.segments; })
            | std::views::join;
        }

        auto allPoints() {
            return allSegments() | std::views::transform([](const TrackSegment& segment) -> const std::vector<TrackPoint>& { return segment.points; })
            | std::views::join;
        }

        [[nodiscard]] auto allPoints() const {
            return allSegments() | std::views::transform([](const TrackSegment& segment) -> const std::vector<TrackPoint>& { return segment.points; })
            | std::views::join;
        }
    };

    inline std::ostream& operator<< (std::ostream& out, const Document& tp) {
        for (const auto& t : tp.tracks) {
            out << t;
        }
        return out;
    }
}
