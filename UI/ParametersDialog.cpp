
// Includes.
#include "UI/ParametersDialog.h"

// Qt.
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFileInfo>

ParametersDialog::ParametersDialog(QWidget *parent)
    : QDialog(parent)
    , value_edit_(nullptr)
    , browse_button_(nullptr)
{
    QComboBox* type_box = new QComboBox;
    type_box->addItems(QStringList() << "float" << "string" << "file_name"); // TODO: query supported types from app.
    connect(type_box, SIGNAL(currentTextChanged(QString)), this, SLOT(typeSelected(QString)));

    name_edit_ = new QLineEdit;
    name_edit_->setMinimumWidth(200);
    connect(name_edit_, &QLineEdit::textChanged, this, &ParametersDialog::nameChanged);

    value_edit_ = new QLineEdit;
    value_edit_->setMinimumWidth(200);
    connect(value_edit_, &QLineEdit::textChanged, this, &ParametersDialog::valueChanged);
    browse_button_ = new QPushButton(tr("Browse..."));
    browse_button_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    browse_button_->setVisible(false);
    connect(browse_button_, &QPushButton::clicked, this, &ParametersDialog::browseClicked);

    QHBoxLayout* value_layout = new QHBoxLayout;
    value_layout->addWidget(value_edit_);
    value_layout->addWidget(browse_button_);

    QFormLayout* form_layout = new QFormLayout;
    form_layout->addRow(tr("Type:"), type_box);
    form_layout->addRow(tr("Value:"), value_layout);
    form_layout->addRow(tr("Name:"), name_edit_);


    QPushButton* ok_button = new QPushButton(tr("Ok"));
    connect(ok_button, &QPushButton::clicked, this, &QDialog::accept);
    QPushButton* cancel_button = new QPushButton(tr("Cancel"));
    connect(cancel_button, &QPushButton::clicked, this, &QDialog::reject);

    // Set focus to ok button, so that user just has to press type and press enter.
    ok_button->setFocus();

    QHBoxLayout* button_layout = new QHBoxLayout;
    button_layout->addStretch();
    button_layout->addWidget(ok_button);
    button_layout->addWidget(cancel_button);
    button_layout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(form_layout);
    layout->addLayout(button_layout);
    setLayout(layout);
}

void ParametersDialog::typeSelected(const QString &type)
{
    // TODO: replace hard-coded strings with constant!

    if (type == "file_name")
    {
        output_type_ = "string";
        browse_button_->setVisible(true);
    }
    else
    {
        output_type_ = type.toStdString();
        browse_button_->setVisible(false);
    }
}

void ParametersDialog::valueChanged(const QString &value)
{
    value_ = value.toStdString();
}

void ParametersDialog::nameChanged(const QString &name)
{
    name_ = name.toStdString();
}

void ParametersDialog::browseClicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open file..."));
    if (!file_name.isEmpty())
    {
        value_edit_->setText(file_name);

        QFileInfo info(file_name);
        if (info.isDir())
        {
            name_edit_->setText(info.dir().dirName());
        }
        else
        {
            name_edit_->setText(info.fileName());
        }
    }
}
