#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSqlTableModel>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QTableWidgetItem"
#include "QVector"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *timer;
    QStringList list;
    QSqlDatabase db;
    QSqlTableModel *model;
    QStringList list_bd;

    int table_number_toltip = 0;
    QVector<QString> ship_tooltop;
    QVector<QString> port_tooltop;
    QVector<QString> weather_tooltip;

    QString toltip_last = "";


public slots:
    void timeOut();


private slots:

    void on_pushButton_9_clicked();
    void slotEditRecord(QModelIndex index);
    void update_model();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void end_end_end_end(QModelIndex item);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_18_clicked();

    void select_buttons();

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_19_clicked();

    void on_action_2_triggered();

    void on_action_triggered();
    void on_menu_2();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_29_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
