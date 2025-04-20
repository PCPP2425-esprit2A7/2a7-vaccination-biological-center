#include "clickablelabel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "connection.h"
#include "vaccin.h"
#include <QString>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPen>
#include <QBrush>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QDesktopServices> // Ajoutez cette ligne en haut du fichier
#include <QUrl> // Ajoutez aussi cette ligne si ce n'est pas déjà présent
#include <conccurance.h>
#include <QUrlQuery>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
     //le signal émis automatiquement par QLineEdit chaque fois que l'utilisateur tape ou modifie le texte.
    ui->setupUi(this);
    connect(ui->id2, &QLineEdit::textChanged, this, &MainWindow::filtrerVaccins);
    connect(ui->label_stat, &ClickableLabel::clicked, this, &MainWindow::on_StatButton_clicked);
    ClickableLabel* clickable = qobject_cast<ClickableLabel*>(ui->labelEtude);
    if (clickable) {
        connect(clickable, &ClickableLabel::clicked, this, &MainWindow::on_btnEtudeConcurrence_clicked);
    } else {
        qDebug() << "Erreur : labelEtude n'est pas un ClickableLabel.";
    }

    connect(ui->labelEtude, &ClickableLabel::clicked, this, &MainWindow::on_btnEtudeConcurrence_clicked);



    // Configuration du tableau
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Connexion pour détecter les sélections
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, [this]() {
        auto selected = ui->tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            currentSelectedId = ui->tableWidget->item(selected.first()->row(), 0)->text().toInt();
        }

    });
    chargerDonneesDansTableWidget(); // Au lieu de setModel



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chargerDonneesDansTableWidget()
{
    ui->chartLayout->setVisible(false);  // Masquer le chartLayout

    QSqlQueryModel *model = v.afficher(); // Utilise votre méthode existante

    // Configure le nombre de colonnes
    ui->tableWidget->setColumnCount(model->columnCount());

    // Configure les en-têtes
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Remplit les données
    ui->tableWidget->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidget->setItem(row, col, item);
        }
    }

    delete model; // Nettoyage mémoire
}
void MainWindow::verifierNom()
{
    QString nom = ui->nom->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$"); // Accepte uniquement les lettres avec accents

    if (nom.isEmpty()) {
        ui->nom_erreur->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(nom).hasMatch()) {
        ui->nom_erreur->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->nom_erreur->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}

void MainWindow::verifierValidation()
{
    QString validation = ui->validation->text();
    QRegularExpression regex("^[0-9]+$"); // Accepte uniquement des chiffres

    if (validation.isEmpty()) {
        ui->validation_erreur->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(validation).hasMatch()) {
        ui->validation_erreur->setText("La validation doit contenir uniquement des chiffres.");
    } else {
        ui->validation_erreur->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}
void MainWindow::verifierDescription()
{
    QString description = ui->description->toPlainText();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$"); // Accepte uniquement des lettres (avec accents) et des espaces

    if (description.isEmpty()) {
        ui->description_erreur->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(description).hasMatch()) {
        ui->description_erreur->setText("La description ne doit contenir que des lettres et des espaces.");
    } else {
        ui->description_erreur->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}
void MainWindow::verifierDateFabrication()
{
    QString fabricationStr = ui->fabrication->text();
    QDate dateFabrication = QDate::fromString(fabricationStr, "yyyy-MM-dd"); // Assurez-vous du bon format
    QDate dateActuelle = QDate::currentDate();
    QDate dateMinimale = dateActuelle.addDays(-30); // La limite est 30 jours avant aujourd’hui

    if (!dateFabrication.isValid()) {
        ui->fabrication_erreur->setText("Format de date invalide. Utilisez AAAA-MM-JJ.");
    }
    else if (dateFabrication < dateMinimale || dateFabrication > dateActuelle) {
        ui->fabrication_erreur->setText("La date doit être entre aujourd'hui et il y a 30 jours.");
    }
    else {
        ui->fabrication_erreur->clear(); // Efface l'erreur si la date est correcte
    }
}
void MainWindow::verifierMaladie()
{
    QString maladie = ui->maladie->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$"); // Accepte uniquement les lettres avec accents

    if (maladie.isEmpty()) {
        ui->maladie_erreur->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(maladie).hasMatch()) {
        ui->maladie_erreur->setText("Le maladie doit contenir uniquement des lettres.");
    } else {
        ui->maladie_erreur->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}

void MainWindow::on_pushButton_15_clicked()
{
     if (isEditMode) return;
    // Validation des champs (identique à votre version originale)
    verifierNom();
    verifierValidation();
    verifierDescription();
    verifierDateFabrication();
    verifierMaladie();

    QString nom = ui->nom->text();
    QString type = ui->type->currentText();
    QString maladie = ui->maladie->text();
    QString fabrication = ui->fabrication->text();
    int validation = ui->validation->text().toInt();
    QString description = ui->description->toPlainText();
    // Connexions pour la validation en temps réel
    connect(ui->nom, &QLineEdit::textChanged, this, &MainWindow::verifierNom);
    connect(ui->validation, &QLineEdit::textChanged, this, &MainWindow::verifierValidation);
    connect(ui->description, &QTextEdit::textChanged, this, &MainWindow::verifierDescription);
    connect(ui->fabrication, &QDateEdit::dateChanged, this, &MainWindow::verifierDateFabrication);
    connect(ui->maladie, &QLineEdit::textChanged, this, &MainWindow::verifierMaladie);


    // Validation des champs (votre logique existante)
    if (nom.isEmpty() || maladie.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    // Vérification que le nom contient uniquement des lettres
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le nom doit contenir uniquement des lettres.");
        return;
    }

    QString validationStr = ui->validation->text();
    QRegularExpression regex1("^[0-9]+$");

    if (!regex1.match(validationStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La validation doit contenir uniquement des chiffres.");
        return;
    }

    QRegularExpression regex2("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$"); // Accepte uniquement des lettres (avec accents) et des espaces
    QString descriptionStr = ui->description->toPlainText();
    if (!regex2.match(descriptionStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La description ne doit contenir que des lettres et des espaces.");
        return;
    }

    verifierDateFabrication();
    if (!ui->fabrication_erreur->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Corrigez la date avant d'ajouter.");
        return;
    }

    // Vérification que le maladie contient uniquement des lettres
    QRegularExpression regex3("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex3.match(maladie).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La maladie doit contenir uniquement des lettres.");
        return;
    }



    // Création et ajout du vaccin
    vaccin newVaccin(nom, type, maladie, fabrication, validation, description);
    bool test = newVaccin.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "Vaccin ajouté avec succès.");
        chargerDonneesDansTableWidget();

        // Réinitialisation des champs
        ui->nom->clear();
        ui->maladie->clear();
        ui->fabrication->clear();
        ui->validation->clear();
        ui->description->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du vaccin.");
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        // Conversion sécurisée
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // Vérification du widget cliqué
        QWidget *clickedWidget = QApplication::widgetAt(mouseEvent->globalPosition().toPoint());

        // Si le clic n'est pas dans le tableau
        if (clickedWidget != ui->tableWidget &&
            (clickedWidget->parentWidget() == nullptr ||
             !clickedWidget->parentWidget()->inherits("QHeaderView")))
        {
            ui->tableWidget->clearSelection();
            ui->tableWidget->clearFocus();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
void MainWindow::on_drop_clicked()
{
    if (currentSelectedId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un vaccin en cliquant sur une ligne");
        return;
    }

    if (QMessageBox::Yes == QMessageBox::question(this, "Confirmation",
                                                  "Voulez-vous vraiment supprimer ce vaccin?",
                                                  QMessageBox::Yes|QMessageBox::No))
    {
        if (v.supprimer(currentSelectedId)) {
            // Recharger les données ou supprimer la ligne directement
            chargerDonneesDansTableWidget();
            currentSelectedId = -1;
            QMessageBox::information(this, "Succès", "Suppression effectuée");
        }
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);

    // Ne pas effacer currentSelectedId ici, seulement la sélection visuelle
    if (!ui->tableWidget->underMouse()) {
        ui->tableWidget->clearSelection();
        currentSelectedId = -1;
    }
}
void MainWindow::on_pushButton_Modifier_clicked()
{
    int id = ui->id2->text().toInt();
    QString nom, type, maladie, fabrication, description;
    int validation;
    if (currentSelectedId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un vaccin en cliquant sur une ligne");
        return;
    }

    if (v.chargerVaccin(currentSelectedId, nom, type, maladie, fabrication, validation, description)) {
        ui->nom->setText(nom);
        ui->type->setCurrentText(type);
        ui->maladie->setText(maladie);
        ui->fabrication->setDate(QDate::fromString(fabrication, "yyyy-MM-dd"));
        ui->validation->setText(QString::number(validation));
        ui->description->setText(description);

        // 3. Transforme le bouton "Ajouter" en "Rafraîchir" FONCTIONNEL
        ui->pushButton_15->setText("Rafraîchir");
        isEditMode = true;

        // 4. Reconnecte dynamiquement le bouton
        disconnect(ui->pushButton_15, nullptr, nullptr, nullptr); // Désactive les anciennes connexions
        connect(ui->pushButton_15, &QPushButton::clicked, this, [this]() {
            on_pushButton_Rafraichir_clicked(); // Appel DIRECT à votre fonction existante
        });
    } else {
        QMessageBox::critical(this, "Erreur", "Aucun vaccin trouvé avec cet ID.");
    }
}

void MainWindow::on_pushButton_Rafraichir_clicked()
{
    // Logique identique à on_pushButton_15_clicked() mais avec modification
    int id = ui->id2->text().toInt();
    if (isEditMode) {
    QString nom = ui->nom->text();
    QString type = ui->type->currentText();
    QString maladie = ui->maladie->text();
    QString fabrication = ui->fabrication->text();
    int validation = ui->validation->text().toInt();
    QString description = ui->description->toPlainText();
    connect(ui->nom, &QLineEdit::textChanged, this, &MainWindow::verifierNom);
    connect(ui->validation, &QLineEdit::textChanged, this, &MainWindow::verifierValidation);
    connect(ui->description, &QTextEdit::textChanged, this, &MainWindow::verifierDescription);
    connect(ui->fabrication, &QDateEdit::dateChanged, this, &MainWindow::verifierDateFabrication);
    connect(ui->maladie, &QLineEdit::textChanged, this, &MainWindow::verifierMaladie);

    if (nom.isEmpty() || maladie.isEmpty()  || description.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Vérification que le nom contient uniquement des lettres
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le nom doit contenir uniquement des lettres.");
        return;
    }

    QString validationStr = ui->validation->text();
    QRegularExpression regex1("^[0-9]+$");

    if (!regex1.match(validationStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La validation doit contenir uniquement des chiffres.");
        return;
    }

    QRegularExpression regex2("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$"); // Accepte uniquement des lettres (avec accents) et des espaces
    QString descriptionStr = ui->description->toPlainText();
    if (!regex2.match(descriptionStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La description ne doit contenir que des lettres et des espaces.");
        return;
    }

    verifierDateFabrication();
    if (!ui->fabrication_erreur->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Corrigez la date avant d'ajouter.");
        return;
    }

    // Vérification que le maladie contient uniquement des lettres
    QRegularExpression regex3("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex3.match(maladie).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La maladie doit contenir uniquement des lettres.");
        return;
    }

    bool test = v.modifier(currentSelectedId, nom, type, maladie, fabrication, validation, description);

    if (test) {
        QMessageBox::information(this, "Succès", "Vaccin modifié avec succès.");
       chargerDonneesDansTableWidget();
        // 2. Réinitialise le bouton à "Ajouter"
        ui->pushButton_15->setText("Ajouter");
        isEditMode = false;

        // 3. Reconnecte à la fonction d'ajout
        disconnect(ui->pushButton_15, nullptr, nullptr, nullptr);
        connect(ui->pushButton_15, &QPushButton::clicked, this, &MainWindow::on_pushButton_15_clicked);
        currentEditId = -1;
        ui->nom->clear();
        ui->maladie->clear();
        ui->fabrication->clear();
        ui->validation->clear();
        ui->description->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du vaccin.");
    }
}
}

//rechercher vaccin
void MainWindow::filtrerVaccins(const QString &term)
{
    QString critere = ui->comboBox_critere->currentText();
    QSqlQueryModel* model = nullptr;

    // Si le champ est vide, charger tous les vaccins
    if (term.isEmpty()) {
        model = v.afficher();  // Afficher tous les vaccins
        ui->label_info->hide();  // Cacher le message d'erreur éventuel
    } else {
        model = v.rechercher(term, critere);
    }

    if (!model) return;

    // Vérifier s'il y a des résultats
    if (model->rowCount() == 0) {
        // Tableau : une seule ligne avec un message
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Message");
        QTableWidgetItem *item = new QTableWidgetItem("🔍 Aucun vaccin ne correspond à votre recherche.");
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(0, 0, item);

        // Label : message doux au-dessus du tableau
        ui->label_info->setText("Aucun résultat trouvé pour \"" + term + "\".");
        ui->label_info->setStyleSheet("color: orange; font-weight: bold;");
        ui->label_info->show();

        delete model;
        return;
    }

    // Si on a des résultats
    ui->label_info->hide();  // Cacher le label d’erreur
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(model->columnCount());
   // On récupère les noms des colonnes (ex: nom, type…) et on les stocke dans headers
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setRowCount(model->rowCount());

    QColor highlightColor = QColor(173, 216, 230); // Bleu clair

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());

            if (!term.isEmpty()) {
                item->setBackground(highlightColor);  // Colorer uniquement si recherche
            }

            ui->tableWidget->setItem(row, col, item);
        }
    }

    delete model;
}













void MainWindow::on_pushButton_Reinitialiser_clicked()
{
    ui->tableWidget->setVisible(true);
    ui->tableWidget->clear(); // Supprime tout (colonnes + données)
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    // Ensuite tu ajoutes les colonnes + tu remplis avec les données du modèle si besoin

    // 1. Réinitialiser les couleurs
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            if (QTableWidgetItem* item = ui->tableWidget->item(i, j)) {
                item->setBackground(Qt::white);
                item->setForeground(Qt::black);
            }
        }
    }

    // 2. Vider les champs de recherche/modification
    ui->id2->clear();
    ui->nom->clear();
    ui->maladie->clear();
    ui->fabrication->clear();
    ui->validation->clear();
    ui->description->clear();

    // 3. Recharger toutes les données depuis la base
    chargerDonneesDansTableWidget();  // Votre fonction existante

    // 4. Remettre le bouton en mode "Ajouter" si nécessaire
    if (ui->pushButton_15->text() == "Rafraîchir") {
        ui->pushButton_15->setText("Ajouter");
    }

    QMessageBox::information(this, "Succès", "Affichage réinitialisé");
}




void MainWindow::on_pushButton_tri_clicked()
{
    QString critere = ui->trier->currentText().toLower();
    bool ascendant = true; // ou false selon votre besoin

    QSqlQueryModel* model = v.trier(critere, ascendant);

    ui->tableWidget->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidget->setItem(row, col, item);
        }
    }
    delete model;
}





QString MainWindow::getSelectedVaccinId() {
    QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        return "";  // Aucun vaccin sélectionné
    }

    // Supposons que l'ID du vaccin se trouve dans la première colonne (colonne 0)
    //récupère seulement la première ligne sélectionnée
    QModelIndex index = selectedRows.first();
    return ui->tableWidget->item(index.row(), 0)->text();  // Retourne l'ID du vaccin
}





void MainWindow::exporterCSV() {
    QSqlQueryModel* model = v.exporterPDF(); // ou autre méthode qui retourne un QSqlQueryModel*
    if (!model) return;

    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer CSV", "", "Fichiers CSV (*.csv)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream stream(&file);

    // Écrire les en-têtes
    QStringList headers;
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        header.replace(";", " "); // éviter les séparateurs dans les en-têtes
        headers << "\"" + header + "\"";
    }
    stream << headers.join(";") << "\n";

    // Écrire les lignes de données
    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->data(model->index(row, col)).toString();
            text.replace("\n", " ");
            text.replace("\r", " ");
            text.replace(";", ","); // éviter les séparateurs dans le contenu
            rowData << "\"" + text + "\"";
        }
        stream << rowData.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Succès", "Le fichier CSV a été exporté avec succès !");
}








#pragma execution_character_set("utf-8")

void MainWindow::on_pushButton_PDF_clicked() {
    /*QString idVaccin = getSelectedVaccinId();
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QSqlQueryModel* model = idVaccin.isEmpty() ? v.exporterPDF() : v.exporterPDF(idVaccin);
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données !");
        return;
    }*/


    //À chaque fois que l’utilisateur clique sur le bouton PDF, la fonction est rappelée, mais pdfClickCount garde sa valeur d’avant.
    static int pdfClickCount = 0; // Garde en mémoire le nombre de clics

    QString idVaccin = getSelectedVaccinId();
    bool isVaccinSelected = !idVaccin.isEmpty();

    if (isVaccinSelected) {
        pdfClickCount = 0; // Réinitialiser le compteur
    } else {
        pdfClickCount++; // Incrémenter si aucun vaccin sélectionné
    }

    if (!isVaccinSelected && pdfClickCount >= 2) {
        pdfClickCount = 0;
        exporterCSV(); // Appel à ta fonction Excel
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QSqlQueryModel* model = isVaccinSelected ? v.exporterPDF(idVaccin) : v.exporterPDF();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données !");
        return;
    }




    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);

    QPainter painter(&writer);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bleuBiomed(0, 102, 204);
    QPixmap logo("C:/Users/weldk/OneDrive/Documents/jihedd/image/Adobe Express - file (5).png");

    int y = 600;
    int currentPage = 1;

    // === EN-TÊTE FIXE DE LA PAGE
    auto drawHeader = [&]() {
        if (!logo.isNull()) painter.drawPixmap(100, 100, 150, 150, logo);
        painter.setPen(bleuBiomed);
        painter.setFont(QFont("Arial", 18, QFont::Bold));
        painter.drawText(300, 150, "Laboratoire Biomed");
        painter.setFont(QFont("Arial", 12));
        painter.drawText(300, 200, "Fichier généré automatiquement");
        painter.drawText(300, 250, "Date : " + QDate::currentDate().toString("dd/MM/yyyy"));
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(200, 400, idVaccin.isEmpty() ? "🧬 Liste des vaccins enregistrés" : "🧬 Détails du vaccin");
        painter.setPen(QPen(Qt::gray, 2));
        painter.drawLine(100, 530, 5000, 530);
    };

    auto drawFooter = [&](int pageNum) {
        int footerTopY = writer.height() - 350;
        int leftX = 100;
        painter.setPen(QPen(Qt::gray, 1));
        painter.drawLine(leftX, footerTopY, writer.width() - leftX, footerTopY);
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.setPen(bleuBiomed);
        painter.drawText(leftX, footerTopY + 40, "Nos contacts");
        painter.setFont(QFont("Arial", 9));
        painter.setPen(Qt::black);
        painter.drawText(leftX, footerTopY + 90, "📍Adresse     : Tunis, Tunisie");
        painter.drawText(leftX, footerTopY + 135, "✉Email       : contact@biomed-lab.tn");
        painter.drawText(leftX, footerTopY + 180, "📞Téléphone   : +216 70 123 456");
        painter.drawText(leftX, footerTopY + 225, "🌐Site Web    : www.biomed-lab.tn");
        painter.setFont(QFont("Arial", 9, QFont::StyleItalic));
        painter.drawText(writer.width() - 200, writer.height() - 80, QString("Page %1").arg(pageNum));
    };

    drawHeader();

    // === DONNÉES
    painter.setFont(QFont("Arial", 10));
    painter.setPen(Qt::black);  // S'assurer que la couleur du texte est noire
    int xStart = 100;
    QVector<int> columnWidths = {200, 250, 250, 250, 250, 250, 700}; // Augmenté pour plus d'espace
    QFontMetrics metrics(painter.font());

    if (idVaccin.isEmpty()) {
        int maxHeight = 0;
        //Calcul de la hauteur maximale d’une ligne du tableau
        for (int row = 0; row < model->rowCount(); ++row) {
            int rowHeight = 0;
            for (int col = 0; col < model->columnCount(); ++col) {
                QString text = model->data(model->index(row, col)).toString();
                // mesurer combien de hauteur il faut pour afficher ce texte avec retour à la ligne (WordWrap) dans la largeur prévue (columnWidths[col])
                QRect rect = metrics.boundingRect(QRect(0, 0, columnWidths[col], 0), Qt::TextWordWrap, text);
                rowHeight = std::max(rowHeight, rect.height());
            }
            maxHeight = std::max(maxHeight, rowHeight);
        }

        int rowHeight = maxHeight + 50;  // Augmenter l'espace entre les lignes

        auto drawTableHeader = [&]() {
            painter.setFont(QFont("Arial", 11, QFont::Bold));
            int xPos = xStart;
            QStringList headers = {"ID", "Nom", "Type", "Maladie", "Fabrication", "Validation", "Description"};
            for (int i = 0; i < headers.size(); ++i) {
                QRect rect(xPos, y, columnWidths[i], 60);  // Augmenter la hauteur de l'en-tête
                painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, headers[i]);
                xPos += columnWidths[i];
            }
            y += 80; // Plus grand espace entre l’en-tête et la première ligne
            painter.setFont(QFont("Arial", 10));
        };

        drawTableHeader();

        for (int row = 0; row < model->rowCount(); ++row) {
            // changer de page
            if (y + rowHeight + 350 > writer.height()) {
                drawFooter(currentPage++);
                writer.newPage();
                y = 600;
                drawHeader();
                drawTableHeader(); // Redessiner en-tête du tableau
                painter.setPen(Qt::black);  // Réinitialiser la couleur à noir
            }

            int xPos = xStart;
            for (int col = 0; col < model->columnCount(); ++col) {
                QString text = model->data(model->index(row, col)).toString();
                QRect cellRect(xPos, y, columnWidths[col], rowHeight);
                painter.drawText(cellRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, text);
                xPos += columnWidths[col];
            }
            //dessiner la ligne suivante
            y += rowHeight;
        }
    } else {
        QStringList labels = {"ID", "Nom", "Type", "Maladie", "Fabrication", "Validation", "Description"};
        int xLeft = 200;
        for (int i = 0; i < model->columnCount(); ++i) {
            QString label = labels[i] + " : ";
            QString value = model->data(model->index(0, i)).toString();
            painter.drawText(xLeft, y, label + value);
            y += 150;
        }
    }

    drawFooter(currentPage);
    painter.end();

    QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès !");
}















void MainWindow::afficherHistoriqueVaccin(int idVaccin)
{
    QSqlQueryModel *model = v.afficherHistorique(idVaccin);
    if (!model) return;

    // Vider le tableau
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(model->columnCount());

    // Définir les en-têtes
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Activer le retour à la ligne
    ui->tableWidget->setWordWrap(true);

    // Remplir les données
    ui->tableWidget->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();

            QTableWidgetItem *item = new QTableWidgetItem(data);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft); //en haut et à gauche
            item->setToolTip(data); // Texte complet au survol
            item->setFlags(item->flags() ^ Qt::ItemIsEditable); // Cela permet de désactiver l'édition d'un item

            ui->tableWidget->setItem(row, col, item);
        }
    }

    // Ajuster taille des colonnes et lignes au contenu
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    // Pour empêcher l'édition directe (sécurité visuelle)
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //rend le QTableWidget en lecture seule

    delete model;
}





/*void MainWindow::on_pushButton_Historique_clicked()
{
    int row = ui->tableWidget->currentRow();

    // Si aucune ligne n'est sélectionnée → afficher tout l'historique
    if (row < 0) {
        int reponse = QMessageBox::question(
            this,
            "Affichage de l'historique",
            "Aucun vaccin sélectionné.\nSouhaitez-vous afficher l'historique de tous les vaccins ?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reponse == QMessageBox::Yes) {
            afficherHistoriqueVaccin(-1);  // -1 pour tous les vaccins
        }

        return;
    }

    // Sinon → afficher l’historique du vaccin sélectionné
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    if (!item) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer l'ID du vaccin.");
        return;
    }

    int idVaccin = item->text().toInt();
    afficherHistoriqueVaccin(idVaccin);


}*/


void MainWindow::on_pushButton_Historique_clicked()
{
    QItemSelectionModel* selectionModel = ui->tableWidget->selectionModel(); //Récupère le modèle de sélection
    int row = -1;

    if (selectionModel && selectionModel->hasSelection()) {  //si une ou plusieurs lignes sont sélectionnées
        row = selectionModel->currentIndex().row();   //envoie le numéro de la ligne de cette cellule.
    }

    if (row >= 0) {
        // Un vaccin est sélectionné  afficher l’historique du vaccin sélectionné
        QTableWidgetItem *item = ui->tableWidget->item(row, 0);
        if (item) {
            int idVaccin = item->text().toInt();
            afficherHistoriqueVaccin(idVaccin);
        }
    } else {
        // Aucun vaccin sélectionné → afficher tout l’historique (sans message)
        afficherHistoriqueVaccin(-1);  // -1 pour tous les vaccins
    }
}








void MainWindow::on_StatButton_clicked() {
    ui->chartLayout->setVisible(true);
    ui->tableWidget->setVisible(false);

    // Nettoyer l'ancien contenu
    QLayout *layout = ui->chartLayout->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();  // Supprimer les widgets (graphiques)
            delete item;
        }
    } else {
        layout = new QHBoxLayout();  // Disposition horizontale
        ui->chartLayout->setLayout(layout);
    }

    // Récupérer les statistiques
    // QVector<QPair<int, int>> stats = v.getStatistiquesValidation();
    QVector<QPair<QString, int>> stats = v.getStatistiquesParType();
    if (stats.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Aucune donnée disponible pour les statistiques.");
        return;
    }

    QStringList categories;
    QVector<int> values;
    int maxValue = 0;
    //Boucle for sur un vecteur de paires
    for (const auto &stat : stats) {
        categories.append(stat.first);
        //categories.append(QString::number(stat.first));  //categories = ["30", "60", "90"]
        values.append(stat.second);  //values = [5, 2, 7]
        maxValue = std::max(maxValue, stat.second);   //On met à jour la valeur maximale parmi toutes les values
    }

    // === CAMEMBERT
    QPieSeries *pieSeries = new QPieSeries();
    //On remplit la série avec les données categories et values.
    for (int i = 0; i < categories.size(); ++i) {
        // pieSeries->append("Durée " + categories[i] + " jrs", values[i]);
        pieSeries->append("type : " + categories[i] + " ", values[i]);
    }
    //Création du graphique principal qui va contenir la série pieSeries
    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    //pieChart->setTitle("Répartition des vaccins par durée de validation");
    pieChart->setTitle("Répartition des vaccins par leur type");
    pieChart->legend()->setAlignment(Qt::AlignRight);
    pieChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
    pieChart->setBackgroundPen(Qt::NoPen);  //pas de ligne de contour
    //Création d’une vue graphique pour afficher le QChart
    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumSize(400, 300);
    pieChartView->setStyleSheet("background-color: rgb(243, 249, 251);");

    // === BARRES AVEC ANIMATION
    QGraphicsScene *scene = new QGraphicsScene();
    int barWidth = 50, gap = 30, chartHeight = 300;
    int xPos = 50, yBase = chartHeight - 70;

    for (int i = 0; i < values.size(); ++i) {
        int barHeight = (values[i] * (chartHeight - 100)) / maxValue;
        QColor barColor = pieSeries->slices().at(i)->brush().color();

        // 🔸 Création de la barre animée
        AnimatedBarItem *bar = new AnimatedBarItem(xPos, yBase, barWidth, barColor);
        scene->addItem(bar);

        QPropertyAnimation *anim = new QPropertyAnimation(bar, "barHeight");
        anim->setDuration(800);
        anim->setStartValue(0);
        anim->setEndValue(barHeight);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        // 🔸 Ajout du texte en dessous
        //QGraphicsTextItem *label = new QGraphicsTextItem(categories[i] + " jrs");
        QGraphicsTextItem *label = new QGraphicsTextItem(" type: "+ categories[i]);
        label->setDefaultTextColor(Qt::black);
        label->setFont(QFont("Arial", 10, QFont::Bold));
        qreal labelX = xPos + (barWidth / 2) - (label->boundingRect().width() / 2);
        qreal labelY = yBase + 5;
        label->setPos(labelX, labelY);
        scene->addItem(label);

        xPos += barWidth + gap;
    }

    scene->setSceneRect(0, 0, xPos + 50, chartHeight + 50);

    QGraphicsView *barView = new QGraphicsView(scene);
    barView->setRenderHint(QPainter::Antialiasing);
    barView->setMinimumSize(500, 350);
    barView->setStyleSheet("background-color: rgb(243, 249, 251);");

    // === AJOUTER LES GRAPHIQUES AU LAYOUT
    ui->chartLayout->layout()->addWidget(barView);       // Barres à gauche
    ui->chartLayout->layout()->addWidget(pieChartView);  // Camembert à droite
}





#include <QMessageBox>  // Ajoute l'inclusion de QMessageBox






/*void MainWindow::on_btnEtudeConcurrence_clicked()
{
    // ✅ Vérifie la sélection
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un vaccin.");
        return;
    }

    // ✅ Récupération des infos du vaccin sélectionné
    QString id = ui->tableWidget->item(row, 0)->text();
    QString type = ui->tableWidget->item(row, 2)->text();
    QString maladie = ui->tableWidget->item(row, 3)->text();
    QString description = ui->tableWidget->item(row, 6)->text();

    // ✅ Requête pour obtenir les concurrents du même type et maladie
    QStringList descriptionsConcurrents;
    QSqlQuery query;
    query.prepare("SELECT NOM, DESCRIPTION FROM VACCINS WHERE TYPE = :type AND MALADIE = :maladie AND ID != :id");
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":id", id);

    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value("NOM").toString();
            QString desc = query.value("DESCRIPTION").toString();

            // Format attendu par GPT : "Nom : X | Description : Y"
            descriptionsConcurrents << QString("Nom : %1 | Description : %2").arg(nom, desc);
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les autres vaccins.");
        return;
    }

    // ✅ Appel à l'IA pour analyse
    Conccurance *ai = new Conccurance(this);
    connect(ai, &Conccurance::analysisReady, this, [=](const QString &result) {
        QMessageBox::information(this, "Résultat de l'analyse de concurrence", result);
    });
    ai->analyserConcurrence(type, maladie, description, descriptionsConcurrents);
}
*/

void MainWindow::on_btnEtudeConcurrence_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un vaccin.");
        return;
    }

    QString id = ui->tableWidget->item(row, 0)->text();
    QString type = ui->tableWidget->item(row, 2)->text();
    QString maladie = ui->tableWidget->item(row, 3)->text();
    QString description = ui->tableWidget->item(row, 6)->text();

    /*QStringList descriptionsConcurrents;
    QSqlQuery query;
    query.prepare("SELECT NOM, DESCRIPTION FROM VACCINS WHERE TYPE = :type AND MALADIE = :maladie AND ID != :id");
    query.bindValue(":type", type);
    query.bindValue(":maladie", maladie);
    query.bindValue(":id", id);

    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value("NOM").toString();
            QString desc = query.value("DESCRIPTION").toString();
            descriptionsConcurrents << QString("Nom : %1 | Description : %2").arg(nom, desc); //stocke nom et desc
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les autres vaccins.");
        return;
    }
    */

    QStringList descriptionsConcurrents = v.getConcurrents(type, maladie, id);


    Conccurance *ai = new Conccurance(this);  // Cela signifie que this est passé comme paramètre au constructeur
    connect(ai, &Conccurance::analysisReady, this, [=](const QString &result) { //Quand tu as fini d'analyser, dis-le-moi, et moi j'affiche le résultat dans une fenêtre
        //ce slot est une fonction lambda [=](const QString &result), qui prend le résultat de l'analyse de concurrence en entrée et affiche ce résultat
        QMessageBox::information(this, "Résultat de l'analyse de concurrence", result);
    });
    ai->analyserConcurrence(type, maladie, description, descriptionsConcurrents);
}


















