#include "schedule_dialog.h"
#include "ui_schedule_dialog.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolTip>

#include <QDebug>
#include <QTime>

SCHEDULE_Dialog::SCHEDULE_Dialog(QStringList list_h,QStringList list_present,QStringList list_bd,QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCHEDULE_Dialog)
{
    ui->setupUi(this);
    this->installEventFilter(this);
   // vec.clear();
    list_BD = list_bd;
    db2 = db;
    db2.open();
    QSqlQuery query;
    query.exec("SELECT name FROM SHIP");
    while (query.next()){
        ui->comboBox_3->addItem(query.value(0).toString());
    }
    query.exec("SELECT name FROM PORT");
    while (query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }
    query.exec("SELECT name FROM PORT");
    while (query.next()){
        ui->comboBox_2->addItem(query.value(0).toString());
    }



        if(list_present.size()>0){
            id_delete = list_present[0].toInt();
            ui->lineEdit->setText(list_present[0]);//
            query.exec("SELECT name FROM SHIP WHERE SHIP.id = "+list_present[1]);
            while (query.next()){
                ui->comboBox_3->setCurrentText(query.value(0).toString());
            }
            query.exec("SELECT name FROM PORT WHERE PORT.id = "+list_present[2]);
            while (query.next()){
                ui->comboBox->setCurrentText(query.value(0).toString());
            }
            query.exec("SELECT name FROM PORT WHERE PORT.id = "+list_present[3]);
            while (query.next()){
                ui->comboBox_2->setCurrentText(query.value(0).toString());
            }
            QDate a;
            a = a.fromString(list_present[4],"dd/MM/yyyy");
            ui->dateEdit_2->setDate(a);
            QTime b;
            b = b.fromString(list_present[5],"hh:mm");
            ui->timeEdit_2->setTime(b);
            a = a.fromString(list_present[6],"dd/MM/yyyy");
            ui->dateEdit->setDate(a);
            b = b.fromString(list_present[7],"hh:mm");
            ui->timeEdit->setTime(b);

            ui->pushButton_3->setEnabled(true);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setText("Добавить");
        }

db2.close();
}

SCHEDULE_Dialog::~SCHEDULE_Dialog()
{
    delete ui;
}

void SCHEDULE_Dialog::on_pushButton_clicked()
{
    this->close();
}

void SCHEDULE_Dialog::on_pushButton_2_clicked()//добавить сохранить
{

    db2.open();
    QSqlQuery query;
    QString nameShip = "";
    query.exec("SELECT id FROM PORT WHERE PORT.name = \""+ui->comboBox->currentText()+"\"");
    while (query.next()){
        nameShip = query.value(0).toString();
    }
    QString nameShip2 = "";
    query.exec("SELECT id FROM PORT WHERE PORT.name = \""+ui->comboBox_2->currentText()+"\"");
    while (query.next()){
        nameShip2 = query.value(0).toString();
    }
    QString nameShip3 = "";
    query.exec("SELECT id FROM SHIP WHERE SHIP.name = \""+ui->comboBox_3->currentText()+"\"");
    while (query.next()){
        nameShip3 = query.value(0).toString();
    }
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
            a_query.addBindValue(nameShip3);
            a_query.addBindValue(nameShip);
            a_query.addBindValue(nameShip2);
            QDate aa = ui->dateEdit_2->date();
            QString d = aa.toString("dd/MM/yyyy");
            a_query.addBindValue(d);
            QTime bb = ui->timeEdit_2->time();
            QString dd = bb.toString("hh:mm");
            a_query.addBindValue(dd);
            aa = ui->dateEdit->date();
            d = aa.toString("dd/MM/yyyy");
            a_query.addBindValue(d);
            bb = ui->timeEdit->time();
            dd = bb.toString("hh:mm");
            a_query.addBindValue(dd);


    a_query.exec();

    db2.close();
    emit close_dialog();
    this->close();

}

void SCHEDULE_Dialog::on_pushButton_3_clicked()//delete
{
     db2.open();
     QSqlQuery a_query;
     QString str = "";
     a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
     db2.close();
     emit close_dialog();
     this->close();
}
