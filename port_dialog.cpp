#include "port_dialog.h"
#include "ui_port_dialog.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolTip>

#include <QDebug>

PORT_Dialog::PORT_Dialog(QStringList list_h,QStringList list_present,QStringList list_bd,QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PORT_Dialog)
{
    ui->setupUi(this);
    this->installEventFilter(this);
   // vec.clear();
    list_BD = list_bd;
    db2 = db;
    db2.open();
    QSqlQuery query;
    query.exec("SELECT id FROM WEATHER");
    while (query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }

    db2.close();

        if(list_present.size()>0){
            id_delete = list_present[0].toInt();
            ui->lineEdit->setText(list_present[0]);//
            ui->lineEdit_2->setText(list_present[1]);
            ui->lineEdit_3->setText(list_present[2]);
            ui->lineEdit_4->setText(list_present[3]);
            ui->lineEdit_5->setText(list_present[4]);
            ui->lineEdit_6->setText(list_present[5]);
            ui->lineEdit_8->setText(list_present[7]);
            ui->comboBox->setCurrentText(list_present[6]);

            ui->pushButton_3->setEnabled(true);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setText("Добавить");
        }


}

PORT_Dialog::~PORT_Dialog()
{
    delete ui;
}

void PORT_Dialog::on_pushButton_clicked()
{
    this->close();
}

void PORT_Dialog::on_pushButton_2_clicked()//добавить сохранить
{

    db2.open();
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
            a_query.addBindValue(ui->lineEdit_2->text());
            a_query.addBindValue(ui->lineEdit_3->text());
            a_query.addBindValue(ui->lineEdit_4->text());
            a_query.addBindValue(ui->lineEdit_5->text());
            a_query.addBindValue(ui->lineEdit_6->text());
            a_query.addBindValue(ui->comboBox->currentText());
            a_query.addBindValue(ui->lineEdit_8->text());

    a_query.exec();

    db2.close();
    emit close_dialog();
    this->close();

}

void PORT_Dialog::on_pushButton_3_clicked()//delete
{
     db2.open();
     QSqlQuery a_query;
     QString str = "";
     a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
     db2.close();
     emit close_dialog();
     this->close();
}

