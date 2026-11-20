#include <iostream>
#include <ranges>

#include "gpxpp/gpxpp.h"

int main() {
    auto document { gpxpp::loadDocument(DATA_DIR "test.gpx") };
    if (!document.has_value()) {
        std::cout << "Failed to load the document" << std::endl;
    }

    auto allPoints { document.value().allPoints() };
    auto allSegments { document.value().allSegments() };
    auto allTracks { document.value().tracks };
    auto allPointsOfFirstTrack { document.value().tracks.at(0).allPoints() };
    auto allSegmentsOfFirstTrack { document.value().tracks.at(0).segments };
    auto allPointsOfFirstSegmentOfFirstTrack { document.value().tracks.at(0).segments.at(0).points };
    auto allPointsOfSecondSegmentOfFirstTrack { document.value().tracks.at(0).segments.at(1).points };

    auto totalDistance { gpxpp::totalDistance(document.value()) };

    auto totalDistanceOfFirstTrack { gpxpp::totalDistance(document.value().tracks.at(0)) };

    auto totalDistanceOfFirstSegmentOfFirstTrack {
        gpxpp::totalDistance(document.value().tracks.at(0).segments | std::views::take(1))
    }; // same as segments.at(0)

    auto totalDistanceOfSecondSegmentOfFirstTrack {
        gpxpp::totalDistance(document.value().tracks.at(0).segments.at(1))
    };

    std::cout <<
        std::format("Total distance of all points (!!!): {} km != totalDistance: {} km",
            gpxpp::totalDistance(allPoints), totalDistance) << std::endl;
    // ^^
    // Total distance of all points (!!!): 778.2525276716221 km != totalDistance: 102.81462597504155 km

    // When using the overload of the totalDistance() that takes a range of TrackPoints as an argument,
    // these points might be flattened from a range of segments, this means the potential spaces
    // between the segments get included in the sum of the distance.
    // The segments in a .gpx file mean that the recording was paused or the device had trouble recording points.
    // That means it's usually intended not to include the spaces between the segments.
    // The same goes for if the .gpx file has multiple tracks that are separate on the map -> if using the overload
    // of the totalDistance() that takes a range of TrackPoints as an argument, you will also include the
    // distances between those individual tracks - this might not be wanted.

    // If you want to be sure the distance is correct, pass anything other than a range of TrackPoints to the function.
    // If measuring a segment, it does not matter though.

    std::cout <<
        std::format("Total distance of all segments: {} km == totalDistance: {} km",
            gpxpp::totalDistance(allSegments), totalDistance) << std::endl;

    std::cout <<
        std::format("Total distance of all tracks: {} km == totalDistance: {} km",
            gpxpp::totalDistance(allTracks), totalDistance) << std::endl;

    std::cout <<
        std::format("Total distance of all points of first track (!!!): {} km != totalDistanceOfFirstTrack: {} km",
            gpxpp::totalDistance(allPointsOfFirstTrack), totalDistanceOfFirstTrack) << std::endl;

    std::cout <<
        std::format("Total distance of all segments of first track: {} km == totalDistanceOfFirstTrack: {} km",
            gpxpp::totalDistance(allSegmentsOfFirstTrack), totalDistanceOfFirstTrack) << std::endl;

    std::cout <<
        std::format("Total distance of all points of first segment of first track: {} km == "
                    "totalDistanceOfFirstSegmentOfFirstTrack: {}",
            gpxpp::totalDistance(allPointsOfFirstSegmentOfFirstTrack),
            totalDistanceOfFirstSegmentOfFirstTrack) << std::endl;

    std::cout <<
        std::format("Total distance of all points of second segment of first track: {} km =="
                    " totalDistanceOfSecondSegmentOfFirstTrack: {} km",
            gpxpp::totalDistance(allPointsOfSecondSegmentOfFirstTrack),
            totalDistanceOfSecondSegmentOfFirstTrack) << std::endl;
}
