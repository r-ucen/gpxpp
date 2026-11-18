#pragma once
#include <ranges>
#include <vector>

#include "gpxpp/types/track.h"

namespace gpxpp {
    struct Document {
        std::vector<Track> tracks;

        auto allPoints() {
            return tracks | std::views::transform([](Track& track) { return track.allPoints(); })
            | std::views::join;
        }

        [[nodiscard]] auto allPoints() const {
            return tracks | std::views::transform([](const Track& track) { return track.allPoints(); })
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
