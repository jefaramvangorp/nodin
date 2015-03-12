
// Includes.
#include "UI/ScriptEditorWindow.h"

#include "App/App.h"

// Qt.
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>

ScriptEditorWindow::ScriptEditorWindow(App *app, QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , app_(app)
{
    buildUI();
}

void ScriptEditorWindow::buildUI()
{
    QPushButton* validate_button = new QPushButton(tr("Validate"));
    validate_button->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    validate_button->setToolTip(tr("Build the script and check whether it adheres to the requirements."));

    QHBoxLayout* button_layout = new QHBoxLayout;
    button_layout->addStretch();
    button_layout->addWidget(validate_button);
    button_layout->addStretch();

    QLineEdit* name_edit = new QLineEdit;
    QLineEdit* input_types_edit = new QLineEdit;
    input_types_edit->setMinimumWidth(300);
    QLineEdit* output_types_edit = new QLineEdit;
    output_types_edit->setMinimumWidth(300);
    QTextEdit* evaluate_edit = new QTextEdit;
    evaluate_edit->setMinimumSize(400, 300);
    evaluate_edit->setText("function evaluateForOutput(outputIndex)\n"
                           "    -- TODO: implement this function.\n"
                           "end");

    QFormLayout* form_layout = new QFormLayout;
    form_layout->setFormAlignment(Qt::AlignLeft);
    form_layout->addRow(tr("Name/Type"), name_edit);
    form_layout->addRow(tr("Input types"), input_types_edit);
    form_layout->addRow(tr("Output types"), output_types_edit);
    form_layout->addRow(tr("Evaluation Code"), evaluate_edit);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(button_layout);
    layout->addLayout(form_layout);
    setLayout(layout);

    setMinimumSize(500, 600);
}
