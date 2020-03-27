#ifndef IMPORTFROMWEBVIEW_H
#define IMPORTFROMWEBVIEW_H

#include <QDialog>

namespace Ui {
class ImportFromWebView;
}

class ImportFromWebView : public QDialog
{
    Q_OBJECT

public:
    explicit ImportFromWebView(QWidget *parent = nullptr);
    ~ImportFromWebView();

    bool isImportAllMostSearched() const;
    std::string getWebPageUrl() const;

private slots:
    void on_radio_importWebPage_clicked();

    void on_radio_importAllMostSearched_clicked();

private:
    Ui::ImportFromWebView *ui;
};

#endif // IMPORTFROMWEBVIEW_H
