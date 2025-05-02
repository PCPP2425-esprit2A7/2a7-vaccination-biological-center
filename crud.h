#ifndef CRUD_H
#define CRUD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QTableWidget>

class Crud {
private:
    int IDE;
    QString NOME;
    QString EMAILE;
    int TELE;
    QString ADRESSEE;
    QString MDPE;
    QString ROLEE;
    int SALAIREE;
    QString RFID_UID;  // New field for RFID UID

public:
    Crud();
    Crud(int id, QString name, QString email, int phone,
         QString address, QString password, QString role,
         int salary, QString rfid_uid);  // Constructor updated

    void add_utilisateur(QTableWidget *tableWidget);
    void delete_utilisateur(int IDE, QTableWidget *tableWidget);
    void update_utilisateur(int IDE);
    static void load_utilisateur_data(QTableWidget *tableWidget);
    void load_utilisateur_byName(const QString &name, QTableWidget *tableWidget);
    void load_utilisateur_byRole(const QString &role, QTableWidget *tableWidget);
    void load_sorted_utilisateur(QTableWidget *tableWidget, const QString &sortType);

    static bool login(const QString &email, const QString &password);
};

#endif // CRUD_H
