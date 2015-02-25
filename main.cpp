
// Includes.
#include "UI/mainwindow.h"
#include "App/App.h"

// Qt.
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App app;

    MainWindow w(&app);
    w.setMinimumSize(640, 480);
    w.show();

    app.setUI(&w);

    return a.exec();
}
