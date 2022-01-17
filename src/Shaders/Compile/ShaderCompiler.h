#pragma once

#include "Common.h"

enum ShaderType {
    VERTEX = 1,
    FRAGMENT,
    COMPUTE
};

class ShaderCompiler {
private:
    static std::string getShaderSuffix(ShaderType type);

public:
    static std::vector<uint32_t> spirvFromGlsl(std::string_view path, ShaderType type, bool optimize = false);
    static std::vector<uint32_t> loadCached(std::string_view name, ShaderType type, bool forceReload, bool optimize = false);
};



