#include "rendervous.h"
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


rendervous::rendervous(){}

rendervous::rendervous(QString date, int heure, int id_employe, int id_patient, int dur, QString status, int code)
{
    this->date = date;
    this->heure = heure;
    this->id_employe = id_employe;
    this->id_patient = id_patient;
    this->dur = dur;
    this->status = status;
    this->code_patient = (code == -1) ? QRandomGenerator::global()->bounded(1000, 9999) : code;
}


// Méthode d'ajout
bool rendervous::ajouter() {
    QSqlQuery query;

    // Préparer la requête avec le champ code_patient ajouté
    query.prepare("INSERT INTO rendezvous (date_rdv, heure, id_employe, id_patient, duree, status, code_patient) "
                  "VALUES (:date, :heure, :id_employe, :id_patient, :duree, :status, :code_patient)");

    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":id_patient", id_patient);
    query.bindValue(":duree", dur);
    query.bindValue(":status", status);
    query.bindValue(":code_patient", code_patient); // 🎯 nouveau champ

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }

    return true;
}


// Méthode de suppression
bool rendervous::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
    return true;
}

// Méthode d'affichage
void rendervous::afficher(QTableView *table) {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id AS \"ID\", date_rdv AS \"Date\", "
                    "heure AS \"Heure\", "
                    "duree AS \"Durée (min)\", "
                    "status AS \"Statut\", "
                    "id_employe AS \"ID Employé\", "
                    "id_patient AS \"ID Patient\" "
                    "FROM rendezvous "
                    "ORDER BY date_rdv, heure");

    if(model->lastError().isValid()) {
        qDebug() << "Erreur lors du chargement des données:" << model->lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Impossible de charger les données des rendez-vous");
        return;
    }

    // Apply the model to the table
    table->setModel(model);

    // Styling improvements
    table->setStyleSheet(
        "QTableView {"
        "   background-color: #f8f9fa;"
        "   alternate-background-color: #e9ecef;"
        "   gridline-color: #dee2e6;"
        "   font-family: Segoe UI, Arial;"
        "   font-size: 12px;"
        "}"
        "QTableView::item {"
        "   padding: 5px;"
        "}"
        "QHeaderView::section {"
        "   background-color: #343a40;"
        "   color: white;"
        "   padding: 5px;"
        "   font-weight: bold;"
        "   border: 1px solid #495057;"
        "}"
        "QTableView QTableCornerButton::section {"
        "   background-color: #343a40;"
        "   border: 1px solid #495057;"
        "}"
        );

    // Enable alternating row colors
    table->setAlternatingRowColors(true);

    // Selection behavior
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Column sizing
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->verticalHeader()->setDefaultSectionSize(25);
    table->horizontalHeader()->setStretchLastSection(true);

    // Sortable columns
    table->setSortingEnabled(true);

    // Resize columns to content with minimum widths
    table->resizeColumnsToContents();
    for(int i = 0; i < model->columnCount(); ++i) {
        int width = table->columnWidth(i);
        // Set different minimum widths for different columns
        int minWidth = 100; // Default minimum width
        if(i == 0) minWidth = 60;  // ID column
        else if(i == 1) minWidth = 120;  // Date column
        else if(i == 2) minWidth = 80;   // Time column
        table->setColumnWidth(i, qMax(width, minWidth));
    }

    // Make the ID column visible (removed the hideColumn(0) line)
    // You can adjust the ID column width specifically if needed
    table->setColumnWidth(0, 80); // Set a specific width for ID column
}
// Méthode de modification
bool rendervous::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE rendezvous SET "
                  "date_rdv = :date, "
                  "heure = :heure, "
                  "id_employe = :id_employe, "
                  "id_patient = :id_patient, "
                  "duree = :duree, "
                  "status = :status "
                  "WHERE id = :id");

    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":id_patient", id_patient);
    query.bindValue(":duree", dur);
    query.bindValue(":status", status);
    query.bindValue(":id", id);

    if(!query.exec()) {
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

QSqlQueryModel *rendervous::sort(bool ordreCroissant)
{
    connection c;
    QSqlDatabase db = c.get_database();
    if(db.open()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query(db);

        // Improved query with proper column names
        QString queryStr = "SELECT id AS \"ID\", "
                           "date_rdv AS \"Date\", "
                           "heure AS \"Heure\", "
                           "duree AS \"Durée\", "
                           "status AS \"Statut\", "
                           "id_employe AS \"ID Employé\", "
                           "id_patient AS \"ID Patient\" "
                           "FROM rendezvous ORDER BY heure ";

        queryStr += ordreCroissant ? "ASC" : "DESC";

        if(!query.exec(queryStr)) {
            qDebug() << "Sort query error:" << query.lastError().text();
            delete model;
            return nullptr;
        }

        model->setQuery(query);

        // Set header data (already included in the query as aliases)
        // These can be kept for additional formatting if needed
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Heure"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Durée"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID Employé"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID Patient"));

        return model;
    } else {
        qDebug() << "Database connection error:" << db.lastError().text();
        return nullptr;
    }
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
    int id_patient = query.value("id_patient").toInt();

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
    query.prepare("SELECT heure, duree FROM rendezvous WHERE date_rdv = :date AND id_employe = :employeeId");
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
    query.prepare("SELECT id_patient, COUNT(*) AS nb_absences "
                  "FROM rendezvous "
                  "WHERE status = 'Absent' "
                  "GROUP BY id_patient "
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
    getAbsents.prepare("SELECT DISTINCT id_patient, id_employe, date_rdv "
                       "FROM rendezvous "
                       "WHERE status = 'Absent'");

    if (!getAbsents.exec()) {
        qDebug() << "Erreur récupération absents:" << getAbsents.lastError().text();
        return;
    }

    int count = 0;

    while (getAbsents.next()) {
        int id_patient = getAbsents.value("id_patient").toInt();
        int id_employe = getAbsents.value("id_employe").toInt();
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
            insert.prepare("INSERT INTO rendezvous (date_rdv, heure, id_employe, id_patient, duree, status) "
                           "VALUES (:date, :heure, :id_employe, :id_patient, :duree, 'Reprogrammé')");

            insert.bindValue(":date", newDateStr);
            insert.bindValue(":heure", newHeure);
            insert.bindValue(":id_employe", id_employe);
            insert.bindValue(":id_patient", id_patient);
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



