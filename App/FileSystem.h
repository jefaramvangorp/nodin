#ifndef APP_FILESYSTEM_H_
#define APP_FILESYSTEM_H_

// STD.
#include <string>
#include <vector>

class FileMonitor
{
public:
    virtual ~FileMonitor() {}
    virtual void fileWasModified() = 0;
};

class FileSystem
{
public:
    virtual ~FileSystem() {}

    virtual std::string generateUUID() const = 0;
    virtual std::vector<std::string> listFilesInDir(const std::string& path, const std::string& extension) = 0;
    virtual void registerFileMonitor(const std::string& fileName, FileMonitor* monitor) = 0;
    virtual void unregisterFileMonitor(const std::string& fileName) = 0;
};

#endif // APP_FILESYSTEM_H_
