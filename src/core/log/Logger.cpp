#include "Logger.h"
#include <ctime>

Logger::Logger() {
    // Default to console output
    streams_.push_back(&std::cout);
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::addOutputStream(std::ostream& stream) {
    std::lock_guard<std::mutex> lock(mutex_);
    streams_.push_back(&stream);
}

void Logger::addFileOutput(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto file = std::make_unique<std::ofstream>(filename, std::ios::app);
    if (file->good()) {
        fileStreams_.push_back(std::move(file));
        streams_.push_back(fileStreams_.back().get());
    }
}

void Logger::log(Level level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    
    for (auto& stream : streams_) {
        *stream << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] "
                << "[" << levelToString(level) << "] "
                << message << std::endl;
    }
}

std::string Logger::levelToString(Level level) {
    switch(level) {
        case Level::TRACE: return "TRACE";
        case Level::DEBUG: return "DEBUG";
        case Level::INFO: return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR: return "ERROR";
        case Level::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

// Convenience methods implementation
void Logger::trace(const std::string& message) { log(Level::TRACE, message); }
void Logger::debug(const std::string& message) { log(Level::DEBUG, message); }
void Logger::info(const std::string& message) { log(Level::INFO, message); }
void Logger::warning(const std::string& message) { log(Level::WARNING, message); }
void Logger::error(const std::string& message) { log(Level::ERROR, message); }
void Logger::critical(const std::string& message) { log(Level::CRITICAL, message); }