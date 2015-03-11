
// Includes.
#include "System/QtBasedFileSystem.h"

// Qt.
#include <QUuid>
#include <QDir>

QtBasedFileSystem::QtBasedFileSystem()
{
}

QtBasedFileSystem::~QtBasedFileSystem()
{

}

std::string QtBasedFileSystem::generateUUID() const
{
    return QUuid::createUuid().toString().toStdString();
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
