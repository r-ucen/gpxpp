#pragma once
#include <algorithm>
#include <ranges>
#include <concepts>

#include "gpxpp/types/track_point.h"
#include "gpxpp/types/track_segment.h"
#include "gpxpp/types/document.h"

namespace gpxpp {
    // TYPES -----------------------------------------------------------------------------------------------------------

    /**
     * Configuration parameters for elevation gain and loss calculations
     */
    struct ElevationOptions {
        /// Minimum elevation change in meters required to register a climb or descent
        double threshold { 1.0 };

        /// The size of the window used by the moving average algorithm
        /// Set to 1 or less to disable smoothing
        int movingAverageWindowSize { 5 };
    };

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

    /**
     *  Calculates the total elevation gain of all tracks in the document
     *
     * @param document The document containing tracks
     * @param options Configuration parameters controlling smoothing and elevation threshold
     * @return The total elevation gain of all tracks in the document in meters
     */
    inline double elevationGain(const Document& document, ElevationOptions options = {});
    /**
     *  Calculates the total elevation gain of all segments in the track
     *
     * @param track The track used to calculate the elevation gain
     * @param options Configuration parameters controlling smoothing and elevation threshold
     * @return The total elevation gain of all segments in the given track in meters
     */
    inline double elevationGain(const Track& track, ElevationOptions options = {});
    /**
     * Calculates the total elevation gain of all points in the given segment
     *
     * @param segment The segment containing points for elevation gain calculation
     * @param options Configuration parameters controlling smoothing and elevation threshold
     * @return The total elevation gain of the points in the segment in meters
     */
    inline double elevationGain(const TrackSegment& segment, ElevationOptions options = {});

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

    /// Requires an element of a range to be so when passed into the elevationGain function,
    /// the function successfully returns a double value
    template <typename T>
    concept ElevationGainCalculableElementOfRange = requires
    (std::ranges::range_reference_t<T> element, ElevationOptions options) {
        { elevationGain(element, options) } -> std::convertible_to<double>;
    };

    /// Requires T to be an input range of any values other than TrackPoint
    /// and requires this input range elements to be so when passed into the elevationGain function,
    /// the function successfully returns a double value
    template <typename T>
    concept ElevationGainCalculableRange = OtherThanTrackPointRange<T>
    && ElevationGainCalculableElementOfRange<T>;

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

    /**
     * Calculates the total elevation gain of the given range of TrackPoints
     *
     * @tparam T A range of TrackPoints to calculate elevation gain from
     * @param points The points used in the elevation gain calculation
     * @param options Configuration parameters controlling smoothing and elevation threshold
     * @return The total elevation gain of the points in meters
     */
    template <typename T> requires TrackPointRange<T>
    auto elevationGain(T&& points, ElevationOptions options = {});

    /**
     * Calculates the total elevation gain of the given elements
     *
     * @tparam T A range of elements that have an elevationGain() of their own such as TrackSegment, Track; the elements must satisfy the ElevationGainCalculableRange concept
     * @param elements The elements to sum up their elevation gain
     * @param options Configuration parameters controlling smoothing and elevation threshold
     * @return The total elevation gain of the given elements in meters
     */
    template <typename T> requires ElevationGainCalculableRange<T>
    double elevationGain(T&& elements, ElevationOptions options = {});

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

    template<typename T> requires TrackPointRange<T>
    auto elevationGain(T&& points, const ElevationOptions options) {
        auto validPoints = std::forward<T>(points)
            | std::views::filter([](const TrackPoint& point) { return point.elevation.has_value(); });

        auto calculateElevationGain = [threshold = options.threshold](auto&& range) {
            auto it { std::ranges::begin(range) };
            auto end { std::ranges::end(range) };

            if (it == end) { return 0.0; }

            double totalGain { 0.0 };
            double anchor { (*it).elevation.value() };
            ++it;

            for (; it != end; ++it) {
                const double currentElevation { (*it).elevation.value() };
                const auto difference { currentElevation - anchor };

                if (difference >= threshold) {
                    anchor = currentElevation;
                    totalGain += difference;
                } else if (difference <= -threshold) {
                    anchor = currentElevation;
                }
            }

            return totalGain;
        };

        if (options.movingAverageWindowSize <= 1) { return calculateElevationGain(validPoints); }

        auto it { std::ranges::begin(validPoints) };
        const auto end { std::ranges::end(validPoints) };
        int count { 0 };
        while (it != end && count < options.movingAverageWindowSize) {
            ++count;
            ++it;
        }
        if (count < options.movingAverageWindowSize) { return calculateElevationGain(validPoints); }

        return calculateElevationGain(movingAverageElevation(validPoints, options.movingAverageWindowSize));
    }

    inline double elevationGain(const Document& document, const ElevationOptions options) {
        return elevationGain(document.tracks, options);
    }
    inline double elevationGain(const Track& track, const ElevationOptions options) {
        return elevationGain(track.segments, options);
    }
    inline double elevationGain(const TrackSegment& segment, const ElevationOptions options) {
        return elevationGain(segment.points, options);
    }

    template <typename T> requires ElevationGainCalculableRange<T>
    double elevationGain(T&& elements, const ElevationOptions options) {
        double result { 0.0 };
        for (const auto& element : elements) {
            result += elevationGain(element, options);
        }

        return result;
    }
}
