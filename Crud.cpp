#include "Crud.h"
#include "connection.h"
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>

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

void Crud::add_patient(QTableWidget *tableWidget) { //ajout
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("INSERT INTO PATIENT(id, NOM, PRENOM, GENRE, DATE_NAISSANCE, TEL, DOSSIER) "
                       "VALUES (:id, :nom, :prenom, :genre, :date, :tel, :dossier)");
        thisdb.bindValue(":id", id);
        thisdb.bindValue(":nom", nom);
        thisdb.bindValue(":prenom", prenom);
        thisdb.bindValue(":genre", genre);
        thisdb.bindValue(":date", date);
        thisdb.bindValue(":tel", tel);
        thisdb.bindValue(":dossier", dossier);

        if (thisdb.exec()) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);

            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
            tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
            tableWidget->setItem(row, 3, new QTableWidgetItem(genre));
            tableWidget->setItem(row, 4, new QTableWidgetItem(date));
            tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(tel)));
            tableWidget->setItem(row, 6, new QTableWidgetItem(dossier));

            qDebug() << "Patient ajouté avec succès.";
        } else {
            qDebug() << "Erreur lors de l'ajout du patient :" << thisdb.lastError().text();
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors de l'ajout du patient.");
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
    }
}

void Crud::delete_patient(int id, QTableWidget *tableWidget) {  //supp
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("DELETE FROM PATIENT WHERE id = :id");
        thisdb.bindValue(":id", id);

        if (thisdb.exec()) {
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                QTableWidgetItem *item = tableWidget->item(row, 0);
                if (item && item->text().toInt() == id) {
                    tableWidget->removeRow(row);
                    break;
                }
            }
            qDebug() << "Patient supprimé avec succès.";
        } else {
            qDebug() << "Erreur lors de la suppression du patient :" << thisdb.lastError().text();
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors de la suppression du patient.");
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
    }
}

void Crud::update_patient(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel, QTableWidget *tableWidget) {
    // mod
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);

        // Vérifier que les champs obligatoires ne sont pas vides
        if (nom.isEmpty() || prenom.isEmpty() || genre.isEmpty() || date.isEmpty() || dossier.isEmpty()) {
            qDebug() << "Erreur : Un ou plusieurs champs obligatoires sont vides.";
            QMessageBox::warning(nullptr, "Erreur", "Tous les champs doivent être remplis.");
            return;
        }

        query.prepare("UPDATE PATIENT SET NOM = :nom, PRENOM = :prenom, GENRE = :genre, DATE_NAISSANCE = :date, TEL = :tel, DOSSIER = :dossier WHERE id = :id");
        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":genre", genre);
        query.bindValue(":date", date);
        query.bindValue(":tel", tel);
        query.bindValue(":dossier", dossier);

        if (query.exec()) {
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                QTableWidgetItem *item = tableWidget->item(row, 0);
                if (item && item->text().toInt() == id) {
                    tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
                    tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
                    tableWidget->setItem(row, 3, new QTableWidgetItem(genre));
                    tableWidget->setItem(row, 4, new QTableWidgetItem(date));
                    tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(tel)));
                    tableWidget->setItem(row, 6, new QTableWidgetItem(dossier));
                    break;
                }
            }
            qDebug() << "Patient mis à jour avec succès.";
        } else {
            qDebug() << "Erreur lors de la mise à jour du patient :" << query.lastError().text();
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors de la mise à jour du patient.");
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
    }
}

void Crud::load_patients(QTableWidget *tableWidget) {  // affichage des patients dans la tablewidget
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        if (query.exec("SELECT * FROM PATIENT ORDER BY nom ASC")) { // Tri par nom
            tableWidget->setRowCount(0);

            while (query.next()) {
                int id = query.value(0).toInt();
                QString nom = query.value(1).toString();
                QString prenom = query.value(2).toString();
                QString genre = query.value(3).toString();
                QString date = query.value(4).toString();
                int tel = query.value(5).toInt();
                QString dossier = query.value(6).toString();

                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
                tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
                tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
                tableWidget->setItem(row, 3, new QTableWidgetItem(genre));
                tableWidget->setItem(row, 4, new QTableWidgetItem(date));
                tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(tel)));
                tableWidget->setItem(row, 6, new QTableWidgetItem(dossier));
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
            query.prepare("SELECT * FROM PATIENT WHERE id = :id OR nom LIKE :nom ORDER BY nom ASC");
            query.bindValue(":id", id);
            query.bindValue(":nom", "%" + nom + "%");
        } else if (id > 0) {
            query.prepare("SELECT * FROM PATIENT WHERE id = :id ORDER BY nom ASC");
            query.bindValue(":id", id);
        } else if (!nom.isEmpty()) {
            query.prepare("SELECT * FROM PATIENT WHERE nom LIKE :nom ORDER BY nom ASC");
            query.bindValue(":nom", "%" + nom + "%");
        } else {
            query.prepare("SELECT * FROM PATIENT ORDER BY nom ASC");
        }

        if (query.exec()) {
            tableWidget->setRowCount(0);

            while (query.next()) {
                int patientId = query.value(0).toInt();
                QString patientNom = query.value(1).toString();
                QString patientPrenom = query.value(2).toString();
                QString patientGenre = query.value(3).toString();
                QString patientDate = query.value(4).toString();
                int patientTel = query.value(5).toInt();
                QString patientDossier = query.value(6).toString();

                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(patientId)));
                tableWidget->setItem(row, 1, new QTableWidgetItem(patientNom));
                tableWidget->setItem(row, 2, new QTableWidgetItem(patientPrenom));
                tableWidget->setItem(row, 3, new QTableWidgetItem(patientGenre));
                tableWidget->setItem(row, 4, new QTableWidgetItem(patientDate));
                tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(patientTel)));
                tableWidget->setItem(row, 6, new QTableWidgetItem(patientDossier));
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
        query.prepare("SELECT * FROM PATIENT WHERE id = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            // Récupérer les données du patient
            patientData["id"] = query.value(0).toString();
            patientData["nom"] = query.value(1).toString();
            patientData["prenom"] = query.value(2).toString();
            patientData["genre"] = query.value(3).toString();
            patientData["date"] = query.value(4).toString();
            patientData["tel"] = query.value(5).toString();
            patientData["dossier"] = query.value(6).toString();
        } else {
            qDebug() << "Erreur lors de la récupération des données du patient :" << query.lastError().text();
        }
    } else {
        qDebug() << "Impossible de se connecter à la base de données.";
    }

    return patientData;
}
