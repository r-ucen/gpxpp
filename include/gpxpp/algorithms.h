#pragma once
#include <algorithm>
#include <ranges>
#include <concepts>
#include <numeric>

#include "gpxpp/types/track_point.h"
#include "gpxpp/types/track_segment.h"
#include "gpxpp/types/document.h"

namespace gpxpp {
    // FUNCTIONS -------------------------------------------------------------------------------------------------------

    /**
     * Calculates the distance in kilometers between two points using the haversine formula
     *
     * @param lat1 Latitude of point1
     * @param lon1 Longitude of point1
     * @param lat2 Latitude of point2
     * @param lon2 Longitude of point2
     * @return The distance between the given points in kilometers
     */
    double haversineDistance(Latitude lat1, Longitude lon1, Latitude lat2, Longitude lon2);

    /**
     *
     * @param value The angle to be converted
     * @return The given angle in radians
     */
    double toRadians(double value);

    /**
     * Calculates the total distance of all tracks in the document
     *
     * @param document The document containing tracks that get measured
     * @return The total distance of tracks in kilometers
     */
    inline double totalDistance(const Document& document);

    /**
     * Calculates the total distance of all segments in the track
     *
     * @param track The track to measure
     * @return The total distance of the track in kilometers
     */
    inline double totalDistance(const Track& track);

    /**
     *  Calculated the total distance of all points in a given segment
     *
     * @param segment The segment to be measured
     * @return The total distance of points in the given segment
     */
    inline double totalDistance(const TrackSegment& segment);

    // CONCEPTS --------------------------------------------------------------------------------------------------------

    /// Requires T to be an input range and the values in that range to be of type TrackPoint
    template <typename T>
    concept TrackPointRange = std::ranges::input_range<T> && std::same_as<std::ranges::range_value_t<T>, TrackPoint>;

    /// Requires T to be an input range of any values other than TrackPoint
    template <typename T>
    concept OtherThanTrackPointRange =
        std::ranges::input_range<T>
    && !std::same_as<std::ranges::range_value_t<T>, TrackPoint>;

    /// Requires an element of a range to be so when passed into the totalDistance function,
    /// the function successfully returns a double value
    template <typename T>
    concept DistanceCalculableElementOfRange = requires
    (std::ranges::range_reference_t<T> element) {
        { totalDistance(element) } -> std::convertible_to<double>;
    };

    /// Requires T to be an input range of any values other than TrackPoint
    /// and requires this input range elements to be so when passed into the totalDistance function,
    /// the function successfully returns a double value
    template <typename T>
    concept DistanceCalculableRange = OtherThanTrackPointRange<T>
    && DistanceCalculableElementOfRange<T>;

    // TEMPLATE FUNCTIONS ----------------------------------------------------------------------------------------------

    /**
     * Calculates the total distance of all given points
     *
     * Careful when using this function on multiple segments/tracks flattened into a range of points - the result will
     * contain also the distances between those tracks/segments
     *
     * @tparam T A range of TrackPoints
     * @param points The points to measure
     * @return The total distance of the points in kilometers
     */
    template <typename T> requires TrackPointRange<T>
    double totalDistance(T&& points);

    /**
     *  Calculates the total distance of a range of elements
     *
     *  Each element is measured on its own and the results are summed,
     *  so the gaps between consecutive elements (for example, between two segments) are not being take in account
     *
     * @tparam T A range of elements that have a totalDistance() of their own, such as TrackSegment, Track; the elements must satisfy the DistanceCalculableRange concept
     * @param elements The elements to measure
     * @return The sum of distances of all elements
     */
    template <typename T> requires DistanceCalculableRange<T>
    double totalDistance(T&& elements);

    /**
     * Smooths the elevation of TrackPoints in a given range using centered moving average.
     *
     * @tparam T A range of TrackPoints to be smoothed by the elevation
     * @param points The points to be smoothed by the elevation
     * @param windowSize The size of the moving average window
     * @return A range view of TrackPoints with smoothed elevation data
     */
    template <typename T> requires TrackPointRange<T>
    auto movingAverageElevation(T&& points, int windowSize = 5);

    // DEFINITIONS -----------------------------------------------------------------------------------------------------

    template <typename T> requires TrackPointRange<T>
    double totalDistance(T&& points) {
        double result { 0.0 };

        auto it { std::ranges::begin(points) };
        auto end { std::ranges::end(points) };

        if (it == end) { return 0.0; }

        TrackPoint previous = *it;
        ++it;
        for (; it != end; ++it) {
            const TrackPoint& current = *it;
            result += haversineDistance(previous.lat, previous.lon, current.lat, current.lon);
            previous = current;
        }

        return result;
    }

    inline double totalDistance(const Document& document) { return totalDistance(document.tracks); }
    inline double totalDistance(const Track& track) { return totalDistance(track.segments); }
    inline double totalDistance(const TrackSegment& segment) { return totalDistance(segment.points); }

    template <typename T> requires DistanceCalculableRange<T>
    double totalDistance(T&& elements) {
        double result { 0.0 };
        for (const auto& element : elements) {
            result += totalDistance(element);
        }

        return result;
    }

    template <typename T> requires TrackPointRange<T>
    auto movingAverageElevation(T&& points, int windowSize) {
        // When when returning some kind of a view, std::forward needs to be called on the points,
        // it is important when calling the movingAverage function with an rvalue

        // points itself is an lvalue
        // the && in T&& points is a forwarding reference in a function template, it binds to both lvalues and rvalues

        // reference collapsing:
        // U& + && collapses to U&
        // U + && stays U&&

        // if caller passes lvalue of U, T is deduced as U&, collapsing makes it U&, type of points is U&
        // if caller passes rvalue of U, T is deduced as U, collapsing makes it stay U&&, type of points is U&&

        // std::forward just casts points via the above two rules using reference collapsing (std::forward<T>(x) == static_cast<T&&>(x))

        // Lets say we call movingAverage like this:
        // auto result = movingAverage(getData());

        // getData() returns a temporary vector

        // owning_view is a view that has unique ownership of a range. It is move-only and stores that range within it.
        // ref_view is a view of the elements of some other range. It wraps a reference to that range.

        // With std::forward, the temporary vector gets moved into an owning_view inside the returned pipeline
        // without std::forward, we are working with a ref_view pointing at the temporary vector, the temporary dies
        // at the end of auto result = movingAverage(getData()); and we get a dangling result

        return std::forward<T>(points)
            | std::views::filter([](const auto& point){ return point.elevation.has_value(); })
            | std::views::slide(windowSize)
            | std::views::transform([windowSize](auto window) {

                const auto sum {
                    // Cannot use std::accumulate because the begin and end iterators of win are of a different type
                    std::ranges::fold_left(window, 0.0, [](double sum, const TrackPoint& point) {
                        return sum + point.elevation.value();
                    })
                };

                auto smoothedPointByElevation { *std::ranges::next(std::ranges::begin(window), windowSize / 2) };
                smoothedPointByElevation.elevation = sum / static_cast<double>(windowSize);
                return smoothedPointByElevation;
            });
    }
}
