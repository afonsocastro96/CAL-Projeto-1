#ifndef UPDATELINES_H
#define UPDATELINES_H

#include <QDialog>

namespace Ui {
class UpdateLines;
}

class UpdateLines : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateLines(QWidget *parent = 0);
    ~UpdateLines();

private slots:
    void on_buttonBox_clicked();

private:
    Ui::UpdateLines *ui;
};

#endif // UPDATELINES_H
