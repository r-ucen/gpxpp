#pragma once
#include <vector>

#include "gpxpp/types/track.h"

namespace gpxpp {
    struct Document {
        std::vector<Track> tracks;
    };
}
