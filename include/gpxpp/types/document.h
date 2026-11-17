#pragma once
#include <vector>

#include "track.h"

namespace gpxpp {
    class Document {
    public:
        std::vector<Track>& getTracks() { return m_tracks; }
        [[nodiscard]] const std::vector<Track>& getTracks() const { return m_tracks; }

        void setTracks(std::vector<Track> tracks) { m_tracks = std::move(tracks); }
    private:
        std::vector<Track> m_tracks;
    };
}
