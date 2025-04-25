#include "grendervous.h"
#include "ui_grendervous.h"
#include "rendervous.h"
#include "smtp_mailer_secure.h"

#include <QStackedWidget>
#include <QWidget>
#include <QMessageBox>
#include <QApplication>
#include <QStandardPaths>
#include <QSortFilterProxyModel>
#include <QMenu>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QFont>
#include "QrCode.hpp" // From qrcodegen
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QChartView>
#include <QPieSeries>
#include <QChart>
#include <QHBoxLayout>


#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QInputDialog>



using qrcodegen::QrCode;
using qrcodegen::QrSegment;

grendervous::grendervous(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grendervous)
{
    ui->setupUi(this);
    //connect(ui->updatebutton_2, &QPushButton::clicked, this, &grendervous::onpage4);
}

void grendervous::onpage4() {
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


grendervous::~grendervous()
{
    delete ui;
}


void grendervous::on_addbutton_2_clicked()
{
    QString date = ui->date_2->text().trimmed();
    QString heureStr = ui->heure_2->text().trimmed();
    QString dureeStr = ui->dur_2->text().trimmed();
    QString status = ui->statut_2->text().trimmed();
    QString id_employeStr = ui->ide_2->text().trimmed();
    QString id_patientStr = ui->idp_2->text().trimmed();

    if (date.isEmpty() || heureStr.isEmpty() || dureeStr.isEmpty() ||
        status.isEmpty() || id_employeStr.isEmpty() || id_patientStr.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Tous les champs doivent être remplis!");
        return;
    }

    bool ok1, ok2, ok3, ok4;
    int heure = heureStr.toInt(&ok1);
    int duree = dureeStr.toInt(&ok2);
    int id_employe = id_employeStr.toInt(&ok3);
    int id_patient = id_patientStr.toInt(&ok4);

    if (!ok1 || !ok2 || !ok3 || !ok4) {
        QMessageBox::warning(this, "Erreur", "Les champs numériques doivent contenir des valeurs valides.");
        return;
    }

    if (heure < 0 || heure > 23) {
        QMessageBox::warning(this, "Heure invalide", "L'heure doit être entre 0 et 23.");
        return;
    }

    if (duree <= 0) {
        QMessageBox::warning(this, "Durée invalide", "La durée doit être positive.");
        return;
    }

    // 💡 Vérification du conflit ici :
    if (rendervous::isAppointmentConflict(date, heure, duree, id_employe)) {
        QMessageBox::warning(this, "Conflit détecté",
                             "Un autre rendez-vous existe déjà pour cet employé à cette heure.");
        return;
    }

    rendervous r(date, heure, id_employe, id_patient, duree, status);
    if (r.ajouter()) {
        QMessageBox::information(this, "Succès", "Rendez-vous ajouté avec succès.");
        r.afficher(ui->tableView_2);

        ui->date_2->clear();
        ui->heure_2->clear();
        ui->dur_2->clear();
        ui->statut_2->clear();
        ui->ide_2->clear();
        ui->idp_2->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout du rendez-vous a échoué.");
    }
}




void grendervous::on_displaybutton_2_clicked()
{
    rendervous r;
    r.afficher(ui->tableView_2);
}


void grendervous::on_deletebutton_2_clicked()
{
    // Get and validate ID input
    QString idd = ui->id_2->text().trimmed();
    if (idd.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un ID à supprimer");
        return;
    }

    // Convert ID to integer
    bool ok;
    int id = idd.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "ID invalide", "L'ID doit être un nombre positif");
        return;
    }

    // Confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer le rendez-vous #" + QString::number(id) + "?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    // Attempt deletion
    rendervous r;
    if (r.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Rendez-vous supprimé avec succès");
        r.afficher(ui->tableView_2);
        ui->search->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du rendez-vous.\n"
                                              "Vérifiez que l'ID existe.");
    }
}

void grendervous::on_updatebutton_2_clicked()
{
    // Get and validate ID input
    QString idd = ui->id_2->text().trimmed();
    if (idd.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un ID à modifier");
        return;
    }

    // Convert ID to integer
    bool ok;
    int id = idd.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "ID invalide", "L'ID doit être un nombre positif");
        return;
    }

    // Fetch appointment data from database
    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Rendez-vous non trouvé ou erreur de base de données");
        return;
    }

    // Store the ID in a member variable for later use
    currentEditId = id;

    // Switch to edit page (page_4)
    ui->stackedWidget->setCurrentWidget(ui->page_4);

    // Fill the edit form with existing data
    ui->id_3->setText(QString::number(id));
    ui->date_3->setText(query.value("date_rdv").toString());
    ui->heure_3->setText(query.value("heure").toString());
    ui->dur_3->setText(query.value("duree").toString());
    ui->statut_3->setText(query.value("status").toString());
    ui->ide_3->setText(query.value("id_employe").toString());
    ui->idp_3->setText(query.value("id_patient").toString());
}

void grendervous::on_save_clicked()
{
    QString date = ui->date_3->text().trimmed();
    QString heure = ui->heure_3->text().trimmed();
    QString duree = ui->dur_3->text().trimmed();
    QString status = ui->statut_3->text().trimmed();
    QString id_employe = ui->ide_3->text().trimmed();
    QString id_patient = ui->idp_3->text().trimmed();

    // Validate inputs
    if (date.isEmpty() || heure.isEmpty() || duree.isEmpty() ||
        status.isEmpty() || id_employe.isEmpty() || id_patient.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Tous les champs doivent être remplis");
        return;
    }

    // Convert numeric fields
    bool ok1, ok2, ok3, ok4;
    int he = heure.toInt(&ok1);
    int du = duree.toInt(&ok2);
    int ide = id_employe.toInt(&ok3);
    int idp = id_patient.toInt(&ok4);

    if (!ok1 || !ok2 || !ok3 || !ok4) {
        QMessageBox::warning(this, "Valeur invalide",
                             "Les champs numérique doivent contenir des nombres valides");
        return;
    }

    // Update database
    QSqlQuery query;
    query.prepare("UPDATE rendezvous SET "
                  "date_rdv = :date, "
                  "heure = :heure, "
                  "duree = :duree, "
                  "status = :status, "
                  "id_employe = :id_employe, "
                  "id_patient = :id_patient "
                  "WHERE id = :id");

    query.bindValue(":date", date);
    query.bindValue(":heure", he);
    query.bindValue(":duree", du);
    query.bindValue(":status", status);
    query.bindValue(":id_employe", ide);
    query.bindValue(":id_patient", idp);
    query.bindValue(":id", currentEditId);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Rendez-vous modifié avec succès");
        // Return to previous page and refresh table
        ui->stackedWidget->setCurrentWidget(ui->page_3); // Set your actual previous page here
        rendervous r;
        r.afficher(ui->tableView_2);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification: " + query.lastError().text());
    }
}


void grendervous::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}




void grendervous::on_pushButton_18_clicked()
{
    // Get the table view model (replace 'tableView' with your actual table view variable name)
    QAbstractItemModel *model = ui->tableView_2->model();
    if (!model) {
        QMessageBox::warning(this, "Error", "No data to export!");
        return;
    }

    // Ask user for save location
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    "PDF Files (*.pdf)");
    if (fileName.isEmpty())
        return;

    // Create a printer for PDF generation
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fileName);

    // Create a painter to draw on the PDF
    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(this, "Error", "Could not create PDF file!");
        return;
    }

    // Set up fonts and metrics
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);
    QFontMetrics fontMetrics(font);

    // Calculate column widths and row heights
    const int rowCount = model->rowCount();
    const int columnCount = model->columnCount();
    const int margin = 20;
    const int spacing = 10;

    // Calculate required width
    int totalWidth = 0;
    QVector<int> columnWidths(columnCount);
    for (int col = 0; col < columnCount; ++col) {
        // Header width
        int width = fontMetrics.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString()) + spacing;

        // Content width
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex index = model->index(row, col);
            QString text = model->data(index).toString();
            width = qMax(width, fontMetrics.horizontalAdvance(text) + spacing);
        }

        columnWidths[col] = width;
        totalWidth += width;
    }

    // Draw header
    int x = margin;
    int y = margin;
    const int rowHeight = fontMetrics.height() + spacing;

    painter.setPen(Qt::black);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(x, y, totalWidth, rowHeight);

    for (int col = 0; col < columnCount; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(x + spacing/2, y + spacing/2, columnWidths[col] - spacing, rowHeight - spacing,
                         Qt::AlignLeft | Qt::AlignVCenter, header);
        x += columnWidths[col];
    }

    // Draw rows
    y += rowHeight;
    x = margin;

    for (int row = 0; row < rowCount; ++row) {
        x = margin;
        for (int col = 0; col < columnCount; ++col) {
            QModelIndex index = model->index(row, col);
            QString text = model->data(index).toString();

            painter.setPen(Qt::black);
            painter.setBrush(Qt::white);
            painter.drawRect(x, y, columnWidths[col], rowHeight);
            painter.drawText(x + spacing/2, y + spacing/2, columnWidths[col] - spacing, rowHeight - spacing,
                             Qt::AlignLeft | Qt::AlignVCenter, text);

            x += columnWidths[col];
        }
        y += rowHeight;
    }

    painter.end();

    QMessageBox::information(this, "Success", "Table exported to PDF successfully!");
}

void grendervous::on_searchbutton_2_clicked()
{
    QString id = ui->search->text().trimmed();  // Added trim() to remove whitespace

    if(id.isEmpty())
    {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID à rechercher.");
        return;
    }

    QSqlQueryModel *model = rendervous::search(id);

    if(model)
    {
        // Safely handle the old model
        QAbstractItemModel *oldModel = ui->tableView_2->model();
        ui->tableView_2->setModel(nullptr);  // Prevent dangling pointer
        delete oldModel;

        // Set the new model
        ui->tableView_2->setModel(model);

        // Adjust column widths
        ui->tableView_2->setColumnWidth(0, 50);   // ID
        ui->tableView_2->setColumnWidth(1, 150);  // Date
        ui->tableView_2->setColumnWidth(2, 100);  // Heure
        ui->tableView_2->setColumnWidth(3, 80);   // ID Employe
        ui->tableView_2->setColumnWidth(4, 80);   // ID Patient
        ui->tableView_2->setColumnWidth(5, 60);   // Duree

        // Enable sorting
        ui->tableView_2->setSortingEnabled(true);

        // Resize rows to contents
        ui->tableView_2->resizeRowsToContents();
    }
    else
    {
        QMessageBox::information(this, "Recherche", "Aucun rendez-vous trouvé avec cet ID.");
    }
}


void grendervous::on_pushButton_16_clicked() // quit from Desktop application
{
    QApplication::quit();
}


void grendervous::on_sort_clicked()
{
    QMenu menu(this);
    QAction *action = menu.addAction("Tri croissant");
    QAction *actiond = menu.addAction("Tri décroissant");

    // Connect ascending sort action
    connect(action, &QAction::triggered, [this]() {
        QSqlQueryModel *model = rendervous::sort(true); // true = ascending
        if(model) {
            // Safely replace the current model
            QAbstractItemModel *oldModel = ui->tableView_2->model();
            ui->tableView_2->setModel(model);
            delete oldModel;

            // Apply column widths and other settings if needed
            ui->tableView_2->resizeColumnsToContents();
        } else {
            QMessageBox::warning(this, "Erreur", "Échec du tri des rendez-vous");
        }
    });

    // Connect descending sort action
    connect(actiond, &QAction::triggered, [this]() {
        QSqlQueryModel *model = rendervous::sort(false); // false = descending
        if(model) {
            // Safely replace the current model
            QAbstractItemModel *oldModel = ui->tableView_2->model();
            ui->tableView_2->setModel(model);
            delete oldModel;

            // Apply column widths and other settings if needed
            ui->tableView_2->resizeColumnsToContents();
        } else {
            QMessageBox::warning(this, "Erreur", "Échec du tri des rendez-vous");
        }
    });

    // Show the menu at cursor position
    menu.exec(QCursor::pos());
}

void grendervous::on_qr_clicked()
{
    QString id = ui->id_2->text();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an appointment first");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save QR Code",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                                                        QString("/appointment_%1.png").arg(id),
                                                    "PNG Files (*.png)");


    if (!fileName.isEmpty()) {
        generateQRCode(id.toInt(), fileName);
        QMessageBox::information(this, "Success",
                                 "QR code saved successfully!\n\nFile: " + fileName);
    }
}


void grendervous::generateQRCode(int id, const QString &outputPath) {
    // Étape 1 : récupérer les données du RDV
    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur lors de la récupération des données pour QR code";
        return;
    }

    QString date = query.value("date_rdv").toString();
    int heure = query.value("heure").toInt();
    QString status = query.value("status").toString();
    int id_patient = query.value("id_patient").toInt();

    // Étape 2 : contenu sécurisé du QR code (sans caractères douteux)
    QString content = QString(
                          "This QR code contains your appointment summary.\n\n"
                          "Appointment ID = %1\n"
                          "Date = %2\n"
                          "Time = %3:00\n"
                          "Patient ID = %4\n"
                          "Status = %5"
                          ).arg(id).arg(date).arg(heure).arg(id_patient).arg(status);

    // Étape 3 : générer le QR PNG
    QrCode qr = QrCode::encodeText(content.toUtf8().constData(), QrCode::Ecc::LOW);
    const int scale = 5;
    const int size = qr.getSize() * scale;

    QImage image(size, size, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);

    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                painter.drawRect(x * scale, y * scale, scale, scale);
            }
        }
    }

    painter.end();

    if (!image.save(outputPath, "PNG")) {
        QMessageBox::critical(this, "Erreur", "Échec de la sauvegarde du QR code en PNG.");
        return;
    }

    // Étape 4 : générer le PDF professionnel
    /*QString pdfPath = outputPath;
    pdfPath.replace(".png", ".pdf");
    generatePDF(id, pdfPath);*/

    // Étape 5 : demander l'adresse email
    QString email = QInputDialog::getText(this, "Send by Email", "Patient email address:");
    if (email.isEmpty()) {
        QMessageBox::information(this, "Info", "No email provided. The PDF has been saved locally.");
        return;
    }

    // Étape 6 : envoyer le PDF (pas le PNG !) par email
    envoyerEmailAvecQRCode(email, outputPath);
}



void grendervous::on_voice_clicked()
{
    QProcess process;
    process.start("python", QStringList() << "reco_rdv_whisper_mic.py");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QString errorOutput = process.readAllStandardError();

    // 🔥 Ignorer le warning FP16 (facultatif)
    if (errorOutput.contains("FP16 is not supported")) {
        errorOutput.clear();
    }

    if (!errorOutput.isEmpty()) {
        QMessageBox::critical(this, "Erreur Python", errorOutput);
        return;
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(output.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        QMessageBox::critical(this, "Erreur JSON", parseError.errorString());
        return;
    }

    QJsonObject obj = doc.object();

    if (obj.contains("texte")) {
        QString texteRecu = obj["texte"].toString();
        QMessageBox::information(this, "Texte vocal reconnu", texteRecu);
    }

    if (!obj.contains("ok") || !obj["ok"].toBool()) {
        QMessageBox::warning(this, "Erreur", obj["error"].toString());
        return;
    }

    QString date = obj["date"].toString();
    int heure = obj["heure"].toInt();
    int id_patient = obj["id_patient"].toInt();
    int id_employe = obj["id_employe"].toInt();
    QString status = obj["status"].toString();

    rendervous r(date, heure, id_employe, id_patient, 30, status);
    if (r.ajouter()) {
        QMessageBox::information(this, "Succès", "RDV vocal ajouté !");
        r.afficher(ui->tableView_2);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de création du RDV.");
    }
}

void grendervous::on_btnPrioriser_clicked() {
    QSqlQueryModel *model = rendervous::prioriserPatients();

    if (model) {
        // Libère l'ancien modèle si nécessaire
        QAbstractItemModel *oldModel = ui->tableView_2->model();
        ui->tableView_2->setModel(model);
        delete oldModel;

        ui->tableView_2->resizeColumnsToContents();
        QMessageBox::information(this, "Résultat", "Patients priorisés par nombre d'absences !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'obtenir la liste des absents.");
    }
}


void grendervous::on_btnGenererAuto_clicked() {
    rendervous::genererAutoRendezVousPourAbsents();

    rendervous r;
    r.afficher(ui->tableView_2); // pour actualiser les données
}

void grendervous::envoyerEmailAvecQRCode(const QString &email, const QString &pathFichierPNG) {
    QString fileName = QFileInfo(pathFichierPNG).baseName();  // "appointment_12"
    QString id = fileName.section('_', 1, 1);

    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    QString date = query.value("date_rdv").toString();
    QString heure = query.value("heure").toString();
    QString status = query.value("status").toString();
    QString id_patient = query.value("id_patient").toString();
    QString code_patient = query.value("code_patient").toString();

    QString subject = "Appointment Confirmation – Vaccination & Research Center";

    QString body = QString(R"(
Dear Sir or Madam,

This email confirms the registration of your appointment at the Vaccination & Research Center.

Please find your personal QR code attached. It will be required upon arrival for quick and secure identification at the entrance.

📅 Appointment Details:
- Appointment ID: %1
- Date: %2
- Time: %3:00
- Patient ID: %4
- Status: %5
- Your Unique Code: %6

Thank you for choosing our center.
Should you need any further information, feel free to contact us.

Sincerely,
<b>Medical Secretary</b>
Vaccination & Research Center
)").arg(id, date, heure, id_patient, status, code_patient);

    SmtpMailerSecure *mailer = new SmtpMailerSecure(this);
    mailer->sendMail(
        "secretaire@vaccination-center.com",  // sender address
        email,
        subject,
        body,
        pathFichierPNG,
        "smtp.gmail.com",
        465,
        "ahmedbrahmi530@gmail.com",
        "fnhr islt fzsy fvlk"
        );
}


void grendervous::afficherStatistiques() {
    // Affiche la page des statistiques
    ui->stackedWidget->setCurrentWidget(ui->page_statistiques);

    // Nettoyer l'ancien layout si existant
    QLayout *layout = ui->statChartLayout->layout();
    if (!layout) {
        layout = new QHBoxLayout();
        ui->statChartLayout->setLayout(layout);
    } else {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    // Récupérer les statistiques
    QVector<QPair<int, int>> stats = rendervous::getStatistiquesValidation();
    if (stats.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Aucune donnée disponible pour les statistiques.");
        return;
    }

    QStringList categories;
    QVector<int> values;
    int maxValue = 0;
    for (const auto &stat : stats) {
        categories.append(QString::number(stat.first));
        values.append(stat.second);
        maxValue = std::max(maxValue, stat.second);
    }

    // === Camembert
    QPieSeries *pieSeries = new QPieSeries();
    for (int i = 0; i < categories.size(); ++i) {
        pieSeries->append("Durée " + categories[i] + " min", values[i]);
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition des rendez-vous par durée");
    pieChart->legend()->setAlignment(Qt::AlignRight);
    pieChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
    pieChart->setBackgroundPen(Qt::NoPen);

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setFixedSize(300, 250);
    pieChartView->setStyleSheet("background-color: white;");
    pieChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // === Barres animées
    QGraphicsScene *scene = new QGraphicsScene();
    int barWidth = 40, gap = 25, chartHeight = 250;
    int xPos = 40, yBase = chartHeight - 60;

    for (int i = 0; i < values.size(); ++i) {
        int barHeight = (values[i] * (chartHeight - 80)) / maxValue;
        QColor barColor = pieSeries->slices().at(i)->brush().color();

        QGraphicsRectItem *bar = scene->addRect(xPos, yBase - barHeight, barWidth, barHeight,
                                                QPen(Qt::NoPen), QBrush(barColor));

        QGraphicsTextItem *label = new QGraphicsTextItem(categories[i] + " min");
        label->setDefaultTextColor(Qt::black);
        label->setFont(QFont("Arial", 9, QFont::Bold));
        qreal labelX = xPos + (barWidth / 2) - (label->boundingRect().width() / 2);
        label->setPos(labelX, yBase + 5);
        scene->addItem(label);

        xPos += barWidth + gap;
    }

    scene->setSceneRect(0, 0, xPos + 50, chartHeight + 50);

    QGraphicsView *barView = new QGraphicsView(scene);
    barView->setRenderHint(QPainter::Antialiasing);
    barView->setFixedSize(350, 250);
    barView->setStyleSheet("background-color: white;");
    barView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Ajout au layout
    layout->addWidget(barView);
    layout->addWidget(pieChartView);

    this->resize(800, 500);  // largeur, hauteur

}


void grendervous::on_statsButton_clicked() {
    afficherStatistiques();
}


void grendervous::on_btnFermerStats_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);  // Remplace par le nom réel de ta page d'accueil

    this->resize(1920, 1080);  // remets la taille d’accueil

}

void grendervous::generatePDF(int id, const QString &pdfPath) {
    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur lors de la récupération des données pour PDF";
        return;
    }

    QString date = query.value("date_rdv").toString();
    int heure = query.value("heure").toInt();
    QString status = query.value("status").toString();
    int id_patient = query.value("id_patient").toInt();

    QString content = QString(R"(
<h2 style='color:#2E86C1;'>Vaccination & Research Center</h2>
<hr>
<p><b>Appointment ID:</b> %1</p>
<p><b>Date:</b> %2</p>
<p><b>Time:</b> %3:00</p>
<p><b>Patient ID:</b> %4</p>
<p><b>Status:</b> %5</p>
<hr>
<p style='font-size:10pt;'>Please present this document at the center reception.</p>
)").arg(id).arg(date).arg(heure).arg(id_patient).arg(status);

    QTextDocument document;
    document.setHtml(content);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfPath);
    printer.setPageSize(QPageSize::A4);

    document.print(&printer);
}


