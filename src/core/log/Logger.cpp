#include "Logger.h"

#include <ctime>

Logger::Logger()
{
    streams_.push_back(&std::cout); // Default: log to console
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::addOutputStream(std::ostream& stream)
{
    std::lock_guard<std::mutex> lock(mutex_);
    streams_.push_back(&stream);
}

void Logger::addFileOutput(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto                        file = std::make_unique<std::ofstream>(filename, std::ios::app);
    if (file->good())
    {
        fileStreams_.push_back(std::move(file));
        streams_.push_back(fileStreams_.back().get());
    }
}

std::string Logger::levelToString(Level level)
{
    switch (level)
    {
        case Level::TRACE:
            return "TRACE";
        case Level::DEBUG:
            return "DEBUG";
        case Level::INFO:
            return "INFO";
        case Level::WARNING:
            return "WARN";
        case Level::ERROR:
            return "ERROR";
        case Level::CRITICAL:
            return "CRIT";
        default:
            return "UNKNOWN";
    }
}