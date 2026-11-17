#pragma once
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "track_segment.h"

namespace gpxpp {
    class Track {
    public:
        [[nodiscard]] std::optional<std::string> getName() const { return m_name; }
        [[nodiscard]] std::optional<std::string> getDescription() const { return m_description; }
        [[nodiscard]] std::optional<std::string> getType() const { return m_type; }
        std::vector<TrackSegment>& getSegments() { return m_segments; }

        void setName(std::optional<std::string> name) { m_name = std::move(name); }
        void setDescription(std::optional<std::string> description) { m_description = std::move(description); }
        void setType(std::optional<std::string> type) { m_type = std::move(type); }
        void setSegments(std::vector<TrackSegment> segments) { m_segments = std::move(segments); }

    private:
        std::optional<std::string> m_name {};
        std::optional<std::string> m_description {};
        std::optional<std::string> m_type {};

        std::vector<TrackSegment> m_segments {};
    };
}
