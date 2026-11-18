#include <iostream>
#include <ranges>

#include "gpxpp/gpxpp.h"

int main() {
    auto document { gpxpp::loadDocument(DATA_DIR "test.gpx") };
    if (!document.has_value()) {
        std::cout << "Failed to load the document" << std::endl;
    }

    auto allSegments { document.value().allSegments() };
    std::size_t segmentNumber {};
    for (const auto& segment : allSegments) {
        std::cout << "Size of segment " << segmentNumber << ": " << segment.points.size() << std::endl;
        ++segmentNumber;
    }
}
