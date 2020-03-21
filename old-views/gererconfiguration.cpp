#include "gererconfiguration.h"
#include "ui_gererconfiguration.h"
#include <iostream>
#include <sstream>
#include "XMLParser.h"

GererConfiguration::GererConfiguration(QWidget *parent):
    QWidget(parent),
    ui(new Ui::GererConfiguration),
    nombreSemaines(1)
{
    ui->setupUi(this);
}

GererConfiguration::~GererConfiguration()
{
    delete ui;
}

void GererConfiguration::init(Data *sourcesG)
{
    sources = sourcesG;
    ui->spinBox->setValue(sources->getRepetitionCongel());
    ui->spinBox_2->setValue(sources->getRepetitionLegume());
    ui->spinBox_feculents->setValue(sources->getRepetitionFeculent());
    ui->spinBox_viandes->setValue(sources->getRepetitionViande());
    ui->spinBox_autres->setValue(sources->getRepetitionAutre());
}

void GererConfiguration::on_spinBox_valueChanged(int arg1)
{
    sources->setRepetitionCongel(arg1);
    init(sources);
}

void GererConfiguration::on_spinBox_2_valueChanged(int arg1)
{
    sources->setRepetitionLegume(arg1);
    init(sources);
}

void GererConfiguration::on_spinBox_feculents_valueChanged(int arg1)
{
    sources->setRepetitionFeculent(arg1);
    init(sources);
}

void GererConfiguration::on_spinBox_viandes_valueChanged(int arg1)
{
    sources->setRepetitionViande(arg1);
    init(sources);
}

void GererConfiguration::on_spinBox_autres_valueChanged(int arg1)
{
    sources->setRepetitionAutre(arg1);
    init(sources);
}
