#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QCryptographicHash>

class connection{
public:
    connection();
    bool set_connection();
    QSqlDatabase get_database();
    bool login(const QString& email, const QString& password);
    static QString hashPassword(const QString& password);
};

#endif // CONNECTION_H
