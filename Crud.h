#ifndef CRUD_H
#define CRUD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QTableWidget>

class Crud {
private:
    int IDR;
    QString TITRER;
    QString CLASSR;
    QString DESCR;
    QString DATEM;

public:
    Crud();
    Crud(int IDR, QString TITRER, QString CLASSR, QString DESCR, QString DATEM);

    void add_recherche(QTableWidget *tableWidget);
    void delete_recherche(int IDR, QTableWidget *tableWidget);
    void update_recherche(int IDR);
};

#endif //CRUD_H
