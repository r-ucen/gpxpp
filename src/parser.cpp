#include "pugixml.hpp"
#include "gpxpp/parser.h"

#include <iostream>

namespace gpxpp {

    bool canLoadGpxFile(const std::string &path) {
        pugi::xml_document doc;
        const auto res = doc.load_file(path.c_str());

        if (!res) {
            std::cout << "Failed to load '" << path << "': " << res.description() << '\n';
        }
        return res;
    }

}
