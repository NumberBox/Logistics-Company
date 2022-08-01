#include "otshet_dialog.h"
#include "ui_otshet_dialog.h"

Otshet_Dialog::Otshet_Dialog(QSqlDatabase db,int spin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Otshet_Dialog)
{
    ui->setupUi(this);

    db2 = db;
    db2.open();
    QSqlQuery query;
    ui->label->setText(ui->label->text()+QString::number(spin));

    query.exec("SELECT zak FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin));
    while (query.next()){
        ui->label_2->setText(ui->label_2->text()+"<font color = #545454> "+query.value(0).toString()+" </ font> ");
    }
    query.exec("SELECT ship FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin));
    while (query.next()){
        ui->label_3->setText(ui->label_3->text()+"<font color = #545454> "+query.value(0).toString()+" ("+" </ font> ");
    }
    query.exec("SELECT name FROM SHIP WHERE SHIP.id = (SELECT ship FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin)+")");
    while (query.next()){
        ui->label_3->setText(ui->label_3->text()+"<font color = #545454> "+query.value(0).toString()+")"+" </ font> ");
    }
    query.exec("SELECT name FROM PORT WHERE PORT.id = (SELECT port_departure FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin)+")");
    while (query.next()){
        ui->label_4->setText(ui->label_4->text()+"<font color = #545454> "+" порт "+query.value(0).toString()+" </ font> ");
    }
    query.exec("SELECT name FROM PORT WHERE PORT.id = (SELECT port_purpose FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin)+")");
    while (query.next()){
        ui->label_5->setText(ui->label_5->text()+"<font color = #545454> "+" порт "+query.value(0).toString()+" </ font> ");
    }
    query.exec("SELECT date_departure FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin));
    while (query.next()){
        ui->label_6->setText(ui->label_6->text()+"<font color = #545454> "+query.value(0).toString()+" </ font> ");
    }
    query.exec("SELECT time_depatrure FROM ORDER_SHIP WHERE ORDER_SHIP.id = "+QString::number(spin));
    while (query.next()){
        ui->label_7->setText(ui->label_7->text()+"<font color = #545454> "+query.value(0).toString()+" </ font> ");
    }
    query.exec("SELECT name, type_cargo, quantity FROM CAPASITY_ORDER WHERE CAPASITY_ORDER.order_id = "+QString::number(spin));
    while (query.next()){
        ui->label_9->setText(ui->label_9->text()+"         - "+query.value(0).toString()
                             +" ("+query.value(1).toString()+") - "+query.value(2).toString()+" ");
        if(query.value(1).toString()=="Сухогруз"){
          ui->label_9->setText(ui->label_9->text()+"кг\n");
        }
        if(query.value(1).toString()=="Наливной"){
          ui->label_9->setText(ui->label_9->text()+"тонн/л\n");
        }
        if(query.value(1).toString()=="Навалочный"){
          ui->label_9->setText(ui->label_9->text()+"кг\n");
        }
        if(query.value(1).toString()=="Контейнерный"){
          ui->label_9->setText(ui->label_9->text()+"шт\n");
        }
        if(query.value(1).toString()=="Рефрижераторный"){
          ui->label_9->setText(ui->label_9->text()+"кг\n");
        }
        if(query.value(1).toString()=="Авто"){
          ui->label_9->setText(ui->label_9->text()+"шт\n");
        }
        if(query.value(1).toString()=="Газ"){
          ui->label_9->setText(ui->label_9->text()+"куб/м\n");
        }
    }


    db2.close();

}

Otshet_Dialog::~Otshet_Dialog()
{
    delete ui;
}

void Otshet_Dialog::on_pushButton_clicked()
{
    this->close();
}
