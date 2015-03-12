#ifndef UI_SCRIPTEDITORWINDOW_H_
#define UI_SCRIPTEDITORWINDOW_H_

// Qt.
#include <QWidget>

// Forward declarations.
class App;

class ScriptEditorWindow : public QWidget
{
    Q_OBJECT

public:

    ScriptEditorWindow(App* app, QWidget *parent = 0, Qt::WindowFlags flags = 0);

private:

    void buildUI();

    App* app_;
};

#endif // UI_SCRIPTEDITORWINDOW_H_
