
// Includes.
#include "UI/mainwindow.h"
#include "App/App.h"

#include "App/Factories/AdditionNodeFactoryDelegate.h"
#include "App/Factories/ConstantNodeFactoryDelegate.h"
#include "App/Factories/PrinterNodeFactoryDelegate.h"

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

    App app;
    app.addNodeFactory(new AdditionNodeFactoryDelegate);
    app.addNodeFactory(new ConstantNodeFactoryDelegate);
    app.addNodeFactory(new PrinterNodeFactoryDelegate);

    MainWindow w(&app);
    w.setWindowTitle(titleString());
    w.setMinimumSize(640, 480);
    w.show();

    app.setUI(&w);
    app.setDelegate(&w);

    return a.exec();
}
