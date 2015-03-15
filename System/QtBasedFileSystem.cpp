
// Includes.
#include "System/QtBasedFileSystem.h"

// Qt.
#include <QUuid>
#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>

QtBasedFileSystem::QtBasedFileSystem()
    : watcher_(new QFileSystemWatcher(this))
{
    connect(watcher_, &QFileSystemWatcher::fileChanged, this, &QtBasedFileSystem::fileChanged);
}

QtBasedFileSystem::~QtBasedFileSystem()
{
    foreach (FileMonitor* monitor, file_monitors_.values())
    {
        delete monitor;
    }
    file_monitors_.clear();
}

std::string QtBasedFileSystem::generateUUID() const
{
    return QUuid::createUuid().toString().toStdString();
}

std::string QtBasedFileSystem::baseName(const std::string &absolutePath) const
{
    QFileInfo info(QString::fromStdString(absolutePath));
    if (info.isDir())
    {
        return info.dir().dirName().toStdString(); // E.g. returns "mail" for "/var/spool/mail"
    }
    else
    {
        return info.fileName().toStdString(); // E.g. returns "archive.tar.gz" for "/tmp/archive.tar.gz"
    }
}

std::vector<std::string> QtBasedFileSystem::listFilesInDir(const std::string &path, const std::string &extension)
{
    std::vector<std::string> result;

    QDir dir(QString::fromStdString(path));
    QString extension_filter = QString("*.%1").arg(QString::fromStdString(extension));
    QStringList files = dir.entryList(QStringList() << extension_filter, QDir::Files);

    foreach (QString file, files)
    {
        result.push_back(dir.absoluteFilePath(file).toStdString());
    }

    return result;
}

void QtBasedFileSystem::registerFileMonitor(const std::string &fileName, FileMonitor *monitor)
{
    QString path = QString::fromStdString(fileName);

    unregisterFileMonitor(fileName);
    file_monitors_.insert(path, monitor);
    watcher_->addPath(path);
}

void QtBasedFileSystem::unregisterFileMonitor(const std::string &fileName)
{
    QString path = QString::fromStdString(fileName);

    if (file_monitors_.contains(path))
    {
        delete file_monitors_.take(path);
        watcher_->removePath(path);
    }
}

void QtBasedFileSystem::fileChanged(const QString &fileName)
{
    if (file_monitors_.contains(fileName))
    {
        file_monitors_[fileName]->fileWasModified();
    }

    watcher_->addPath(fileName);
}
