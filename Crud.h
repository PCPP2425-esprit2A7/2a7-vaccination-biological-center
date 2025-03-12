#ifndef CRUD_H
#define CRUD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>

class Crud {
private:
    QString nom;
    QString prenom;
    QString genre;
    QString date;
    QString dossier;
    int tel;
    int id;

public:
    Crud();
    Crud(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel);
    void add_patient(QTableWidget *tableWidget);
    void delete_patient(int id, QTableWidget *tableWidget);
    void update_patient(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel, QTableWidget *tableWidget);
    void load_patients(QTableWidget *tableWidget);
    void search_patient(int id, const QString &nom, QTableWidget *tableWidget);
    QMap<QString, QString> getPatientById(int id);
};

#endif // CRUD_H
