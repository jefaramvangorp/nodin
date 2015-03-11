#ifndef APP_FILESYSTEM_H_
#define APP_FILESYSTEM_H_

// STD.
#include <string>
#include <vector>

class FileSystem
{
public:
    virtual ~FileSystem() {}

    virtual std::string generateUUID() const = 0;
    virtual std::vector<std::string> listFilesInDir(const std::string& path, const std::string& extension) = 0;
};

#endif // APP_FILESYSTEM_H_
