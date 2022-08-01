#ifndef RASPIS_H
#define RASPIS_H

#include <QDialog>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

namespace Ui {
class Raspis;
}

class Raspis : public QDialog
{
    Q_OBJECT

public:
    explicit Raspis(QSqlDatabase db,int wath_this, QWidget *parent = nullptr);
    ~Raspis();

    int wath_this;
    QSqlDatabase db;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Raspis *ui;
};

#endif // RASPIS_H
