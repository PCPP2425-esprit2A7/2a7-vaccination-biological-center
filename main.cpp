#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Enable debug output
    qSetMessagePattern("[%{type}] %{function}: %{message}");
    qDebug() << "Application starting...";
    
    MainWindow w;
    w.show();
    
    return a.exec();
}
