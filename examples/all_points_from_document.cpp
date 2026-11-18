#include <iostream>
#include <ranges>

#include "gpxpp/gpxpp.h"

int main() {
    auto document { gpxpp::loadDocument(DATA_DIR "test.gpx") };
    if (!document.has_value()) {
        std::cout << "Failed to load the document" << std::endl;
    }

    auto allPoints { document.value().allPoints() };
    for (const auto& p : allPoints | std::views::filter([](const gpxpp::TrackPoint& point){ return point.elevation > 1110; })) {
        std::cout << p << std::endl;
    }
}
