#pragma once

namespace gpxpp {
    struct Latitude {
        double value {};
        auto operator<=>(const Latitude &) const = default;
    };

    struct Longitude {
        double value {};
        auto operator<=>(const Longitude &) const = default;
    };
}