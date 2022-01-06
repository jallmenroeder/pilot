#pragma once

#include <string>
#include <iostream>

class Logger {
public:
    enum Level {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
    };

    static Logger& get() {
        static Logger instance;
        return instance;
    }

    void _setLogLevel(Level level) {
        logLevel = level;
    }

    Level _getLogLevel() {
        return logLevel;
    }

    void _log(Level severity, std::string_view message) {
        if (severity >= logLevel) {
            std::cout << logLevelToString(severity) << ": " << message << "\n";
        }
    }

    static void setLogLevel(Level level) {
        Logger::get()._setLogLevel(level);
    }

    static Level getLogLevel() {
        return Logger::get()._getLogLevel();
    }

    static Level vulkanMessageSeverityToLogLevel(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
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

    std::string logLevelToString(Level level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "YOU FORGOT TO ADD THE NEW LOG LEVEL TO THE TO_STRING METHOD, SILLY";
        }
    }

    Level logLevel = DEBUG;
};

void LOG(Logger::Level severity, std::string_view message) {
    Logger::get()._log(severity, message);
}
