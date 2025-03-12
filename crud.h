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
    QString DATEDR;
    QString DATEFR;

public:
    Crud();
    Crud(int IDR, QString TITRER, QString CLASSR, QString DESCR, QString DATEDR, QString DATEFR);

    void add_recherche(QTableWidget *tableWidget);
    void delete_recherche(int IDR, QTableWidget *tableWidget);
    void update_recherche(int IDR);
    static void load_recherche_data(QTableWidget *tableWidget);
    void load_recherche_byTitle(const QString &title, QTableWidget *tableWidget);
    void load_recherche_byClass(const QString &classification, QTableWidget *tableWidget);
    void load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType);
};

#endif // CRUD_H
