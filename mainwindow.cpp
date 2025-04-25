#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "Crud.h"
#include "PatientDetailsDialog.h"
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QFileDialog>
#include <QUrl>
#include <QFileInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QEasingCurve>
#include "animatedbaritem.h"
#include <QPropertyAnimation>
#include <QtCharts/QPieSeries>
#include <QtCharts>
#include <QGraphicsDropShadowEffect>

// Define constant for telephone length to avoid encoding issues
const int TELEPHONE_LENGTH = 8;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileLabel(nullptr),
    dnaWindow(nullptr),
    showingStats(false)

{
    ui->setupUi(this);
    ui->chartLayout->setVisible(false);

    // Empêcher l'entrée de lettres dans les champs ID et Téléphone
    ui->id->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->tel->setValidator(new QIntValidator(10000000, 99999999, this));

    // Empêcher l'entrée de chiffres dans les champs "Nom" et "Prénom"
    QRegularExpression rx("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->nom->setValidator(validator);
    ui->prenom->setValidator(validator);

    // Initialiser le QComboBox pour le genre
    ui->genre->addItem("Homme");
    ui->genre->addItem("Femme");

    // Initialize fileLabel
    fileLabel = ui->fileLabel;

    // Connexion à la base de données
    connection c;
    if (c.set_connection()) {
        qDebug() << "Database connected";
        Crud crud;
        crud.load_patients(ui->tableWidget);
    } else {
        qDebug() << "Failed to connect to database";
    }

    // Connexions des boutons
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_cellClicked);
    connect(ui->sortComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBox_changed);
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::on_browseButton_clicked);
    connect(ui->DNAbutton, &QPushButton::clicked, this, &MainWindow::on_DNAbutton_clicked);

}

MainWindow::~MainWindow() {
    delete ui;
    if (dnaWindow) {
        delete dnaWindow;  // Nettoyage mémoire
    }
}

void MainWindow::showPatientTable()
{
    // Hide statistics and show patient table
    ui->chartLayout->setVisible(false);
    ui->tableWidget->setVisible(true);

    // Refresh the table data if needed
    Crud crud;
    crud.load_patients(ui->tableWidget);

    // Reset the stats button text/icon if needed
    ui->StatButton->setText("Show Statistics");
}

void MainWindow::on_StatButton_clicked() {
    if (showingStats) {
        showPatientTable();
    } else {
        showStatistics();
    }
    showingStats = !showingStats;
}

void MainWindow::showStatistics() {
    ui->tableWidget->setVisible(false);
    ui->chartLayout->setVisible(true);
    Crud crud;
    crud.load_patients(ui->tableWidget);
    // Nettoyer l'ancien contenu
    QLayout *layout = ui->chartLayout->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        layout = new QVBoxLayout();
        ui->chartLayout->setLayout(layout);
    }

    // Compter les hommes et femmes
    int hommeCount = 0, femmeCount = 0;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *genreItem = ui->tableWidget->item(row, 3);
        if (genreItem) {
            QString genre = genreItem->text().toLower();
            if (genre == "homme") hommeCount++;
            else if (genre == "femme") femmeCount++;
        }
    }

    // === CAMEMBERT ANIMÉ ===
    QPieSeries *pieSeries = new QPieSeries();
    QPieSlice *hommeSlice = pieSeries->append("Hommes", hommeCount);
    QPieSlice *femmeSlice = pieSeries->append("Femmes", femmeCount);

    // Couleurs modernes
    hommeSlice->setColor(QColor(65, 105, 225)); // Bleu royal
    femmeSlice->setColor(QColor(255, 105, 180)); // Rose vif

    // Animation des tranches
    hommeSlice->setExploded(true);
    hommeSlice->setExplodeDistanceFactor(0.1);
    femmeSlice->setExploded(true);
    femmeSlice->setExplodeDistanceFactor(0.1);

    // Effet de lumière
    hommeSlice->setBorderColor(Qt::white);
    femmeSlice->setBorderColor(Qt::white);
    hommeSlice->setBorderWidth(2);
    femmeSlice->setBorderWidth(2);

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    pieChart->legend()->setAlignment(Qt::AlignRight);
    pieChart->legend()->setFont(QFont("Arial", 10));
    pieChart->setBackgroundBrush(QBrush(QColor(240, 248, 255)));
    pieChart->setAnimationOptions(QChart::AllAnimations);

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumSize(400, 400);

    // === GRAPHIQUE À BARRES ANIMÉ ===
    QBarSeries *barSeries = new QBarSeries();

    QBarSet *setHommes = new QBarSet("Hommes");
    *setHommes << hommeCount;
    setHommes->setColor(QColor(65, 105, 225));

    QBarSet *setFemmes = new QBarSet("Femmes");
    *setFemmes << femmeCount;
    setFemmes->setColor(QColor(255, 105, 180));

    barSeries->append(setHommes);
    barSeries->append(setFemmes);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->setBackgroundBrush(QBrush(QColor(240, 248, 255)));
    barChart->legend()->setVisible(true);
    barChart->legend()->setAlignment(Qt::AlignBottom);
    barChart->legend()->setFont(QFont("Arial", 10));

    // Configuration des axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("Genre");
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, std::max(hommeCount, femmeCount) + 1); // +1 pour un peu d'espace
    axisY->setTickCount(std::max(hommeCount, femmeCount) + 2); // Nombre de ticks
    axisY->setLabelFormat("%d"); // Format entier
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->setMinimumSize(250, 400);

    // === CONTENEUR PRINCIPAL ===
    QWidget *container = new QWidget();
    QHBoxLayout *chartLayout = new QHBoxLayout(container);
    chartLayout->addWidget(barChartView);
    chartLayout->addWidget(pieChartView);

    // Style du conteneur
    container->setStyleSheet("background-color: #f0f8ff; border-radius: 15px; padding: 15px;");

    // Effet d'ombre
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(15);
    shadow->setXOffset(5);
    shadow->setYOffset(5);
    shadow->setColor(QColor(0, 0, 0, 150));
    container->setGraphicsEffect(shadow);

    // Titre stylisé
    QLabel *titleLabel = new QLabel("Patients statics");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #4169e1; margin-bottom: 15px;");

    // Layout final
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(container);

    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    ui->chartLayout->layout()->addWidget(mainWidget);
}


void MainWindow::on_DNAbutton_clicked()
{
    if (!dnaWindow) {
        dnaWindow = new DnaWindow(this);  // Création de la fenêtre
        dnaWindow->setAttribute(Qt::WA_DeleteOnClose);  // Gestion automatique de la mémoire
    }

    dnaWindow->show();  // Affichage de la fenêtre
    dnaWindow->raise();  // Mise au premier plan
    dnaWindow->activateWindow();  // Activation de la fenêtre
}


void MainWindow::on_ajouter_clicked() {
    // Récupérer les valeurs des champs de texte
    QString id = ui->id->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString genre = ui->genre->currentText();
    QString date = ui->date->text();
    QString tel = ui->tel->text();

    // Vérification de la longueur de l'ID et du téléphone
    if (id.length() != TELEPHONE_LENGTH || tel.length() != TELEPHONE_LENGTH) {
        QMessageBox::warning(this, "Erreur", "L'ID et le téléphone doivent contenir exactement 8 chiffres.");
        return;
    }

    // Vérification que tous les champs sont remplis et qu'un fichier est sélectionné
    if (nom.isEmpty() || prenom.isEmpty() || currentFilePath.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis et un fichier doit être sélectionné.");
        return;
    }

    // Lire le fichier sélectionné
    QFile file(currentFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier sélectionné.");
        return;
    }
    QByteArray fileData = file.readAll();
    file.close();

    // Extraire uniquement le nom du fichier (pour l'affichage dans l'interface)
    QFileInfo fileInfo(currentFilePath);
    QString fileName = fileInfo.fileName();

    // Créer un objet Crud pour ajouter le patient
    Crud crud;

    // Ajouter le patient à la base de données, en incluant le fichier (dossier de type BLOB)
    crud.add_patient(id.toInt(), nom, prenom, genre, date, fileName, tel.toInt(), fileData);

    // Rafraîchir le tableau
    crud.load_patients(ui->tableWidget);

    // Appeler une fonction pour réinitialiser les champs du formulaire
    on_cancel_clicked();


}

void MainWindow::on_cancel_clicked() {
    ui->id->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->genre->setCurrentIndex(-1);
    ui->date->clear();
    ui->tel->clear();
    if (fileLabel) {
        fileLabel->clear();
    }
    currentFilePath.clear();
    selectedPatientId = -1;
}

void MainWindow::on_nom2_textChanged(const QString &text) {
    Crud crud;
    crud.search_patient(-1, text, ui->tableWidget);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column) {
    Q_UNUSED(column);
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0); // column 0 = ID

    if (idItem) {
        selectedPatientId = idItem->text().toInt();

        // Open the detailed dialog
        PatientDetailsDialog *dialog = new PatientDetailsDialog(selectedPatientId, ui->tableWidget, this);
        dialog->exec();
        delete dialog;


    }
}



void MainWindow::on_sortComboBox_changed(const QString &sortType) {
    Crud crud;
    ui->tableWidget->setRowCount(0);  // Clear the table first
    crud.load_sorted_recherche(ui->tableWidget, sortType);
}

void MainWindow::on_browseButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "All Files (*)");
    if (!filePath.isEmpty()) {
        currentFilePath = filePath;
        QFileInfo fileInfo(filePath);
        if (fileLabel) {
            fileLabel->setText(fileInfo.fileName());  // Show the file name
        }
    }
}
