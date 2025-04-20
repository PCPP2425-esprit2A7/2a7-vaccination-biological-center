#include "connection.h"

connection::connection() {}

bool connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("PVaccin");//inserer le nom de la source de données
    db.setUserName("tahar8");//inserer nom de l'utilisateur
    db.setPassword("2003");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    qDebug() << "Database opened successfully.";
    qDebug() << "Connection name:" << db.connectionName();
    qDebug() << "Database name:" << db.databaseName();



    return  test;
}
