#include "outputcalcs.h"
#include "ui_outputcalcs.h"

#include <QMessageBox>

OutputCalcs::OutputCalcs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutputCalcs)
{
    this->setWindowTitle(QString("Itinerário"));
    ui->setupUi(this);
    ui->textBrowser->append(QString("Siga a pé até à estação de metro Marquês.\nSiga até à estação de metro IPO.\nSiga a pé até à estação de autocarro Hospital São João.\nSiga até à estação de autocarro Faculdade de Engenharia."));
}

OutputCalcs::~OutputCalcs()
{
    delete ui;
}
