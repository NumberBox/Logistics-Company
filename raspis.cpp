#include "raspis.h"
#include "ui_raspis.h"

Raspis::Raspis(QSqlDatabase db,int wath_this,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Raspis)
{
    ui->setupUi(this);
    this->wath_this = wath_this;
    this->db = db;
    ui->comboBox->addItem("Ледокол");
    ui->comboBox->addItem("Газовоз");
    ui->comboBox->addItem("Танкер");
    ui->comboBox->addItem("Лихтеровоз");
    ui->comboBox->addItem("Рефрижераторное судно");
    ui->comboBox->addItem("Роллер");
    ui->comboBox->addItem("Контейнеровоз");
    ui->comboBox->addItem("Балкер");
    ui->comboBox->addItem("Сухогруз");
    ui->dateEdit->setDate(QDate::currentDate());

    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->comboBox->hide();
    ui->dateEdit->hide();
    ui->horizontalLayout->setStretch(5,80);



    ui->pushButton->setDefault(true);
    db.open();

    if(wath_this==1){
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->comboBox->show();
        ui->dateEdit->show();
        ui->horizontalLayout->setStretch(5,25);


        ui->tableWidget->setColumnCount(9);
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Судно"));
        ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Вид судна"));
        ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Порт \nотправки"));
        ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Порт \nприбытия"));
        ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Дата \nотправления"));
        ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Время \nотправления"));
        ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Дата \nприбытия"));
        ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Время \nприбытия"));
        ui->tableWidget->setHorizontalHeaderItem(8,new QTableWidgetItem("Последний \nпосещенный порт"));
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(2,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(3,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(4,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(5,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(6,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(7,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(8,ui->tableWidget->width()/4);
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

        QSqlQuery query;
        query.exec("SELECT SCHEDULE.ship, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes, PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on ROUTE.current_port = PORT.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,8,new QTableWidgetItem(query.value(8).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
    }
    if(wath_this==2){//погода

        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Порт 1"));
        ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Порт 2"));
        ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Ветер м/с"));
        ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Направление ветра"));
        ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Температура"));
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/5);
        ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/5);
        ui->tableWidget->setColumnWidth(2,ui->tableWidget->width()/5);
        ui->tableWidget->setColumnWidth(3,ui->tableWidget->width()/5);
        ui->tableWidget->setColumnWidth(4,ui->tableWidget->width()/5);
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);


        QSqlQuery query;
        query.exec("SELECT PORT.name, WEATHER.wind,WEATHER.direction_wind,WEATHER.temperature, T.name from PORT INNER JOIN WEATHER on PORT.weather = WEATHER.id INNER JOIN (SELECT PORT.id, PORT.name FROM PORT) as T on PORT.next = T.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(3).toString()));
        }

    }
    if(wath_this==3){//расписание

        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->comboBox->show();
        ui->dateEdit->show();
        ui->horizontalLayout->setStretch(5,25);



        ui->tableWidget->setColumnCount(8);
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Имя судна"));
        ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Вид судна"));
        ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Порт \nотправки"));
        ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Порт \nприбытия"));
        ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Дата \nотправления"));
        ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Время \nотправления"));
        ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Дата \nприбытия"));
        ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Время \nприбытия"));
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(2,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(3,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(4,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(5,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(6,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(7,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(8,ui->tableWidget->width()/4);
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

        QSqlQuery query;
        query.exec("SELECT SHIP.name, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }

    }
    if(wath_this==4){
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Название"));
        ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Тип судна"));
        ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Скорость (уз)"));
        ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Месторасположение (порт)"));
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(2,ui->tableWidget->width()/4);
        ui->tableWidget->setColumnWidth(3,ui->tableWidget->width()/4);

        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);


        QSqlQuery query;
        query.exec("SELECT SHIP.name, SHIP.type_ship, SHIP.speed, PORT.name from SHIP INNER join PORT on SHIP.location = PORT.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
        }
        query.exec("SELECT SHIP.name, SHIP.type_ship, SHIP.speed, PORT.name from SHIP INNER join ROUTE on SHIP.id = ROUTE.ship INNER join PORT on ROUTE.current_port = PORT.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
        }


    }


    if(wath_this==5){
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Порт 1"));
        ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Расстояние (км)"));
        ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Порт 2"));
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/3);
        ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/3);
        ui->tableWidget->setColumnWidth(2,ui->tableWidget->width()/3);
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);


        QSqlQuery query;
        query.exec("SELECT PORT.name, PORT.km_from_to, T.name from PORT INNER join (SELECT * from PORT) as T on PORT.next = T.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
        }
    }




    db.close();
}

Raspis::~Raspis()
{
    delete ui;
}

void Raspis::on_pushButton_clicked()
{
    this->close();
}

void Raspis::on_pushButton_2_clicked()
{
    db.open();
    if(wath_this==1){

        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        QSqlQuery query;
        query.exec("SELECT SCHEDULE.ship, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes, PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on ROUTE.current_port = PORT.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,8,new QTableWidgetItem(query.value(8).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
    }
    if(wath_this==3){//расписание
           ui->tableWidget->clearContents();
           ui->tableWidget->setRowCount(0);
        QSqlQuery query;
        query.exec("SELECT SHIP.name, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }

    }
    db.close();
}

void Raspis::on_pushButton_3_clicked() // по типу
{
    db.open();

    if(wath_this==1){

        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        QSqlQuery query;
        query.exec("SELECT SCHEDULE.ship, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes, PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on ROUTE.current_port = PORT.id WHERE SHIP.type_ship = \""+ui->comboBox->currentText()+"\"");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,8,new QTableWidgetItem(query.value(8).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
    }
    if(wath_this==3){//расписание
           ui->tableWidget->clearContents();
           ui->tableWidget->setRowCount(0);
        QSqlQuery query;
        query.exec("SELECT SHIP.name, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id WHERE SHIP.type_ship = \""+ui->comboBox->currentText()+"\"");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }

    }

    db.close();
}

void Raspis::on_pushButton_4_clicked() // date
{
    db.open();
    if(wath_this==1){

        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);

        QSqlQuery query;
        QDate date = ui->dateEdit->date();
        QString d = date.toString("dd/MM/yyyy");
        query.exec("SELECT SCHEDULE.ship, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes, PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on ROUTE.current_port = PORT.id WHERE SCHEDULE.date_departures = \""+d+"\"");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,8,new QTableWidgetItem(query.value(8).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id INNER JOIN ROUTE on SCHEDULE.ship = ROUTE.ship INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
    }
    if(wath_this==3){//расписание
           ui->tableWidget->clearContents();
           ui->tableWidget->setRowCount(0);
        QSqlQuery query;
        QDate date = ui->dateEdit->date();
        QString d = date.toString("dd/MM/yyyy");
        query.exec("SELECT SHIP.name, SHIP.type_ship, SCHEDULE.port_departures, SCHEDULE.port_purposes, SCHEDULE.date_departures, SCHEDULE.time_departures, date_purposes, SCHEDULE.time_purposes from SCHEDULE INNER JOIN SHIP on SCHEDULE.ship = SHIP.id WHERE SCHEDULE.date_departures = \""+d+"\"");
        while (query.next()){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget->setItem(0+ui->tableWidget->rowCount()-1,7,new QTableWidgetItem(query.value(7).toString()));
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_departures = PORT.id");
        int row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }
        query.exec("SELECT PORT.name from SCHEDULE INNER JOIN PORT on SCHEDULE.port_purposes = PORT.id");
        row = 0;
        while (query.next()){
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(query.value(0).toString()));
            row++;
        }

    }
    db.close();
}
