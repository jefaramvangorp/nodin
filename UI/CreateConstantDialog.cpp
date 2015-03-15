
// Includes.
#include "UI/CreateConstantDialog.h"

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

CreateConstantDialog::CreateConstantDialog(QWidget *parent)
    : QDialog(parent)
    , value_edit_(nullptr)
    , browse_button_(nullptr)
{
    QComboBox* type_box = new QComboBox;
    type_box->addItems(QStringList() << "float" << "string" << "file_name"); // TODO: query supported types from app.
    connect(type_box, SIGNAL(currentTextChanged(QString)), this, SLOT(typeSelected(QString)));

    // Note: we have to initialize output type here with selected item,
    //       because otherwise the output type is an empty string when
    //       the user does not change the selection of the combo box.
    output_type_ = type_box->currentText().toStdString();

    value_edit_ = new QLineEdit;
    value_edit_->setMinimumWidth(200);
    connect(value_edit_, &QLineEdit::textChanged, this, &CreateConstantDialog::valueChanged);
    browse_button_ = new QPushButton(tr("Browse..."));
    browse_button_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    browse_button_->setVisible(false);
    connect(browse_button_, &QPushButton::clicked, this, &CreateConstantDialog::browseClicked);

    QHBoxLayout* value_layout = new QHBoxLayout;
    value_layout->addWidget(value_edit_);
    value_layout->addWidget(browse_button_);

    QFormLayout* form_layout = new QFormLayout;
    form_layout->addRow(tr("Type:"), type_box);
    form_layout->addRow(tr("Value:"), value_layout);


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

const std::string& CreateConstantDialog::chosenOutputType() const
{
    if (output_type_ == "file_name")
    {
        return "string";
    }
    else
    {
        return output_type_;
    }
}

void CreateConstantDialog::typeSelected(const QString &type)
{
    // TODO: replace hard-coded strings with constant!

    output_type_ = type.toStdString();
    if (output_type_ == "file_name")
    {
        browse_button_->setVisible(true);
    }
    else
    {
        browse_button_->setVisible(false);
    }
}

void CreateConstantDialog::valueChanged(const QString &value)
{
    value_ = value.toStdString();
    setName();
}

void CreateConstantDialog::setName()
{
    if (output_type_ == "file_name")
    {
        QFileInfo info(QString::fromStdString(value_));
        if (info.isDir())
        {
            name_ = info.dir().dirName().toStdString();
        }
        else
        {
            name_ = info.fileName().toStdString();
        }
    }
    else
    {
        name_ = value_;
    }
}

void CreateConstantDialog::browseClicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open file..."));
    if (!file_name.isEmpty())
    {
        value_edit_->setText(file_name);
        setName();
    }
}
