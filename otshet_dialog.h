#ifndef OTSHET_DIALOG_H
#define OTSHET_DIALOG_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

namespace Ui {
class Otshet_Dialog;
}

class Otshet_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Otshet_Dialog(QSqlDatabase db,int spin, QWidget *parent = nullptr);
    ~Otshet_Dialog();

     QSqlDatabase db2;

private slots:
     void on_pushButton_clicked();

private:
    Ui::Otshet_Dialog *ui;
};

#endif // OTSHET_DIALOG_H
