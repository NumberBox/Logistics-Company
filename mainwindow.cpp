#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_edit.h"
#include "raspis.h"
#include "otshet_dialog.h"

#include "port_dialog.h"
#include "schedule_dialog.h"
#include "ship_dialog.h"
#include "capasity_ships_dialog.h"
#include "route_dialog.h"
#include "order_dialog.h"
#include "capasity_order_dialog.h"
#include "weather_dialog.h"
#include "statictics_dialog.h"

#include <QDebug>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QMessageBox>
#include <QFile>
#include <QToolTip>
#include <QHelpEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate date_c;
    date_c = date_c.currentDate();
    QTime time_c;
    time_c = time_c.currentTime();
    ui->label_time->setText(time_c.toString("hh:mm"));
    ui->label_date->setText(date_c.toString("dd/MM/yyyy"));
    timer = new QTimer();
    timer->start(60000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeOut()));
    QAction *helpAction = ui->menubar->addAction("Справка");
    connect(helpAction, SIGNAL(triggered()), this, SLOT(on_menu_2()));
    ui->groupBox_admin->hide();
    ui->groupBox_sotry->hide();
    ui->groupBox_start->hide();

    QFile file("BD_kursash.db3");
        if((!file.exists())||(!file.open(QIODevice::ReadOnly))){
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    file.close();
                    db = QSqlDatabase::addDatabase("QSQLITE");
                    db.setDatabaseName("BD_kursash.db3");
                    db.open();
                    QMessageBox::warning(this,"Warning", "Отсутствует база данных\nДальнейшее использование невозможно");
                    db.close();
            }
        }
        else{
              file.close();
              db = QSqlDatabase::addDatabase("QSQLITE");
              db.setDatabaseName("BD_kursash.db3");
              //db.open();
        }

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
           // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
           // Устанавливаем размер колонок по содержимому
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
           //ui->tableView->resizeColumnsToContents();
            ui->tableView->setMouseTracking(true);

            connect(ui->tableView, SIGNAL(entered(QModelIndex)), this, SLOT(end_end_end_end(QModelIndex)));
            ui->tableView->setStyleSheet("QTableView {"
                                            "color: rgb(0, 0, 0);"
                                            "selection-background-color: rgb(220, 255, 255);"
                                            "background-color: rgb(255, 255, 255);"
                                            "selection-color: rgb(0, 0, 0);"
                                             "}"
                                         "QTableView::item:hover {"
                                             "background-color: #D3F1FC;"
                                         "}"
                                         "QHeaderView {"
                                            "background-color: rgb(0, 230, 245);"
                                            "font-size:14px;"
                                             "}"
                                         "QHeaderView::section:horizontal { "
                                            "color: rgb(0, 0, 0);"
                                            "font-size:14px;"
                                            "font: bold;"
                                            "background-color: rgb(0, 230, 245);"
                                             "}");
            ui->tableWidget->setStyleSheet("QTableView { background-color: rgb(255, 255, 255); }"
                                           "QHeaderView::section:horizontal { "
                                            "color: rgb(0, 0, 0);"
                                          //  "font-size:14px;"
                                            "font: bold;"
                                            "background-color: rgb(0, 230, 245);"
                                             "}");
            ui->tableWidget_2->setStyleSheet("QTableView { background-color: rgb(255, 255, 255); }"
                                            "QHeaderView::section:horizontal { "
                                            "color: rgb(0, 0, 0);"
                                          //  "font-size:14px;"
                                            "font: bold;"
                                            "background-color: rgb(0, 230, 245);"
                                             "}");
            ui->tableWidget_3->setStyleSheet("QTableView { background-color: rgb(255, 255, 255); }"
                                            "QHeaderView::section:horizontal { "
                                            "color: rgb(0, 0, 0);"
                                            //"font-size:14px;"
                                            "font: bold;"
                                            "background-color: rgb(0, 230, 245);"
                                             "}");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->hide();

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Тип груза"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Количество"));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/2);
    ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/2);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableWidget_2->setColumnCount(6);
    ui->tableWidget_2->setHorizontalHeaderItem(0,new QTableWidgetItem("Номер"));
    ui->tableWidget_2->setHorizontalHeaderItem(1,new QTableWidgetItem("Имя"));
    ui->tableWidget_2->setHorizontalHeaderItem(2,new QTableWidgetItem("Вид"));
    ui->tableWidget_2->setHorizontalHeaderItem(3,new QTableWidgetItem("Порт \nотправки"));
    ui->tableWidget_2->setHorizontalHeaderItem(4,new QTableWidgetItem("Порт \nприбытия"));
    ui->tableWidget_2->setHorizontalHeaderItem(5,new QTableWidgetItem("Последний \nпосещенный порт"));
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setColumnWidth(0,ui->tableWidget->width()/5);
    ui->tableWidget_2->setColumnWidth(1,ui->tableWidget->width()/5);
    ui->tableWidget_2->setColumnWidth(2,ui->tableWidget->width()/5);
    ui->tableWidget_2->setColumnWidth(3,ui->tableWidget->width()/5);
    ui->tableWidget_2->setColumnWidth(4,ui->tableWidget->width()/5);
    ui->tableWidget_2->setColumnWidth(5,ui->tableWidget->width()/5);
    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableWidget_3->setColumnCount(4);
    ui->tableWidget_3->setHorizontalHeaderItem(0,new QTableWidgetItem("Номер"));
    ui->tableWidget_3->setHorizontalHeaderItem(1,new QTableWidgetItem("Имя"));
    ui->tableWidget_3->setHorizontalHeaderItem(2,new QTableWidgetItem("Вид"));
    ui->tableWidget_3->setHorizontalHeaderItem(3,new QTableWidgetItem("Порт стоянки"));
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_3->setColumnWidth(0,ui->tableWidget->width()/4);
    ui->tableWidget_3->setColumnWidth(1,ui->tableWidget->width()/4);
    ui->tableWidget_3->setColumnWidth(2,ui->tableWidget->width()/4);
    ui->tableWidget_3->setColumnWidth(3,ui->tableWidget->width()/4);
    ui->tableWidget_3->verticalHeader()->hide();
    ui->tableWidget_3->setSelectionMode(QAbstractItemView::NoSelection);

    db.open();
    QSqlQuery query;
    int k = 1;
    QVector<QString> zap;
    query.exec("SELECT id FROM SHIP");    
    while (query.next()){
        zap.push_back(query.value(0).toString());
    }
    for (int i = 0;i<zap.size();i++) {
        if(zap.at(i).toInt()==k){
            k++;
            ui->comboBox_2->addItem(zap.at(i));
            i=-1;
        }
    }
    query.exec("SELECT id, name FROM PORT");
    zap.clear();
    while (query.next()){
        zap.push_back(query.value(0).toString());
        zap.push_back(query.value(1).toString());
    }
    k = 1;
    for (int i = 0;i<zap.size();i+=2) {
        if(zap.at(i).toInt()==k){
            k++;
            ui->comboBox_3->addItem(zap.at(i+1));
            ui->comboBox_4->addItem(zap.at(i+1));
            i=-2;
        }

    }


    query.exec("SELECT id FROM SHIP");
    while (query.next()){
        ship_tooltop.push_back(query.value(0).toString());
    }
    ship_tooltop.push_back(QString::number(0));
    query.exec("SELECT id, name FROM SHIP");
    while (query.next()){
        ship_tooltop[query.value(0).toInt()] = query.value(1).toString();
    }

    query.exec("SELECT id FROM PORT");
    while (query.next()){
        port_tooltop.push_back(query.value(0).toString());
    }
    port_tooltop.push_back(QString::number(0));
    query.exec("SELECT id, name FROM PORT");
    while (query.next()){
        port_tooltop[query.value(0).toInt()] = query.value(1).toString();
    }
    port_tooltop[0]="0";

    query.exec("SELECT id FROM WEATHER");
    while (query.next()){
        weather_tooltip.push_back(query.value(0).toString());
    }
    weather_tooltip.push_back(QString::number(0));
    query.exec("SELECT id, wind,direction_wind, temperature FROM WEATHER");
    while (query.next()){
        weather_tooltip[query.value(0).toInt()] = query.value(1).toString()+" м/с "+query.value(2).toString()+" "+query.value(3).toString()+" C";
    }



    db.close();



ui->pushButton_18->hide();
ui->lineEdit->setInputMask("00000");
ui->lineEdit->setText("10");
ui->lineEdit_4->setText(ui->label_time->text());
ui->lineEdit_5->setText(ui->label_date->text());


//QDate da1;
//QTime ti1;
//int d =0;
//da1 = QDate::fromString("21/01/2020","dd/MM/yyyy");
//ti1 = QTime::fromString("06:00","hh:mm");

//QDate da2;
//QTime ti2;
//da2 = QDate::fromString("22/01/2020","dd/MM/yyyy");
//ti2 = QTime::fromString("07:00","hh:mm");
//d = da1.daysTo(da2);

//qDebug()<<d;



}
void MainWindow::slotEditRecord(QModelIndex index)
{

    QStringList list_present;
    for(int i =0;i<list.size();i++){
        list_present<<ui->tableView->model()->data(ui->tableView->model()->index(index.row(),i)).toString();
    }
    if(list_bd.at(0)=="PORT"){
         PORT_Dialog *edit = new PORT_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="SCHEDULE"){
         SCHEDULE_Dialog *edit = new SCHEDULE_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="SHIP"){
         SHIP_Dialog *edit = new SHIP_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="CAPASITY_SHIPS"){
         CAPASITY_SHIPS_Dialog *edit = new CAPASITY_SHIPS_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="ROUTE"){
         ROUTE_Dialog *edit = new ROUTE_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="ORDER_SHIP"){
         ORDER_Dialog *edit = new ORDER_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="CAPASITY_ORDER"){
         CAPASITY_ORDER_Dialog *edit = new CAPASITY_ORDER_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="WEATHER"){
         WEATHER_Dialog *edit = new WEATHER_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="STATICTICS"){
         STATICTICS_Dialog *edit = new STATICTICS_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="EMPLOYEE"){
         Dialog_edit *edit = new Dialog_edit(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Редактирование");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }



}

void MainWindow::update_model()
{
    db.open();
    model->select();
    db.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeOut()
{
    QDate date;
    date = QDate::fromString(ui->label_date->text(),"dd/MM/yyyy");
    QTime time;
   // time = QTime::fromString(ui->label_time->text(),"hh:mm");
    //time = time.addSecs(21600);
    time = time.currentTime();
    ui->label_time->setText(time.toString("hh:mm"));
    if(time == QTime(00,00)){
        date = date.addDays(1);
        ui->label_date->setText(date.toString("dd/MM/yyyy"));
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    QStringList list_present;
    if(list_bd.at(0)=="PORT"){
         PORT_Dialog *edit = new PORT_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="SCHEDULE"){
         SCHEDULE_Dialog *edit = new SCHEDULE_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="SHIP"){
         SHIP_Dialog *edit = new SHIP_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="CAPASITY_SHIPS"){
         CAPASITY_SHIPS_Dialog *edit = new CAPASITY_SHIPS_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="ROUTE"){
         ROUTE_Dialog *edit = new ROUTE_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="ORDER_SHIP"){

             this->on_pushButton_18_clicked();

         ORDER_Dialog *edit = new ORDER_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();

    }
    if(list_bd.at(0)=="CAPASITY_ORDER"){
         CAPASITY_ORDER_Dialog *edit = new CAPASITY_ORDER_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="WEATHER"){
         WEATHER_Dialog *edit = new WEATHER_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="STATICTICS"){
         STATICTICS_Dialog *edit = new STATICTICS_Dialog(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
    if(list_bd.at(0)=="EMPLOYEE"){
         Dialog_edit *edit = new Dialog_edit(list,list_present,list_bd,db,this);
         edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
         edit->setWindowTitle("Добавление");
         connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
         edit->exec();
    }
}



void MainWindow::on_pushButton_4_clicked()//PORT
{
    this->select_buttons();
    table_number_toltip = 4;
    ui->pushButton_4->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("PORT");
    list<<"Предыдущий порт"<<"Id"<<"Название"<<"Следуюющий порт"<<"Километраж (тек/след)"<<"Километраж на заход"<<"Погода"<<"Ледокол";
    list_bd<<"PORT"<<"previous"<<"id"<<"name"<<"next"<<"km_from_to"<<"km_port"<<"weather"<<"icebreaker";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::on_pushButton_clicked() //SCHEDULE
{
    this->select_buttons();
    table_number_toltip = 1;
    ui->pushButton->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("SCHEDULE");
    list<<"Id"<<"Судно"<<"Порт отправки"<<"Порт прибытия"<<"Дата отправления"<<"Время отправления"<<"Дата прибытия"<<"Время прибытия";
    list_bd<<"SCHEDULE"<<"id"<<"ship"<<"port_departures"<<"port_purposes"<<"date_departures"<<"time_departures"<<"date_purposes"<<"time_purposes";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::end_end_end_end(QModelIndex item)
{



   QToolTip::hideText();
   QPoint a = QCursor::pos();
   if(table_number_toltip==1){
       if(item.column()==1){
           QString s = ship_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
       if(item.column()==2||item.column()==3){
           QString s = port_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
   }
   if(table_number_toltip==2){
       if(item.column()==4){
           QString s = port_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
   }
   if(table_number_toltip==3){
       if(item.column()==3){
           QString s = ship_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
   }
   if(table_number_toltip==4){
       if(item.column()==0||item.column()==1||item.column()==3){
           if(!(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt()==-1||
               ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt()==21)){
            QString s = port_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
            QToolTip::showText(a,s);
           }
       }
       if(item.column()==6){
           QString s = weather_tooltip.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
   }
   if(table_number_toltip==5){
       if(item.column()==4||item.column()==3){
           QString s = port_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
       if(item.column()==1){
           QString s = ship_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
   }
   if(table_number_toltip==6){
       if(item.column()==3||item.column()==4){
           QString s = port_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
       if(item.column()==1){
           QString s = ship_tooltop.at(ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toInt());
           QToolTip::showText(a,s);
       }
   }





    //QToolTip *tip = new QToolTip()

   // QString s = ui->tableView->model()->data(ui->tableView->model()->index(item.row(),item.column())).toString();


}

void MainWindow::on_pushButton_2_clicked() //SHIP
{
    this->select_buttons();
    table_number_toltip = 2;
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("SHIP");
    list<<"Id"<<"Название"<<"Вид"<<"Скорость"<<"Расположение (порт)"<<"Маршрут";
    list_bd<<"SHIP"<<"id"<<"name"<<"type_ship"<<"speed"<<"location"<<"route";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}
void MainWindow::on_pushButton_22_clicked() //Employee
{
    this->select_buttons();
    table_number_toltip = 10;
    ui->pushButton_22->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("EMPLOYEE");
    list<<"Id"<<"Имя"<<"Должность"<<"Логин"<<"Пароль";
    list_bd<<"EMPLOYEE"<<"id"<<"name"<<"position"<<"login"<<"password";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}


void MainWindow::on_pushButton_3_clicked() // CAPASITY_SHIPS
{
    this->select_buttons();
    table_number_toltip = 3;
    ui->pushButton_3->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("CAPASITY_SHIPS");
    list<<"Id"<<"Тип груза"<<"Количество"<<"Судно";
    list_bd<<"CAPASITY_SHIPS"<<"id"<<"type"<<"quantity"<<"ship";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::on_pushButton_5_clicked() //ROUTE
{
    this->select_buttons();
    table_number_toltip = 5;
    ui->pushButton_5->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("ROUTE");
    list<<"Id"<<"Судно"<<"Направление (З/В)"<<"Текущий порт"<<"Следующий порт"<<"Дата прибытия в\nследующий порт"<<"Время прибытия в\nследующий порт";
    list_bd<<"ROUTE"<<"id"<<"ship"<<"west_east"<<"current_port"<<"next_port"<<"time_from_to"<<"current_time";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::on_pushButton_6_clicked()//ORDER
{
    this->select_buttons();
    table_number_toltip = 6;
    ui->pushButton_6->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("ORDER_SHIP");
    list<<"Id"<<"Судно"<<"Заказчик"<<"Порт отправки"<<"Порт назначения"<<"Дата отправления"<<"Время отправления";
    list_bd<<"ORDER_SHIP"<<"id"<<"ship"<<"zak"<<"port_departure"<<"port_purpose"<<"date_departure"<<"time_depatrure";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::on_pushButton_7_clicked()// CAPASITY_ORDER
{
    this->select_buttons();
    table_number_toltip = 7;
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("CAPASITY_ORDER");
    list<<"Id"<<"Название"<<"Тип груза"<<"Количество"<<"Заказ";
    list_bd<<"CAPASITY_ORDER"<<"id"<<"name"<<"type_cargo"<<"quantity"<<"order_id";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::on_pushButton_8_clicked() // WEATHER
{
    this->select_buttons();
    table_number_toltip = 8;
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("WEATHER");
    list<<"Id"<<"Ветер м/с"<<"Направление ветра"<<"Температура";
    list_bd<<"WEATHER"<<"id"<<"wind"<<"direction_wind"<<"temperature";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}
void MainWindow::on_pushButton_17_clicked()//STATICTICS
{
    this->select_buttons();
    table_number_toltip = 9;
    ui->pushButton_17->setStyleSheet("QPushButton { background-color: rgb(220, 255, 255); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(213, 247, 247);} QPushButton::pressed { border: 3px solid #000000;}");
    list.clear();
    list_bd.clear();
    db.open();
    QSqlQuery query;
    model = new QSqlTableModel();
    model->setTable("STATICTICS");
    list<<"Id"<<"Расписание"<<"Дата прибытия"<<"Время прибытия"<<"Погрешность в часах";
    list_bd<<"STATICTICS"<<"id"<<"schedule"<<"date_arrivals"<<"time_arrivals"<<"time_error";
    for(int i = 0; i < model->columnCount(); i++){
        model->setHeaderData(i,Qt::Horizontal,list[i]);
    }
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();
    db.close();
}

void MainWindow::on_pushButton_12_clicked()//добавить сотрудник груз
{
    QString col = ui->lineEdit->text();
    QString type = ui->comboBox->currentText();
    QString type1 = "";
    for (int i = 0;i<type.length();i++) {
        if(type[i]!=" ")
            type1+=type[i];
        else
            break;
    }
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(type1));
    ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(col));

}

void MainWindow::on_pushButton_11_clicked()//очистить таблицу грузов
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_10_clicked()//найти подходящее судно
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_3->clearContents();
    ui->tableWidget_3->setRowCount(0);

    QVector<QVector<QString>> vec;
            db.open();
            QSqlQuery query;
            query.exec("SELECT SHIP.id, CAPASITY_SHIPS.type,CAPASITY_SHIPS.quantity FROM SHIP INNER JOIN CAPASITY_SHIPS on SHIP.id = CAPASITY_SHIPS.ship");
            while (query.next()){
                QVector<QString> vek1;
                vek1.push_back(query.value(0).toString());
                vek1.push_back(query.value(1).toString());
                vek1.push_back(query.value(2).toString());
                vec.push_back(vek1);
            }

            query.exec("SELECT SHIP.id, CAPASITY_ORDER.type_cargo, CAPASITY_ORDER.quantity FROM SHIP INNER JOIN ORDER_SHIP on SHIP.id = ORDER_SHIP.ship INNER JOIN CAPASITY_ORDER on ORDER_SHIP.id = CAPASITY_ORDER.order_id");
            while (query.next()){

                QString id = query.value(0).toString();
                QString type =  query.value(1).toString();
                QString kol =  query.value(2).toString();
                for(int i = 0; i<vec.size();i++){
                   if((vec.at(i).at(0)==id)&&(vec.at(i).at(1)==type)){
                       int a = vec.at(i).at(2).toInt()-kol.toInt();
                       vec[i].pop_back();
                       vec[i].push_back(QString::number(a));

                   }

                }
            }

            QVector<QString> vek_end;
            for (int x = 0;x<ui->tableWidget->rowCount();x++) {

                for (int i = 0; i<vec.size();i++) {
                    if((ui->tableWidget->item(x,0)->text()==vec.at(i).at(1))&&(ui->tableWidget->item(x,1)->text().toInt()<=vec.at(i).at(2).toInt())){
                         vek_end.push_back(vec.at(i).at(0));


                    }
                }
            }

            QVector<QString> vek_end1;
            for (int i = 0; i<vek_end.size();i++) {
                int chet = 0;
                for (int j = 0; j<vek_end.size();j++){
                    if(vek_end.at(i)==vek_end.at(j)){
                        chet++;
                    }
                }
                if(chet == ui->tableWidget->rowCount()){
                    vek_end1.push_back(vek_end.at(i));

                }

            }

            for (int i = 0; i<vek_end1.size()-1;i++) {
                for (int j = i+1; j<vek_end1.size();j++){
                    if(vek_end1[i]==vek_end1[j]){
                        vek_end1[j]="-1";
                    }
                }
            }
            vek_end.clear();
                for (int i = 0; i<vek_end1.size();i++){
                   if(vek_end1.at(i)!="-1"){
                       vek_end.push_back(vek_end1.at(i));
                   }
                }

            QString str = "SELECT SHIP.id,SHIP.name,SHIP.type_ship,PORT.name FROM SHIP INNER JOIN PORT on SHIP.location = PORT.id WHERE SHIP.route = 0 AND SHIP.id in(";
            for (int i = 0; i<vek_end.size();i++){
                if(i==vek_end.size()-1){
                    str+=vek_end.at(i)+")";
                }
                else
                    str+=vek_end.at(i)+",";
            }

            query.exec(str);
            while (query.next()){
                ui->tableWidget_3->setRowCount(ui->tableWidget_3->rowCount()+1);
                ui->tableWidget_3->setItem(0+ui->tableWidget_3->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget_3->setItem(0+ui->tableWidget_3->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget_3->setItem(0+ui->tableWidget_3->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));               
                ui->tableWidget_3->setItem(0+ui->tableWidget_3->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            }

            QString str2 = "SELECT SHIP.id,SHIP.name,SHIP.type_ship,SCHEDULE.port_departures,SCHEDULE.port_purposes,PORT.name FROM SHIP INNER JOIN SCHEDULE on SHIP.id = SCHEDULE.ship INNER JOIN ROUTE on SHIP.route = ROUTE.id INNER JOIN PORT on ROUTE.current_port = PORT.id WHERE SHIP.route != 0 AND SHIP.id in(";
            for (int i = 0; i<vek_end.size();i++){
                if(i==vek_end.size()-1){
                    str2+=vek_end.at(i)+")";
                }
                else
                    str2+=vek_end.at(i)+",";
            }

            query.exec(str2);
            while (query.next()){
                ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
                ui->tableWidget_2->setItem(0+ui->tableWidget_2->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget_2->setItem(0+ui->tableWidget_2->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget_2->setItem(0+ui->tableWidget_2->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget_2->setItem(0+ui->tableWidget_2->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tableWidget_2->setItem(0+ui->tableWidget_2->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tableWidget_2->setItem(0+ui->tableWidget_2->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            }

            QString str2_2 = "SELECT PORT.name FROM SHIP INNER JOIN SCHEDULE on SHIP.id = SCHEDULE.ship INNER JOIN ROUTE on SHIP.route = ROUTE.id INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id WHERE SHIP.route != 0 AND SHIP.id in(";
            for (int i = 0; i<vek_end.size();i++){
                if(i==vek_end.size()-1){
                    str2_2+=vek_end.at(i)+")";
                }
                else
                    str2_2+=vek_end.at(i)+",";
            }

            query.exec(str2_2);
            int row = 0;
            while (query.next()){
                ui->tableWidget_2->setItem(row,4,new QTableWidgetItem(query.value(0).toString()));
                row++;
            }
            QString str2_3 = "SELECT PORT.name FROM SHIP INNER JOIN SCHEDULE on SHIP.id = SCHEDULE.ship INNER JOIN ROUTE on SHIP.route = ROUTE.id INNER JOIN PORT on SCHEDULE.port_departures = PORT.id WHERE SHIP.route != 0 AND SHIP.id in(";
            for (int i = 0; i<vek_end.size();i++){
                if(i==vek_end.size()-1){
                    str2_3+=vek_end.at(i)+")";
                }
                else
                    str2_3+=vek_end.at(i)+",";
            }

            query.exec(str2_3);
            row = 0;
            while (query.next()){
                ui->tableWidget_2->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
                row++;
            }

            db.close();

}

void MainWindow::on_pushButton_13_clicked() // расчет времени
{
    ui->label_15->setAlignment(Qt::AlignCenter);
    ui->label_16->setAlignment(Qt::AlignCenter);
    db.open();
    QVector<QString> vec;
    QSqlQuery query;
    QString str ="SELECT ORDER_SHIP.port_departure, ORDER_SHIP.port_purpose FROM ORDER_SHIP WHERE ORDER_SHIP.ship = ";
    str+= ui->comboBox_2->currentText();

    query.exec(str);
    while (query.next()){
        vec.push_back(query.value(0).toString());
        vec.push_back(query.value(1).toString());
    }

    for (int i = 0; i<vec.size()-1;i++) {
        for (int j = i+1; j<vec.size();j++){
            if(vec[i]==vec[j]){
                vec[j]="-1";
            }
        }
    }
    QVector<QString> vek_end;
    for (int i = 0; i<vec.size();i++){
       if(vec.at(i)!="-1"){
           vek_end.push_back(vec.at(i));
       }
    }

    int first = 0;
    query.exec("SELECT PORT.id FROM PORT WHERE PORT.name = '"+ui->comboBox_4->currentText()+"'");
    while (query.next()){
        first = query.value(0).toInt();
    }
    int last = 0;
    query.exec("SELECT PORT.id FROM PORT WHERE PORT.name = '"+ui->comboBox_3->currentText()+"'");
    while (query.next()){
        last = query.value(0).toInt();
    }
    int speed = 0;
    query.exec("SELECT SHIP.speed FROM SHIP WHERE SHIP.id = "+ui->comboBox_2->currentText());
    while (query.next()){
        speed = query.value(0).toInt();
    }
    double speed1 = speed*1.852;
    int km = 0;
    bool check =false;
    for (int i = 0; i<vek_end.size();i++){
       if(vek_end.at(i).toInt()==last){
           query.exec("SELECT PORT.km_port FROM PORT WHERE PORT.id = "+vek_end.at(i));
           while (query.next()){
               km += (query.value(0).toInt()/2);
           }
           check = true;
       }
       else{
           query.exec("SELECT PORT.km_port FROM PORT WHERE PORT.id = "+vek_end.at(i));
           while (query.next()){
               km += query.value(0).toInt();
           }
       }
    }
    int km_watcher = km;
    if(last>=first){
        for (int i = first;i<last;i++) {
            query.exec("SELECT PORT.km_from_to FROM PORT WHERE PORT.id = "+QString::number(i));
            while (query.next()){
                km += query.value(0).toInt();
            }

        }
    }
    else{
        for (int i = first-1;i>=last;i--) {
            query.exec("SELECT PORT.km_from_to FROM PORT WHERE PORT.id = "+QString::number(i));
            while (query.next()){
                km += query.value(0).toInt();
            }
        }
    }

    bool shtorm = false;
    bool cold = false;
    QVector<QString> shtorm_vec;
    QVector<QString> cold_vec;
    double time_watcher = 0;
    double speed_watcher = 0;
    if(last>=first){
        for (int i = first;i<last;i++) {
            query.exec("SELECT PORT.km_from_to FROM PORT WHERE PORT.id = "+QString::number(i));
            int km_1;
            while (query.next()){
              km_1 = query.value(0).toInt();
            }
            query.exec("SELECT WEATHER.wind,WEATHER.direction_wind FROM PORT INNER JOIN WEATHER on PORT.weather = WEATHER.id WHERE PORT.id = "+QString::number(i));
            while (query.next()){
                if(query.value(0).toInt()>=15){
                    shtorm_vec.push_back(QString::number(i));
                    shtorm = true;
                }
                if(query.value(1).toString()=="В"){
                    speed_watcher = speed1+(3.6*query.value(0).toInt());
                    //qDebug()<<speed1;
                   // qDebug()<<speed_watcher;
                }
                else{
                    speed_watcher = speed1-(3.6*query.value(0).toInt());
                }
            }

            //
            time_watcher += km_1/speed_watcher;

            query.exec("SELECT PORT.icebreaker FROM PORT WHERE PORT.id = "+QString::number(i));
            while (query.next()){
              if(query.value(0).toInt()==1){
                  cold_vec.push_back(QString::number(i));
                  cold = true;
              }
            }

        }
    }
    else{
        for (int i = first-1;i>=last;i--) {
            query.exec("SELECT PORT.km_from_to FROM PORT WHERE PORT.id = "+QString::number(i));
            int km_1;
            while (query.next()){
              km_1 = query.value(0).toInt();
            }
            query.exec("SELECT WEATHER.wind,WEATHER.direction_wind FROM PORT INNER JOIN WEATHER on PORT.weather = WEATHER.id WHERE PORT.id = "+QString::number(i));
            while (query.next()){
                if(query.value(0).toInt()>=15){
                    shtorm_vec.push_back(QString::number(i));
                    shtorm = true;
                }
                if(query.value(1).toString()=="З"){
                    speed_watcher = speed1+(3.6*query.value(0).toInt());
                }
                else{
                    speed_watcher = speed1-(3.6*query.value(0).toInt());
                }
            }

            //
            time_watcher += km_1/speed_watcher;
            query.exec("SELECT PORT.icebreaker FROM PORT WHERE PORT.id = "+QString::number(i));
            while (query.next()){
              if(query.value(0).toInt()==1){
                  cold_vec.push_back(QString::number(i));
                  cold = true;
              }
            }

        }
    }

    if(!check){
        query.exec("SELECT PORT.km_port FROM PORT WHERE PORT.id = "+QString::number(last));
        while (query.next()){
            km += (query.value(0).toInt()/2);
            km_watcher+=(query.value(0).toInt()/2);
        }
    }
    time_watcher+=km_watcher/speed1;



    int hours = km/speed1;
    QString s = ui->lineEdit_4->text();
    QString t = "";
    t+=s[0];
    t+=s[1];
    hours+=t.toInt();
    time_watcher+=t.toInt();
   // qDebug()<<hours;
  //  qDebug()<< time_watcher;
    int day1 = time_watcher/24;
    int time11 = (int)time_watcher%24;
    int day = hours/24;
    int time = hours%24;
    QDate date;
    date = QDate::fromString(ui->lineEdit_5->text(),"dd/MM/yyyy");
    QTime time1;
    time1 = QTime::fromString("00:00","hh:mm");
    time1 = time1.addSecs(time*60*60);
    ui->label_18->setText(time1.toString("hh:mm"));
    date = date.addDays(day);
    ui->label_17->setText(date.toString("dd/MM/yyyy"));

    date = QDate::fromString(ui->lineEdit_5->text(),"dd/MM/yyyy");
    time1 = QTime::fromString("00:00","hh:mm");
    time1 = time1.addSecs(time11*60*60);

    ui->label_16->setText(time1.toString("hh:mm"));
    date = date.addDays(day1);
    ui->label_15->setText(date.toString("dd/MM/yyyy"));
    if(shtorm||cold){
        ui->label_15->setAlignment(Qt::AlignRight);
        ui->label_16->setAlignment(Qt::AlignLeft);
        ui->label_15->setText("Расчет не возможен из-за\nпредупреждения или по причине");
        ui->label_16->setText("наличия на пути штормового\nнепроходимости пути из-за льда");
        QString str1 = "Штормовое предупреждение: ";
        if(shtorm_vec.size()==0){
           str1+="\n";
        }
        for (int i = 0;i<shtorm_vec.size();i++) {
            QSqlQuery query;
            query.exec("SELECT PORT.name FROM PORT WHERE PORT.id = "+shtorm_vec.at(i));
            while (query.next()){
                str1+=query.value(0).toString()+" - ";
            }
            query.exec("SELECT PORT.name FROM PORT WHERE PORT.id = "+QString::number(shtorm_vec.at(i).toInt()+1));
            while (query.next()){
                str1+=query.value(0).toString()+"\n                                             ";
            }
        }
        str1+="\nНеобходимость ледокола:       ";
        for (int i = 0;i<cold_vec.size();i++) {
            QSqlQuery query;
            query.exec("SELECT PORT.name FROM PORT WHERE PORT.id = "+cold_vec.at(i));
            while (query.next()){
                str1+=query.value(0).toString()+" - ";
            }
            query.exec("SELECT PORT.name FROM PORT WHERE PORT.id = "+QString::number(cold_vec.at(i).toInt()+1));
            while (query.next()){
                str1+=query.value(0).toString()+"\n                                             ";
            }
        }





        ui->label_22->setText(str1);


    }

    db.close();



}

void MainWindow::on_pushButton_18_clicked()
{
    if(ui->groupBox_admin->isVisible()){
        ui->groupBox_admin->hide();
        ui->groupBox_sotry->show();
        ui->pushButton_18->setText("|>");
    }
    else{
        ui->groupBox_admin->show();
        ui->groupBox_sotry->hide();
        ui->pushButton_18->setText("<|");
    }
    if(ui->label_20->text()=="Менеджер"){
        ui->pushButton_18->hide();
        ui->pushButton_18->setText("<|");
        ui->label_21->show();
    }

}

void MainWindow::select_buttons()
{
    ui->pushButton->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");

    ui->pushButton_2->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_3->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_4->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_5->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_6->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_17->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
    ui->pushButton_22->setStyleSheet("QPushButton { background-color: rgb(0, 230, 245); border: 1px solid #000000;} QPushButton::hover { background-color: rgb(0, 243, 255);} QPushButton::pressed { border: 3px solid #000000;}");
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->label_15->setText("00/00/0000");
    ui->label_17->setText("00/00/0000");
    ui->label_16->setText("00:00");
    ui->label_18->setText("00:00");
    ui->label_15->setAlignment(Qt::AlignCenter);
    ui->label_16->setAlignment(Qt::AlignCenter);
    ui->label_22->setText("");
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}



void MainWindow::on_pushButton_16_clicked()// открыть расписание
{
    Raspis *edit = new Raspis(db,1,this);
    edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    edit->setWindowTitle("Расписание");
   // connect(edit,SIGNAL(close_dialog()),this,SLOT(update_model()));
    edit->exec();
}

void MainWindow::on_pushButton_20_clicked() //прейти к грузам
{
    if(ui->label_20->text()=="Администратор"){
        ui->groupBox_admin->show();
        ui->groupBox_sotry->hide();
        ui->pushButton_18->setText("<|");
        this->on_pushButton_7_clicked();
        return;
    }
    ui->pushButton_18->show();
    ui->label_21->hide();
    this->on_pushButton_7_clicked();
    ui->groupBox_sotry->hide();
    ui->groupBox_admin->show();
    ui->gridLayout_2->setColumnStretch(0,0);
    ui->gridLayout_2->setColumnStretch(1,100);

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_17->hide();
    ui->pushButton_19->hide();
    ui->pushButton_18->setText("<|");
    ui->pushButton_22->hide();
}

void MainWindow::on_pushButton_21_clicked() //перейти к заказам
{
    if(ui->label_20->text()=="Администратор"){
        ui->groupBox_admin->show();
        ui->groupBox_sotry->hide();
        ui->pushButton_18->setText("<|");
        this->on_pushButton_6_clicked();
        return;
    }

    ui->pushButton_18->show();
    ui->label_21->hide();
    this->on_pushButton_6_clicked();
    ui->groupBox_sotry->hide();
    ui->groupBox_admin->show();
    ui->gridLayout_2->setColumnStretch(0,0);
    ui->gridLayout_2->setColumnStretch(1,100);

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_17->hide();
    ui->pushButton_19->hide();
    ui->pushButton_18->setText("<|");
    ui->pushButton_22->hide();
}

void MainWindow::on_pushButton_19_clicked()//обновить статистику
{
    this->on_pushButton_17_clicked();
    int a = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->model()->rowCount()-1,0)).toInt();
    db.open();


    QSqlQuery query;
    QVector<QString> shedule;
    QVector<QString> date_s;
    QVector<QString> time_s;
    QVector<QString> error;
    QDate date_cur;
    QTime time_cur;
    QDate date_sche;
    QTime time_sche;
    int days = 0;

    query.exec("SELECT SCHEDULE.id, ROUTE.time_from_to, ROUTE.current_time, SCHEDULE.date_purposes,SCHEDULE.time_purposes from ROUTE INNER join SCHEDULE on ROUTE.ship = SCHEDULE.ship WHERE ROUTE.next_port = SCHEDULE.port_purposes");
    while (query.next()){
        shedule.push_back(query.value(0).toString());
        date_s.push_back(query.value(1).toString());
        time_s.push_back(query.value(2).toString());
        date_cur = QDate::fromString(query.value(1).toString(),"dd/MM/yyyy");
        time_cur = QTime::fromString(query.value(2).toString(),"hh:mm");
        date_sche = QDate::fromString(query.value(3).toString(),"dd/MM/yyyy");
        time_sche = QTime::fromString(query.value(4).toString(),"hh:mm");
        days = date_cur.daysTo(date_sche);
        if(days<0){
           // qDebug()<<days;
            days = days*-24;
         //   qDebug()<<days;
            days = days-time_sche.hour();
            days = days+time_cur.hour();
        }
        else{
            days = days*24;
            days = days-time_cur.hour();
            days = days+time_sche.hour();

        }
        if(days<0){
            days = days*-1;
        }
        error.push_back(QString::number(days));
    }




   // date = QDate::fromString(,"dd/MM/yyyy");

    //time = QTime::fromString(,"hh:mm");


    for(int i = 0; i<shedule.size();i++){
        QSqlQuery a_query;
        a_query.prepare("INSERT INTO STATICTICS (id, schedule, date_arrivals, time_arrivals, time_error) VALUES (?, ?, ?, ?, ?)");
        a_query.addBindValue(++a);
        a_query.addBindValue(shedule.at(i));
        a_query.addBindValue(date_s.at(i));
        a_query.addBindValue(time_s.at(i));
        a_query.addBindValue(error.at(i));
        a_query.exec();
    }




    db.close();

    this->update_model();
}

void MainWindow::on_action_2_triggered()//выход
{
    QApplication::quit();
}

void MainWindow::on_action_triggered()//смена пользователя
{
    ui->groupBox_admin->hide();
    ui->groupBox_sotry->hide();
    ui->groupBox_start->show();
    ui->groupBox->hide();
    ui->pushButton_18->hide();
    //ui->label_21->hide();
  //  this->on_pushButton_6_clicked();
    ui->gridLayout_2->setColumnStretch(0,10);
    ui->gridLayout_2->setColumnStretch(1,90);
    this->on_pushButton_14_clicked();
    this->on_pushButton_11_clicked();
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_3->clearContents();
    ui->tableWidget_3->setRowCount(0);
    ui->lineEdit->setText("10");
    ui->lineEdit_4->setText(ui->label_time->text());
    ui->lineEdit_5->setText(ui->label_date->text());

    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_17->show();
    ui->pushButton_19->show();
    ui->pushButton_22->show();
    ui->label_20->setText("");
    ui->label_22->setText("");
    ui->comboBox->setCurrentText(ui->comboBox->itemText(0));
    ui->comboBox_2->setCurrentText(ui->comboBox_2->itemText(0));
    ui->comboBox_3->setCurrentText(ui->comboBox_3->itemText(0));
    ui->comboBox_4->setCurrentText(ui->comboBox_4->itemText(0));
    ui->pushButton_22->setEnabled(true);
    ui->pushButton_20->setEnabled(true);
    ui->pushButton_21->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
}

void MainWindow::on_menu_2()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setStyleSheet("QMessageBox {"
                          "background-color: rgb(187, 245, 243);"
                           "}"
                          "QMessageBox QPushButton {"
                           "background-color: rgb(0, 230, 245);"
                           "font:bold;"
                           "border: 1px solid #000000;"
                            "}"
                          "QMessageBox QPushButton:pressed {"
                           "border: 3px solid #000000;"
                            "}"
                          "QMessageBox QPushButton:hover {"
                           "background-color: rgb(0, 243, 255);"
                            "}");
     msgBox->setWindowTitle("Справка");
     msgBox->setText("Курсовой проект\nТема: Разработка информационного обеспечения для морской логистической компании");
     msgBox->setInformativeText("Cтудент группы 484 Сусленников Мелетий Феликсович 2020 год");
     msgBox->setIcon(QMessageBox::Information);
     QPushButton *edit = msgBox->addButton("Закрыть", QMessageBox::ActionRole);
     edit->setMinimumWidth(110);
     edit->setMinimumHeight(40);
     msgBox->setDefaultButton(edit);
     if(msgBox->clickedButton()== edit){
         msgBox->close();
     }
     msgBox->exec();



}


void MainWindow::on_pushButton_23_clicked()//войти по логину
{
    db.open();
    QSqlQuery query;
    QVector<QString> employ;
    query.exec("SELECT position, login, password FROM EMPLOYEE");
    while (query.next()){
        employ.push_back(query.value(0).toString());
        employ.push_back(query.value(1).toString());
        employ.push_back(query.value(2).toString());
    }
    db.close();

    for (int i = 1;i<employ.size();i+=3) {
        if((ui->lineEdit_2->text()==employ.at(i))&&(ui->lineEdit_3->text()==employ.at(i+1))){
            if(employ.at(i-1)=="Администратор"){
                    ui->label_20->setText("Администратор");
                    ui->label_21->hide();
                    ui->groupBox_start->hide();
                    ui->groupBox_admin->show();
                    ui->pushButton_18->show();
                    ui->pushButton_18->setText("<|");
                    this->on_pushButton_clicked();
            }
            if(employ.at(i-1)=="Менеджер"){

                    ui->label_20->setText("Менеджер");
                    ui->label_21->show();
                    ui->groupBox_start->hide();
                    ui->groupBox_sotry->show();
            }
            if(employ.at(i-1)=="Оператор"){

                    ui->label_20->setText("Оператор");
                    ui->label_21->hide();
                    ui->groupBox_start->hide();
                    ui->groupBox_admin->show();
                    ui->pushButton_18->show();
                    ui->pushButton_18->setText("<|");
                    this->on_pushButton_clicked();
                    ui->pushButton_22->setEnabled(false);
                    ui->pushButton_20->setEnabled(false);
                    ui->pushButton_21->setEnabled(false);
                    ui->pushButton_6->setEnabled(false);
                    ui->pushButton_7->setEnabled(false);
            }

        }

    }


    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

}

void MainWindow::on_pushButton_25_clicked()
{
    ui->groupBox->hide();
    ui->groupBox_start->show();
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->groupBox->show();
    ui->groupBox_start->hide();
    ui->groupBox_admin->hide();
    ui->groupBox_sotry->hide();
}

void MainWindow::on_pushButton_28_clicked()//погода главный экран
{
    Raspis *edit = new Raspis(db,2,this);
    edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    edit->setWindowTitle("Погода на пути");
    edit->exec();
}

void MainWindow::on_pushButton_26_clicked()//расписание
{
    Raspis *edit = new Raspis(db,3,this);
    edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    edit->setWindowTitle("Расписание");
    edit->exec();
}

void MainWindow::on_pushButton_24_clicked()
{
    Raspis *edit = new Raspis(db,4,this);
    edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    edit->setWindowTitle("Суда");
    edit->exec();
}

void MainWindow::on_pushButton_27_clicked()
{
    Raspis *edit = new Raspis(db,5,this);
    edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    edit->setWindowTitle("Наши порты");
    edit->exec();
}

void MainWindow::on_pushButton_29_clicked()//отчет по заказам
{
    db.open();
    QSqlQuery query;
        query.exec("SELECT id FROM ORDER_SHIP");
        bool ok =false;
        while (query.next()){
            if(query.value(0).toString()==QString::number(ui->spinBox->value())){
                ok = true;
            }
        }
    if(!ok)
       return;
    db.close();

    Otshet_Dialog *edit = new Otshet_Dialog(db,ui->spinBox->value(),this);
    edit->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    edit->setWindowTitle("Отчет по заказу");
    edit->exec();
}




















