cmake_minimum_required(VERSION 4.3)
project(gpxpp)

set(CMAKE_CXX_STANDARD 23)

# pugixml - XML parsing lib
include(FetchContent)

FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        GIT_TAG        v1.16
)

FetchContent_MakeAvailable(pugixml)


# Create gpxpp library target and an alias for it in the gpxpp::gpxpp format
add_library(gpxpp
        src/parser.cpp
        src/algorithms.cpp
)

add_library(gpxpp::gpxpp ALIAS gpxpp)

target_include_directories(gpxpp
        PUBLIC  ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${PROJECT_SOURCE_DIR}/src
)


target_link_libraries(gpxpp PRIVATE pugixml::pugixml)


add_subdirectory(examples)
