#ifndef SYSTEM_QTBASEDFILESYSTEM_H_
#define SYSTEM_QTBASEDFILESYSTEM_H_

// Includes.
#include "App/FileSystem.h"

// Qt.
#include <QObject>
#include <QString>
#include <QHash>

// Forward declarations.
class QFileSystemWatcher;

class QtBasedFileSystem : public QObject, public FileSystem
{
    Q_OBJECT

public:
    QtBasedFileSystem();
    virtual ~QtBasedFileSystem();

    virtual std::string generateUUID() const;
    virtual std::string baseName(const std::string& absolutePath) const;
    virtual std::vector<std::string> listFilesInDir(const std::string& path, const std::string& extension);
    virtual void registerFileMonitor(const std::string& fileName, FileMonitor* monitor);
    virtual void unregisterFileMonitor(const std::string& fileName);

private slots:

    void fileChanged(const QString& fileName);

private:

    QHash<QString, FileMonitor*> file_monitors_;
    QFileSystemWatcher* watcher_;
};

#endif // SYSTEM_QTBASEDFILESYSTEM_H_
