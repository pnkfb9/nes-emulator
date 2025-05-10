#pragma once

#include <fmt/format.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class Logger
{
public:
    enum class Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    static Logger& getInstance();

    // Delete copy/move
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Output control
    void addOutputStream(std::ostream& stream);
    void addFileOutput(const std::string& filename);

    // Core logging function
    template <typename... Args>
    void log(Level level, std::string_view module, std::string_view format, Args&&... args);

private:
    Logger(); // Private constructor
    std::string levelToString(Level level);

    std::mutex                                  mutex_;
    std::vector<std::ostream*>                  streams_;
    std::vector<std::unique_ptr<std::ofstream>> fileStreams_;
};

// --- Helper to extract module name from file path ---
inline std::string_view extractModuleName(std::string_view filepath)
{
    size_t last_slash = filepath.find_last_of("/\\");
    size_t last_dot = filepath.find_last_of('.');
    if (last_dot == std::string_view::npos)
        last_dot = filepath.size();
    return filepath.substr(last_slash == std::string_view::npos ? 0 : last_slash + 1,
                           last_dot - (last_slash == std::string_view::npos ? 0 : last_slash + 1));
}

template <typename... Args>
void Logger::log(Level level, std::string_view module, std::string_view format, Args&&... args)
{
    std::lock_guard<std::mutex> lock(mutex_);

    const auto         now = std::chrono::system_clock::now();
    const auto         time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream timestamp;
    timestamp << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

    std::string formatted_msg = fmt::format(fmt::runtime(format), std::forward<Args>(args)...);

    for (auto& stream : streams_)
    {
        *stream << fmt::format("[{}] [{}] [{}] {}\n",
                               timestamp.str(),
                               module,
                               levelToString(level),
                               formatted_msg);
    }
}

// --- LOG macro with automatic module name ---
#define LOG(verbosity, ...)                                                                        \
    Logger::getInstance().log(Logger::Level::verbosity, extractModuleName(__FILE__), __VA_ARGS__)
