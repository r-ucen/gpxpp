#include <iostream>

#include "gpxpp/gpxpp.h"

int main() {
    std::cout << std::boolalpha << gpxpp::canLoadGpxFile(DATA_DIR "test.gpx") << std::endl;
    return 0;
}
