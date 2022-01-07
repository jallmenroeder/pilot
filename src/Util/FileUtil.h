
#pragma once

#include <fstream>
#include <vector>

#include "Logger/Logger.h"

static std::vector<char> readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::string message = "failed to open file!";
        LOG(ERROR, message);
        throw std::runtime_error(message);
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

