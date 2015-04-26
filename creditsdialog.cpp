#include "creditsdialog.h"
#include "ui_creditsdialog.h"

CreditsDialog::CreditsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsDialog)
{
    ui->setupUi(this);
}

CreditsDialog::~CreditsDialog()
{
    delete ui;
}
