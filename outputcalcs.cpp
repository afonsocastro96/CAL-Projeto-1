#include "outputcalcs.h"
#include "ui_outputcalcs.h"
#include <string>

#include <QMessageBox>

OutputCalcs::OutputCalcs(QWidget *parent, std::string percurso) :
    QDialog(parent),
    ui(new Ui::OutputCalcs)
{
    this->setWindowTitle(QString("Itinerário"));
    ui->setupUi(this);
    ui->textBrowser->append(QString(percurso.c_str()));
}

OutputCalcs::~OutputCalcs()
{
    delete ui;
}
