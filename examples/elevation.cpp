#include <iostream>
#include <ranges>

#include "gpxpp/gpxpp.h"

int main() {
    auto document { gpxpp::loadDocument(DATA_DIR "test.gpx") };
    if (!document.has_value()) {
        std::cout << "Failed to load the document" << std::endl;
    }

    std::cout << gpxpp::elevationGain(
        document.value(),
{ .threshold = 1, .movingAverageWindowSize = 0 }) // no smoothing
    << std::endl;

    std::cout << gpxpp::elevationGain(
        document.value(),
{ .threshold = 1, .movingAverageWindowSize = 5 })
    << std::endl;

    std::cout << gpxpp::elevationGain(
        document.value(),
{ .threshold = 0.1, .movingAverageWindowSize = 0 }) // no smoothing & minimal threshold
    << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << gpxpp::elevationGain(document.value()) << std::endl;
    std::cout << gpxpp::elevationGain(document.value().allSegments()) << std::endl;
    std::cout << gpxpp::elevationGain(document.value().allPoints()) << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << gpxpp::elevationGain(document.value().tracks[0]) << std::endl;
    std::cout << gpxpp::elevationGain(document.value().tracks.at(0).segments.at(1)) << std::endl;
    std::cout << gpxpp::elevationGain(document.value().tracks.at(0).segments.at(0).points) << std::endl;
}
