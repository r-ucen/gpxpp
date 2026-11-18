#pragma once
#include <vector>

#include "gpxpp/types/track.h"

namespace gpxpp {
    struct Document {
        std::vector<Track> tracks;
    };

    inline std::ostream& operator<< (std::ostream& out, const Document& tp) {
        for (const auto& t : tp.tracks) {
            out << t;
        }
        return out;
    }
}
