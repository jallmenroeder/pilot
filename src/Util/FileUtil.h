
#pragma once

#include <fstream>
#include <sstream>

#include "Common.h"

static std::string readFile(std::string_view path) {
    std::ifstream file(path.data(), std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::string message = std::string("failed to open file with path \"") + path.data() + "\"";
        THROW_LOGGED_ERROR(message)
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return {buffer.begin(), buffer.end()};
}

