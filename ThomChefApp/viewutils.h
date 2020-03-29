#ifndef VIEWUTILS_H
#define VIEWUTILS_H

#include <string>

/**
 * @brief The ViewUtils class is a UI helper class.
 */
class ViewUtils
{
public:
    ViewUtils();

    static void showError(std::string message);
    static void showInformation(std::string message);
    static bool askQuestion(std::string message);
};

#endif // VIEWUTILS_H
