#ifndef RENDERVOUS_H
#define RENDERVOUS_H
#include "connection.h"
#include <QString>
#include <QTableView>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileDialog>
#include <QTextTable>
#include <QSqlQueryModel>


class rendervous{
private:
    // attribte de la class rendervous
    // id autincremnt
    QString date;
    QString status;
    int heure;
    int id_employe;
    int id_patient;
    int dur; //duree
    int code_patient; // nouveau champ

public:
    //  les methode de la classe rendervous
    rendervous(QString, int, int, int, int, QString, int code = -1); // mise à jour ici
     // constructeur parametere
    rendervous(); // constructeur par default
    //les method  de la crud
    bool ajouter();
    bool supprimer(int id);
    void afficher(QTableView *table);
    bool modifier(int id);

    // metier simple
    void export_pdf();
    void generateQRCode(int id, const QString &outputPath);
    static bool isAppointmentConflict(const QString &date, int newHour, int newDuration, int employeeId);
    static QSqlQueryModel * search(const QString &id);
    static QSqlQueryModel *sort(bool ordreCroissant);
    static QSqlQueryModel* prioriserPatients();
    static void genererAutoRendezVousPourAbsents();
    static QVector<QPair<int, int>> getStatistiquesValidation();




};

#endif // RENDERVOUS_H
