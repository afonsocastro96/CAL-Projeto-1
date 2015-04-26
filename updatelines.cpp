#include "updatelines.h"
#include "ui_updatelines.h"
#include <QString>
#include <unistd.h>
#include "init.h"

UpdateLines::UpdateLines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateLines)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Atualizar linhas"));
    ui->progressBar->setValue(0);
}

UpdateLines::~UpdateLines()
{
    delete ui;
}

void UpdateLines::on_buttonBox_clicked()
{
    ui->label_3->setText("A transferir as paragens de autocarro...");
    callUpdateBusScript();
    ui->label_3->setText("A transferir as paragens de metro...");
    ui->progressBar->setValue(10);
    callUpdateSubwayScript();
    ui->label_3->setText("A tratar a informação obtida...");
    ui->progressBar->setValue(20);
    createFiles();
    ui->label_3->setText("A carregar a informação obtida...");
    ui->progressBar->setValue(50);
    loadFiles(g);
    ui->progressBar->setValue(100);
    ui->label_3->setText("Concluído!");
#ifdef __linux__
    sleep(1);
#else
    Sleep(1000);
#endif


}
