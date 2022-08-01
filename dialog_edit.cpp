#include "dialog_edit.h"
#include "ui_dialog_edit.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolTip>

#include <QDebug>

Dialog_edit::Dialog_edit(QStringList list_h,QStringList list_present,QStringList list_bd,QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    vec.clear();
    list_BD = list_bd;
    db2 = db;
    db2.open();
    QSqlQuery query;
//    toltip+="Корабли:\n";
//    query.exec("SELECT id, name FROM SHIP");
//    while (query.next()){
//        toltip+=query.value(0).toString()+" "+query.value(1).toString()+"\n";
//    }
//    toltip+="Порты:\n";
//    query.exec("SELECT id, name FROM PORT");
//    while (query.next()){
//        toltip+=query.value(0).toString()+" "+query.value(1).toString()+"\n";
//    }
//    toltip+="Погода:\n";
//    query.exec("SELECT id, wind,direction_wind, temperature FROM WEATHER");
//    while (query.next()){
//        toltip+=query.value(0).toString()+" "+query.value(1).toString()+" м/с "+query.value(2).toString()+" "+query.value(3).toString()+" C"+"\n";
//    }
    db2.close();

    for (int i = 0;i<list_h.size();i++) {

        QHBoxLayout *layout = new QHBoxLayout();
        QLabel *label = new QLabel(list_h[i]+":");

        QLineEdit * edit_l = new QLineEdit();

        if(list_present.size()>0){
            id_delete = list_present[0].toInt();
            edit_l->setText(list_present[i]);
            ui->pushButton_3->setEnabled(true);
        }
        else{
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setText("Добавить");
        }
        layout->addWidget(label);
        layout->addWidget(edit_l);
        vec.push_back(edit_l);
        layout->setStretch(0,25);
        layout->setStretch(1,75);
        label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Ignored);
        edit_l->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Ignored);


        ui->verticalLayout->addLayout(layout);
    }



}

Dialog_edit::~Dialog_edit()
{
    delete ui;
}

//bool Dialog_edit::eventFilter(QObject *watched, QEvent *event)
//{
//        if(watched == this)
//        {
//            if(event->type() == QEvent::Enter)
//            {
//                QToolTip::showText(this->pos()+QPoint(this->width(),0),toltip);
//                return true;
//            }
//            if(event->type() == QEvent::Leave)
//            {
//                QToolTip::showText(this->pos()+QPoint(this->width(),0),toltip);
//                return true;
//            }
//        }
//        return false;
//}



void Dialog_edit::on_pushButton_clicked()
{
    this->close();
}

void Dialog_edit::on_pushButton_2_clicked()//добавить сохранить
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
        for (int i = 1;i<list_BD.size();i++) {
            a_query.addBindValue(vec.at(i-1)->text());
        }
    a_query.exec();

    db2.close();
    emit close_dialog();
    this->close();

}

void Dialog_edit::on_pushButton_3_clicked()//delete
{
     db2.open();
     QSqlQuery a_query;
     QString str = "";
//     for (int i = 1;i<list_BD.size();i++) {
//         if(i==list_BD.size()-1){
//           str+=list_BD[i]+" = " + vec.at(i-1)->text();
//         }
//         else
//           str+=list_BD[i]+" = " + vec.at(i-1)->text()+" AND ";
//     }

     //qDebug()<<str;
     a_query.exec("DELETE FROM "+list_BD[0]+" WHERE "+list_BD[1]+" = "+QString::number(id_delete)+"");
     db2.close();
     emit close_dialog();
     this->close();
}
