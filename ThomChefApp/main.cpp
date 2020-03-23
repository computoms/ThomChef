#include "thomchefwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>

#include "viewutils.h"

int main(int argc, char *argv[])
{
    // UTF-8 Encoding
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    qApp->setWindowIcon(QIcon("Resources/icone.icns"));

    try
    {
        ThomChefWindow w;
        w.setWindowIcon(QIcon("Resources/icon.icns"));
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
