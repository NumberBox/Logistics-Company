#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.setStyleSheet("QToolTip {"
                    "border: 1px solid rgb(213, 247, 247);"
                    "background-color: rgb(220, 255, 255);"
                    "opacity: 200;"
                 "}");
    return a.exec();
}
