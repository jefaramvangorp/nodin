#ifndef APP_FILESYSTEM_H_
#define APP_FILESYSTEM_H_

// STD.
#include <string>

class FileSystem
{
public:
    virtual ~FileSystem() {}

    virtual std::string generateUUID() const = 0;
};

#endif // APP_FILESYSTEM_H_
