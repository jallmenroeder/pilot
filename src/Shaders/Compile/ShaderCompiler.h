#pragma once

#include "Common.h"

enum ShaderType {
    VERTEX = 1,
    FRAGMENT,
    COMPUTE
};

class ShaderCompiler {

public:
    static std::vector<uint32_t> spirvFromGlsl(std::string_view path, ShaderType type, bool optimize = false);
};



