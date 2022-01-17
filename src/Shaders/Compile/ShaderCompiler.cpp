#include "ShaderCompiler.h"

#include <shaderc/shaderc.hpp>
#include <filesystem>
#include <algorithm>

#include "Util/FileUtil.h"

#define SHADER_SRC "/shaders/in/"
#define SHADER_CACHE "/shaders/out/"

class ShaderIncluder: public shaderc::CompileOptions::IncluderInterface {
    // Handles shaderc_include_resolver_fn callbacks.
private:
    std::string content;
    std::string sourceName;
    std::vector<std::string> includedFiles;

public:
    shaderc_include_result* GetInclude(const char* requested_source, shaderc_include_type type,
                                               const char* requesting_source, size_t include_depth) override {
        auto* result = new shaderc_include_result();

        std::filesystem::path sourcePath(requesting_source);
        // first look in directory of the file that included
        std::filesystem::path requestedPath(std::string(PROJECT_SOURCE_DIR) + SHADER_SRC + sourcePath.parent_path().string() + "/" + requested_source);
        // now look in the shader directory
        if (!exists(requestedPath)) {
            requestedPath = std::filesystem::path(std::string(PROJECT_SOURCE_DIR) + SHADER_SRC + requested_source);
            if (!exists(requestedPath)) {
                LOG(ERROR, "Could not find shader file '" + std::string(requested_source) + "' included in '" + requesting_source + "'");
                return result;
            }
        }

        sourceName = requestedPath.string();
        // early return, if file was already loaded.
        if (std::find(includedFiles.begin(), includedFiles.end(), sourceName) != includedFiles.end()) {
            result->content = "\n";
            result->content_length = 1;
            result->source_name = sourceName.c_str();
            result->source_name_length = sourceName.size();
            return result;
        }
        content = readFile(sourceName);
        result->content = content.c_str();
        result->content_length = content.size();
        result->source_name = sourceName.c_str();
        result->source_name_length = sourceName.size();
        includedFiles.emplace_back(sourceName);
        return result;
    }

    // Handles shaderc_include_result_release_fn callbacks.
    void ReleaseInclude(shaderc_include_result* data) override {
        sourceName = "";
        content = "";
        delete data;
    }
};

std::string ShaderCompiler::getShaderSuffix(ShaderType type) {
    switch(type) {
        case VERTEX: return ".vert";
        case FRAGMENT: return ".frag";
        case COMPUTE: return ".comp";
        default: return ".unknown";
    }
}

static shaderc_shader_kind getShaderKind(ShaderType type) {
    switch(type) {
        case VERTEX: return shaderc_glsl_vertex_shader;
        case FRAGMENT: return shaderc_glsl_fragment_shader;
        case COMPUTE: return shaderc_glsl_compute_shader;
        default:
        THROW_LOGGED_ERROR("Unknown shader type, ABORTING!")
    }
}

std::vector<uint32_t> ShaderCompiler::spirvFromGlsl(std::string_view path, ShaderType type, bool optimize) {
    shaderc_shader_kind kind = getShaderKind(type);
    std::string suffix = getShaderSuffix(type);

    // load glsl shader code
    std::string fullPath = std::string(PROJECT_SOURCE_DIR) + SHADER_SRC + path.data() + suffix;
    std::string shaderCode = readFile(fullPath);

    auto includer = std::make_unique<ShaderIncluder>();

    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    if (optimize) options.SetOptimizationLevel(shaderc_optimization_level_size);
    options.SetIncluder(std::move(includer));


    shaderc::SpvCompilationResult spirvCode = compiler.CompileGlslToSpv(shaderCode, kind, path.data(), options);

    if (spirvCode.GetCompilationStatus() != shaderc_compilation_status_success) {
        LOG(ERROR, spirvCode.GetErrorMessage());
        throw std::runtime_error("Error while loading shader!");
    }

    return {spirvCode.cbegin(), spirvCode.cend()};
}

std::vector<uint32_t>
ShaderCompiler::loadCached(std::string_view name, ShaderType type, bool forceReload, bool optimize) {
    std::string cachePath = std::string(PROJECT_SOURCE_DIR) + SHADER_CACHE + name.data() + getShaderSuffix(type) + ".spv";
    std::vector<uint32_t> spirvCode;

    if (forceReload || !fileExists(cachePath)) {
        spirvCode = ShaderCompiler::spirvFromGlsl(name, type, optimize);
        writeFile(cachePath, spirvCode);
    } else {
        spirvCode = readFileBinary(cachePath);
    }
    return spirvCode;
}