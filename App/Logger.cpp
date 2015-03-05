
// Includes
#include "Logger.h"

// STD.
#include <iostream>

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::logMessage(const std::string &message)
{
    fprintf(stdout, "%s\n", message.c_str());

    std::vector<Delegate*>::iterator iter;
    for (iter = delegates_.begin(); iter != delegates_.end(); ++iter)
    {
        (*iter)->logMessage(message);
    }
}

void Logger::logError(const std::string &message)
{
    fprintf(stderr, "%s\n", message.c_str());

    std::vector<Delegate*>::iterator iter;
    for (iter = delegates_.begin(); iter != delegates_.end(); ++iter)
    {
        (*iter)->logError(message);
    }
}

void Logger::addDelegate(Logger::Delegate *delegate)
{
    if (delegate != nullptr)
    {
        delegates_.push_back(delegate);
    }
}

void Logger::removeDelegate(Logger::Delegate *delegate)
{
    if (delegate != nullptr)
    {
        delegates_.push_back(delegate);
    }
}

Logger::Logger()
{
}
