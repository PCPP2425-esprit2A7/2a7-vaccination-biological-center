#include "PatientDetailsDialog.h"
#include "ui_PatientDetailsDialog.h"
#include "connection.h"
#include "Crud.h"
#include <QSqlQuery>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QTemporaryFile>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>

const int TELEPHONE_LENGTH = 8;
const int MAX_PREVIEW_SIZE = 50000;

PatientDetailsDialog::PatientDetailsDialog(int id, QTableWidget *mainTable, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::PatientDetailsDialog),
    parentTable(mainTable),
    editMode(false),
    patientId(id)
{
    ui->setupUi(this);

    // Configurer les validateurs
    QRegularExpressionValidator *idValidator = new QRegularExpressionValidator(QRegularExpression("[0-9]{8}"), this);
    ui->idLineEdit->setValidator(idValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("[a-zA-ZÀ-ÿ\\s\\-']+"), this);
    ui->nomLineEdit->setValidator(nameValidator);
    ui->prenomLineEdit->setValidator(nameValidator);

    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(QRegularExpression("[0-9]{8}"), this);
    ui->telLineEdit->setValidator(phoneValidator);

    // Ajouter les placeholders
    ui->idLineEdit->setPlaceholderText("8 chiffres");
    ui->telLineEdit->setPlaceholderText("8 chiffres");
    ui->nomLineEdit->setPlaceholderText("Lettres seulement");
    ui->prenomLineEdit->setPlaceholderText("Lettres seulement");

    // Configuration du documentPreview
    documentPreview = new QTextBrowser(this);
    documentPreview->setMinimumHeight(300);
    documentPreview->setStyleSheet(
        "QTextBrowser {"
        "   background-color: #f8f8f8;"
        "   border: 1px solid #ddd;"
        "   border-radius: 4px;"
        "   padding: 8px;"
        "}"
        );
    documentPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    documentPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QVBoxLayout* docLayout = new QVBoxLayout(ui->documentFrame);
    docLayout->addWidget(documentPreview);

    // Connexions des signaux

    connect(ui->saveButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::saveDocumentp);
    connect(ui->pdfButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::exportPDFp);
    connect(ui->deleteButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::deletePatientp);
    connect(ui->editButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::enableEditingp);
    connect(ui->modifyButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::modifyPatientp);
    connect(ui->cancelButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::cancelEditingp);
    connect(ui->browseButtonp, &QPushButton::clicked, this, &PatientDetailsDialog::browseDocumentp);

    ui->modifyButtonp->setEnabled(false);
    loadPatientData(patientId);
}

PatientDetailsDialog::~PatientDetailsDialog()
{
    delete ui;
}

void PatientDetailsDialog::loadPatientData(int id)
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query;
        query.prepare("SELECT ID, NOM, PRENOM, GENRE, DATE_NAISSANCE, TEL, DOSSIER FROM PATIENT WHERE ID = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            ui->idLineEdit->setText(query.value(0).toString());
            ui->nomLineEdit->setText(query.value(1).toString());
            ui->prenomLineEdit->setText(query.value(2).toString());

            QString genre = query.value(3).toString();
            int index = ui->genreComboBox->findText(genre);
            if (index != -1) {
                ui->genreComboBox->setCurrentIndex(index);
            }

            QString dateStr = query.value(4).toString();
            QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
            if (!date.isValid()) {
                date = QDate::fromString(dateStr, "dd/MM/yyyy");
            }
            if (date.isValid()) {
                ui->dateEdit->setDate(date);
            }

            ui->telLineEdit->setText(query.value(5).toString());
            documentData = query.value(6).toByteArray();

            if (!documentData.isEmpty()) {
                ui->documentNameLabel->setText("Document disponible");
                ui->documentSizeLabel->setText(
                    QString("Taille: %1 KB").arg(documentData.size() / 1024.0, 0, 'f', 2)
                    );

                ui->saveButtonp->setEnabled(true);
                ui->pdfButtonp->setEnabled(true);

                QTimer::singleShot(0, this, [this]() {
                    updatePatientDetails();
                });
            } else {
                ui->documentNameLabel->setText("Aucun document");
                ui->documentSizeLabel->setText("Taille: 0 KB");
                ui->saveButtonp->setEnabled(false);
                ui->pdfButtonp->setEnabled(false);
                documentPreview->setText("Aucun document disponible pour ce patient.");
            }
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données du patient.");
            qDebug() << "SQL Error:" << query.lastError().text();
            accept();
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de connexion à la base de données.");
        accept();
    }
}

void PatientDetailsDialog::updatePatientDetails()
{
    documentPreview->clear();




    QString htmlContent = QString(
                              "<div style='font-family:Arial; max-width:600px; margin:0 auto; padding:15px;'>"

                              // En-tête avec logo et titre
                              "<div style='display:flex; align-items:center; margin-bottom:20px; padding-bottom:15px; border-bottom:2px solid #3498db;'>"
                              "<h1 style='color:#2c3e50; margin:0; font-size:24px;'>FICHE PATIENT</h1>"
                              "</div>"

                              // Section Informations Patient
                              "<div style='background-color:#f8f9fa; padding:20px; border-radius:8px; margin-bottom:20px; box-shadow:0 2px 4px rgba(0,0,0,0.05);'>"
                              "<h2 style='color:#3498db; margin-top:0; margin-bottom:15px; font-size:18px;'>INFORMATIONS PERSONNELLES</h2>"

                              "<table style='width:100%; border-collapse:collapse;'>"
                              "<tr><td style='width:150px; padding:8px 0; font-weight:bold; vertical-align:top;'>ID :</td><td style='padding:8px 0;'>%1</td></tr>"
                              "<tr><td style='padding:8px 0; font-weight:bold; vertical-align:top;'>Nom :</td><td>%2</td></tr>"
                              "<tr><td style='padding:8px 0; font-weight:bold; vertical-align:top;'>Prénom :</td><td>%3</td></tr>"
                              "<tr><td style='padding:8px 0; font-weight:bold; vertical-align:top;'>Genre :</td><td>%4</td></tr>"
                              "<tr><td style='padding:8px 0; font-weight:bold; vertical-align:top;'>Date naissance :</td><td>%5</td></tr>"
                              "<tr><td style='padding:8px 0; font-weight:bold; vertical-align:top;'>Téléphone :</td><td>%6</td></tr>"
                              "</table>"
                              "</div>"

                              // Section Document
                              "<div style='background-color:#f8f9fa; padding:20px; border-radius:8px; box-shadow:0 2px 4px rgba(0,0,0,0.05);'>"
                              "<h2 style='color:#3498db; margin-top:0; margin-bottom:15px; font-size:18px;'>DOCUMENT MÉDICAL</h2>"
                              "<p style='margin:8px 0;'><span style='font-weight:bold;'>Nom :</span> %7</p>"
                              "<p style='margin:8px 0;'><span style='font-weight:bold;'>Taille :</span> %8 KB</p>"
                              "</div>"
                              "</div>"
                              ).arg(ui->idLineEdit->text(),
                                   ui->nomLineEdit->text(),
                                   ui->prenomLineEdit->text(),
                                   ui->genreComboBox->currentText(),
                                   ui->dateEdit->date().toString("dd/MM/yyyy"),
                                   ui->telLineEdit->text(),
                                   ui->documentNameLabel->text(),
                                   documentData.isEmpty() ? "0" : QString::number(documentData.size()/1024.0, 'f', 2)
                                   );

    documentPreview->setHtml(htmlContent);
}


bool PatientDetailsDialog::validateId(const QString& id)
{
    if (id.length() != 8) return false;

    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(id).hasMatch();
}

bool PatientDetailsDialog::validateName(const QString& name)
{
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s\\-']+$");
    return regex.match(name).hasMatch();
}

bool PatientDetailsDialog::validatePhone(const QString& phone)
{
    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(phone).hasMatch();
}


QString PatientDetailsDialog::formatPhoneNumber(const QString& phone) const
{
    if (phone.length() != 8) return phone;
    return QString("%1 %2 %3 %4").arg(phone.left(2))
        .arg(phone.mid(2, 2))
        .arg(phone.mid(4, 2))
        .arg(phone.right(2));
}

void PatientDetailsDialog::setFieldsReadOnly(bool readOnly)
{
    ui->nomLineEdit->setReadOnly(readOnly);
    ui->prenomLineEdit->setReadOnly(readOnly);
    ui->genreComboBox->setEnabled(!readOnly);
    ui->dateEdit->setReadOnly(readOnly);
    ui->telLineEdit->setReadOnly(readOnly);
    ui->browseButtonp->setEnabled(!readOnly);
}

void PatientDetailsDialog::enableEditingp()
{
    editMode = true;
    setFieldsReadOnly(false);
    ui->editButtonp->setEnabled(false);
    ui->modifyButtonp->setEnabled(true);
}

void PatientDetailsDialog::cancelEditingp()
{
    if (editMode) {
        loadPatientData(patientId);
        setFieldsReadOnly(true);
        ui->editButtonp->setEnabled(true);
        ui->modifyButtonp->setEnabled(false);
        editMode = false;
    } else {
        accept();
    }
}



void PatientDetailsDialog::saveDocumentp()
{
    if (documentData.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun document disponible.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le document",
                                                    ui->nomLineEdit->text() + "_" + ui->prenomLineEdit->text() + "_document",
                                                    "Tous les fichiers (*)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(documentData);
        file.close();
        QMessageBox::information(this, "Succès", "Document enregistré avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'enregistrer le document.");
    }
}

void PatientDetailsDialog::exportPDFp()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty()) return;

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    int pageWidth = pdfWriter.width();
    int yPosition = 300, rowHeight = 300, padding = 100;

    QFont titleFont("Arial", 30, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(QRect(0, 100, pageWidth, 100), Qt::AlignCenter, "Dossier Patient");

    QPixmap logo(":/new/prefix1/image/Adobe Express - file (5).png");
    if (!logo.isNull()) {
        painter.drawPixmap(pageWidth - 450, 50, 400, 350, logo);
    }

    QStringList headers = {"ID", "Nom", "Prénom", "Genre", "Date de naissance", "Téléphone", "Dossier médical"};
    QStringList data;
    data << ui->idLineEdit->text()
         << ui->nomLineEdit->text()
         << ui->prenomLineEdit->text()
         << ui->genreComboBox->currentText()
         << ui->dateEdit->date().toString("dd/MM/yyyy")
         << ui->telLineEdit->text()
         << (documentData.isEmpty() ? "<Aucun Document>" : "Document disponible");

    QFont headerFont("Arial", 18, QFont::Bold);
    QFont contentFont("Arial", 16);

    for (int i = 0; i < headers.size(); ++i) {
        painter.setFont(headerFont);
        painter.drawText(QRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2), Qt::AlignLeft, headers[i] + " :");
        yPosition += rowHeight / 2;

        painter.setFont(contentFont);
        painter.drawText(QRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2), Qt::AlignLeft, data[i]);
        yPosition += rowHeight / 2 + 50;
    }

    if (!documentData.isEmpty()) {
        QString textContent = QString::fromUtf8(documentData);
        bool isTextData = true;

        for (int i = 0; i < qMin(100, documentData.size()); i++) {
            char c = documentData.at(i);
            if (c < 32 && c != '\n' && c != '\r' && c != '\t') {
                isTextData = false;
                break;
            }
        }

        yPosition += 50;
        painter.setFont(headerFont);
        painter.drawText(QRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2),
                         Qt::AlignLeft, "Contenu du Document:");
        yPosition += rowHeight / 2;

        if (isTextData) {
            painter.setFont(QFont("Courier New", 12));
            QStringList lines = textContent.split('\n');
            for (const QString &line : lines) {
                if (yPosition > pdfWriter.height() - rowHeight) {
                    painter.end();
                    pdfWriter.newPage();
                    painter.begin(&pdfWriter);
                    painter.setFont(QFont("Courier New", 12));
                    yPosition = 100;
                }
                painter.drawText(QRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 3),
                                 Qt::AlignLeft, line);
                yPosition += rowHeight / 3;
            }
        } else {
            painter.setFont(contentFont);
            painter.drawText(QRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2),
                             Qt::AlignLeft, "Ce document contient des données binaires qui ne peuvent pas être affichées.");
            yPosition += rowHeight / 2;
            painter.drawText(QRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2),
                             Qt::AlignLeft, "Taille du document: " + QString::number(documentData.size() / 1024) + " KB");
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
}

void PatientDetailsDialog::deletePatientp()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              "Êtes-vous sûr de vouloir supprimer ce patient?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Crudp crudp;
        bool success = crudp.delete_patient_by_id(patientId, parentTable);

        if (success) {
            QMessageBox::information(this, "Succès", "Patient supprimé avec succès.");
            accept();
        }
    }
}

void PatientDetailsDialog::browseDocumentp()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner un document", "", "Tous les fichiers (*)");
    if (!filePath.isEmpty()) {
        currentFilePath = filePath;
        QFileInfo fileInfo(filePath);
        ui->documentNameLabel->setText(fileInfo.fileName());

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            documentData = file.readAll();
            file.close();
            updatePatientDetails();
        }
    }
}

void PatientDetailsDialog::modifyPatientp()
{
    if (!editMode) return;

    QString id = ui->idLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString genre = ui->genreComboBox->currentText();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString tel = ui->telLineEdit->text();

    // Validations
    if (!validateId(id)) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir exactement 8 chiffres.");
        return;
    }

    if (!validateName(nom)) {
        QMessageBox::warning(this, "Erreur", "Le nom ne peut contenir que des lettres.");
        return;
    }

    if (!validateName(prenom)) {
        QMessageBox::warning(this, "Erreur", "Le prénom ne peut contenir que des lettres.");
        return;
    }

    if (!validatePhone(tel)) {
        QMessageBox::warning(this, "Erreur", "Le téléphone doit contenir exactement 8 chiffres.");
        return;
    }

    if (nom.isEmpty() || prenom.isEmpty() || tel.isEmpty() || tel.length() != TELEPHONE_LENGTH) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis et le numéro de téléphone doit contenir 8 chiffres.");
        return;
    }

    QByteArray fileData;
    QString fileName;
    if (!currentFilePath.isEmpty()) {
        QFile file(currentFilePath);
        if (file.open(QIODevice::ReadOnly)) {
            fileData = file.readAll();
            file.close();
            QFileInfo fileInfo(currentFilePath);
            fileName = fileInfo.fileName();
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier sélectionné.");
            return;
        }
    } else {
        fileName = ui->documentNameLabel->text();
    }

    Crudp crudp;
    crudp.update_patient(id.toInt(), nom, prenom, genre, date, fileName, tel.toInt(),
                        fileData.isEmpty() ? documentData : fileData);

    crudp.load_patients(parentTable);

    if (!fileData.isEmpty()) {
        documentData = fileData;
        ui->documentSizeLabel->setText("Taille du document: " +
                                       QString::number(documentData.size() / 1024) + " KB");
        ui->saveButtonp->setEnabled(true);
        ui->pdfButtonp->setEnabled(true);
        updatePatientDetails();
    }

    setFieldsReadOnly(true);
    ui->editButtonp->setEnabled(true);
    ui->modifyButtonp->setEnabled(false);
    editMode = false;

    QMessageBox::information(this, "Succès", "Patient mis à jour avec succès.");
}
