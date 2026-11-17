#pragma once
#include <string>
#include <string_view>
#include <optional>
#include <chrono>

#include "gpxpp/types/document.h"

namespace gpxpp {

    std::optional<Document> loadDocument(const std::string &path);
    std::optional<std::chrono::sys_seconds> parseTime(std::string_view sv);

}
