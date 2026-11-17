#pragma once
#include <string_view>
#include <optional>
#include <chrono>
#include <filesystem>

#include "gpxpp/types/document.h"

namespace gpxpp {

    std::optional<Document> loadDocument(const std::filesystem::path& path);
    std::optional<std::chrono::sys_seconds> parseTime(std::string_view sv);

}
