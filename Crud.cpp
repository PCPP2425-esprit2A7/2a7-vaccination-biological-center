#include "connection.h"
#include "Crud.h"
#include <QDebug>
#include <QTableWidget>

Crud::Crud(){}

Crud::Crud(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel) {
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->genre = genre;
    this->date = date;
    this->dossier = dossier;
    this->tel = tel;
}

void Crud::add_patient(QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("INSERT INTO PATIENT(id, NOM, PRENOM, GENRE, DATE_NAISSANCE, TEL, DOSSIER) "
                       "VALUES (:id, :nom, :prenom, :genre, :date, :tel, :dossier)");
        thisdb.bindValue(":id", id); // Lier la valeur de l'identifiant.
        thisdb.bindValue(":nom", nom);
        thisdb.bindValue(":prenom", prenom);
        thisdb.bindValue(":genre", genre);
        thisdb.bindValue(":date", date);
        thisdb.bindValue(":tel", tel);
        thisdb.bindValue(":dossier", dossier);

        if (thisdb.exec()) {
            // Si la requête s'exécute avec succès, ajouter le patient au QTableWidget
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);

            // Ajouter les données du patient au QTableWidget
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id))); // Add id
            tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
            tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
            tableWidget->setItem(row, 3, new QTableWidgetItem(genre));
            tableWidget->setItem(row, 4, new QTableWidgetItem(date));
            tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(tel))); // Convert tel to QString
            tableWidget->setItem(row, 6, new QTableWidgetItem(dossier));

            qDebug() << "Patient added successfully to both database and table widget.";
        } else {
            qDebug() << "Failed to execute query:" << thisdb.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}


void Crud::delete_patient(int id, QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("DELETE FROM PATIENT WHERE id = :id");
        thisdb.bindValue(":id", id);

        if (thisdb.exec()) {
            qDebug() << "Patient with ID" << id << "deleted successfully from the database.";

            // Remove the patient from the QTableWidget
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                QTableWidgetItem *item = tableWidget->item(row, 0); // Assuming ID is in the first column
                if (item && item->text().toInt() == id) {
      tableWidget->removeRow(row);
                    qDebug() << "Patient with ID" << id << "removed from the table widget.";
                    break; // Exit loop after removing
                }
            }
        } else {
            qDebug() << "Deletion failed: " << thisdb.lastError().text();
        }
    } else {
        qDebug() << "Problem connecting to the database.";
    }
}



void Crud::update_patient(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel, QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // 1. Récupérer les anciennes données du patient
        QSqlQuery query(db);
        query.prepare("SELECT NOM, PRENOM, GENRE, DATE_NAISSANCE, TEL, DOSSIER FROM PATIENT WHERE id = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            QString old_nom = query.value(0).toString();
            QString old_prenom = query.value(1).toString();
            QString old_genre = query.value(2).toString();
            QString old_date = query.value(3).toString();
            int old_tel = query.value(4).toInt();
            QString old_dossier = query.value(5).toString();

            // 2. Garder les anciennes valeurs si l'utilisateur ne remplit pas un champ
            if (nom.isEmpty()) nom = old_nom;
            if (prenom.isEmpty()) prenom = old_prenom;
            if (genre.isEmpty()) genre = old_genre;
            if (date.isEmpty()) date = old_date;
            if (dossier.isEmpty()) dossier = old_dossier;
            if (tel == 0) tel = old_tel;

            // 3. Mise à jour avec les nouvelles valeurs
            QSqlQuery updateQuery(db);
            updateQuery.prepare("UPDATE PATIENT SET NOM = :nom, PRENOM = :prenom, GENRE = :genre, DATE_NAISSANCE = :date, TEL = :tel, DOSSIER = :dossier WHERE id = :id");
            updateQuery.bindValue(":id", id);
            updateQuery.bindValue(":nom", nom);
            updateQuery.bindValue(":prenom", prenom);
            updateQuery.bindValue(":genre", genre);
            updateQuery.bindValue(":date", date);
            updateQuery.bindValue(":tel", tel);
            updateQuery.bindValue(":dossier", dossier);

            if (updateQuery.exec()) {
                qDebug() << "Patient mis à jour avec succès.";

                // 4. Mise à jour de l'affichage dans QTableWidget
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
            } else {
                qDebug() << "Échec de la mise à jour : " << updateQuery.lastError().text();
            }
        } else {
            qDebug() << "Impossible de récupérer les anciennes données du patient.";
        }
    } else {
        qDebug() << "Problème de connexion à la base de données.";
    }
}






