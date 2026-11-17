#pragma once
#include <chrono>
#include <optional>

namespace gpxpp {
    class TrackPoint {
    public:
        TrackPoint(double lat, double lon, std::optional<double> elevation, std::optional<std::chrono::sys_seconds> time)
        : m_lat(lat), m_lon(lon), m_elevation(elevation), m_time(time) {}

        [[nodiscard]] double getLat() const { return m_lat; }
        [[nodiscard]] double getLon() const { return m_lon; }
        [[nodiscard]] std::optional<double> getElevation() const { return m_elevation; }
        [[nodiscard]] std::optional<std::chrono::sys_seconds> getTime() const { return m_time; }

        void setLat(const double lat) { m_lat = lat; }
        void setLon(const double lon) { m_lon = lon; }
        void setElevation(const std::optional<double> elevation) { m_elevation = elevation; }
        void setTime(const std::optional<std::chrono::sys_seconds> time) { m_time = time; }

    private:
        double m_lat {};
        double m_lon {};
        std::optional<double> m_elevation {};
        std::optional<std::chrono::sys_seconds> m_time {};
    };
}
