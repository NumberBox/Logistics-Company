#include "ship_dialog.h"
#include "ui_ship_dialog.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolTip>

#include <QDebug>
#include <QTime>

SHIP_Dialog::SHIP_Dialog(QStringList list_h,QStringList list_present,QStringList list_bd,QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SHIP_Dialog)
{
    ui->setupUi(this);
    this->installEventFilter(this);
   // vec.clear();
    list_BD = list_bd;
    db2 = db;
    db2.open();
    QSqlQuery query;
    ui->comboBox->addItem("Ледокол");
    ui->comboBox->addItem("Газовоз");
    ui->comboBox->addItem("Танкер");
    ui->comboBox->addItem("Лихтеровоз");
    ui->comboBox->addItem("Рефрижераторное судно");
    ui->comboBox->addItem("Роллер");
    ui->comboBox->addItem("Контейнеровоз");
    ui->comboBox->addItem("Балкер");
    ui->comboBox->addItem("Сухогруз");

    query.exec("SELECT name FROM PORT");
    while (query.next()){
        ui->comboBox_4->addItem(query.value(0).toString());
    }
    ui->comboBox_4->addItem("0");


        if(list_present.size()>0){
            id_delete = list_present[0].toInt();
            ui->lineEdit->setText(list_present[0]);//
            ui->lineEdit_4->setText(list_present[1]);//
            ui->comboBox->setCurrentText(list_present[2]);//
            ui->lineEdit_3->setText(list_present[3]);//
            query.exec("SELECT name FROM PORT WHERE PORT.id = "+list_present[4]);
            while (query.next()){
                ui->comboBox_4->setCurrentText(query.value(0).toString());
            }
            ui->lineEdit_2->setText(list_present[5]);//

            ui->pushButton_3->setEnabled(true);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setText("Добавить");
        }

db2.close();
}

SHIP_Dialog::~SHIP_Dialog()
{
    delete ui;
}

void SHIP_Dialog::on_pushButton_clicked()
{
    this->close();
}

void SHIP_Dialog::on_pushButton_2_clicked()//добавить сохранить
{

    db2.open();
    QSqlQuery query;

    QString nameShip2 = "";
    if(ui->comboBox_4->currentText()=="0")
        nameShip2="0";
    else{
        query.exec("SELECT id FROM PORT WHERE PORT.name = \""+ui->comboBox_4->currentText()+"\"");
        while (query.next()){
            nameShip2 = query.value(0).toString();
        }
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
            a_query.addBindValue(ui->lineEdit_4->text());//
            a_query.addBindValue(ui->comboBox->currentText());//
            a_query.addBindValue(ui->lineEdit_3->text());//
            a_query.addBindValue(nameShip2);//
            a_query.addBindValue(ui->lineEdit_2->text());//




    a_query.exec();

    db2.close();
    emit close_dialog();
    this->close();

}

void SHIP_Dialog::on_pushButton_3_clicked()//delete
{
     db2.open();
     QSqlQuery a_query;
     QString str = "";
     a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
     db2.close();
     emit close_dialog();
     this->close();
}
