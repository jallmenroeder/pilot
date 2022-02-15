
#pragma once

#include <fstream>
#include <sstream>

#include "Common.h"

static std::string readFile(std::string_view path) {
    std::ifstream file(path.data(), std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::string message = std::string("failed to read file with path \"") + path.data() + "\"";
        LOGGED_EXIT(message)
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return {buffer.begin(), buffer.end()};
}

static std::vector<uint32_t> readFileBinary(std::string_view path) {
    std::ifstream file(path.data(), std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::string message = std::string("failed to read file with path \"") + path.data() + "\"";
        LOGGED_EXIT(message)
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<uint32_t> buffer((fileSize + 1) * sizeof(char) / sizeof(uint32_t));

    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), sizeof(uint32_t) * buffer.size());
    file.close();

    return {buffer.begin(), buffer.end()};
}

static void writeFile(std::string_view path, const std::vector<uint32_t>& data) {
    std::ofstream file(path.data(), std::ios::trunc | std::ios::binary);

    if (!file.is_open()) {
        std::string message = std::string("failed to write file with path \"") + path.data() + "\"";
        LOGGED_EXIT(message)
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint32_t));
    file.close();
}

static bool fileExists(std::string_view path) {
    std::ifstream file(path.data(), std::ios::in);
    return file.is_open();
}

