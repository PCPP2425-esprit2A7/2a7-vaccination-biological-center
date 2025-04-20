#include "vaccin.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
// chat includes
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
// Constructeur par défaut
vaccin::vaccin()
{
    // Initialisation des attributs (facultatif)
    id = 0;
    validation = 0;
    nom = "";
    type = "";
    maladie = "";
    fabrication = "";
    description = "";
}

// Constructeur paramétré
vaccin::vaccin( QString nom, QString type, QString maladie, QString fabrication, int validation, QString description)
{
    this->id = id;
    this->nom = nom;
    this->type = type;
    this->maladie = maladie;
    this->fabrication = fabrication;
    this->validation = validation;
    this->description = description;
}

// Méthode pour ajouter un vaccin à la base de données
bool vaccin::ajouter()
{
    QSqlQuery query;

    // Convertir l'attribut id en QString
    // Utiliser this-> pour éviter l'ambiguïté
   // QString validationStr = QString::number(this->validation);

    // Préparer la requête SQL
    query.prepare("INSERT INTO VACCINS(NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION) "
                  "VALUES ( :nom, :type, :maladie, :fabrication, :validation, :description)");

    // Lier les valeurs aux paramètres de la requête

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":fabrication", fabrication);
    query.bindValue(":validation", validation);
    query.bindValue(":description", description);

    // Exécuter la requête
    if (query.exec())
    {
        qDebug() << "Vaccin ajouté avec succès !";
        return true;
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout du vaccin :" << query.lastError().text();
        return false;
    }
}

// Méthode pour afficher la liste des vaccins
QSqlQueryModel* vaccin::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Définir la requête SQL pour sélectionner tous les vaccins
    model->setQuery("select * from VACCINS");
    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Maladie"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fabrication"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Validation"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));

    return model;
}

// Méthode pour supprimer un vaccin de la base de données
/*bool vaccin::supprimer(int id)
{
    QSqlQuery query;

    // Convertir l'ID en QString
   // QString idStr = QString::number(id);
    bool test=false;
    // Préparer la requête SQL
    query.prepare("DELETE FROM VACCINS WHERE id = :id");
    // Lier les valeurs aux paramètres de la requête
    query.bindValue(":id", id);

    // Exécuter la requête
    if (query.exec())
    {
        test=true;
        qDebug() << "Vaccin supprimé avec succès !";
        return test;
    }
    else
    {
        test=false;
        qDebug() << "Erreur lors de la suppression du vaccin :" << query.lastError().text();
        return test;
    }
}
*/



bool vaccin::supprimer(int id)
{
    QSqlQuery query;

    // Étape 1 : récupérer les données actuelles
    query.prepare("SELECT nom, type, maladie, fabrication, validation, description FROM VACCINS WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur récupération du vaccin avant suppression :" << query.lastError().text();
        return false;
    }

    // Étape 2 : construire les QStringList
    QStringList champs = {"Nom", "Type", "Maladie", "Fabrication", "Validation", "Description"};
    QStringList anciennesValeurs = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL"};

    QStringList nouvellesValeurs;
    nouvellesValeurs << query.value(0).toString(); // nom
    nouvellesValeurs << query.value(1).toString(); // type
    nouvellesValeurs << query.value(2).toString(); // maladie
    nouvellesValeurs << query.value(3).toString(); // fabrication
    nouvellesValeurs << QString::number(query.value(4).toInt()); // validation
    nouvellesValeurs << query.value(5).toString(); // description

    QStringList action = {"SUPPRIMER"};

    // Étape 3 : appeler la fonction pour ajouter à l’historique
    if (!ajouterHistorique(id, champs, anciennesValeurs, nouvellesValeurs, action)) {
        qDebug() << "Erreur lors de l’ajout à l’historique. Annulation de la suppression.";
        return false; // si l'historique échoue, on ne supprime pas le vaccin
    }

    // Étape 4 : supprimer le vaccin
    query.prepare("DELETE FROM VACCINS WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Vaccin supprimé avec succès !";
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression du vaccin :" << query.lastError().text();
        return false;
    }
}














bool vaccin::chargerVaccin(int id, QString &nom, QString &type, QString &maladie, QString &fabrication, int &validation, QString &description)
{
    QSqlQuery query;

    // Convertir l'ID en QString
    //QString idStr = QString::number(id);

    // Préparer la requête SQL pour sélectionner le vaccin
    query.prepare("SELECT  NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION FROM VACCINS WHERE id = :id");
    query.bindValue(":id", id);

     //Si query.next() retourne false, cela signifie qu’aucun vaccin avec cet ID n’a été trouvé
    // Exécuter la requête
    if (query.exec() && query.next())
    {
        // Récupérer les valeurs de la base de données

        nom = query.value(0).toString();
        type = query.value(1).toString();
        maladie = query.value(2).toString();
        fabrication = query.value(3).toString();
        validation = query.value(4).toInt();
        description = query.value(5).toString();

        return true;  // Vaccin trouvé
    }
    else
    {
        qDebug() << "Vaccin non trouvé ou erreur de requête :" << query.lastError().text();
        return false;  // Vaccin non trouvé ou erreur
    }
}






bool vaccin::ajouterHistorique(int idVaccin,
                               const QStringList &champs,
                               const QStringList &anciennesValeurs,
                               const QStringList &nouvellesValeurs,
                               QStringList &action)
{
    if (champs.size() != anciennesValeurs.size() || champs.size() != nouvellesValeurs.size()) {
        qDebug() << "Taille des listes invalide pour l'historique.";
        return false;
    }

    QString champStr = champs.join(", ");  //join(", ") transforme une liste (QStringList) en une seule chaîne de caractère
    QString ancienneStr = anciennesValeurs.join(", ");
    QString nouvelleStr = nouvellesValeurs.join(", ");
    QString actionStr = action.join(", ");  // Valeur à définir, tu peux la laisser telle quelle ou l'ajuster

    QSqlQuery query;

    query.prepare("INSERT INTO HISTORIQUE_VACCINS "
                  "(ID_VACCIN, DATE_MODIFICATION,CHAMP_MODIFIE, ANCIENNE_VALEUR, NOUVELLE_VALEUR, ACTION) "
                  "VALUES (:id,SYSDATE, :champ, :ancienne, :nouvelle, :action)");

    query.bindValue(":id", idVaccin);
    query.bindValue(":champ", champStr);
    query.bindValue(":ancienne", ancienneStr);
    query.bindValue(":nouvelle", nouvelleStr);
    query.bindValue(":action", actionStr);

    if (!query.exec()) {
        qDebug() << "Erreur insertion historique groupée:" << query.lastError().text();
        return false;
    }

    return true;
}



/*bool vaccin::modifier(int id, const QString &nom, const QString &type, const QString &maladie, const QString &fabrication, int validation, const QString &description)
{
    QSqlQuery query;

    // Convertir l'ID en QString
    //QString idStr = QString::number(id);
    query.prepare("SELECT NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION FROM VACCINS WHERE ID = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur récupération ancienne valeur:" << query.lastError().text();
        return false;
    }
    QString ancienNom = query.value(0).toString();
    QString ancienType = query.value(1).toString();
    QString ancienneMaladie = query.value(2).toString();
    QString ancienneFabrication = query.value(3).toString();
    int ancienneValidation = query.value(4).toInt();
    QString ancienneDescription = query.value(5).toString();
    // Préparer la requête SQL pour mettre à jour le vaccin
    query.prepare("UPDATE VACCINS SET nom = :nom, type = :type, maladie = :maladie, fabrication = :fabrication, validation = :validation, description = :description WHERE id = :id");

    // Lier les valeurs aux paramètres de la requête
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":fabrication", fabrication);
    query.bindValue(":validation", validation);
    query.bindValue(":description", description);

    if (ancienNom != nom) ajouterHistorique(id, "Nom", ancienNom, nom);
    if (ancienType != type) ajouterHistorique(id, "Type", ancienType, type);
    if (ancienneMaladie != maladie) ajouterHistorique(id, "Maladie", ancienneMaladie, maladie);
    if (ancienneFabrication != fabrication) ajouterHistorique(id, "Fabrication", ancienneFabrication, fabrication);
    if (ancienneValidation != validation) {
        ajouterHistorique(id, "Validation", QString::number(ancienneValidation), QString::number(validation));
    }


    if (ancienneDescription != description) ajouterHistorique(id, "Description", ancienneDescription, description);

    // Exécuter la requête
    if (query.exec())
    {
        qDebug() << "Vaccin modifié avec succès !";
        return true;
    }
    else
    {
        qDebug() << "Erreur lors de la modification du vaccin :" << query.lastError().text();
        return false;
    }
}*/

bool vaccin::modifier(int id, const QString &nom, const QString &type, const QString &maladie,
                      const QString &fabrication, int validation, const QString &description)
{
    QSqlQuery query;

    query.prepare("SELECT NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION FROM VACCINS WHERE ID = :id");
    query.bindValue(":id", id);
    qDebug() << "Tentative récupération vaccin ID:" << id;

    if (!query.exec()) {
        qDebug() << "Erreur exec SELECT :" << query.lastError().text();
        return false;
    }
    //query.next() déplace le curseur sur le premier enregistrement.

    //S’il n’y a aucun résultat (aucun vaccin trouvé), on affiche une erreur.
    if (!query.next()) {
        qDebug() << "Aucun vaccin trouvé avec ID =" << id;
        return false;
    }
    QString ancienNom = query.value(0).toString();
    QString ancienType = query.value(1).toString();
    QString ancienneMaladie = query.value(2).toString();
    QString ancienneFabrication = query.value(3).toString();
    int ancienneValidation = query.value(4).toInt();
    QString ancienneDescription = query.value(5).toString();

    QStringList champsModifies;
    QStringList anciennesValeurs;
    QStringList nouvellesValeurs;
    QStringList action;

    if (ancienNom != nom) {
        champsModifies << "Nom";
        anciennesValeurs << ancienNom;
        nouvellesValeurs << nom;
    }
    if (ancienType != type) {
        champsModifies << "Type";
        anciennesValeurs << ancienType;
        nouvellesValeurs << type;
    }
    if (ancienneMaladie != maladie) {
        champsModifies << "Maladie";
        anciennesValeurs << ancienneMaladie;
        nouvellesValeurs << maladie;
    }
    if (ancienneFabrication != fabrication) {
        champsModifies << "Fabrication";
        anciennesValeurs << ancienneFabrication;
        nouvellesValeurs << fabrication;
    }
    if (ancienneValidation != validation) {
        champsModifies << "Validation";
        anciennesValeurs << QString::number(ancienneValidation);
        nouvellesValeurs << QString::number(validation);
    }
    if (ancienneDescription != description) {
        champsModifies << "Description";
        anciennesValeurs << ancienneDescription;
        nouvellesValeurs << description;
    }
    action << "UPDATE";

    // Enregistrer les changements en une seule ligne s’il y a eu des modifications
    if (!champsModifies.isEmpty()) {
        ajouterHistorique(id, champsModifies, anciennesValeurs, nouvellesValeurs,action);
    }

    query.prepare("UPDATE VACCINS SET nom = :nom, type = :type, maladie = :maladie, "
                  "fabrication = :fabrication, validation = :validation, description = :description WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":fabrication", fabrication);
    query.bindValue(":validation", validation);
    query.bindValue(":description", description);

    if (query.exec()) {
        qDebug() << "Vaccin modifié avec succès !";
        return true;
    } else {
        qDebug() << "Erreur lors de la modification du vaccin :" << query.lastError().text();
        return false;
    }
}




QSqlQueryModel* vaccin::rechercher(const QString &term, const QString &critere) {
    if (term.isEmpty()) {
        return nullptr;  // Ne rien faire si le champ est vide
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString queryStr;

    // Construire la requête selon le critère
    if (critere == "type") {
        queryStr = "SELECT * FROM VACCINS WHERE TYPE LIKE :term";  //contient juste le texte
    } else if (critere == "maladie") {
        queryStr = "SELECT * FROM VACCINS WHERE MALADIE LIKE :term";
    }

    //La méthode prepare() est utilisée quand tu as une requête avec des paramètres dynamiques (comme :term, :id, etc.)
    query.prepare(queryStr);  //je vais utiliser cette requête, prépare-la
    query.bindValue(":term", term + "%");  // remplace ce paramètre dans la requête par cette valeur.

    if (!query.exec()) {
        qDebug() << "Erreur recherche:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}








QSqlQueryModel* vaccin::trier(const QString& critere, bool ascendant) {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Vérifier que le critère est valide
    QString colonne;
    if (critere == "nom") {
        colonne = "NOM";
    } else if (critere == "date_fabrication") {
        colonne = "FABRICATION";
    } else if (critere == "duree_validation") {
        colonne = "VALIDATION";
    } else {
        qDebug() << "Critère de tri invalide :" << critere;
        delete model;
        return nullptr;
    }


    //La méthode prepare() est utilisée quand tu as une requête avec des paramètres dynamiques (comme :term, :id, etc.)
    //Remplace le %1 dans la chaîne précédente par le contenu de la variable colonne
    // Construire la requête SQL avec un tri
    QString queryString = QString("SELECT ID, NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION FROM VACCINS ORDER BY %1 %2")
                              .arg(colonne)
                              .arg(ascendant ? "ASC" : "DESC");

    model->setQuery(queryString);

    // Vérifier s'il y a une erreur dans l'exécution de la requête
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors du tri :" << model->lastError().text();
        delete model;
        return nullptr;
    }

    return model; // Retourne le modèle trié
}



QSqlQueryModel* vaccin::exporterPDF(const QString& idVaccin) {
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte.";
        delete model;
        return nullptr;
    }

    QSqlQuery query(db);

    if (idVaccin.isEmpty()) {
        query.prepare("SELECT ID, NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION FROM VACCINS");
    } else {
        query.prepare("SELECT ID, NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION FROM VACCINS WHERE ID = :id");
        query.bindValue(":id", idVaccin);
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'extraction des données pour le PDF:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}











/*QSqlQueryModel* vaccin::afficherHistorique(int idVaccin)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT TO_CHAR(DATE_MODIFICATION, 'DD/MM/YYYY HH24:MI') AS DATE_MODIFICATION, "
                  "CHAMP_MODIFIE, ANCIENNE_VALEUR, NOUVELLE_VALEUR "
                  "FROM HISTORIQUE_VACCINS "
                  "WHERE ID_VACCIN = :id "
                  "ORDER BY DATE_MODIFICATION DESC");

    query.bindValue(":id", idVaccin);

    if (!query.exec()) {
        qDebug() << "Erreur chargement historique:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date modification"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Champ modifié"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Ancienne valeur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nouvelle valeur"));


    return model;
}
*/


QSqlQueryModel* vaccin::afficherHistorique(int idVaccin)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    if (idVaccin != -1) {
        // Affichage classique si vaccin sélectionné
        query.prepare("SELECT TO_CHAR(DATE_MODIFICATION, 'DD/MM/YYYY HH24:MI') AS DATE_MODIFICATION, "
                      "CHAMP_MODIFIE, ANCIENNE_VALEUR, NOUVELLE_VALEUR "
                      "FROM HISTORIQUE_VACCINS "
                      "WHERE ID_VACCIN = :id "
                      "ORDER BY DATE_MODIFICATION DESC");
        query.bindValue(":id", idVaccin);
    } else {

        query.prepare("SELECT ID_VACCIN, "
                      "TO_CHAR(DATE_MODIFICATION, 'DD/MM/YYYY HH24:MI') AS DATE_MODIFICATION, "
                      "CHAMP_MODIFIE || ': ' || NOUVELLE_VALEUR AS CHANGEMENTS, "
                      "ACTION "
                      "FROM HISTORIQUE_VACCINS "
                      "ORDER BY DATE_MODIFICATION DESC");

    }



    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return nullptr;
    }

    qDebug() << "Nombre de lignes retournées :" << query.size();
    while (query.next()) {
        qDebug() << "Ligne :" << query.value(0) << query.value(1) << query.value(2);
    }

    model->setQuery(query);

    if (idVaccin != -1) {
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date modification"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Champ modifié"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Ancienne valeur"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nouvelle valeur"));
    } else {
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Vaccin"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date modification"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Changements"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Action"));
    }

    return model;
}






QSqlQuery vaccin::getVaccinsByValidationDuration() {
    QSqlQuery query;

    // Requête SQL pour récupérer les vaccins et leur durée de validation
    QString queryString = R"(
        SELECT VALIDATION, COUNT(*)
        FROM VACCINS
        WHERE VALIDATION IS NOT NULL
        GROUP BY VALIDATION
        ORDER BY VALIDATION
    )";

    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
    }

    return query;  // Retourne l'objet QSqlQuery contenant les résultats
}





/*
QVector<QPair<int, int>> vaccin::getStatistiquesValidation() {
    QVector<QPair<int, int>> stats;

    // Requête SQL pour récupérer le nombre de vaccins par durée de validation
    QSqlQuery query;
    query.prepare("SELECT VALIDATION, COUNT(*) FROM VACCINS WHERE VALIDATION IS NOT NULL GROUP BY VALIDATION ORDER BY VALIDATION");

    if (query.exec()) {
        // Ajouter les résultats à un QVector
        while (query.next()) {
            int validation = query.value(0).toInt(); // lit la valeur de la colonne VALIDATION (durée)
            int count = query.value(1).toInt(); //lit la valeur du COUNT(*) (combien de vaccins ont cette durée)
            stats.append(qMakePair(validation, count));  // creer Paire (durée, nombre de vaccins) et ajouter cette paire dans le vecteur
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return stats;  // Retourner les statistiques sous forme de QVector
}*/

QVector<QPair<QString, int>> vaccin::getStatistiquesParType() {
    QVector<QPair<QString, int>> stats;

    // Requête SQL pour récupérer le nombre de vaccins par type
    QSqlQuery query;
    query.prepare("SELECT TYPE, COUNT(*) FROM VACCINS WHERE TYPE IS NOT NULL GROUP BY TYPE ORDER BY TYPE");

    if (query.exec()) {
        // Ajouter les résultats à un QVector
        while (query.next()) {
            QString type = query.value(0).toString(); // lit la valeur de la colonne TYPE
            int count = query.value(1).toInt();       // lit le nombre de vaccins de ce type
            stats.append(qMakePair(type, count));     // créer Paire (type, nombre) et l'ajouter dans le vecteur
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return stats; // Retourner les statistiques sous forme de QVector
}





QStringList vaccin::getConcurrents(const QString &type, const QString &maladie, const QString &id)
{
    QStringList descriptionsConcurrents;  // Liste pour stocker les descriptions des concurrents
    QSqlQuery query;

    // Préparer la requête SQL pour obtenir les vaccins concurrents
    query.prepare("SELECT NOM, DESCRIPTION FROM VACCINS WHERE TYPE = :type AND MALADIE = :maladie AND ID != :id");
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":id", id);

    // Exécuter la requête et parcourir les résultats
    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value("NOM").toString();
            QString desc = query.value("DESCRIPTION").toString();
            // Ajouter chaque vaccin concurrent sous forme de chaîne formatée dans la liste
            descriptionsConcurrents << QString("Nom : %1 | Description : %2").arg(nom, desc);
        }
    } else {
        // Si la requête échoue, afficher un message d'erreur
        qDebug() << "Erreur lors de la récupération des concurrents : " << query.lastError().text();
    }

    // Retourner la liste des descriptions des concurrents
    return descriptionsConcurrents;
}




















