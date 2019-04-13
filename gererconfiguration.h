#ifndef GERERCONFIGURATION_H
#define GERERCONFIGURATION_H

#include <QWidget>
//#include "configuration.h"
#include "data.h"

namespace Ui {
class GererConfiguration;
}

class GererConfiguration : public QWidget
{
    Q_OBJECT
    
public:
    explicit GererConfiguration(QWidget *parent = 0);
    void init(Data* sourcesG);
    ~GererConfiguration();
    
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_feculents_valueChanged(int arg1);

    void on_spinBox_viandes_valueChanged(int arg1);

    void on_spinBox_autres_valueChanged(int arg1);

private:
    Ui::GererConfiguration *ui;
    Data* sources;

    unsigned int nombreSemaines;
};

#endif // GERERCONFIGURATION_H
