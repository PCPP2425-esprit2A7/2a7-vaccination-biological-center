#include "connection.h"


connection::connection(){}


bool connection::set_connection(){
    QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("PVaccin");
    db.setUserName("tahar8");
    db.setPassword("2003");
    return db.open();
}

QSqlDatabase connection::get_database(){
    return QSqlDatabase::database();
}
