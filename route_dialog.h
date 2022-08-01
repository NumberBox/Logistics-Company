#ifndef ROUTE_DIALOG_H
#define ROUTE_DIALOG_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"


namespace Ui {
class ROUTE_Dialog;
}

class ROUTE_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ROUTE_Dialog(QStringList list_h, QStringList list_present,QStringList list_bd,QSqlDatabase db, QWidget *parent = nullptr);
    ~ROUTE_Dialog();
    QStringList list_BD;
   // QVector<QLineEdit*> vec;
    QSqlDatabase db2;
    int id_delete;

    QVector<QString> ship_tooltop;
    QVector<QString> port_tooltop;
    QVector<QString> weather_tooltip;
    QString toltip="";
   // bool eventFilter(QObject *watched, QEvent *event);


signals:
    void close_dialog();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
private:
    Ui::ROUTE_Dialog *ui;
};

#endif // ROUTE_DIALOG_H
