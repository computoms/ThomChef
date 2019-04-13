#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    // UTF-8 Encoding
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    qApp->setWindowIcon(QIcon("icone.icns"));

    MainWindow w;
    w.setWindowIcon(QIcon("icone.icns"));
    w.showMaximized();
    return a.exec();
}
