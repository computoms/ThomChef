#include "thomchefwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>
#include <QFile>

#include "viewutils.h"

int main(int argc, char *argv[])
{
    // UTF-8 Encoding
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    qApp->setWindowIcon(QIcon("icone.icns"));

    QFile file("style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);

    try
    {
        ThomChefWindow w;
        w.setWindowIcon(QIcon("icon.icns"));
        w.initialize();
        w.showMaximized();

        return a.exec();
    }
    catch (std::exception e)
    {
        ViewUtils::showError(e.what());
        return EXIT_FAILURE;
    }
}
