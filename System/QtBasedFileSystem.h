#ifndef SYSTEM_QTBASEDFILESYSTEM_H_
#define SYSTEM_QTBASEDFILESYSTEM_H_

// Includes.
#include "App/FileSystem.h"

class QtBasedFileSystem : public FileSystem
{
public:
    QtBasedFileSystem();
    virtual ~QtBasedFileSystem();

    virtual std::string generateUUID() const;
};

#endif // SYSTEM_QTBASEDFILESYSTEM_H_
