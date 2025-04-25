#ifndef CRUD_H
#define CRUD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
#include <QMap>

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

    // Add a patient with file data
    void add_patient(int id, const QString &nom, const QString &prenom, const QString &genre, const QString &date,
                     const QString &doc, int tel, const QByteArray &fileData);

    // Delete patient by ID and refresh table
    bool delete_patient_by_id(int id, QTableWidget *tableWidget);

    // Update patient with optional file data
    void update_patient(int id, const QString &nom, const QString &prenom, const QString &genre,
                        const QString &date, const QString &fileName, int tel, const QByteArray &fileData);

    // Search for patients by ID or name
    void search_patient(int id, const QString &nom, QTableWidget *tableWidget);

    // Load all patients into table widget
    void load_patients(QTableWidget *tableWidget);

    // Load patients sorted by different criteria
    void load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType);

    // Get patient data by ID
    QMap<QString, QString> getPatientById(int id);
};
#endif // CRUD_H
