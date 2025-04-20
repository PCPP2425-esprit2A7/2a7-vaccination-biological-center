#ifndef VACCIN_H
#define VACCIN_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QString>
#include <QTableWidget>
class vaccin{
private:
    int id;
    int validation;
    QString nom,type,maladie,fabrication,description;
public:
    vaccin();
    vaccin(QString nom,QString type,QString maladie,QString fabrication,int validation,QString description);

    void setid(int id1){id=id1;}
    int getid(){return id;}

    void setnom(QString nom1){ nom=nom1; }
    QString getnom(){return nom;}

    void settype(QString type1){ type=type1; }
    QString gettype(){return type;}

    void setmaladie(QString maladie1){ maladie=maladie1; }
    QString getmaladie(){return maladie;}

    void setfabrication(QString fabrication1){ fabrication=fabrication1 ;}
    QString getfabrication(){return fabrication;}

    void set(QString description1){ description=description1; }
    QString get(){return description;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
     bool chargerVaccin(int id, QString &nom, QString &type, QString &maladie, QString &fabrication, int &validation, QString &description);
    bool modifier(int id, const QString &nom, const QString &type, const QString &maladie, const QString &fabrication, int validation, const QString &description);
     QSqlQueryModel* rechercher(const QString &term, const QString &critere);
    QSqlQueryModel* trier(const QString& critere, bool ascendant);
     QSqlQueryModel* exporterPDF(const QString& idVaccin = "");
    QSqlQueryModel* afficherHistorique(int idVaccin);
     bool ajouterHistorique(int idVaccin,const QStringList &champs,const QStringList &anciennesValeurs,const QStringList &nouvellesValeurs,QStringList &action );
     //bool ajouterHistorique(int idVaccin, const QString &champ, const QString &ancienneValeur, const QString &nouvelleValeur);
    QSqlQuery getVaccinsByValidationDuration();
    // QVector<QPair<int, int>> getStatistiquesValidation();
    QVector<QPair<QString, int>> getStatistiquesParType();
    QStringList getConcurrents(const QString &type, const QString &maladie, const QString &id);

};



#endif // VACCIN_H
