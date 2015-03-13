#ifndef UI_PARAMETERSDIALOG_H_
#define UI_PARAMETERSDIALOG_H_

// Qt.
#include <QDialog>
#include <QMap>

// STD.
#include <vector>
#include <string>
#include <map>

// Forward declarations.
class QLineEdit;
class QPushButton;

class ParametersDialog : public QDialog
{
    Q_OBJECT

public:

    ParametersDialog(QWidget* parent = 0);

    const std::string& chosenName() const { return name_; }
    const std::string& chosenValue() const { return value_; }
    const std::string& chosenOutputType() const { return output_type_; }

private slots:

    void typeSelected(const QString& type);
    void valueChanged(const QString& value);
    void nameChanged(const QString& name);
    void browseClicked();

private:

    std::string name_;
    std::string value_;
    std::string output_type_;

    QLineEdit* name_edit_;
    QLineEdit* value_edit_;
    QPushButton* browse_button_;
};

#endif // UI_PARAMETERSDIALOG_H_
