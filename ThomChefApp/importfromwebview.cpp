#include "importfromwebview.h"
#include "ui_importfromwebview.h"

ImportFromWebView::ImportFromWebView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportFromWebView)
{
    ui->setupUi(this);
    ui->radio_importWebPage->setChecked(true);
}

ImportFromWebView::~ImportFromWebView()
{
    delete ui;
}

bool ImportFromWebView::isImportAllMostSearched() const
{
    return ui->radio_importAllMostSearched->isChecked();
}

std::string ImportFromWebView::getWebPageUrl() const
{
    return ui->lineEdit->text().toStdString();
}

void ImportFromWebView::on_radio_importWebPage_clicked()
{
    ui->radio_importAllMostSearched->setChecked(!ui->radio_importWebPage->isChecked());
}

void ImportFromWebView::on_radio_importAllMostSearched_clicked()
{
    ui->radio_importWebPage->setChecked(!ui->radio_importAllMostSearched->isChecked());
}
