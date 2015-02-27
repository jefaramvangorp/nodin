
// Includes.
#include "UI/mainwindow.h"
#include "App/App.h"

#include "App/Factories/AdditionNodeFactoryDelegate.h"
#include "App/Factories/ConstantNodeFactoryDelegate.h"
#include "App/Factories/PrinterNodeFactoryDelegate.h"

// Qt.
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App app;
    app.addNodeFactory(new AdditionNodeFactoryDelegate);
    app.addNodeFactory(new ConstantNodeFactoryDelegate);
    app.addNodeFactory(new PrinterNodeFactoryDelegate);

    MainWindow w(&app);
    w.setMinimumSize(640, 480);
    w.show();

    app.setUI(&w);
    app.setDelegate(&w);

    return a.exec();
}
