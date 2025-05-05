#include "connection.h"
#include "Crud.h"
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlRecord>
#include <QFile>
#include <QByteArray>
//includes_vaccins_jihed
#include <QSqlQuery>
#include <QSqlQueryModel>
// chat includes
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
// haw fi khatrek
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlRecord>
#include <QFile>
#include <QByteArray>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QHeaderView>
#include <QWidget>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QPageSize>
#include <QTableView>
#include <QtSvg/QSvgGenerator>
#include <QRandomGenerator>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QDate>
#include <QPdfWriter>
#include <QPixmap>
#include <QRect>
#include <QFont>





//Employe_taherrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
int CrudE::idN = 0;
QString CrudE::roleN = "";

// Constructor implementation
CrudE::CrudE(){}

CrudE::CrudE(int id, QString name, QString email, int phone,
           QString address, QString password, QString role,
           int salary, QString rfid_uid)
    : IDE(id), NOME(name), EMAILE(email), TELE(phone),
    ADRESSEE(address), MDPE(password), ROLEE(role),
    SALAIREE(salary), RFID_UID(rfid_uid)  // Updated constructor
{
    // No additional implementation needed
}

// Add user to database and table
void CrudE::add_utilisateur(QTableWidget *tableWidget) {
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
void CrudE::delete_utilisateur(int IDE, QTableWidget *tableWidget) {
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
void CrudE::update_utilisateur(int IDE) {
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
void CrudE::load_utilisateur_data(QTableWidget *tableWidget) {
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
void CrudE::load_utilisateur_byName(const QString &name, QTableWidget *tableWidget) {
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
void CrudE::load_utilisateur_byRole(const QString &role, QTableWidget *tableWidget) {
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
void CrudE::load_sorted_utilisateur(QTableWidget *tableWidget, const QString &sortType) {
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
bool CrudE::login(const QString &email, const QString &password, int &idN, QString &roleN) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM EMPLOYES WHERE EMAILE = :email AND MDPE = :mdp");
        query.bindValue(":email", email);
        query.bindValue(":mdp", password);

        if (query.exec() && query.next()) {
            idN = query.value("IDE").toInt();
            roleN = query.value("ROLEE").toString();
            return true;
        }
    }
    return false;
}








//recherche_abiddddddddddddddddddddddddddddddddddddddddddddddddddd





CrudR::CrudR(){}

CrudR::CrudR(int IDR, QString TITRER, QString CLASSR, QString DESCR, QString DATEDR, QString DATEFR, int EMPLOYE) {
    this->IDR = IDR;
    this->TITRER = TITRER;
    this->CLASSR = CLASSR;
    this->DESCR = DESCR;
    this->DATEDR = DATEDR;
    this->DATEFR = DATEFR;
    this->EMPLOYE= EMPLOYE;
}

bool CrudR::add_recherche(QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("INSERT INTO RECHERCHE (TITRER, CLASSR, DESCR, DATEDR, DATEFR, EMPLOYE) "
                       "VALUES (:TITRER, :CLASSR, :DESCR, TO_DATE(:DATEDR, 'YYYY-MM-DD'), TO_DATE(:DATEFR, 'YYYY-MM-DD'), :EMPLOYE)");

        thisdb.bindValue(":TITRER", TITRER);
        thisdb.bindValue(":CLASSR", CLASSR);
        thisdb.bindValue(":DESCR", DESCR);
        thisdb.bindValue(":DATEDR", DATEDR);
        thisdb.bindValue(":DATEFR", DATEFR);
        thisdb.bindValue(":EMPLOYE", CrudE::idN);


        if (thisdb.exec()) {
            int newId = 0;
            QSqlQuery getIdQuery(db);
            getIdQuery.prepare("SELECT MAX(IDR) FROM RECHERCHE");
            if (getIdQuery.exec() && getIdQuery.next()) {
                newId = getIdQuery.value(0).toInt();
                qDebug() << "Got new ID:" << newId;
            } else {
                qDebug() << "Failed to get ID:" << getIdQuery.lastError().text();
            }
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(newId)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(TITRER));
            tableWidget->setItem(row, 2, new QTableWidgetItem(CLASSR));
            tableWidget->setItem(row, 3, new QTableWidgetItem(DESCR));
            tableWidget->setItem(row, 4, new QTableWidgetItem(DATEDR));
            tableWidget->setItem(row, 5, new QTableWidgetItem(DATEFR));

            qDebug() << "Recherche added successfully to both database and table widget.";
            return true;
        } else {
            qDebug() << "Failed to execute query:" << thisdb.lastError().text();
            qDebug() << "SQL:" << thisdb.lastQuery();
            return false;
        }
    } else {
        qDebug() << "Failed to open database.";
        return false;
    }
}

void CrudR::delete_recherche(int IDR, QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // Check if the current user is the owner
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT EMPLOYE FROM RECHERCHE WHERE IDR = :IDR");
        checkQuery.bindValue(":IDR", IDR);

        if (checkQuery.exec() && checkQuery.next()) {
            int employeId = checkQuery.value(0).toInt();
            if (employeId != CrudE::idN) {
                qDebug() << "Deletion denied: current user is not the owner of IDR" << IDR;
                QMessageBox::warning(nullptr, "Accès refusé", "Vous n'avez pas la permission de supprimer cette recherche.");
                return;
            }
        } else {
            qDebug() << "Failed to check EMPLOYE for IDR" << IDR << ":" << checkQuery.lastError().text();
            return;
        }

        // Proceed with deletion
        QSqlQuery thisdb(db);
        thisdb.prepare("DELETE FROM RECHERCHE WHERE IDR = :IDR");
        thisdb.bindValue(":IDR", IDR);

        if (thisdb.exec()) {
            qDebug() << "Recherche with IDR" << IDR << "deleted successfully from the database.";
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                QTableWidgetItem *item = tableWidget->item(row, 0);
                if (item && item->text().toInt() == IDR) {
                    tableWidget->removeRow(row);
                    qDebug() << "Recherche with IDR" << IDR << "removed from the table widget.";
                    break;
                }
            }
        } else {
            qDebug() << "Deletion failed: " << thisdb.lastError().text();
        }
    } else {
        qDebug() << "Problem connecting to the database.";
    }
}



void CrudR::update_recherche(int IDR) {
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        // Step 1: Check if EMPLOYE matches idN
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT EMPLOYE FROM RECHERCHE WHERE IDR = :IDR");
        checkQuery.bindValue(":IDR", IDR);

        if (checkQuery.exec() && checkQuery.next()) {
            int employeId = checkQuery.value("EMPLOYE").toInt();

            if (employeId != CrudE::idN) {
                qDebug() << "Permission denied: EMPLOYE doesn't match idN.";
                QMessageBox::warning(nullptr, "Accès refusé", "Vous n'avez pas la permission de modifier cette recherche.");
                return;
            }
        } else {
            qDebug() << "Échec de la vérification de l'EMPLOYE :" << checkQuery.lastError().text();
            return;
        }

        // Step 2: Proceed with update
        QSqlQuery thisdb(db);
        thisdb.prepare("UPDATE RECHERCHE SET TITRER = :TITRER, CLASSR = :CLASSR, "
                       "DESCR = :DESCR, DATEDR = TO_DATE(:DATEDR, 'YYYY-MM-DD'), "
                       "DATEFR = TO_DATE(:DATEFR, 'YYYY-MM-DD'), EMPLOYE = :EMPLOYE "
                       "WHERE IDR = :IDR");

        thisdb.bindValue(":IDR", IDR);
        thisdb.bindValue(":TITRER", TITRER);
        thisdb.bindValue(":CLASSR", CLASSR);
        thisdb.bindValue(":DESCR", DESCR);
        thisdb.bindValue(":DATEDR", DATEDR);
        thisdb.bindValue(":DATEFR", DATEFR);
        thisdb.bindValue(":EMPLOYE", CrudE::idN);

        if (thisdb.exec()) {
            qDebug() << "Recherche with IDR" << IDR << "updated successfully.";
        } else {
            qDebug() << "Update failed: " << thisdb.lastError().text();
        }
    } else {
        qDebug() << "Problem connecting to the database.";
    }
}


void CrudR::load_recherche_data(QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDR, TITRER, CLASSR, DESCR, "
                      "TO_CHAR(DATEDR, 'YYYY-MM-DD') as DATEDR, "
                      "TO_CHAR(DATEFR, 'YYYY-MM-DD') as DATEFR FROM RECHERCHE ORDER BY IDR");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);
                int id = query.value("IDR").toInt();
                QString title = query.value("TITRER").toString();
                QString classification = query.value("CLASSR").toString();
                QString description = query.value("DESCR").toString();
                QString startDate = query.value("DATEDR").toString();
                QString endDate = query.value("DATEFR").toString();
                QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(id));
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);
                tableWidget->setItem(row, 1, new QTableWidgetItem(title));
                tableWidget->setItem(row, 2, new QTableWidgetItem(classification));
                tableWidget->setItem(row, 3, new QTableWidgetItem(description));
                tableWidget->setItem(row, 4, new QTableWidgetItem(startDate));
                tableWidget->setItem(row, 5, new QTableWidgetItem(endDate));
            }
            qDebug() << "Successfully loaded" << tableWidget->rowCount() << "records from database";
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void CrudR::load_recherche_byTitle(const QString &title, QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDR, TITRER, CLASSR, DESCR, "
                      "TO_CHAR(DATEDR, 'YYYY-MM-DD') as DATEDR, "
                      "TO_CHAR(DATEFR, 'YYYY-MM-DD') as DATEFR "
                      "FROM RECHERCHE WHERE TITRER LIKE :title ORDER BY IDR");
        query.bindValue(":title", "%" + title + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDR").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TITRER").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("CLASSR").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DESCR").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATEDR").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("DATEFR").toString()));
            }
            qDebug() << "Search by Title loaded" << tableWidget->rowCount() << "results.";
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void CrudR::load_recherche_byClass(const QString &classification, QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDR, TITRER, CLASSR, DESCR, "
                      "TO_CHAR(DATEDR, 'YYYY-MM-DD') as DATEDR, "
                      "TO_CHAR(DATEFR, 'YYYY-MM-DD') as DATEFR "
                      "FROM RECHERCHE WHERE CLASSR LIKE :classification ORDER BY IDR");
        query.bindValue(":classification", "%" + classification + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDR").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TITRER").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("CLASSR").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DESCR").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATEDR").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("DATEFR").toString()));
            }
            qDebug() << "Search by Classification loaded" << tableWidget->rowCount() << "results.";
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void CrudR::load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType) {
    if (sortType == "Show All") {
        load_recherche_data(tableWidget);
        return;
    }
    if (sortType== "my research"){
        load_recherche_byEmployee(tableWidget);
        return;
    }

    tableWidget->setRowCount(0);
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        QString queryString;

        if (sortType == "Title (A-Z)") {
            queryString = "SELECT * FROM RECHERCHE ORDER BY TITRER ASC";
        } else if (sortType == "Title (Z-A)") {
            queryString = "SELECT * FROM RECHERCHE ORDER BY TITRER DESC";
        } else if (sortType == "Classification (BSL-4 → BSL-1)") {
            queryString = "SELECT * FROM RECHERCHE ORDER BY "
                          "CASE CLASSR WHEN 'BSL-4' THEN 1 WHEN 'BSL-3' THEN 2 "
                          "WHEN 'BSL-2' THEN 3 WHEN 'BSL-1' THEN 4 ELSE 5 END ASC";
        } else if (sortType == "Classification (BSL-1 → BSL-4)") {
            queryString = "SELECT * FROM RECHERCHE ORDER BY "
                          "CASE CLASSR WHEN 'BSL-4' THEN 1 WHEN 'BSL-3' THEN 2 "
                          "WHEN 'BSL-2' THEN 3 WHEN 'BSL-1' THEN 4 ELSE 5 END DESC";
        } else {
            queryString = "SELECT * FROM RECHERCHE ORDER BY IDR";
        }

        query.prepare(queryString);
        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDR").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TITRER").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("CLASSR").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DESCR").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATEDR").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("DATEFR").toString()));
            }
            qDebug() << "Sorting applied: " << sortType;
        } else {
            qDebug() << "Sorting query failed: " << query.lastError().text();
        }
    } else {
        qDebug() << "Database connection failed.";
    }
}

void CrudR::load_recherche_byEmployee(QTableWidget *tableWidget) {
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDR, TITRER, CLASSR, DESCR, "
                      "TO_CHAR(DATEDR, 'YYYY-MM-DD') as DATEDR, "
                      "TO_CHAR(DATEFR, 'YYYY-MM-DD') as DATEFR "
                      "FROM RECHERCHE WHERE EMPLOYE = :employe ORDER BY IDR");

        query.bindValue(":employe", CrudE::idN); // Current employee's ID

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDR").toString()));
                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TITRER").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("CLASSR").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DESCR").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DATEDR").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("DATEFR").toString()));
            }
            qDebug() << "Search by EMPLOYE loaded" << tableWidget->rowCount() << "results.";
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}







//patient_YSSSSSSSSSSSSSSSSSSSS777777777777777777777777777








Crudp::Crudp() {}

Crudp::Crudp(int id, QString nom, QString prenom, QString genre, QString date, QString dossier, int tel) {
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->genre = genre;
    this->date = date;
    this->dossier = dossier;
    this->tel = tel;
}

void Crudp::add_patient(int id, const QString &nom, const QString &prenom, const QString &genre, const QString &date,
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

bool Crudp::delete_patient_by_id(int id, QTableWidget *tableWidget) {
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

void Crudp::update_patient(int id, const QString &nom, const QString &prenom, const QString &genre,
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

void Crudp::load_patients(QTableWidget *tableWidget) {
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

void Crudp::search_patient(int id, const QString &nom, QTableWidget *tableWidget) {
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

QMap<QString, QString> Crudp::getPatientById(int id) {
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

void Crudp::load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType) {
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





//vaccin_Jihedddddddddddddddddddddddddddddddddddddddddddddddddddddd





vaccin::vaccin()
{
    // Initialisation des attributs (facultatif)
    id = 0;
    validation = 0;
    temperature=0;
    nom = "";
    type = "";
    maladie = "";
    fabrication = "";
    description = "";
}

// Constructeur paramétré
vaccin::vaccin( QString nom, QString type, QString maladie, QString fabrication, int validation, QString description,double temperature, int EMPLOYE)
{
    this->id = id;
    this->nom = nom;
    this->type = type;
    this->maladie = maladie;
    this->fabrication = fabrication;
    this->validation = validation;
    this->description = description;
    this->temperature = temperature;
    this->EMPLOYE = EMPLOYE;
}

// Méthode pour ajouter un vaccin à la base de données
bool vaccin::ajouterv()
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return false;
    }

    QSqlQuery query(db);  // Utilise explicitement la bonne connexion

    // Convertir l'attribut id en QString
    // Utiliser this-> pour éviter l'ambiguïté
    // QString validationStr = QString::number(this->validation);

    // Préparer la requête SQL
    query.prepare("INSERT INTO VACCINS(NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION,TEMPERATURE,EMPLOYE) "
                  "VALUES ( :nom, :type, :maladie, :fabrication, :validation, :description, :temperature , :EMPLOYE)");

    // Lier les valeurs aux paramètres de la requête

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":fabrication", fabrication);
    query.bindValue(":validation", validation);
    query.bindValue(":description", description);
    query.bindValue(":temperature", temperature);
    query.bindValue(":EMPLOYE", EMPLOYE);

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
QSqlQueryModel* vaccin::afficherv()
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return nullptr;

    }

    QSqlQuery query(db);  // Utilise explicitement la bonne connexion

    QSqlQueryModel* model = new QSqlQueryModel();

    // Définir la requête SQL pour sélectionner tous les vaccins
    model->setQuery("SELECT * FROM VACCINS", db);

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Disease"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Production date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Validation Period"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Temperature"));
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



bool vaccin::supprimerv(int id)
{
    int employeId;
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return false;
    }

    QSqlQuery query(db);


    query.prepare("SELECT EMPLOYE FROM VACCINS WHERE ID = :id");
    query.bindValue(":id", id); // Remplacez 'id' par l'ID du vaccin recherché

    if (query.exec() && query.next()) {
        employeId = query.value("EMPLOYE").toInt();
        qDebug() << "Employé correspondant à l'ID:" << employeId;
        // Vous pouvez maintenant utiliser employeId comme vous le souhaitez
    } else {
        qDebug() << "Aucun employé trouvé pour cet ID ou erreur dans la requête.";
    }


    if (employeId != CrudE::idN && "Chercheur" == CrudE::roleN){

            //QMessageBox::critical(nullptr, "Erreur", "ya bro les vaccins mehomch besmkk tajmch tsupprimiii.");
            QMessageBox::warning(nullptr, "Accès refusé", "Vous ne pouvez pas modifier un vaccin créé par un autre chercheur.");


        return false;
    }

    // Étape 1 : récupérer les données actuelles
    query.prepare("SELECT nom, type, maladie, fabrication, validation, description, temperature FROM VACCINS WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur récupération du vaccin avant suppression :" << query.lastError().text();
        return false;
    }

    // Étape 2 : construire les QStringList
    QStringList champs = {"Nom", "Type", "Maladie", "Fabrication", "Validation", "Description", "Temperature"};
    QStringList anciennesValeurs = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"};

    QStringList nouvellesValeurs;
    nouvellesValeurs << query.value(0).toString(); // nom
    nouvellesValeurs << query.value(1).toString(); // type
    nouvellesValeurs << query.value(2).toString(); // maladie
    nouvellesValeurs << query.value(3).toString(); // fabrication
    nouvellesValeurs << QString::number(query.value(4).toInt()); // validation
    nouvellesValeurs << query.value(5).toString(); // description
    nouvellesValeurs << QString::number(query.value(6).toDouble(), 'f', 2); // temperature avec 2 décimales


    QStringList action = {"SUPPRIMER"};

    // Étape 3 : appeler la fonction pour ajouter à l’historique
    if (!ajouterHistoriquev(id, champs, anciennesValeurs, nouvellesValeurs, action)) {
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














bool vaccin::chargerVaccinv(int id, QString &nom, QString &type, QString &maladie, QString &fabrication, int &validation, QString &description,double &temperature)
{
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return false;
    }

    QSqlQuery query(db);
    // Convertir l'ID en QString
    //QString idStr = QString::number(id);

    // Préparer la requête SQL pour sélectionner le vaccin
    query.prepare("SELECT  NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION, TEMPERATURE FROM VACCINS WHERE id = :id");
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
        temperature = query.value(6).toDouble();


        return true;  // Vaccin trouvé
    }
    else
    {
        qDebug() << "Vaccin non trouvé ou erreur de requête :" << query.lastError().text();
        return false;  // Vaccin non trouvé ou erreur
    }
}






bool vaccin::ajouterHistoriquev(int idVaccin,
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

    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return false;
    }

    QSqlQuery query(db);

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

bool vaccin::modifierv(int id, const QString &nom, const QString &type, const QString &maladie,
                       const QString &fabrication, int validation, const QString &description,const double &temperature)
{
    int employeId;
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // Step 1: Check if EMPLOYE matches idN
        qDebug() << "La base de données vac_connection est ouverte.";
        }
    QSqlQuery query(db);
    query.prepare("SELECT EMPLOYE FROM VACCINS WHERE ID = :id");
    query.bindValue(":id", id); // Remplacez 'id' par l'ID du vaccin recherché

    if (query.exec() && query.next()) {
         employeId = query.value("EMPLOYE").toInt();
        qDebug() << "Employé correspondant à l'ID:" << employeId;
        // Vous pouvez maintenant utiliser employeId comme vous le souhaitez
    } else {
        qDebug() << "Aucun employé trouvé pour cet ID ou erreur dans la requête.";
    }


    if (employeId != CrudE::idN && "Chercheur" == CrudE::roleN ){
        //QMessageBox::critical(nullptr, "Erreur", "ya bro les vaccins mehomch besmkk tajmch tmodifi.");
        QMessageBox::warning(nullptr, "Accès refusé", "Vous ne pouvez pas modifier un vaccin créé par un autre chercheur.");


        return false;
    }

    query.prepare("SELECT NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION, TEMPERATURE FROM VACCINS WHERE ID = :id");
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
    double ancienneTemperature = query.value(6).toDouble();


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
    if (ancienneTemperature != temperature) {
        champsModifies << "Temperature";
        anciennesValeurs << QString::number(ancienneTemperature, 'f', 2); // par exemple, 2 décimales
        nouvellesValeurs << QString::number(temperature, 'f', 2);

    }


    action << "UPDATE";

    // Enregistrer les changements en une seule ligne s’il y a eu des modifications
    if (!champsModifies.isEmpty()) {
        ajouterHistoriquev(id, champsModifies, anciennesValeurs, nouvellesValeurs,action);
    }

    query.prepare("UPDATE VACCINS SET nom = :nom, type = :type, maladie = :maladie, "
                  "fabrication = :fabrication, validation = :validation, description = :description, temperature= :temperature WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":fabrication", fabrication);
    query.bindValue(":validation", validation);
    query.bindValue(":description", description);
    query.bindValue(":temperature", temperature);

    if (query.exec()) {
        qDebug() << "Vaccin modifié avec succès !";
        return true;
    } else {
        qDebug() << "Erreur lors de la modification du vaccin :" << query.lastError().text();
        return false;
    }
}




QSqlQueryModel* vaccin::rechercherv(const QString &term, const QString &critere) {
    if (term.isEmpty()) {
        return nullptr;  // Ne rien faire si le champ est vide
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return nullptr;
    }

    QSqlQuery query(db);
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








/*QSqlQueryModel* vaccin::trierv(const QString& critere, bool ascendant) {
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
    QString queryString = QString("SELECT ID, NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION, TEMPERATURE FROM VACCINS ORDER BY %1 %2")
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
*/


QSqlQueryModel* vaccin::trierv(const QString& critere, bool ascendant) {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Vérifier que le critère est valide
    QString colonne;
    if (critere == "nom") {
        colonne = "NOM";
    } else if (critere == "date_fabrication") {
        colonne = "FABRICATION";
    } else if (critere == "duree_validation") {
        colonne = "VALIDATION";
        }
    else if (critere == "EMP") {
        colonne = "EMPLOYE";
    }
         else {
        qDebug() << "Critère de tri invalide :" << critere;
        delete model;
        return nullptr;
    }

    // Obtenir la base de données via la classe connection
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.isOpen()) {
        qDebug() << "La base de données main_connection n'est pas ouverte.";
        delete model;
        return nullptr;
    }

    // Construire et exécuter la requête via QSqlQuery
    QString queryString = QString("SELECT ID, NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION, TEMPERATURE FROM VACCINS ORDER BY %1 %2")
                              .arg(colonne)
                              .arg(ascendant ? "ASC" : "DESC");

    QSqlQuery query(db);
    if (!query.exec(queryString)) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        delete model;
        return nullptr;
    }

    // Associer la requête au modèle
    model->setQuery(query);

    // Vérifier les erreurs dans le modèle
    if (model->lastError().isValid()) {
        qDebug() << "Erreur dans QSqlQueryModel :" << model->lastError().text();
        delete model;
        return nullptr;
    }

    return model;
}



QSqlQueryModel* vaccin::trierMesVaccins() {
    QSqlQueryModel* model = new QSqlQueryModel();

    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.open()) {
        qDebug() << "Base de données non ouverte.";
        delete model;
        return nullptr;
    }

    QSqlQuery query(db);
    query.prepare("SELECT ID, NOM, TYPE, MALADIE, FABRICATION, VALIDATION, DESCRIPTION, TEMPERATURE "
                  "FROM VACCINS WHERE EMPLOYE = :emp");
    query.bindValue(":emp", CrudE::idN);

    if (!query.exec()) {
        qDebug() << "Erreur requête EMPLOYE:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur modèle SQL:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    return model;
}







QSqlQueryModel* vaccin::exporterPDFv(const QString& idVaccin) {


    QSqlQueryModel* model = new QSqlQueryModel();
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
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














QSqlQueryModel* vaccin::afficherHistoriquev(int idVaccin)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return nullptr;
    }

    QSqlQuery query(db);

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
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Modification date"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Modified field"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Old value"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("New value"));
    } else {
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Vaccine"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Modification date"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Changes"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Action"));
    }

    return model;
}






QSqlQuery vaccin::getVaccinsByValidationDurationv() {
    QSqlQueryModel* model = new QSqlQueryModel();
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return QSqlQuery(); // Retourne un QSqlQuery vide

    }

    QSqlQuery query(db);

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



QVector<QPair<QString, int>> vaccin::getStatistiquesParTypev() {
    QVector<QPair<QString, int>> stats;

    // Requête SQL pour récupérer le nombre de vaccins par type
    QSqlQueryModel* model = new QSqlQueryModel();
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return QVector<QPair<QString, int>>(); // retourne un vecteur vide

    }

    QSqlQuery query(db);
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





QStringList vaccin::getConcurrentsv(const QString &type, const QString &maladie, const QString &id)
{
    QStringList descriptionsConcurrents;  // Liste pour stocker les descriptions des concurrents
    QSqlQueryModel* model = new QSqlQueryModel();
    connection c;
    QSqlDatabase db = c.get_database();
    if (!db.isOpen()) {
        qDebug() << "La base de données vac_connection n'est pas ouverte.";
        return QStringList();  // retourne une liste vide proprement
    }

    QSqlQuery query(db);

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

// crud el boh

rendervous::rendervous(){}

rendervous::rendervous(QString date, int heure, int employe, int patient, int dur, QString status, int code )
{
    this->date = date;
    this->heure = heure;
    this->id_employe = employe;   // même variable, mais ira dans EMPLOYE
    this->id_patient = patient;   // même variable, mais ira dans PATIENT
    this->dur = dur;
    this->status = status;
    this->code_patient = (code == -1) ? QRandomGenerator::global()->bounded(1000, 9999) : code;

}



// Méthode d'ajout
bool rendervous::ajouter() {
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données.";
        return false;
    }

    // Vérifier si l'EMPLOYE existe
    QSqlQuery checkEmploye(db);
    checkEmploye.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE IDE = :ide");
    checkEmploye.bindValue(":ide", id_employe);
    if (!checkEmploye.exec() || !checkEmploye.next() || checkEmploye.value(0).toInt() == 0) {
        QMessageBox::warning(nullptr, "Erreur", "L'employé spécifié n'existe pas.");
        return false;
    }

    // Vérifier si le PATIENT existe
    QSqlQuery checkPatient(db);
    checkPatient.prepare("SELECT COUNT(*) FROM PATIENT WHERE ID = :id");
    checkPatient.bindValue(":id", id_patient);
    if (!checkPatient.exec() || !checkPatient.next() || checkPatient.value(0).toInt() == 0) {
        QMessageBox::warning(nullptr, "Erreur", "Le patient spécifié n'existe pas.");
        return false;
    }

    // Préparer la requête d'insertion
    QSqlQuery query(db);
    query.prepare("INSERT INTO rendezvous (date_rdv, heure, EMPLOYE, PATIENT, duree, status, code_patient) "
                  "VALUES (:date, :heure, :employe , :patient, :duree, :status, :code_patient)");

    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":employe", id_employe);
    query.bindValue(":patient", id_patient);
    query.bindValue(":duree", dur);
    query.bindValue(":status", status);
    query.bindValue(":code_patient", code_patient);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }

    return true;
}




// Méthode de suppression
bool rendervous::supprimer(int id) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données.";
        return false;
    }

    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT id FROM rendezvous WHERE id = :id");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec() && checkQuery.next()) {
        int employeId = checkQuery.value(0).toInt();
        if (employeId != CrudE::idN) {
            qDebug() << "Suppression refusée : utilisateur ≠ propriétaire du rendez-vous ID" << id;
            QMessageBox::warning(nullptr, "Accès refusé", "Vous n'avez pas la permission de supprimer ce rendez-vous.");
            return false;
        }
    } else {
        qDebug() << "Erreur lors de la vérification du propriétaire:" << checkQuery.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }

    return true;
}



// Méthode d'affichage
void rendervous::afficher(QTableWidget *table) {
    QSqlQuery query;  // Ne pas passer la requête dans le constructeur
    query.prepare("SELECT id, date_rdv, heure, duree, status, EMPLOYE, PATIENT FROM rendezvous ORDER BY date_rdv, heure");

    if (!query.exec()) {
        qDebug() << "Erreur lors du chargement des données:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Impossible de charger les rendez-vous.");
        return;
    }

    table->clear();
    table->setRowCount(0);
    table->setColumnCount(7);
    QStringList headers = {"ID", "Date", "Heure", "Durée", "Statut", "Employé", "Patient"};
    table->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        for (int col = 0; col < 7; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);  // empêche l'édition
            table->setItem(row, col, item);
        }
        ++row;
    }

    table->resizeColumnsToContents();
    table->setAlternatingRowColors(true);
    table->horizontalHeader()->setStretchLastSection(true);
}



// Méthode de modification
bool rendervous::modifier(int id) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données.";
        return false;
    }

    // Vérification que l'utilisateur est le propriétaire
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT EMPLOYE FROM rendezvous WHERE id = :id");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec() && checkQuery.next()) {
        int employeId = checkQuery.value(0).toInt();
        if (employeId != CrudE::idN) {
            qDebug() << "Modification refusée : l'utilisateur ≠ propriétaire du rendez-vous ID" << id;
            QMessageBox::warning(nullptr, "Accès refusé", "Vous n'avez pas la permission de modifier ce rendez-vous.");
            return false;
        }
    } else {
        qDebug() << "Échec de la vérification du propriétaire pour ID" << id << ":" << checkQuery.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE rendezvous SET "
                  "date_rdv = :date, "
                  "heure = :heure, "
                  "EMPLOYE = :employe, "
                  "PATIENT = :patient, "
                  "duree = :duree, "
                  "status = :status "
                  "WHERE id = :id");

    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":employe", id_employe);
    query.bindValue(":patient", id_patient);
    query.bindValue(":duree", dur);
    query.bindValue(":status", status);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }

    return true;
}



QSqlQueryModel * rendervous::search(const QString &id)
{
    connection c;
    QSqlDatabase db = c.get_database();

    if(db.open())  // Fixed: open() is a function, not a property
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query(db);

        // Fixed: using :id parameter (was :name)
        query.prepare("SELECT * FROM rendezvous WHERE ID LIKE :id");
        query.bindValue(":id", "%" + id + "%");  // Fixed parameter name

        if(!query.exec())  // Fixed condition (we want to check for failure)
        {
            qDebug() << "Query error:" << query.lastError().text();
            delete model;
            return nullptr;
        }

        model->setQuery(query);

        // Set header data (fixed Qt::Horizontal spelling)
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Heure"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Employe"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID Patient"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Duree"));  // Fixed spelling

        return model;
    }
    else
    {
        qDebug() << "Database connection error:" << db.lastError().text();
    }

    return nullptr;
}


void rendervous::sort(QTableWidget *table, bool ordreCroissant) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de se connecter à la base de données.");
        return;
    }

    QSqlQuery query(db);
    QString queryStr = "SELECT id, date_rdv, heure, duree, status, EMPLOYE, PATIENT "
                       "FROM rendezvous ORDER BY heure ";
    queryStr += ordreCroissant ? "ASC" : "DESC";

    if (!query.exec(queryStr)) {
        qDebug() << "Erreur lors du tri:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Échec du tri des rendez-vous.");
        return;
    }

    table->clear();
    table->setRowCount(0);
    table->setColumnCount(7);
    QStringList headers = {"ID", "Date", "Heure", "Durée", "Statut", "Employé", "Patient"};
    table->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        for (int col = 0; col < 7; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            table->setItem(row, col, item);
        }
        ++row;
    }

    table->resizeColumnsToContents();
    table->setAlternatingRowColors(true);
    table->horizontalHeader()->setStretchLastSection(true);
}


void rendervous::generateQRCode(int id, const QString &outputPath) {
    // Get appointment details
    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qDebug() << "Error fetching appointment data for QR code";
        return;
    }

    QString date = query.value("date_rdv").toString();
    int heure = query.value("heure").toInt();
    QString status = query.value("status").toString();
    int id_patient = query.value("PATIENT").toInt();

    // Create QR code content
    QString content = QString("ID:%1|DATE:%2|TIME:%3:00|PATIENT:%4|STATUS:%5")
                          .arg(id).arg(date).arg(heure).arg(id_patient).arg(status);

    // Use a simple QR implementation (actual implementation would use a library like qrencode)
    // Here's a placeholder that generates an SVG with the appointment details
    QSvgGenerator generator;
    generator.setFileName(outputPath);
    generator.setSize(QSize(200, 200));
    generator.setViewBox(QRect(0, 0, 200, 200));
    generator.setTitle(QString("Appointment QR Code #%1").arg(id));
    generator.setDescription(content);

    QPainter painter;
    painter.begin(&generator);

    // Draw a fake QR code (in a real implementation, use a QR code library)
    painter.fillRect(0, 0, 200, 200, Qt::white);
    painter.setPen(Qt::black);

    // Draw some patterns to simulate a QR code
    int blockSize = 10;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            // Create a deterministic pattern based on the appointment ID
            if ((i + j*id) % 3 == 0 || (i*j + id) % 5 == 0) {
                painter.fillRect(i*blockSize, j*blockSize, blockSize, blockSize, Qt::black);
            }
        }
    }

    // Add position detection patterns
    painter.fillRect(0, 0, 30, 30, Qt::black);
    painter.fillRect(170, 0, 30, 30, Qt::black);
    painter.fillRect(0, 170, 30, 30, Qt::black);

    painter.fillRect(10, 10, 10, 10, Qt::white);
    painter.fillRect(180, 10, 10, 10, Qt::white);
    painter.fillRect(10, 180, 10, 10, Qt::white);

    // Add tiny text at the bottom
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 6));
    painter.drawText(QRect(0, 185, 200, 15), Qt::AlignCenter,
                     QString("Appointment #%1").arg(id));

    painter.end();
}

bool rendervous::isAppointmentConflict(const QString &date, int newHour, int newDuration, int employeeId) {
    QSqlQuery query;
    query.prepare("SELECT heure, duree FROM rendezvous WHERE date_rdv = :date AND EMPLOYE = :employeeId");
    query.bindValue(":date", date);
    query.bindValue(":employeeId", employeeId);

    if (!query.exec()) {
        qDebug() << "Error while verifying conflict" << query.lastError().text();
        return false; // Ne bloque pas si erreur DB, mais tu peux return true si tu préfères
    }

    double newStart = newHour;
    double newEnd = newHour + static_cast<double>(newDuration) / 60.0;

    while (query.next()) {
        int existingHour = query.value("heure").toInt();
        int existingDuration = query.value("duree").toInt();
        double oldStart = existingHour;
        double oldEnd = existingHour + static_cast<double>(existingDuration) / 60.0;

        if (newStart < oldEnd && newEnd > oldStart) {
            qDebug() << "Conflict found with RDV de " << existingHour << " at" << oldEnd;
            return true;
        }
    }

    return false;
}

QSqlQueryModel* rendervous::prioriserPatients() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT PATIENT , COUNT(*) AS nb_absences "
                  "FROM rendezvous "
                  "WHERE status = 'Absent' "
                  "GROUP BY PATIENT "
                  "ORDER BY nb_absences DESC");

    if (!query.exec()) {
        qDebug() << "Erreur priorisation:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Patient"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre d'absences"));

    return model;
}

void rendervous::genererAutoRendezVousPourAbsents() {
    QSqlQuery getAbsents;
    getAbsents.prepare("SELECT DISTINCT PATIENT, EMPLOYE, date_rdv "
                       "FROM rendezvous "
                       "WHERE status = 'Absent'");

    if (!getAbsents.exec()) {
        qDebug() << "Erreur récupération absents:" << getAbsents.lastError().text();
        return;
    }

    int count = 0;

    while (getAbsents.next()) {
        int id_patient = getAbsents.value("PATIENT").toInt();
        int id_employe = getAbsents.value("EMPLOYE").toInt();
        QString oldDateStr = getAbsents.value("date_rdv").toString();

        // ⚠️ Format correct
        QDate oldDate = QDate::fromString(oldDateStr, "dd/MM/yyyy");
        if (!oldDate.isValid()) {
            qDebug() << "Date invalide : " << oldDateStr;
            continue;
        }

        QDate newDate = oldDate.addDays(1);
        QString newDateStr = newDate.toString("dd/MM/yyyy");
        int newHeure = 10;
        int duree = 30;

        if (!isAppointmentConflict(newDateStr, newHeure, duree, id_employe)) {
            QSqlQuery insert;
            insert.prepare("INSERT INTO rendezvous (date_rdv, heure, EMPLOYE, PATIENT, duree, status) "
                           "VALUES (:date, :heure, :employe, :patient, :duree, 'Reprogrammé')");

            insert.bindValue(":date", newDateStr);
            insert.bindValue(":heure", newHeure);
            insert.bindValue(":employe", id_employe);
            insert.bindValue(":patient", id_patient);
            insert.bindValue(":duree", duree);

            if (insert.exec()) {
                count++;
            } else {
                qDebug() << "Erreur insertion RDV : " << insert.lastError().text();
            }
        }
    }

    QMessageBox::information(nullptr, "Reprogrammation automatique",
                             QString::number(count) + " rendez-vous reprogrammés.");
}


QVector<QPair<int, int>> rendervous::getStatistiquesValidation() {
    QVector<QPair<int, int>> stats;

    QSqlQuery query;
    query.prepare("SELECT duree, COUNT(*) FROM rendezvous WHERE duree IS NOT NULL GROUP BY duree ORDER BY duree");

    if (query.exec()) {
        while (query.next()) {
            int duree = query.value(0).toInt();
            int count = query.value(1).toInt();
            stats.append(qMakePair(duree, count));
        }
    } else {
        qDebug() << "Erreur statistiques:" << query.lastError().text();
    }

    return stats;
}

QSqlQueryModel* rendervous::load_recherche_byEmployee(bool ordreCroissant)
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query(db);

        QString queryStr = "SELECT id AS \"ID\", "
                           "date_rdv AS \"Date\", "
                           "heure AS \"Heure\", "
                           "duree AS \"Durée\", "
                           "status AS \"Statut\", "
                           "EMPLOYE AS \"ID Employé\", "
                           "PATIENT AS \"ID Patient\" "
                           "FROM rendezvous" "WHERE EMPLOYE = :employe" "ORDER BY heure ";

        queryStr += ordreCroissant ? "ASC" : "DESC";

        query.prepare(queryStr);
        query.bindValue(":employe", CrudE::idN); // identifiant de l'employé courant

        if (!query.exec()) {
            qDebug() << "Query execution failed:" << query.lastError().text();
            delete model;
            return nullptr;
        }

        model->setQuery(query);

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Classe"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date début"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date fin"));

        qDebug() << "Recherche filtrée par employé chargée avec modèle (tri:"
                 << (ordreCroissant ? "ascendant" : "descendant") << ")";
        return model;
    } else {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return nullptr;
    }
}

QSqlQuery rendervous::getSortedByEmployee(int employeId) {
    connection c;
    QSqlDatabase db = c.get_database();

    QSqlQuery query(db);
    if (!db.open()) {
        qDebug() << "Connexion base échouée";
        return QSqlQuery(); // Requête vide
    }

    QString queryStr = "SELECT id, date_rdv, heure, duree, status, EMPLOYE, PATIENT "
                       "FROM rendezvous WHERE EMPLOYE = :empId ORDER BY date_rdv, heure";

    query.prepare(queryStr);
    query.bindValue(":empId", employeId);

    if (!query.exec()) {
        qDebug() << "Erreur tri employé:" << query.lastError().text();
    }

    return query;
}



#include <QSslSocket>
#include <QTextStream>
#include <QDebug>







//**********************************************FFFFFFFFFFFaaaaaresssssssssssssssssssss********************************************************************



equipement::equipement()
{
    nomeq = "";
    etateq = "";
    nbeq = 0;
    typeeq = "";
    tempmeq = QDate::currentDate();
    desceq = "";
    feq = "";
}

equipement::equipement(QString nomeq, QString etateq, int nbeq, QString typeeq, QDate tempmeq, QString desceq, QString feq)
{
    this->nomeq = nomeq;
    this->etateq = etateq;
    this->nbeq = nbeq;
    this->typeeq = typeeq;
    this->tempmeq = tempmeq;
    this->desceq = desceq;
    this->feq = feq;
}

bool equipement::ajouter(QTableWidget *tableWidget)
{
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO EQUIPEMENTS (NOMEQ, ETATEQ, NBEQ, TYPEEQ, TEMPMEQ, DESCEQ, FEQ) "
                      "VALUES (:nomeq, :etateq, :nbeq, :typeeq, TO_DATE(:tempmeq, 'YYYY-MM-DD'), :desceq, :feq)");

        query.bindValue(":nomeq", nomeq);
        query.bindValue(":etateq", etateq);
        query.bindValue(":nbeq", nbeq);
        query.bindValue(":typeeq", typeeq);
        query.bindValue(":tempmeq", tempmeq.toString("yyyy-MM-dd"));
        query.bindValue(":desceq", desceq);
        query.bindValue(":feq", feq);

        if (query.exec()) {
            int newId = 0;
            QSqlQuery getIdQuery(db);
            getIdQuery.prepare("SELECT MAX(IDEQ) FROM EQUIPEMENTS");
            if (getIdQuery.exec() && getIdQuery.next()) {
                newId = getIdQuery.value(0).toInt();
                qDebug() << "Got new ID:" << newId;
            } else {
                qDebug() << "Failed to get ID:" << getIdQuery.lastError().text();
            }

            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(newId)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(nomeq));
            tableWidget->setItem(row, 2, new QTableWidgetItem(etateq));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(nbeq)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(typeeq));
            tableWidget->setItem(row, 5, new QTableWidgetItem(tempmeq.toString("yyyy-MM-dd")));
            tableWidget->setItem(row, 6, new QTableWidgetItem(desceq));
            tableWidget->setItem(row, 7, new QTableWidgetItem(feq));

            qDebug() << "Equipment added successfully to both database and table widget.";
            return true;
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
            qDebug() << "SQL:" << query.lastQuery();
            return false;
        }
    } else {
        qDebug() << "Failed to open database.";
        return false;
    }
}

void equipement::delete_equipement(int id, QTableWidget *tableWidget)
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM EQUIPEMENTS WHERE IDEQ = :id");
        query.bindValue(":id", id);
        if (query.exec()) {
            qDebug() << "Equipment with ID" << id << "deleted successfully from the database.";
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                QTableWidgetItem *item = tableWidget->item(row, 0);
                if (item && item->text().toInt() == id) {
                    tableWidget->removeRow(row);
                    qDebug() << "Equipment with ID" << id << "removed from the table widget.";
                    break;
                }
            }
        } else {
            qDebug() << "Deletion failed: " << query.lastError().text();
        }
    } else {
        qDebug() << "Problem connecting to the database.";
    }
}

void equipement::update_equipement(int id)
{
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("UPDATE EQUIPEMENTS SET NOMEQ = :nomeq, ETATEQ = :etateq, "
                      "NBEQ = :nbeq, TYPEEQ = :typeeq, TEMPMEQ = TO_DATE(:tempmeq, 'YYYY-MM-DD'), "
                      "DESCEQ = :desceq, FEQ = :feq WHERE IDEQ = :id");
        query.bindValue(":id", id);
        query.bindValue(":nomeq", nomeq);
        query.bindValue(":etateq", etateq);
        query.bindValue(":nbeq", nbeq);
        query.bindValue(":typeeq", typeeq);
        query.bindValue(":tempmeq", tempmeq.toString("yyyy-MM-dd"));
        query.bindValue(":desceq", desceq);
        query.bindValue(":feq", feq);

        if (query.exec()) {
            qDebug() << "Equipment with ID" << id << "updated successfully.";
        } else {
            qDebug() << "Update failed: " << query.lastError().text();
        }
    } else {
        qDebug() << "Problem connecting to the database.";
    }
}

void equipement::load_equipement_data(QTableWidget *tableWidget)
{
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                      "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, "
                      "DESCEQ, FEQ FROM EQUIPEMENTS ORDER BY IDEQ");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                // Make ID non-editable
                QTableWidgetItem *idItem = new QTableWidgetItem(query.value("IDEQ").toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOMEQ").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("ETATEQ").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("NBEQ").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("TYPEEQ").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("TEMPMEQ").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("DESCEQ").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("FEQ").toString()));
            }
            qDebug() << "Successfully loaded" << tableWidget->rowCount() << "records from database";
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void equipement::load_equipement_byNom(const QString &nom, QTableWidget *tableWidget)
{
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                      "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, "
                      "DESCEQ, FEQ FROM EQUIPEMENTS WHERE NOMEQ LIKE :nom ORDER BY IDEQ");
        query.bindValue(":nom", "%" + nom + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(query.value("IDEQ").toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOMEQ").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("ETATEQ").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("NBEQ").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("TYPEEQ").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("TEMPMEQ").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("DESCEQ").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("FEQ").toString()));
            }
            qDebug() << "Search by Nom loaded" << tableWidget->rowCount() << "results.";
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void equipement::load_equipement_byEtat(const QString &etat, QTableWidget *tableWidget)
{
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                      "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, "
                      "DESCEQ, FEQ FROM EQUIPEMENTS WHERE ETATEQ LIKE :etat ORDER BY IDEQ");
        query.bindValue(":etat", "%" + etat + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(query.value("IDEQ").toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOMEQ").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("ETATEQ").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("NBEQ").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("TYPEEQ").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("TEMPMEQ").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("DESCEQ").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("FEQ").toString()));
            }
            qDebug() << "Search by Etat loaded" << tableWidget->rowCount() << "results.";
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void equipement::load_equipement_byType(const QString &type, QTableWidget *tableWidget)
{
    tableWidget->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                      "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, "
                      "DESCEQ, FEQ FROM EQUIPEMENTS WHERE TYPEEQ LIKE :type ORDER BY IDEQ");
        query.bindValue(":type", "%" + type + "%");

        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(query.value("IDEQ").toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOMEQ").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("ETATEQ").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("NBEQ").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("TYPEEQ").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("TEMPMEQ").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("DESCEQ").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("FEQ").toString()));
            }
            qDebug() << "Search by Type loaded" << tableWidget->rowCount() << "results.";
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
    }
}

void equipement::load_sorted_equipement(QTableWidget *tableWidget, const QString &sortType)
{
    if (sortType == "Show All") {
        load_equipement_data(tableWidget);
        return;
    }

    tableWidget->setRowCount(0);
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        QString queryString;

        if (sortType == "Nom (A-Z)") {
            queryString = "SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                          "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, DESCEQ, FEQ "
                          "FROM EQUIPEMENTS ORDER BY NOMEQ ASC";
        } else if (sortType == "Nom (Z-A)") {
            queryString = "SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                          "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, DESCEQ, FEQ "
                          "FROM EQUIPEMENTS ORDER BY NOMEQ DESC";
        } else if (sortType == "Type (Consomable-Machine)") {
            queryString = "SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                          "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, DESCEQ, FEQ "
                          "FROM EQUIPEMENTS ORDER BY "
                          "CASE TYPEEQ WHEN 'consomable' THEN 1 WHEN 'machine' THEN 2 ELSE 3 END ASC";
        } else if (sortType == "Etat (Priority-Damaged-Functional)") {
            queryString = "SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                          "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, DESCEQ, FEQ "
                          "FROM EQUIPEMENTS ORDER BY "
                          "CASE ETATEQ WHEN 'priority' THEN 1 WHEN 'damaged' THEN 2 "
                          "WHEN 'functional' THEN 3 ELSE 4 END ASC";
        } else {
            queryString = "SELECT IDEQ, NOMEQ, ETATEQ, NBEQ, TYPEEQ, "
                          "TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') as TEMPMEQ, DESCEQ, FEQ "
                          "FROM EQUIPEMENTS ORDER BY IDEQ";
        }

        query.prepare(queryString);
        if (query.exec()) {
            while (query.next()) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(query.value("IDEQ").toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOMEQ").toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("ETATEQ").toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("NBEQ").toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("TYPEEQ").toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("TEMPMEQ").toString()));
                tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("DESCEQ").toString()));
                tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("FEQ").toString()));
            }
            qDebug() << "Sorting applied: " << sortType;
        } else {
            qDebug() << "Sorting query failed: " << query.lastError().text();
        }
    } else {
        qDebug() << "Database connection failed.";
    }
}

// Add these functions to your equipement class in CRUD_Equipement.cpp

// Get statistics for equipment status (Etat)
QVector<QPair<QString, int>> equipement::getStatistiquesByEtat() {
    QVector<QPair<QString, int>> stats;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT ETATEQ, COUNT(*) FROM EQUIPEMENTS WHERE ETATEQ IS NOT NULL GROUP BY ETATEQ ORDER BY ETATEQ");

        if (query.exec()) {
            while (query.next()) {
                QString etat = query.value(0).toString();
                int count = query.value(1).toInt();
                stats.append(qMakePair(etat, count));
            }
        } else {
            qDebug() << "Etat query failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for statistics.";
    }

    return stats;
}

// Get statistics for equipment type (Type)
QVector<QPair<QString, int>> equipement::getStatistiquesByType() {
    QVector<QPair<QString, int>> stats;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT TYPEEQ, COUNT(*) FROM EQUIPEMENTS WHERE TYPEEQ IS NOT NULL GROUP BY TYPEEQ ORDER BY TYPEEQ");

        if (query.exec()) {
            while (query.next()) {
                QString type = query.value(0).toString();
                int count = query.value(1).toInt();
                stats.append(qMakePair(type, count));
            }
        } else {
            qDebug() << "Type query failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for statistics.";
    }

    return stats;
}

// Get statistics for equipment quantity by type
QVector<QPair<QString, int>> equipement::getStatistiquesByQuantity() {
    QVector<QPair<QString, int>> stats;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT TYPEEQ, SUM(NBEQ) FROM EQUIPEMENTS WHERE TYPEEQ IS NOT NULL GROUP BY TYPEEQ ORDER BY TYPEEQ");

        if (query.exec()) {
            while (query.next()) {
                QString type = query.value(0).toString();
                int totalQuantity = query.value(1).toInt();
                stats.append(qMakePair(type, totalQuantity));
            }
        } else {
            qDebug() << "Quantity query failed:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for statistics.";
    }

    return stats;
}












