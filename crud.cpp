#include "connection.h"
#include "Crud.h"
#include <QDebug>
#include <QTableWidget>

// Constructor implementation
Crud::Crud(){}

Crud::Crud(int id, QString name, QString email, int phone,
           QString address, QString password, QString role,
           int salary, QString rfid_uid)
    : IDE(id), NOME(name), EMAILE(email), TELE(phone),
    ADRESSEE(address), MDPE(password), ROLEE(role),
    SALAIREE(salary), RFID_UID(rfid_uid)  // Updated constructor
{
    // No additional implementation needed
}

// Add user to database and table
void Crud::add_utilisateur(QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO EMPLOYES (IDE, NOME, EMAILE, TELE, ADRESSEE, MDPE, ROLEE, SALAIREE, RFID_UID) "
                      "VALUES (:ide, :nom, :email, :tele, :adresse, :mdp, :role, :salaire, :rfid)");

        query.bindValue(":ide", IDE);
        query.bindValue(":nom", NOME);
        query.bindValue(":email", EMAILE);
        query.bindValue(":tele", TELE);
        query.bindValue(":adresse", ADRESSEE);
        query.bindValue(":mdp", MDPE);
        query.bindValue(":role", ROLEE);
        query.bindValue(":salaire", SALAIREE);
        query.bindValue(":rfid", RFID_UID);  // Bind RFID UID

        if (query.exec()) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);

            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(IDE)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(NOME));
            tableWidget->setItem(row, 2, new QTableWidgetItem(EMAILE));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(TELE)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(ADRESSEE));
            tableWidget->setItem(row, 5, new QTableWidgetItem(MDPE));
            tableWidget->setItem(row, 6, new QTableWidgetItem(ROLEE));
            tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(SALAIREE)));
            tableWidget->setItem(row, 8, new QTableWidgetItem(RFID_UID));  // Display RFID UID

            qDebug() << "Utilisateur added successfully!";
        } else {
            qDebug() << "Add failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Delete user by IDE
void Crud::delete_utilisateur(int IDE, QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM EMPLOYES WHERE IDE = :ide");
        query.bindValue(":ide", IDE);

        if (query.exec()) {
            // Remove from table widget
            for (int i = 0; i < tableWidget->rowCount(); ++i) {
                if (tableWidget->item(i, 0)->text().toInt() == IDE) {
                    tableWidget->removeRow(i);
                    break;
                }
            }
            qDebug() << "Utilisateur deleted successfully!";
        } else {
            qDebug() << "Delete failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Update user information
void Crud::update_utilisateur(int IDE) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("UPDATE EMPLOYES SET "
                      "NOME = :nom, "
                      "EMAILE = :email, "
                      "TELE = :tele, "
                      "ADRESSEE = :adresse, "
                      "MDPE = :mdp, "
                      "ROLEE = :role, "
                      "SALAIREE = :salaire, "
                      "RFID_UID = :rfid "
                      "WHERE IDE = :ide");

        query.bindValue(":ide", IDE);
        query.bindValue(":nom", NOME);
        query.bindValue(":email", EMAILE);
        query.bindValue(":tele", TELE);
        query.bindValue(":adresse", ADRESSEE);
        query.bindValue(":mdp", MDPE);
        query.bindValue(":role", ROLEE);
        query.bindValue(":salaire", SALAIREE);
        query.bindValue(":rfid", RFID_UID);  // Bind RFID UID

        if (query.exec()) {
            qDebug() << "Utilisateur updated successfully!";
        } else {
            qDebug() << "Update failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Load all users
void Crud::load_utilisateur_data(QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query("SELECT * FROM EMPLOYES ORDER BY IDE", db);

        while (query.next()) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);

            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDE").toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOME").toString()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("EMAILE").toString()));
            tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("TELE").toString()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ADRESSEE").toString()));
            tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MDPE").toString()));
            tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("ROLEE").toString()));
            tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("SALAIREE").toString()));
            tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("RFID_UID").toString()));  // Show RFID UID
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Search by name
void Crud::load_utilisateur_byName(const QString &name, QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM EMPLOYES WHERE NOME LIKE :name ORDER BY IDE");
        query.bindValue(":name", "%" + name + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDE").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOME").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("EMAILE").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("TELE").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ADRESSEE").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MDPE").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("ROLEE").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("SALAIREE").toString()));
                tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("RFID_UID").toString()));  // Show RFID UID
            }
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Search by role
void Crud::load_utilisateur_byRole(const QString &role, QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM EMPLOYES WHERE ROLEE LIKE :role ORDER BY IDE");
        query.bindValue(":role", "%" + role + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDE").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOME").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("EMAILE").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("TELE").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ADRESSEE").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MDPE").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("ROLEE").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("SALAIREE").toString()));
                tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("RFID_UID").toString()));  // Show RFID UID
            }
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Sort users (optional)
void Crud::load_sorted_utilisateur(QTableWidget *tableWidget, const QString &sortType) {
    tableWidget->setRowCount(0);
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM EMPLOYES ORDER BY " + sortType);

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDE").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOME").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("EMAILE").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("TELE").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ADRESSEE").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MDPE").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("ROLEE").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("SALAIREE").toString()));
                tableWidget->setItem(row, 8, new QTableWidgetItem(query.value("RFID_UID").toString()));  // Show RFID UID
            }
        }
    } else {
        qDebug() << "Database connection failed";
    }
}

// Login function
bool Crud::login(const QString &email, const QString &password) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM EMPLOYES WHERE EMAILE = :email AND MDPE = :mdp");
        query.bindValue(":email", email);
        query.bindValue(":mdp", password);

        if (query.exec() && query.next()) {
            return true;
        }
    }
    return false;
}
