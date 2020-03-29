#include "Import/recipewebscraper.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

std::string RecipeWebScraper::findRaw(size_t &startingPosition,
                                   std::string opening, std::string closing) const
{
    size_t start = m_rawHtml.find(opening, startingPosition);
    if (start == std::string::npos)
        return "";
    size_t end = m_rawHtml.find(closing, start);
    if (end == std::string::npos)
        return "";
    startingPosition = end;
    return m_rawHtml.substr(start, end - start + closing.size());
}

std::string RecipeWebScraper::findWithoutTags(size_t &startingPosition, std::string opening, std::string closing) const
{
    std::string output = findRaw(startingPosition, opening, closing);
    if (output == "" || output.size() < opening.size() + closing.size() + 1)
        return output;
    return output.substr(opening.size(), output.size() - opening.size() - closing.size());
}

void RecipeWebScraper::extractHtml(std::string url)
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(QString(url.c_str()))));
    QEventLoop event;
    connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QString html = response->readAll();
    m_rawHtml = html.toStdString();
}
