
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

void Crud::add_recherche(QTableWidget *tableWidget) {
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery thisdb(db);
        thisdb.prepare("INSERT INTO RECHERCHE (IDR, TITRER, CLASSR, DESCR, DATEDR, DATEFR) "
                       "VALUES (:IDR, :TITRER, :CLASSR, :DESCR, TO_DATE(:DATEDR, 'YYYY-MM-DD'), TO_DATE(:DATEFR, 'YYYY-MM-DD'))");
        thisdb.bindValue(":IDR", IDR);
        thisdb.bindValue(":TITRER", TITRER);
        thisdb.bindValue(":CLASSR", CLASSR);
        thisdb.bindValue(":DESCR", DESCR);
        thisdb.bindValue(":DATEDR", DATEDR);
        thisdb.bindValue(":DATEFR", DATEFR);

        if (thisdb.exec()) {
            // If successful, add the data to QTableWidget
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);

            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(IDR)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(TITRER));
            tableWidget->setItem(row, 2, new QTableWidgetItem(CLASSR));
            tableWidget->setItem(row, 3, new QTableWidgetItem(DESCR));
            tableWidget->setItem(row, 4, new QTableWidgetItem(DATEDR));
            tableWidget->setItem(row, 5, new QTableWidgetItem(DATEFR));

            qDebug() << "Recherche added successfully to both database and table widget.";
        } else {
            qDebug() << "Failed to execute query:" << thisdb.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database.";
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

            // Remove from the QTableWidget
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                QTableWidgetItem *item = tableWidget->item(row, 0); // IDR is in the first column
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
