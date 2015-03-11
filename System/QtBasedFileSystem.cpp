
// Includes.
#include "System/QtBasedFileSystem.h"

// Qt.
#include <QUuid>

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
