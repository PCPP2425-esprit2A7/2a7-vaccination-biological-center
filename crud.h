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
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <QTableView>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileDialog>
#include <QTextTable>
#include <QDate>




//employee_taherrr
class CrudE {
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
    CrudE();
    CrudE(int id, QString name, QString email, int phone,
         QString address, QString password, QString role,
         int salary, QString rfid_uid);  // Constructor updated

    void add_utilisateur(QTableWidget *tableWidget);
    void delete_utilisateur(int IDE, QTableWidget *tableWidget);
    void update_utilisateur(int IDE);
    static void load_utilisateur_data(QTableWidget *tableWidget);
    void load_utilisateur_byName(const QString &name, QTableWidget *tableWidget);
    void load_utilisateur_byRole(const QString &role, QTableWidget *tableWidget);
    void load_sorted_utilisateur(QTableWidget *tableWidget, const QString &sortType);
    int getIdN() const { return idN; }
    QString getRoleN() const { return roleN; }

    static bool login(const QString &email, const QString &password, int &idN, QString &roleN);
    static int idN;
    static QString roleN;
};



//recherche_abidddddd


class CrudR {
private:
    int IDR;
    QString TITRER;
    QString CLASSR;
    QString DESCR;
    QString DATEDR;
    QString DATEFR;
    int EMPLOYE;

public:
    CrudR();
    CrudR(int IDR, QString TITRER, QString CLASSR, QString DESCR, QString DATEDR, QString DATEFR, int EMPLOYE);

    bool add_recherche(QTableWidget *tableWidget);
    void delete_recherche(int IDR, QTableWidget *tableWidget);
    void update_recherche(int IDR);
    static void load_recherche_data(QTableWidget *tableWidget);
    void load_recherche_byTitle(const QString &title, QTableWidget *tableWidget);
    void load_recherche_byClass(const QString &classification, QTableWidget *tableWidget);
    void load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType);
    void load_recherche_byEmployee(QTableWidget *tableWidget);
};



//patient_YS7



class Crudp {
private:
    QString nom;
    QString prenom;
    QString genre;
    QString date;
    QString dossier;
    int tel;
    int id;

public:
    Crudp();
    Crudp(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel);

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









//vaccin_jiheddddd

class vaccin{
private:
    int id;
    int validation;
    double temperature;
    QString nom,type,maladie,fabrication,description;
    int EMPLOYE;
public:
    vaccin();
    vaccin(QString nom,QString type,QString maladie,QString fabrication,int validation,QString description,double temperature, int EMPLOYE);

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


    bool ajouterv();
    QSqlQueryModel * afficherv();
    bool supprimerv(int);
    bool chargerVaccinv(int id, QString &nom, QString &type, QString &maladie, QString &fabrication, int &validation, QString &description,double &temperature);
    bool modifierv(int id, const QString &nom, const QString &type, const QString &maladie, const QString &fabrication, int validation, const QString &description,const double &temperature);
    QSqlQueryModel* rechercherv(const QString &term, const QString &critere);
    QSqlQueryModel* trierv(const QString& critere, bool ascendant);
    QSqlQueryModel* trierMesVaccins();
    QSqlQueryModel* exporterPDFv(const QString& idVaccin = "");
    QSqlQueryModel* afficherHistoriquev(int idVaccin);
    bool ajouterHistoriquev(int idVaccin,const QStringList &champs,const QStringList &anciennesValeurs,const QStringList &nouvellesValeurs,QStringList &action );
    //bool ajouterHistorique(int idVaccin, const QString &champ, const QString &ancienneValeur, const QString &nouvelleValeur);
    QSqlQuery getVaccinsByValidationDurationv();
    // QVector<QPair<int, int>> getStatistiquesValidation();
    QVector<QPair<QString, int>> getStatistiquesParTypev();
    QStringList getConcurrentsv(const QString &type, const QString &maladie, const QString &id);
    bool envoyerMailSecurev(const QString &emailDest, const QString &sujet, const QString &contenu);
    bool verifierTemperaturev(double temperatureActuelle);
    QPair<QString, double> getVaccinTemperatureMinimalev();

};

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
    int code_patient;       // nouveau champ

public:
    //  les methode de la classe rendervous
    rendervous(QString, int, int, int, int, QString, int code = -1); // mise à jour ici
        // constructeur parametere
    rendervous(); // constructeur par default
    //les method  de la crud
    bool ajouter();
    bool supprimer(int id);
    void afficher(QTableWidget *table);
    bool modifier(int id);

    // metier simple
    void export_pdf();
    void generateQRCode(int id, const QString &outputPath);
    static bool isAppointmentConflict(const QString &date, int newHour, int newDuration, int employeeId);
    static QSqlQueryModel * search(const QString &id);
    static void sort(QTableWidget *table, bool ordreCroissant);

    static QSqlQueryModel * prioriserPatients();
    static void genererAutoRendezVousPourAbsents();
    static QVector<QPair<int, int>> getStatistiquesValidation();
    void load_byEmployee(QTableWidget *tableWidget);
    static QSqlQueryModel* load_recherche_byEmployee(bool ordreCroissant);
    static QSqlQueryModel* sortByEmployee(int employeId);
    static QSqlQuery getSortedByEmployee(int employeId);

};


class equipement
{
public:
    // Constructors
    equipement(); // Default constructor
    equipement(QString nomeq, QString etateq, int nbeq, QString typeeq, QDate tempmeq, QString desceq, QString feq);

    // Methods
    bool ajouter(QTableWidget *tableWidget);
    void delete_equipement(int id, QTableWidget *tableWidget);
    void update_equipement(int id);
    void load_equipement_data(QTableWidget *tableWidget);
    void load_equipement_byNom(const QString &nom, QTableWidget *tableWidget);
    void load_equipement_byEtat(const QString &etat, QTableWidget *tableWidget);
    void load_equipement_byType(const QString &type, QTableWidget *tableWidget);
    void load_sorted_equipement(QTableWidget *tableWidget, const QString &sortType);
    QVector<QPair<QString, int>> getStatistiquesByEtat();
    QVector<QPair<QString, int>> getStatistiquesByType();
    QVector<QPair<QString, int>> getStatistiquesByQuantity();

private:
    QString nomeq;
    QString etateq;
    int nbeq;
    QString typeeq;
    QDate tempmeq;
    QString desceq;
    QString feq;
};

#endif // CRUD_H
