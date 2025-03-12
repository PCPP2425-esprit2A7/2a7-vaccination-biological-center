#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "Crud.h"
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPageSize>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Établir la connexion à la base de données
    connection c;
    if (c.set_connection()) {
        qDebug() << "Database connected";

        // Charger les patients dans le QTableWidget
        Crud crud;
        crud.load_patients(ui->tableWidget); // Charge les patients dans la table
    } else {
        qDebug() << "Failed to connect to database";
    }
    // Initialiser le QComboBox pour le genre
    ui->genre->addItem("Homme");
    ui->genre->addItem("Femme");
    // Connecter le champ de saisie du nom à un slot
    connect(ui->id2, &QLineEdit::textChanged, this, &MainWindow::on_id2_textChanged);
    //  connexion de signal à slot par la tablewidget
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_cellClicked);
    // Connecter le bouton "pdf" à un slot
    connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::on_pdf_clicked);
    // Connecter le bouton "Cancel" à un slot
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow::on_cancel_clicked);
    // Mettre à jour les statistiques
    updateStatistics();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked() {
    QString id = ui->id->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString genre = ui->genre->currentText();
    QString date = ui->date->text();
    QString tel = ui->tel->text();
    QString doc = ui->doc->text();

    bool idOk;
    int idInt = id.toInt(&idOk);
    if (!idOk || id.length() != 8) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir 8 chiffres.");
        return;
    }

    QRegularExpression nameRegex("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$");
    if (!nameRegex.match(nom).hasMatch() || !nameRegex.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le nom et le prénom doivent contenir uniquement des lettres.");
        return;
    }


    QRegularExpression dateRegex("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(\\d{4})$");
    QRegularExpressionMatch dateMatch = dateRegex.match(date);
    if (!dateMatch.hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La date doit être au format jj/mm/aaaa.");
        return;
    }

    bool telOk;
    int telInt = tel.toInt(&telOk);
    if (!telOk || tel.length() != 8) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
        return;
    }

    if (doc.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir la description.");
        return;
    }

    Crud add(idInt, nom, prenom, genre, date, doc, telInt);
    add.add_patient(ui->tableWidget);

    ui->id->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->genre->clear();
    ui->date->clear();
    ui->tel->clear();
    ui->doc->clear();

    QMessageBox::information(this, "Succès", "Patient ajouté avec succès !");
    updateStatistics();
}

void MainWindow::on_drop_clicked() {
    QString id = ui->id2->text();
    bool test;
    int id2int = id.toInt(&test);
    Crud drop;
    drop.delete_patient(id2int, ui->tableWidget);
    QMessageBox::information(this, "Success", "Patient supprimé.");
    updateStatistics();
}

void MainWindow::on_mod_clicked() {
    QString id = ui->id->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString genre = ui->genre->currentText();
    QString date = ui->date->text();
    QString tel = ui->tel->text();
    QString doc = ui->doc->text();

    bool idOk, telOk;
    int idInt = id.toInt(&idOk);
    int telInt = tel.toInt(&telOk);

    if (!idOk) { // controle de saisie
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre.");
        return;
    }

    if (!telOk || tel.length() != 8) { // controle de saisie
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
        return;
    }

    // Appel de la méthode de mise à jour
    Crud update;
    update.update_patient(idInt, nom, prenom, genre, date, doc, telInt, ui->tableWidget);

    // Effacer les champs après la mise à jour
    ui->id->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->genre->clear();
    ui->date->clear();
    ui->tel->clear();
    ui->doc->clear();

    QMessageBox::information(this, "Succès", "Les données du patient ont été mises à jour !");
    updateStatistics();
}



void MainWindow::on_id2_textChanged(const QString &text) { // afficher les anciens données sur les labels
    bool idOk;
    int id = text.toInt(&idOk); // Convertir le texte en ID

    if (idOk && id > 0) {
        // Récupérer les données du patient par son ID
        Crud crud;
        QMap<QString, QString> patientData = crud.getPatientById(id);

        if (!patientData.isEmpty()) {
            // Remplir les champs du formulaire avec les données récupérées
            ui->id->setText(patientData["id"]);
            ui->nom->setText(patientData["nom"]);
            ui->prenom->setText(patientData["prenom"]);
            ui->genre->setCurrentText(patientData["genre"]);
            ui->date->setText(patientData["date"]);
            ui->tel->setText(patientData["tel"]);
            ui->doc->setText(patientData["dossier"]);
        }
    } else {
        // Si l'ID n'est pas valide, vider les champs
        ui->id->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->genre->setCurrentIndex(-1);
        ui->date->clear();
        ui->tel->clear();
        ui->doc->clear();
    }


}



void MainWindow::on_nom2_textChanged(const QString &text) {  //tri par ordre alphbitique

    Crud crud;
    crud.search_patient(-1, text, ui->tableWidget);

}




void MainWindow::on_tableWidget_cellClicked(int row, int column) {
    Q_UNUSED(column); // Pour éviter l'avertissement "unused parameter"

    // Récupérer les données de la ligne sélectionnée
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0); // Colonne ID
    QTableWidgetItem *nomItem = ui->tableWidget->item(row, 1); // Colonne Nom
    QTableWidgetItem *prenomItem = ui->tableWidget->item(row, 2); // Colonne Prénom
    QTableWidgetItem *genreItem = ui->tableWidget->item(row, 3); // Colonne Genre
    QTableWidgetItem *dateItem = ui->tableWidget->item(row, 4); // Colonne Date de naissance
    QTableWidgetItem *telItem = ui->tableWidget->item(row, 5); // Colonne Téléphone
    QTableWidgetItem *dossierItem = ui->tableWidget->item(row, 6); // Colonne Dossier

    // Remplir les champs du formulaire avec les données récupérées
    if (idItem && nomItem && prenomItem && genreItem && dateItem && telItem && dossierItem) {
        ui->id->setText(idItem->text()); // Remplir le champ ID
        ui->nom->setText(nomItem->text()); // Remplir le champ Nom
        ui->prenom->setText(prenomItem->text()); // Remplir le champ Prénom
        ui->genre->setCurrentText(genreItem->text()); // Remplir le champ Genre
        ui->date->setText(dateItem->text()); // Remplir le champ Date de naissance
        ui->tel->setText(telItem->text()); // Remplir le champ Téléphone
        ui->doc->setText(dossierItem->text()); // Remplir le champ Dossier
    } else {
        qDebug() << "Erreur : Impossible de récupérer les données de la ligne sélectionnée.";
    }
}


void MainWindow::on_pdf_clicked() {
    // Vérifier si une ligne est sélectionnée
    int row = ui->tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Erreur de sélection", "Veuillez sélectionner un patient pour générer le PDF.");
        return;
    }

    // Demander le chemin pour enregistrer le fichier PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    // Création du PDF
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    // Taille de la page
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    // Titre du PDF
    QFont titleFont("Arial", 30, QFont::Bold);
    painter.setFont(titleFont);
    QRect titleRect(0, 100, pageWidth, 100);
    painter.drawText(titleRect, Qt::AlignCenter, "Dossier Patient");

    // Logo
    QPixmap logo(":/new/prefix1/image/Adobe Express - file (5).png"); // Vérifie bien le chemin de l'image
    if (!logo.isNull()) {
        int logoWidth = 400;
        int logoHeight = 350;
        int logoX = pageWidth - logoWidth - 50;
        int logoY = 50;
        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }

    // Styles des textes
    QFont headerFont("Arial", 18, QFont::Bold);
    QFont contentFont("Arial", 16);

    // Position de départ pour l'affichage des données
    int yPosition = 300;
    int rowHeight = 300;
    int padding = 100;

    // En-têtes des informations du patient
    QStringList headers = {"ID", "Nom", "Prénom", "Genre", "Date de naissance", "Téléphone", "Dossier médical"};
    QStringList data;

    // Récupérer les valeurs de la ligne sélectionnée
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *item = ui->tableWidget->item(row, col);
        QString cellText = item && !item->text().isEmpty() ? item->text() : "<Vide>";
        data.append(cellText);
    }

    // Afficher les informations dans le PDF
    for (int i = 0; i < headers.size(); ++i) {
        painter.setFont(headerFont);
        QRect headerRect(padding, yPosition, pageWidth - 2 * padding, rowHeight/2);
        painter.drawText(headerRect, Qt::AlignLeft, headers[i] + " :");

        yPosition += rowHeight/2;

        painter.setFont(contentFont);
        QRect dataRect(padding, yPosition, pageWidth - 2 * padding, rowHeight/2);
        painter.drawText(dataRect, Qt::AlignLeft, data[i]);

        yPosition += rowHeight/2;
        yPosition += 50;
    }

    // Fin du document
    painter.end();

    // Confirmation
    QMessageBox::information(this, "Succès", "Le PDF du patient a été généré avec succès !");
}


void MainWindow::on_cancel_clicked() {
    // Effacer les champs du formulaire
    ui->id->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->genre->setCurrentIndex(-1); // Réinitialiser le QComboBox
    ui->date->clear();
    ui->tel->clear();
    ui->doc->clear();

}

void MainWindow::updateStatistics() {
    int hommeCount = 0;
    int femmeCount = 0;

    // Lire directement les données de la table des patients
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *genreItem = ui->tableWidget->item(row, 3); // Colonne "Genre"

        if (genreItem) {
            QString genre = genreItem->text().toLower();
            if (genre == "homme") {
                hommeCount++;
            } else if (genre == "femme") {
                femmeCount++;
            }
        }
    }

    // Mettre à jour la table des statistiques
    ui->tableWidget_2->clearContents(); // Garder les en-têtes
    ui->tableWidget_2->setRowCount(2);

    ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem("Hommes"));
    ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(QString::number(hommeCount)));

    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Femmes"));
    ui->tableWidget_2->setItem(1, 1, new QTableWidgetItem(QString::number(femmeCount)));
}

