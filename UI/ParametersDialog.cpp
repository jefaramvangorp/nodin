
// Includes.
#include "UI/ParametersDialog.h"

// Qt.
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

ParametersDialog::ParametersDialog(const std::vector<std::string> &parameters, QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* param_layout = new QGridLayout;

    for (int i = 0; i < (int)parameters.size(); ++i)
    {
        std::string parameter = parameters.at(i);
        QLabel* parameter_label = new QLabel(QString::fromStdString(parameter));
        QLineEdit* parameter_field = new QLineEdit;

        param_layout->addWidget(parameter_label, i, 0);
        param_layout->addWidget(parameter_field, i, 1);

        parameter_fields_.insert(parameter, parameter_field);
    }

    QPushButton* ok_button = new QPushButton(tr("Ok"));
    connect(ok_button, &QPushButton::clicked, this, &QDialog::accept);
    QPushButton* cancel_button = new QPushButton(tr("Cancel"));
    connect(cancel_button, &QPushButton::clicked, this, &QDialog::reject);

    ok_button->setFocus();

    QHBoxLayout* button_layout = new QHBoxLayout;
    button_layout->addStretch();
    button_layout->addWidget(ok_button);
    button_layout->addWidget(cancel_button);
    button_layout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(param_layout);
    layout->addLayout(button_layout);
    setLayout(layout);
}

std::map<std::string, std::string> ParametersDialog::parameterValues() const
{
    std::map<std::string, std::string> result;

    foreach (std::string param, parameter_fields_.keys())
    {
        result[param] = parameter_fields_.value(param)->text().toStdString();
    }

    return result;
}

std::string ParametersDialog::valueForParameter(const std::string &parameter) const
{
    return parameter_fields_[parameter]->text().toStdString();
}
