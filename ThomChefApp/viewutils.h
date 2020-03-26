#ifndef VIEWUTILS_H
#define VIEWUTILS_H

#include <string>

class ViewUtils
{
public:
    ViewUtils();

    static void showError(std::string message);
    static void showInformation(std::string message);
    static bool askQuestion(std::string message);
};

#endif // VIEWUTILS_H
