#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "Crud.h"
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajouter_clicked()
{
    QString id = ui->id->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString genre = ui->genre->text();
    QString date = ui->date->text();
    QString tel = ui->tel->text();
    QString doc = ui->doc->text();

    // Vérification de l'ID (doit être un nombre positif)
    bool idOk;
    int idInt = id.toInt(&idOk);
    if (!idOk || idInt <= 0) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre entier positif.");
        return;
    }

    // Vérification du nom et prénom (lettres uniquement)
    QRegularExpression nameRegex("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$");
    if (!nameRegex.match(nom).hasMatch() || !nameRegex.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le nom et le prénom doivent contenir uniquement des lettres.");
        return;
    }

    // Vérification du genre (doit être Homme ou Femme)
    if (genre.toLower() != "homme" && genre.toLower() != "femme") {
        QMessageBox::warning(this, "Erreur", "Le genre doit être 'Homme' ou 'Femme'.");
        return;
    }


    // Vérification du numéro de téléphone (8 chiffres)
    bool telOk;
    int telInt = tel.toInt(&telOk);
    if (!telOk || tel.length() != 8) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
        return;
    }

    // Vérifier que la description n'est pas vide
    if (doc.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir la description.");
        return;
    }

    // Création et ajout du patient
    Crud add(idInt, nom, prenom, genre, date, doc, telInt);
    add.add_patient(ui->tableWidget);

    // Effacer les champs
    ui->id->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->genre->clear();
    ui->date->clear();
    ui->tel->clear();
    ui->doc->clear();

    QMessageBox::information(this, "Succès", "Patient ajouté avec succès !");
}


void MainWindow::on_drop_clicked()
{
    QString id=ui->id2->text();
    bool test;
    int id2int=id.toInt(&test);
    Crud drop;
    drop.delete_patient(id2int,ui->tableWidget);
    QMessageBox::information(this,"Success","patient droped");
}



void MainWindow::on_mod_clicked() {
    // Récupérer les valeurs des champs
    QString id = ui->id->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString genre = ui->genre->text();
    QString date = ui->date->text();
    QString tel = ui->tel->text();
    QString doc = ui->doc->text();

    // Vérifier si l'ID est bien renseigné
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'ID du patient à modifier.");
        return;
    }

    // Convertir l'ID et le téléphone en entier
    bool idOk, telOk;
    int idInt = id.toInt(&idOk);
    int telInt = tel.toInt(&telOk);

    if (!idOk) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre.");
        return;
    }

    if (!telOk) {
        telInt = 0;  // Pour éviter une mauvaise conversion
    }

    // Appeler la mise à jour du patient
    Crud update;
    update.update_patient(idInt, nom, prenom, genre, date, doc, telInt, ui->tableWidget);

    // Effacer les champs après modification
    ui->id->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->genre->clear();
    ui->date->clear();
    ui->tel->clear();
    ui->doc->clear();

    QMessageBox::information(this, "Succès", "Les données du patient ont été mises à jour !");
}
