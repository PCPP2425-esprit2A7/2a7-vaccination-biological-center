#include "grendervous.h"
#include "connection.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    grendervous w;
    connection c;
    if(c.set_connection()){
        w.on_displaybutton_2_clicked();
        w.show();
        qDebug()<<"database connected";
    }else{
        qDebug()<<"probleme to connected with ahmed database";
    }
    return a.exec();
}
