#ifndef APP_LOGGER_H_
#define APP_LOGGER_H_

// STD.
#include <vector>

class Logger
{
public:

    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void logMessage(const std::string &message) {}
        virtual void logError(const std::string &message) {}
    };

    static Logger& instance();

    void logMessage(const std::string& message);
    void logError(const std::string& message);

    void addDelegate(Delegate* delegate);
    void removeDelegate(Delegate* delegate);

private:
    Logger();

    std::vector<Delegate*> delegates_;
};

#endif // LOGGER_H
