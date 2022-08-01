#include "statictics_dialog.h"
#include "ui_statictics_dialog.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolTip>

#include <QDebug>
#include <QTime>

STATICTICS_Dialog::STATICTICS_Dialog(QStringList list_h,QStringList list_present,QStringList list_bd,QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STATICTICS_Dialog)
{
    ui->setupUi(this);
    this->installEventFilter(this);
   // vec.clear();
    list_BD = list_bd;
    db2 = db;
    db2.open();
    QSqlQuery query;



        if(list_present.size()>0){
            id_delete = list_present[0].toInt();
            ui->lineEdit->setText(list_present[0]);//
            ui->lineEdit_4->setText(list_present[1]);//
            QDate a;
            a = a.fromString(list_present[2],"dd/MM/yyyy");
            ui->dateEdit->setDate(a);
            QTime b;
            b = b.fromString(list_present[3],"hh:mm");
            ui->timeEdit->setTime(b);

            ui->lineEdit_2->setText(list_present[4]);//

            ui->pushButton_3->setEnabled(true);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setText("Добавить");
        }

db2.close();
}

STATICTICS_Dialog::~STATICTICS_Dialog()
{
    delete ui;
}

void STATICTICS_Dialog::on_pushButton_clicked()
{
    this->close();
}

void STATICTICS_Dialog::on_pushButton_2_clicked()//добавить сохранить
{

    db2.open();
    QSqlQuery query;


    QSqlQuery a_query;

        if(ui->pushButton_2->text()!="Добавить"){
            a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
        }

        QString str = " (";
        for (int i = 1;i<list_BD.size();i++) {
            if(i==list_BD.size()-1){
              str+=list_BD[i]+")";
            }
            else
                str+=list_BD[i]+", ";
        }
        str+="VALUES (";
        for (int i = 1;i<list_BD.size();i++) {
            if(i==list_BD.size()-1){
              str+="?)";
            }
            else
                str+="?, ";
        }

        a_query.prepare("INSERT INTO "+list_BD[0]+str);

            a_query.addBindValue(ui->lineEdit->text());//
            a_query.addBindValue(ui->lineEdit_4->text());//
            QDate aa = ui->dateEdit->date();
            QString d = aa.toString("dd/MM/yyyy");
            a_query.addBindValue(d);
            QTime bb = ui->timeEdit->time();
            QString dd = bb.toString("hh:mm");
            a_query.addBindValue(dd);
            a_query.addBindValue(ui->lineEdit_2->text());//




    a_query.exec();

    db2.close();
    emit close_dialog();
    this->close();

}

void STATICTICS_Dialog::on_pushButton_3_clicked()//delete
{
     db2.open();
     QSqlQuery a_query;
     QString str = "";
     a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
     db2.close();
     emit close_dialog();
     this->close();
}
