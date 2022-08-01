#include "capasity_order_dialog.h"
#include "ui_capasity_order_dialog.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolTip>

#include <QDebug>
#include <QTime>

CAPASITY_ORDER_Dialog::CAPASITY_ORDER_Dialog(QStringList list_h,QStringList list_present,QStringList list_bd,QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAPASITY_ORDER_Dialog)
{
    ui->setupUi(this);
    this->installEventFilter(this);
   // vec.clear();
    list_BD = list_bd;
    db2 = db;
    db2.open();
    QSqlQuery query;
    ui->comboBox->addItem("Сухогруз");
    ui->comboBox->addItem("Наливной");
    ui->comboBox->addItem("Навалочный");
    ui->comboBox->addItem("Контейнерный");
    ui->comboBox->addItem("Рефрижераторный");
    ui->comboBox->addItem("Авто");
    ui->comboBox->addItem("Газ");

    query.exec("SELECT id FROM ORDER_SHIP");
    while (query.next()){
        ui->comboBox_4->addItem(query.value(0).toString());
    }


        if(list_present.size()>0){
            id_delete = list_present[0].toInt();
            ui->lineEdit->setText(list_present[0]);//
            ui->lineEdit_4->setText(list_present[1]);//
            ui->comboBox->setCurrentText(list_present[2]);//
            ui->lineEdit_3->setText(list_present[3]);//
            ui->comboBox_4->setCurrentText(list_present[4]);//

            ui->pushButton_3->setEnabled(true);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setText("Добавить");
        }

db2.close();
}

CAPASITY_ORDER_Dialog::~CAPASITY_ORDER_Dialog()
{
    delete ui;
}

void CAPASITY_ORDER_Dialog::on_pushButton_clicked()
{
    this->close();
}

void CAPASITY_ORDER_Dialog::on_pushButton_2_clicked()//добавить сохранить
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
            a_query.addBindValue(ui->comboBox->currentText());//
            a_query.addBindValue(ui->lineEdit_3->text());//
            a_query.addBindValue(ui->comboBox_4->currentText());//





    a_query.exec();

    db2.close();
    emit close_dialog();
    this->close();

}

void CAPASITY_ORDER_Dialog::on_pushButton_3_clicked()//delete
{
     db2.open();
     QSqlQuery a_query;
     QString str = "";
     a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
     db2.close();
     emit close_dialog();
     this->close();
}
