#include <iostream>
#include <ranges>

#include "gpxpp/gpxpp.h"

int main() {
    auto document { gpxpp::loadDocument(DATA_DIR "test.gpx") };
    if (!document.has_value()) {
        std::cout << "Failed to load the document" << std::endl;
    }

    // GAIN
    std::cout << "GAIN" <<std::endl;

    std::cout << "no smoothing: " << gpxpp::elevationGain(
        document.value(),
{ .threshold = 1, .movingAverageWindowSize = 0 }) // no smoothing
    << std::endl;

    std::cout << "threshold = 1, movingAverageWindowSize = 5: " << gpxpp::elevationGain(
        document.value(),
{ .threshold = 1, .movingAverageWindowSize = 5 })
    << std::endl;

    std::cout << "no smoothing & minimal threshold: " << gpxpp::elevationGain(
        document.value(),
{ .threshold = 0.1, .movingAverageWindowSize = 0 }) // no smoothing & minimal threshold
    << std::endl;

    std::cout << "default optional parameters: -----------" << std::endl;

    std::cout << gpxpp::elevationGain(document.value()) << std::endl;
    std::cout << gpxpp::elevationGain(document.value().allSegments()) << std::endl;
    // !!! produces misleading values since the points of all segments and tracks get flattened into one range
    std::cout << "(misleading) " << gpxpp::elevationGain(document.value().allPoints()) << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << "gain of first track: " << gpxpp::elevationGain(document.value().tracks.at(0)) << std::endl;
    std::cout << "gain of first segment of the track: " << gpxpp::elevationGain(document.value().tracks.at(0).segments.at(1)) << std::endl;
    std::cout << "gain of second segment of the track: " << gpxpp::elevationGain(document.value().tracks.at(0).segments.at(0)) << std::endl;

    // LOSS

    std::cout << "\nLOSS" <<std::endl;

    std::cout << "no smoothing: " << gpxpp::elevationLoss(
        document.value(),
{ .threshold = 1, .movingAverageWindowSize = 0 }) // no smoothing
    << std::endl;

    std::cout << "threshold = 1, movingAverageWindowSize = 5: " << gpxpp::elevationLoss(
        document.value(),
{ .threshold = 1, .movingAverageWindowSize = 5 })
    << std::endl;

    std::cout << "no smoothing & minimal threshold: " << gpxpp::elevationLoss(
        document.value(),
{ .threshold = 0.1, .movingAverageWindowSize = 0 }) // no smoothing & minimal threshold
    << std::endl;

    std::cout << "default optional parameters: -----------" << std::endl;

    std::cout << gpxpp::elevationLoss(document.value()) << std::endl;
    std::cout << gpxpp::elevationLoss(document.value().allSegments()) << std::endl;
    // !!! produces misleading values since the points of all segments and tracks get flattened into one range
    std::cout << "(misleading) " << gpxpp::elevationLoss(document.value().allPoints()) << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << "loss of first track: " << gpxpp::elevationLoss(document.value().tracks.at(0)) << std::endl;
    std::cout << "loss of first segment of the track: " << gpxpp::elevationLoss(document.value().tracks.at(0).segments.at(1)) << std::endl;
    std::cout << "loss of second segment of the track: " << gpxpp::elevationLoss(document.value().tracks.at(0).segments.at(0)) << std::endl;

    // GAIN & LOSS
    std::cout << "\nGAIN & LOSS (misleading if used on all points of document that contains separate tracks)" << std::endl;

    // !!! produces misleading values since the points of all segments and tracks get flattened into one range
    auto [gain, loss] = gpxpp::elevation(document.value().allPoints());
    std::cout << std::format("Gain: {}, Loss: {}", gain, loss) << std::endl;
}
