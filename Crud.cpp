
#include "connection.h"
#include "Crud.h"
#include <QDebug>
#include <QTableWidget>

Crud::Crud(){}

Crud::Crud(int IDR, QString TITRER, QString CLASSR, QString DESCR, QString DATEDR, QString DATEFR) {
    this->IDR = IDR;
    this->TITRER = TITRER;
    this->CLASSR = CLASSR;
    this->DESCR = DESCR;
    this->DATEDR = DATEDR;
    this->DATEFR = DATEFR;
}

bool Crud::add_recherche(QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("INSERT INTO RECHERCHE (TITRER, CLASSR, DESCR, DATEDR, DATEFR) "
                       "VALUES (:TITRER, :CLASSR, :DESCR, TO_DATE(:DATEDR, 'YYYY-MM-DD'), TO_DATE(:DATEFR, 'YYYY-MM-DD'))");

        thisdb.bindValue(":TITRER", TITRER);
        thisdb.bindValue(":CLASSR", CLASSR);
        thisdb.bindValue(":DESCR", DESCR);
        thisdb.bindValue(":DATEDR", DATEDR);
        thisdb.bindValue(":DATEFR", DATEFR);

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

void Crud::delete_recherche(int IDR, QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
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


void Crud::update_recherche(int IDR) {
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("UPDATE RECHERCHE SET TITRER = :TITRER, CLASSR = :CLASSR, "
                       "DESCR = :DESCR, DATEDR = TO_DATE(:DATEDR, 'YYYY-MM-DD'), "
                       "DATEFR = TO_DATE(:DATEFR, 'YYYY-MM-DD') WHERE IDR = :IDR");
        thisdb.bindValue(":IDR", IDR);
        thisdb.bindValue(":TITRER", TITRER);
        thisdb.bindValue(":CLASSR", CLASSR);
        thisdb.bindValue(":DESCR", DESCR);
        thisdb.bindValue(":DATEDR", DATEDR);
        thisdb.bindValue(":DATEFR", DATEFR);

        if (thisdb.exec()) {
            qDebug() << "Recherche with IDR" << IDR << "updated successfully.";
        } else {
            qDebug() << "Update failed: " << thisdb.lastError().text();
        }
    } else {
        qDebug() << "Problem connecting to the database.";
    }
}

void Crud::load_recherche_data(QTableWidget *tableWidget) {
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

void Crud::load_recherche_byTitle(const QString &title, QTableWidget *tableWidget) {
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

void Crud::load_recherche_byClass(const QString &classification, QTableWidget *tableWidget) {
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

void Crud::load_sorted_recherche(QTableWidget *tableWidget, const QString &sortType) {
    if (sortType == "Show All") {
        load_recherche_data(tableWidget);
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
