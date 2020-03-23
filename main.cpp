#include "old-views/mainwindow.h"
#include "views/thomchefwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>

#include "viewutils.h"

//#define OLD_VIEW

int main(int argc, char *argv[])
{
    // UTF-8 Encoding
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    qApp->setWindowIcon(QIcon("Resources/icone.icns"));

    try {

#ifdef OLD_VIEW
    MainWindow w;
    w.setWindowIcon(QIcon("Resources/icone.icns"));
    w.showMaximized();
#else
    ThomChefWindow w;
    w.setWindowIcon(QIcon("Resources/icon.icns"));
    w.initialize();
    w.showMaximized();
#endif


        return a.exec();
    } catch (std::exception e) {
        ViewUtils::showError(e.what());
        return EXIT_FAILURE;
    }
}
