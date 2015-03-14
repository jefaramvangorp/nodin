#ifndef UI_CREATECONSTANTDIALOG_H_
#define UI_CREATECONSTANTDIALOG_H_

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

class CreateConstantDialog : public QDialog
{
    Q_OBJECT

public:

    CreateConstantDialog(QWidget* parent = 0);

    const std::string& chosenName() const { return name_; }
    const std::string& chosenValue() const { return value_; }
    const std::string& chosenOutputType() const;

private slots:

    void typeSelected(const QString& type);
    void valueChanged(const QString& value);
    void browseClicked();

private:

    void setName();

    std::string name_;
    std::string value_;
    std::string output_type_;

    QLineEdit* value_edit_;
    QPushButton* browse_button_;
};

#endif // UI_CREATECONSTANTDIALOG_H_
