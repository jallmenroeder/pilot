#pragma once

#include <string>
#include <iostream>

#include <vulkan/vulkan.h>

enum LogLevel {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
};

class Logger {
public:

    static Logger& get() {
        static Logger instance;
        return instance;
    }

    void _setLogLevel(LogLevel level) {
        logLevel = level;
    }

    LogLevel _getLogLevel() {
        return logLevel;
    }

    void _log(LogLevel severity, std::string_view message) {
        if (severity >= logLevel) {
            std::cout << logLevelToString(severity) << ": " << message << "\n";
        }
    }

    static void setLogLevel(LogLevel level) {
        Logger::get()._setLogLevel(level);
    }

    static LogLevel getLogLevel() {
        return Logger::get()._getLogLevel();
    }

    static LogLevel vulkanMessageSeverityToLogLevel(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
        switch (severity) {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return DEBUG;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return INFO;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return WARNING;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return ERROR;
            default: return ERROR;
        }
    }
private:
    Logger() = default;

    static std::string logLevelToString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "YOU FORGOT TO ADD THE NEW LOG LEVEL TO THE TO_STRING METHOD, SILLY";
        }
    }

    LogLevel logLevel = DEBUG;
};

inline void LOG(LogLevel severity, std::string_view message) {
    Logger::get()._log(severity, message);
}
