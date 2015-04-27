#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "init.h"

#include <string>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Opções"));

    for(unsigned int local = 0; local < g.getVertexSet().size(); local++){
        ui->comboBox_2->addItem(g.getVertexSet().at(local)->getInfo()->getNome().c_str());
        ui->comboBox_3->addItem(g.getVertexSet().at(local)->getInfo()->getNome().c_str());
    }
    ui->comboBox_2->setEditable(true);
    ui->comboBox_3->setEditable(true);
    ui->comboBox_3->setCurrentIndex(1);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::on_buttonBox_accepted()
{
    string res = ui->comboBox->currentText().toStdString();
    string resXstr;
    string resYstr;

    /* Resolucao do ecra */
    int index = 0;

    while(isdigit(res[index])){
        resXstr.push_back(res[index]);
        index++;
    }

    index++;

    while(isdigit(res[index])){
        resYstr.push_back(res[index]);
        index++;
    }

    resX = stoi(resXstr);
    resY = stoi(resYstr);

    /* Preferencia */

    if(ui->radioButton_3->isChecked()){
        preference = DISTANCE;
    }
    else if(ui->radioButton_4->isChecked()){
        preference = PRICE;
    }
    else if(ui->radioButton_5->isChecked()){
        preference = TIME;
    }

    /* Algoritmo */

    if(ui->radioButton->isChecked()){
        algorithm = 0;
    }
    else if(ui->radioButton_2->isChecked()){
        algorithm = 1;
    }

    /* Paragens */
    idPartida = ui->comboBox_2->currentIndex();
    idChegada = ui->comboBox_3->currentIndex();
}
