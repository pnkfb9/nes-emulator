#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    enum class Level { TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL };
    
    // Singleton access
    static Logger& getInstance();
    
    // Prevent copying and moving
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    
    // Output management
    void addOutputStream(std::ostream& stream);
    void addFileOutput(const std::string& filename);
    
    // Main logging function
    void log(Level level, const std::string& message);
    
    // Convenience methods
    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

private:
    Logger(); // Private constructor
    
    std::string levelToString(Level level);
    
    std::mutex mutex_;
    std::vector<std::ostream*> streams_;
    std::vector<std::unique_ptr<std::ofstream>> fileStreams_;
};

// Optional macro definitions for easier usage
#define LOG_TRACE(message) Logger::getInstance().log(Logger::Level::TRACE, message)
#define LOG_DEBUG(message) Logger::getInstance().log(Logger::Level::DEBUG, message)
#define LOG_INFO(message) Logger::getInstance().log(Logger::Level::INFO, message)
#define LOG_WARNING(message) Logger::getInstance().log(Logger::Level::WARNING, message)
#define LOG_ERROR(message) Logger::getInstance().log(Logger::Level::ERROR, message)
#define LOG_CRITICAL(message) Logger::getInstance().log(Logger::Level::CRITICAL, message)

#endif // LOGGER_HPP