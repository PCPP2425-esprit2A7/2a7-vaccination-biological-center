#ifndef CRUD_H
#define CRUD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QTableWidget>
class Crud{
private:
    QString nom;QString prenom;QString genre;QString date;QString dossier;
    int tel;int id;
public:
    Crud();
    Crud(int id,QString nom,QString prenom,QString genre,QString date,QString dossier,int tel);
    void add_patient(QTableWidget *tableWidget);
    void delete_patient(int id, QTableWidget *tableWidget);
    void update_patient(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel, QTableWidget *tableWidget);


};


#endif // CRUD_H
