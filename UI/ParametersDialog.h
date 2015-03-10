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

class ParametersDialog : public QDialog
{
public:

    ParametersDialog(const std::vector<std::string>& parameters, QWidget* parent = 0);

    std::map<std::string, std::string> parameterValues() const;

    std::string valueForParameter(const std::string& parameter) const;

private:

    QMap<std::string, QLineEdit*> parameter_fields_;

};

#endif // UI_PARAMETERSDIALOG_H_
