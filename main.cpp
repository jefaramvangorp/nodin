
// Includes.
#include "UI/mainwindow.h"
#include "App/App.h"

#include "App/Factories/AdditionNFDelegate.h"
#include "App/Factories/ConstantNFDelegate.h"
#include "App/Factories/PrinterNFDelegate.h"
#include "App/Factories/TextFileNFDelegate.h"

#include "System/QtBasedFileSystem.h"

// Qt.
#include <QApplication>

QString titleString()
{
    QString name = QString::fromStdString(App::appName());
    QString version = QString::fromStdString(App::appVersion());
    return QString("%1 - v%2").arg(name).arg(version);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtBasedFileSystem file_system;

    App app(&file_system);
    app.addNodeFactory(new AdditionNFDelegate);
    app.addNodeFactory(new ConstantNFDelegate);
    app.addNodeFactory(new PrinterNFDelegate);
    app.addNodeFactory(new TextFileNFDelegate);

    MainWindow w(&app);
    w.setWindowTitle(titleString());
    w.setMinimumSize(800, 600);
    w.show();

    app.setUI(&w);
    app.setDelegate(&w);

    return a.exec();
}
