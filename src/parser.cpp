#include "pugixml.hpp"
#include "gpxpp/parser.h"

#include <iostream>
#include <sstream>
#include <optional>
#include <string_view>
#include <chrono>

#include "gpxpp/types/document.h"

namespace gpxpp {

    std::optional<Document> loadDocument(const std::string &path) {
        pugi::xml_document xmlDocument;

        if (!xmlDocument.load_file(path.c_str())) { return {}; }

        pugi::xml_node gpxNode { xmlDocument.child("gpx") };
        if (!gpxNode) {
            return {};
        }

        Document document;

        for (pugi::xml_node trkNode : gpxNode.child("trk")) {
            Track track;

            if (pugi::xml_node trkName = trkNode.child("name")) {track.name = trkName.text().as_string();}
            if (pugi::xml_node trkDes = trkNode.child("description")) {track.description = trkDes.text().as_string();}
            if (pugi::xml_node trkType = trkNode.child("type")) {track.type = trkType.text().as_string();}

            for (pugi::xml_node trksegNode : trkNode.child("trkseg")) {
                TrackSegment trackSegment;

                for (pugi::xml_node trkptNode : trksegNode.child("trkpt")) {
                    TrackPoint trackPoint {
                        .lat = trkptNode.attribute("lat").as_double(),
                        .lon = trkptNode.attribute("lon").as_double()
                    };

                    if (pugi::xml_node eleNode = trkptNode.child("ele")) {
                        trackPoint.elevation = eleNode.text().as_double();
                    }

                    if (pugi::xml_node timeNode = trkptNode.child("time")) {
                        trackPoint.time = parseTime(timeNode.text().as_string());
                    }

                    trackSegment.points.push_back(trackPoint);
                }

                track.segments.push_back(trackSegment);
            }

            document.tracks.push_back(track);
        }

        return document;
    }

    std::optional<std::chrono::sys_seconds> parseTime(std::string_view sv) {
        std::istringstream iss { std::string { sv } };
        std::chrono::sys_seconds out {};

        iss >> std::chrono::parse("%FT%TZ", out);
        if (iss.fail()) {
            return {};
        }
        return out;
    }

}
