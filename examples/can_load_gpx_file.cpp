#include <iostream>

#include "gpxpp/gpxpp.h"

int main() {
    auto document { gpxpp::loadDocument(DATA_DIR "test.gpx") };
    if (document.has_value()) {
        std::cout << document.value() << std::endl;
    } else {
        std::cout << "Failed to load the document" << std::endl;
    }
    return 0;
}
