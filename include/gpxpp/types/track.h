#pragma once
#include <optional>
#include <string>
#include <vector>
#include <format>
#include <ostream>
#include <ranges>

#include "gpxpp/types/track_segment.h"

namespace gpxpp {
    struct Track {
        std::optional<std::string> name {};
        std::optional<std::string> description {};
        std::optional<std::string> type {};
        std::vector<TrackSegment> segments {};

        auto allPoints() {
            return segments | std::views::transform([](TrackSegment& segment)-> std::vector<TrackPoint>& { return segment.points; })
            | std::views::join;
        }
        [[nodiscard]] auto allPoints () const {
            return segments | std::views::transform([](const TrackSegment& segment)-> const std::vector<TrackPoint>& { return segment.points; })
            | std::views::join;
        }

    };

    inline std::ostream& operator<< (std::ostream& out, const Track& tp) {
        out << std::format("Track Name: {}, Description: {}, Type: {}", tp.name.value_or(""), tp.description.value_or(""), tp.type.value_or("")) << std::endl;
        for (const auto& s : tp.segments) {
            out << s;
        }
        return out;
    }
}
