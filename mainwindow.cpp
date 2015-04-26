#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "init.h"
#include "updatelines.h"
#include "outputcalcs.h"

#include <QMessageBox>
#include <QString>

Graph<Local*> g;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_options_clicked()
{
    OptionsDialog optionsDialog(this);
    optionsDialog.setModal(true);
    optionsDialog.exec();

}

void MainWindow::on_calculateDistance_clicked()
{
    exec(g);
    OutputCalcs outputcalcs(this);
    outputcalcs.setModal(false);
    outputcalcs.exec();
}

void MainWindow::on_pushButton_clicked()
{
    QString title = "Créditos";
    QString about = "PLANEAMENTO DE ITINERÁRIOS MULTIMODAIS\n\nInterface Gráfica: Afonso Castro\nParsers dos dados do OpenStreetMaps/STCP e scripts para os obter: Afonso Castro\nImplementacao dos algoritmos de cálculo de caminhos: João Silva e Luís Figueiredo\nImplementação do save e load em ficheiros: Afonso Castro, João Silva e Luís Figueiredo\nRelatório: João Silva\nDocumentação Doxygen: Feita pelos autores das respetivas funções/classes.\n\nUm especial obrigado aos professores da unidade curricular por terem disponibilizado uma API para visualização de grafos e ao aluno Gustavo Silva por nos ter fornecido a localização na Internet dos dados dos meios de transporte.\n\nUm obrigado ainda maior a si, utilizador, por estar a usar a nossa aplicação. :)";
    QMessageBox::about(this,title,about);
}

void MainWindow::on_updateLocals_clicked()
{
    UpdateLines updatelines(this);
    updatelines.setModal(false);
    updatelines.exec();
}
