#include "Crud.h"
#include "connection.h"
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlRecord>
#include <QFile>
#include <QByteArray>

Crud::Crud() {}

Crud::Crud(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel) {
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->genre = genre;
    this->date = date;
    this->dossier = dossier;
    this->tel = tel;
}

void Crud::add_patient(int id, const QString &nom, const QString &prenom, const QString &genre, const QString &date,
                       const QString &doc, int tel, const QByteArray &fileData) {
    QSqlQuery query;
    query.prepare("INSERT INTO PATIENT (ID, NOM, PRENOM, GENRE, DATE_NAISSANCE, TEL, DOSSIER) "
                  "VALUES (:id, :nom, :prenom, :genre, :date, :tel, :dossier)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":genre", genre);
    query.bindValue(":date", date);
    query.bindValue(":tel", tel);
    query.bindValue(":dossier", fileData);  // Bind the BLOB data

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du patient : " << query.lastError();
        QMessageBox::warning(nullptr, "Erreur", "Erreur lors de l'ajout du patient: " + query.lastError().text());
    } else {
        qDebug() << "Patient ajouté avec succès.";
    }
}

bool Crud::delete_patient_by_id(int id, QTableWidget *tableWidget) {
    qDebug() << "Requête DELETE pour id =" << id;

    // Vérifier si le patient existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM PATIENT WHERE ID = :id");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count == 0) {
            QMessageBox::warning(nullptr, "Erreur", "Le patient avec cet ID n'existe pas.");
            return false;
        }
    }

    QSqlQuery query;
    query.prepare("DELETE FROM PATIENT WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Suppression réussie.";
        load_patients(tableWidget);
        return true;
    } else {
        qDebug() << "Erreur suppression:" << query.lastError().text();
        QMessageBox::warning(nullptr, "Erreur", "Erreur lors de la suppression du patient: " + query.lastError().text());
        return false;
    }
}

void Crud::update_patient(int id, const QString &nom, const QString &prenom, const QString &genre,
                          const QString &date, const QString &fileName, int tel, const QByteArray &fileData) {
    QSqlQuery query;

    // Check if new file data is provided
    if (fileData.isEmpty()) {
        query.prepare("UPDATE PATIENT SET NOM = :nom, PRENOM = :prenom, GENRE = :genre, "
                      "DATE_NAISSANCE = :date, TEL = :tel WHERE ID = :id");
    } else {
        query.prepare("UPDATE PATIENT SET NOM = :nom, PRENOM = :prenom, GENRE = :genre, "
                      "DATE_NAISSANCE = :date, TEL = :tel, DOSSIER = :dossier WHERE ID = :id");
        query.bindValue(":dossier", fileData);  // Store the file content
    }

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":genre", genre);
    query.bindValue(":date", date);
    query.bindValue(":tel", tel);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error updating patient:" << query.lastError().text();
        QMessageBox::warning(nullptr, "Erreur", "Erreur lors de la mise à jour du patient: " + query.lastError().text());
    } else {
        qDebug() << "Patient mis à jour avec succès.";
    }
}

void Crud::load_patients(QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        if (query.exec("SELECT * FROM PATIENT ORDER BY NOM ASC")) { // Tri par nom
            tableWidget->setRowCount(0);  // Clear the table first

            while (query.next()) {
                int id = query.value(0).toInt();
                QString nom = query.value(1).toString();
                QString prenom = query.value(2).toString();
                QString genre = query.value(3).toString();
                QString date = query.value(4).toString();
                int tel = query.value(5).toInt();
                QByteArray dossier = query.value(6).toByteArray();  // BLOB data

                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
                tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
                tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
                tableWidget->setItem(row, 3, new QTableWidgetItem(genre));
                tableWidget->setItem(row, 4, new QTableWidgetItem(date));
                tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(tel)));
                tableWidget->setItem(row, 6, new QTableWidgetItem("Document disponible"));  // Indicate a document exists
            }
        } else {
            qDebug() << "Erreur lors du chargement des patients :" << query.lastError().text();
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors du chargement des patients.");
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
    }
}

void Crud::search_patient(int id, const QString &nom, QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);

        if (id > 0 && !nom.isEmpty()) {
            query.prepare("SELECT * FROM PATIENT WHERE ID = :id OR NOM LIKE :nom ORDER BY NOM ASC");
            query.bindValue(":id", id);
            query.bindValue(":nom", "%" + nom + "%");
        } else if (id > 0) {
            query.prepare("SELECT * FROM PATIENT WHERE ID = :id ORDER BY NOM ASC");
            query.bindValue(":id", id);
        } else if (!nom.isEmpty()) {
            query.prepare("SELECT * FROM PATIENT WHERE NOM LIKE :nom ORDER BY NOM ASC");
            query.bindValue(":nom", "%" + nom + "%");
        } else {
            query.prepare("SELECT * FROM PATIENT ORDER BY NOM ASC");
        }

        if (query.exec()) {
            tableWidget->setRowCount(0);  // Clear the table first

            while (query.next()) {
                int patientId = query.value(0).toInt();
                QString patientNom = query.value(1).toString();
                QString patientPrenom = query.value(2).toString();
                QString patientGenre = query.value(3).toString();
                QString patientDate = query.value(4).toString();
                int patientTel = query.value(5).toInt();
                QByteArray patientDossier = query.value(6).toByteArray();

                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(patientId)));
                tableWidget->setItem(row, 1, new QTableWidgetItem(patientNom));
                tableWidget->setItem(row, 2, new QTableWidgetItem(patientPrenom));
                tableWidget->setItem(row, 3, new QTableWidgetItem(patientGenre));
                tableWidget->setItem(row, 4, new QTableWidgetItem(patientDate));
                tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(patientTel)));
                tableWidget->setItem(row, 6, new QTableWidgetItem("Document disponible"));  // Indicate a document exists
            }

            if (tableWidget->rowCount() == 0) {
                qDebug() << "Aucun patient trouvé.";
                QMessageBox::information(nullptr, "Recherche", "Aucun patient trouvé.");
            }
        } else {
            qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors de la recherche.");
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
    }
}

QMap<QString, QString> Crud::getPatientById(int id) {
    QMap<QString, QString> patientData;
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM PATIENT WHERE ID = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            // Récupérer les données du patient
            patientData["id"] = query.value(0).toString();
            patientData["nom"] = query.value(1).toString();
            patientData["prenom"] = query.value(2).toString();
            patientData["genre"] = query.value(3).toString();
            patientData["date"] = query.value(4).toString();
            patientData["tel"] = query.value(5).toString();
            // Note: We don't retrieve BLOB data here as it's not needed for display
        } else {
            qDebug() << "Erreur lors de la récupération des données du patient :" << query.lastError().text();
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
    }

    return patientData;
}

void Crud::load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        QString queryString;

        if (sortType == "Nom (A-Z)") {
            queryString = "SELECT * FROM PATIENT ORDER BY NOM ASC";  // Tri par nom de A à Z
        } else if (sortType == "Nom (Z-A)") {
            queryString = "SELECT * FROM PATIENT ORDER BY NOM DESC";  // Tri par nom de Z à A
        } else if (sortType == "Genre (Homme/Femme)") {
            queryString = "SELECT * FROM PATIENT ORDER BY GENRE ASC";  // Tri par genre (Homme/Femme)
        } else {
            queryString = "SELECT * FROM PATIENT ORDER BY ID";  // Par défaut, tri par ID
        }

        query.prepare(queryString);

        if (query.exec()) {
            tableWidget->setRowCount(0);  // Clear the table first

            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem("Document disponible"));  // Indicate a document exists
            }
            qDebug() << "Sorting applied: " << sortType;
        } else {
            qDebug() << "Sorting query failed: " << query.lastError().text();
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors du tri des patients.");
        }
    } else {
        qDebug() << "Database connection failed.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
    }
}
