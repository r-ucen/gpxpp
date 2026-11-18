function(gpxpp_add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE gpxpp::gpxpp)
    target_compile_definitions(${name} PRIVATE
            DATA_DIR="${PROJECT_SOURCE_DIR}/data/")
endfunction()

gpxpp_add_example(can_load_gpx_file)
gpxpp_add_example(all_points_from_document)