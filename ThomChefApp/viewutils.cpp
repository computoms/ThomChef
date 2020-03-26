#include "viewutils.h"
#include <QMessageBox>

ViewUtils::ViewUtils()
{

}

void ViewUtils::showError(std::string message)
{
    QMessageBox msgBox;
    msgBox.setText(QString(message.c_str()));
    msgBox.exec();
}

void ViewUtils::showInformation(std::string message)
{
    QMessageBox msgBox;
    msgBox.setText(message.c_str());
    msgBox.exec();
}
