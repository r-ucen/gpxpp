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

    inline std::ostream& operator<< (std::ostream& out, const Track& tp) {
        out << std::format("Track Name: {}, Description: {}, Type: {}", tp.name.value_or(""), tp.description.value_or(""), tp.type.value_or("")) << std::endl;
        for (const auto& s : tp.segments) {
            out << s;
        }
        return out;
    }
}
