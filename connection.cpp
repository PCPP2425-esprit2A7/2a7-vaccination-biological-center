#include "connection.h"

connection::connection(){} //default constructeur

bool connection::set_connection(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("PVaccin");
    db.setUserName("ahmed");
    db.setPassword("2005");
    return db.open(); // return true if the database was found / return false if the database is not found
}

QSqlDatabase connection::get_database(){
    return QSqlDatabase::database(); // return current database
}
