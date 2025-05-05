#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QString>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QFont>
#include <QRect>
#include <QDate>
#include <QPageSize>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QLayout>
#include <QDateEdit>
#include <QScopedPointer>
#include <QRegularExpression>
#include <QUrl>
#include <QFileInfo>
#include <QEasingCurve>
#include <QtCharts>
#include <QGraphicsDropShadowEffect>
//jiheddddd
#include "clickablelabel.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QtCharts/QChart>
#include <QDesktopServices> // Ajoutez cette ligne en haut du fichier
#include <conccurance.h>
#include <QUrlQuery>
#include <QTimer>
//haw fi khatrek 2
#include <QPropertyAnimation>
#include <QSerialPortInfo>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>
#include <QPrinter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QInputDialog>
#include <QTextDocument>
#include <QDebug>
#include <QMenu>
#include <QProcess>
#include <QCursor>
#include <QFormLayout>
#include "qrcodegen/QrCode.hpp"

//faresssss
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDate>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPixmap>
#include <QRect>
#include <QFont>



// Define constant for telephone length to avoid encoding issues
const int TELEPHONE_LENGTH = 8;
using qrcodegen::QrCode;
ClassificationDelegate::ClassificationDelegate(QObject *parent) : QStyledItemDelegate(parent) {}
QWidget *ClassificationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems({"BSL-1", "BSL-2", "BSL-3", "BSL-4"});
    return editor;
}

void ClassificationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int idx = comboBox->findText(value);
    if (idx >= 0) {
        comboBox->setCurrentIndex(idx);
    }
}

void ClassificationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}
DateDelegate::DateDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *editor = new QDateEdit(parent);
    editor->setDisplayFormat("yyyy-MM-dd");
    editor->setCalendarPopup(true);
    editor->setDate(QDate::currentDate());
    return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);
    QDate date = QDate::fromString(value, "yyyy-MM-dd");
    if (date.isValid()) {
        dateEdit->setDate(date);
    } else {
        dateEdit->setDate(QDate::currentDate());
    }
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);
    QDate date = dateEdit->date();
    model->setData(index, date.toString("yyyy-MM-dd"), Qt::EditRole);
}


//faresssssss

// Type Delegate Implementation
TypeDelegate::TypeDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *TypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems({"Consomable", "Machine"});
    return editor;
}

void TypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int idx = comboBox->findText(value);
    if (idx >= 0) {
        comboBox->setCurrentIndex(idx);
    }
}

void TypeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}

// Etat Delegate Implementation
EtatDelegate::EtatDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *EtatDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems({"Priority", "Damaged", "Functional"});
    return editor;
}

void EtatDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int idx = comboBox->findText(value);
    if (idx >= 0) {
        comboBox->setCurrentIndex(idx);
    }
}

void EtatDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}








MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isConnected(false),
    page(8),
    userEditMode(false),
    currentUserEditId(-1),
    isUserLoggedIn(false),
    researchEditMode(false),
    currentResearchEditId(-1),
    isTableBeingUpdated(false),
    classDelegate(nullptr),
    dateDelegate(nullptr),
    aiWindow(nullptr),
    timer(nullptr),
    arduino(nullptr),
    serialHandler(nullptr),
    fileLabel(nullptr),
    dnaWindowp(nullptr),
    showingStats(false)
{
    ui->setupUi(this);

    // Common UI setup from both constructors
    ui->chartLayoutp->setVisible(false);
    ui->chartLayoutR->setVisible(false);
    ui->tableWidgetR->setVisible(true);
    ui->rfidUID->setReadOnly(true);

    // Input validation from your constructor
    // Empêcher l'entrée de lettres dans les champs ID et Téléphone
    ui->idp->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->telp->setValidator(new QIntValidator(10000000, 99999999, this));

    // Empêcher l'entrée de chiffres dans les champs "Nom" et "Prénom"
    QRegularExpression rx("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->nomp->setValidator(validator);
    ui->prenomp->setValidator(validator);

    // Initialize QComboBox for genre from your constructor
    ui->genrep->addItem("Homme");
    ui->genrep->addItem("Femme");

    // Initialize fileLabel from your constructor
    fileLabel = ui->fileLabelp;


    ui->tablerdv->setStyleSheet(
        "QTableWidget {"
        "    background-color: #f0f0f0;"          // Couleur de fond globale
        "    alternate-background-color: #dbe9ff;" // Alternance ligne sur deux
        "    selection-background-color: #87cefa;" // Couleur sur sélection
        "    selection-color: black;"             // Texte sélectionné
        "    color: black;"                        // Texte normal
        "    gridline-color: #ccc;"               // Couleur des lignes
        "}"
        "QHeaderView::section {"
        "    background-color: #3a7ca5;"          // En-tête
        "    color: white;"
        "    padding: 4px;"
        "    font-weight: bold;"
        "    border: 1px solid #ddd;"
        "}"
        );
    // Database connection (using project's approach but with your patient loading)
    connection c;
    if (c.set_connection()) {
        qDebug() << "Database connected";
        isConnected = true;
        Crudp crudp;
        crudp.load_patients(ui->tableWidgetp);
    } else {
        qDebug() << "Failed to connect to database";
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database!");
    }

    // Create timer but don't start it yet (from project)
    timer = new QTimer(this);
    timer->setInterval(2000);

    // Create Arduino but don't connect yet (from project)
    arduino = new Arduino();
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTemperature);

    // Initialize and connect RFID handler (from project)
    try {
        serialHandler = new SerialHandler();
        if (serialHandler) {
            connect(serialHandler, &SerialHandler::rfidReceived, this, &MainWindow::handleRFID);
        }
    } catch (...) {
        qDebug() << "Failed to initialize serial handler.";
    }

    // Champs page 3
    id_2 = new QLineEdit(this);
    search = new QLineEdit(this);
    addbutton_2 = new QPushButton("Ajouter", this);
    updatebutton_2 = new QPushButton("Modifier", this);
    deletebutton_2 = new QPushButton("Supprimer", this);
    searchbutton_2 = new QPushButton("Rechercher", this);
    displaybutton_2 = new QPushButton("Afficher", this);
    qr = new QPushButton("QR Code", this);
    sort = new QPushButton("Trier", this);
    voice = new QPushButton("🎙️ Vocal", this);
    statsButton = new QPushButton("📊 Statistiques", this);
    btnPrioriser = new QPushButton("Prioriser Absents", this);
    btnGenererAuto = new QPushButton("Générer Auto", this);
    btnConnecterArduino = new QPushButton("Connecter Arduino", this);
    pushButton_18 = new QPushButton("Exporter PDF", this);
    tableView_2 = new QTableView(this);

    // Champs page 4 (modification)
    idp_3 = new QLineEdit(this);
    ide_3 = new QLineEdit(this);
    statut_3 = new QLineEdit(this);
    dur_3 = new QLineEdit(this);
    heure_3 = new QLineEdit(this);
    date_3 = new QLineEdit(this);
    on_saveButton = new QPushButton("Enregistrer", this);
    on_pushButton_28 = new QPushButton("Retour", this);

    // Champs ajout
    idp_2 = new QLineEdit(this);
    ide_2 = new QLineEdit(this);
    statut_2 = new QLineEdit(this);
    dur_2 = new QLineEdit(this);
    heure_2 = new QLineEdit(this);
    date_2 = new QLineEdit(this);

    // Statistiques
    pieChartView = new QChartView(this);
    barChartView = new QGraphicsView(this);
    statChartLayout = new QWidget(this);  // <-- pour afficher les statistiques dynamiquement

    // === Création des pages internes ===
    page_3 = new QWidget(this);
    page_4 = new QWidget(this);
    page_statistiques = new QWidget(this);

    // Layout page 3
    QVBoxLayout *layoutPage3 = new QVBoxLayout(page_3);
    QHBoxLayout *searchRow = new QHBoxLayout();
    searchRow->addWidget(new QLabel("Recherche par ID:", this));
    searchRow->addWidget(search);
    searchRow->addWidget(searchbutton_2);
    layoutPage3->addLayout(searchRow);
    layoutPage3->addWidget(tableView_2);

    QHBoxLayout *actionRow1 = new QHBoxLayout();
    actionRow1->addWidget(addbutton_2);
    actionRow1->addWidget(updatebutton_2);
    actionRow1->addWidget(deletebutton_2);
    actionRow1->addWidget(displaybutton_2);
    layoutPage3->addLayout(actionRow1);

    QHBoxLayout *actionRow2 = new QHBoxLayout();
    actionRow2->addWidget(qr);
    actionRow2->addWidget(pushButton_18);
    actionRow2->addWidget(sort);
    actionRow2->addWidget(voice);
    layoutPage3->addLayout(actionRow2);

    QHBoxLayout *actionRow3 = new QHBoxLayout();
    actionRow3->addWidget(statsButton);
    actionRow3->addWidget(btnPrioriser);
    actionRow3->addWidget(btnGenererAuto);
    actionRow3->addWidget(btnConnecterArduino);
    layoutPage3->addLayout(actionRow3);

    // Layout page 4
    QFormLayout *layoutPage4 = new QFormLayout(page_4);
    layoutPage4->addRow("Date", date_3);
    layoutPage4->addRow("Heure", heure_3);
    layoutPage4->addRow("Durée", dur_3);
    layoutPage4->addRow("Statut", statut_3);
    layoutPage4->addRow("ID Employé", ide_3);
    layoutPage4->addRow("ID Patient", idp_3);
    layoutPage4->addWidget(on_saveButton);
    layoutPage4->addWidget(on_pushButton_28);

    // Layout page statistiques
    // utile pour camembert/barres

    QHBoxLayout *layoutStats = new QHBoxLayout(page_statistiques);
    layoutStats->addWidget(statChartLayout);  // <- tout est local


    layoutStats->addWidget(barChartView);
    layoutStats->addWidget(pieChartView);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);




    // Signal connections from your constructor
    connect(ui->tableWidgetp, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidgetp_cellClicked);
    connect(ui->sortComboBoxp, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxp_changed);
    connect(ui->browseButtonp, &QPushButton::clicked, this, &MainWindow::on_browseButtonp_clicked);
    connect(ui->DNAbutton, &QPushButton::clicked, this, &MainWindow::on_DNAbutton_clicked);
    connect(ui->tablerdv, &QTableWidget::cellDoubleClicked, this, &MainWindow::on_rdvRowDoubleClicked);


    // Show login page (from project)
    showLoginPage();

    //jiheddddddddddd



}


MainWindow::~MainWindow()
{
    // Clean up Arduino resources (from project)
    if (isConnected && arduino) {
        arduino->close_arduino();
    }
    delete arduino;

    // Clean up DNA window (from your code)
    if (dnaWindowp) {
        delete dnaWindowp;
    }

    // Clean up serial handler (should be added)
    if (serialHandler) {
        delete serialHandler;
    }

    // Clean up timer (should be added)
    if (timer) {
        delete timer;
    }

    // Clean up UI (common to both)
    delete ui;
}

void MainWindow::on_ajouterE_clicked()
{
    // Get values from UI
    QString idStr = ui->id->text().trimmed();
    QString nome = ui->nom->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString telStr = ui->tel->text().trimmed();
    QString adresse = ui->address->text().trimmed();
    QString mdp = ui->mdp->text().trimmed();
    QString role = ui->role->currentText().trimmed();
    QString salaireStr = ui->salaire->text().trimmed();
    QString RFID_UID = currentRFID.trimmed();  // Get RFID UID from the UI

    // 🚨 Check if any field is empty
    if (idStr.isEmpty() || nome.isEmpty() || email.isEmpty() || telStr.isEmpty() ||
        adresse.isEmpty() || mdp.isEmpty() || role.isEmpty() || salaireStr.isEmpty() || RFID_UID.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "All fields must be filled!");
        return;
    }

    // ✅ ID Validation (Must be exactly 8 digits)
    if (idStr.length() != 8 || !idStr.toLongLong()) {
        QMessageBox::warning(this, "Invalid Input", "ID must be exactly 8 digits!");
        return;
    }
    int ide = idStr.toInt();

    // ✅ Name Validation (Must be between 1 and 60 characters)
    if (nome.length() < 1 || nome.length() > 60) {
        QMessageBox::warning(this, "Invalid Input", "Name must be between 1 and 60 characters!");
        return;
    }

    // ✅ Email Validation (Must follow standard email format)
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Invalid Input", "Enter a valid email address!");
        return;
    }

    // ✅ Phone Number Validation (Must be exactly 8 digits)
    if (telStr.length() != 8 || !telStr.toLongLong()) {
        QMessageBox::warning(this, "Invalid Input", "Phone number must be exactly 8 digits!");
        return;
    }
    int tele = telStr.toInt();

    // ✅ Password Validation (At least 1 uppercase, 1 number, 1 special character)
    QRegularExpression passwordRegex(R"((?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{6,})");
    if (!passwordRegex.match(mdp).hasMatch()) {
        QMessageBox::warning(this, "Invalid Input", "Password must contain at least one uppercase letter, one number, and one special character!");
        return;
    }

    // ✅ Salary Validation (Must be a valid number)
    bool ok;
    int salaire = salaireStr.toInt(&ok);
    if (!ok || salaire <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Salary must be a positive number!");
        return;
    }

    // ✅ RFID UID Validation (Should not be empty and can be validated further based on your use case)
    if (RFID_UID.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "RFID UID must be provided!");
        return;
    }

    if (userEditMode) {
        // Update existing utilisateur
        CrudE update(ide, nome, email, tele, adresse, mdp, role, salaire, RFID_UID); // Use RFID_UID
        update.update_utilisateur(ide);

        for (int row = 0; row < ui->tableWidgetE->rowCount(); ++row) {
            if (ui->tableWidgetE->item(row, 0)->text().toInt() == ide) {
                ui->tableWidgetE->setItem(row, 1, new QTableWidgetItem(nome));
                ui->tableWidgetE->setItem(row, 2, new QTableWidgetItem(email));
                ui->tableWidgetE->setItem(row, 3, new QTableWidgetItem(QString::number(tele)));
                ui->tableWidgetE->setItem(row, 4, new QTableWidgetItem(adresse));
                ui->tableWidgetE->setItem(row, 5, new QTableWidgetItem(mdp));
                ui->tableWidgetE->setItem(row, 6, new QTableWidgetItem(role));
                ui->tableWidgetE->setItem(row, 7, new QTableWidgetItem(QString::number(salaire)));
                ui->tableWidgetE->setItem(row, 8, new QTableWidgetItem(RFID_UID)); // Update RFID_UID
                break;
            }
        }
        QMessageBox::information(this, "Success", "Utilisateur updated successfully!");
        userEditMode = false;
        ui->ajouterE->setText("Add");
        ui->id->setReadOnly(false);
    } else {
        // Ensure ID is unique before adding
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE IDE = :id");
        checkQuery.bindValue(":id", ide);
        checkQuery.exec();
        if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "Invalid Input", "ID must be unique!");
            return;
        }

        // Add new utilisateur
        CrudE add(ide, nome, email, tele, adresse, mdp, role, salaire, RFID_UID); // Use RFID_UID
        add.add_utilisateur(ui->tableWidgetE);
        QMessageBox::information(this, "Success", "Utilisateur added successfully!");

        // ✉️ Send email with user info
        QString mailBody = QString(
                               "Bonjour %1,\n\n"
                               "Voici les informations que vous avez fournies lors de votre inscription :\n"
                               "ID : %2\n"
                               "Nom : %3\n"
                               "Email : %4\n"
                               "Téléphone : %5\n"
                               "Adresse : %6\n"
                               "Mot de passe : %7\n"
                               "Rôle : %8\n"
                               "Salaire : %9 DT\n"
                               "RFID UID : %10\n" // Add RFID UID in the email
                               "\nBienvenue dans l'équipe !\n\nCordialement,\nL'administration."
                               ).arg(nome)
                               .arg(idStr)
                               .arg(nome)
                               .arg(email)
                               .arg(telStr)
                               .arg(adresse)
                               .arg(mdp)
                               .arg(role)
                               .arg(salaireStr)
                               .arg(RFID_UID); // Include RFID UID in the email

        envoyerEmailAvecInfos(email, mailBody);
    }

    // Clear fields after successful operation
    ui->id->clear();
    ui->nom->clear();
    ui->email->clear();
    ui->tel->clear();
    ui->address->clear();
    ui->mdp->clear();
    ui->role->setCurrentIndex(0);
    ui->salaire->clear();
    ui->rfidUID->clear(); // Clear RFID_UID field
    updateRoleStatistics();
}






void MainWindow::on_deletebE_clicked()
{
    int row = ui->tableWidgetE->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
        return;
    }

    // Get the IDE and RFID_UID of the selected row
    int ide = ui->tableWidgetE->item(row, 0)->text().toInt();
    QString RFID_UID = ui->tableWidgetE->item(row, 8)->text();  // Assuming RFID_UID is in the 8th column

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Deletion",
        QString("Are you sure you want to delete the utilisateur with ID %1 and RFID UID %2?").arg(ide).arg(RFID_UID),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Call the constructor with appropriate arguments for deletion
        // We pass empty values for fields not required for deletion
        CrudE deleteOp(ide, "", "", 0, "", "", "", 0, RFID_UID); // Passing RFID_UID as well
        deleteOp.delete_utilisateur(ide, ui->tableWidgetE); // Pass the IDE to delete the user
        QMessageBox::information(this, "Success", "Utilisateur deleted successfully!");
    }
}


void MainWindow::on_tableWidgetE_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    // Get data from selected row
    int ide = ui->tableWidgetE->item(row, 0)->text().toInt();
    QString nome = ui->tableWidgetE->item(row, 1)->text();
    QString email = ui->tableWidgetE->item(row, 2)->text();
    int tele = ui->tableWidgetE->item(row, 3)->text().toInt();
    QString adresse = ui->tableWidgetE->item(row, 4)->text();
    QString mdp = ui->tableWidgetE->item(row, 5)->text();
    QString role = ui->tableWidgetE->item(row, 6)->text();
    int salaire = ui->tableWidgetE->item(row, 7)->text().toInt();

    // Populate form fields
    ui->id->setText(QString::number(ide));
    ui->id->setReadOnly(true);
    ui->nom->setText(nome);
    ui->email->setText(email);
    ui->tel->setText(QString::number(tele));
    ui->address->setText(adresse);
    ui->mdp->setText(mdp);
    ui->role->setCurrentText(role);
    ui->salaire->setText(QString::number(salaire));

    // Set edit mode
    userEditMode = true;
    ui->ajouterE->setText("Update");
    currentUserEditId = ide;
}

void MainWindow::on_cancelButtonE_clicked()
{
    ui->ajouterE->setText("Add");
    ui->id->setReadOnly(false);
    userEditMode = false;
    currentUserEditId = -1;

    // Clear all fields
    ui->id->clear();
    ui->nom->clear();
    ui->email->clear();
    ui->tel->clear();
    ui->address->clear();
    ui->mdp->clear();
    ui->role->setCurrentIndex(0);
    ui->salaire->clear();
    updateRoleStatistics();

}

void MainWindow::on_rechbE_clicked()
{
    QString searchText = ui->rechE->text().trimmed();
    CrudE search;
    if (searchText.isEmpty()) {
        search.load_utilisateur_data(ui->tableWidgetE); // Load all data if search field is empty
        return;
    }
    if (ui->nom->text().contains(searchText, Qt::CaseInsensitive)) {
        search.load_utilisateur_byName(searchText, ui->tableWidgetE);
    } else {
        search.load_utilisateur_byRole(searchText, ui->tableWidgetE);
    }
    if (ui->tableWidgetE->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No matching records found.");
    }
}

void MainWindow::on_rechE_textChanged(const QString &searchText)
{
    CrudE search;

    // Trim the search text
    QString trimmedText = searchText.trimmed();
    if (trimmedText.isEmpty()) {
        search.load_utilisateur_data(ui->tableWidgetE);
        return;
    }

    // Try searching by role first
    bool foundInRoles = false;
    for (int i = 0; i < ui->role->count(); ++i) {
        if (ui->role->itemText(i).contains(trimmedText, Qt::CaseInsensitive)) {
            foundInRoles = true;
            break;
        }
    }

    if (foundInRoles) {
        search.load_utilisateur_byRole(trimmedText, ui->tableWidgetE);
    } else {
        search.load_utilisateur_byName(trimmedText, ui->tableWidgetE);
    }
}

void MainWindow::on_sortComboBoxE_changed(const QString &sortType) {
    CrudE tree;
    tree.load_sorted_utilisateur(ui->tableWidgetE, sortType);
}

void MainWindow::updateRoleStatistics() {
    // Clear existing content in chart layout
    if (ui->chartLayoutE_2->layout()) {
        QLayout* oldLayout = ui->chartLayoutE_2->layout();
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
        delete oldLayout; // Delete the old layout
    }

    // Create a new layout
    QVBoxLayout* vLayout = new QVBoxLayout(ui->chartLayoutE_2);
    ui->chartLayoutE_2->setLayout(vLayout);

    // Get employee role statistics
    connection c;
    QSqlDatabase db = c.get_database();

    QVector<QPair<QString, int>> stats;

    if (db.open()) {
        QSqlQuery query(db);
        // Count all roles
        QString queryString = "SELECT ROLEE, COUNT(*) FROM EMPLOYES GROUP BY ROLEE ORDER BY ROLEE";

        qDebug() << "Executing query:" << queryString;
        query.prepare(queryString);

        if (query.exec()) {
            while (query.next()) {
                QString role = query.value(0).toString();
                int count = query.value(1).toInt();
                qDebug() << "Role:" << role << ", Count:" << count;
                stats.append(qMakePair(role, count));
            }
        } else {
            qDebug() << "Query failed:" << query.lastError().text();
            QLabel *errorLabel = new QLabel("Failed to load statistics: Database error");
            errorLabel->setAlignment(Qt::AlignCenter);
            vLayout->addWidget(errorLabel);
            return;
        }
    }

    if (stats.isEmpty()) {
        QLabel *noDataLabel = new QLabel("No employee data available");
        noDataLabel->setAlignment(Qt::AlignCenter);
        vLayout->addWidget(noDataLabel);
        return;
    }

    // Add a title for the statistics section
    QLabel *titleLabel = new QLabel("Employee Role Distribution");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #205375; margin: 10px;");
    vLayout->addWidget(titleLabel);

    QStringList categories;
    QVector<int> values;
    int maxValue = 0;
    int totalEmployees = 0;

    // Process stats data
    for (const auto &stat : stats) {
        categories.append(stat.first);  // Role
        values.append(stat.second);     // Count
        maxValue = std::max(maxValue, stat.second);  // Update maximum value
        totalEmployees += stat.second;  // Track total count
    }

    // === PIE CHART ===
    QPieSeries *pieSeries = new QPieSeries();

    // Define specific colors for each role
    QMap<QString, QColor> roleColors;
    roleColors["Administrateur"] = QColor(52, 152, 219); // Blue
    roleColors["Chercheur"] = QColor(46, 204, 113);      // Green
    roleColors["Technicien"] = QColor(231, 76, 60);      // Red

    for (int i = 0; i < categories.size(); ++i) {
        // Add slice with count
        QPieSlice *slice = pieSeries->append(categories[i], values[i]);

        // Set color if defined
        if (roleColors.contains(categories[i])) {
            slice->setBrush(roleColors[categories[i]]);
        }

        // Calculate percentage
        double percentage = (static_cast<double>(values[i]) / totalEmployees) * 100.0;
        slice->setLabel(QString("%1: %2 (%3%)").arg(categories[i]).arg(values[i]).arg(percentage, 0, 'f', 1));

        // Make slice visible
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setExploded(true);
        slice->setExplodeDistanceFactor(0.1);
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Employee Roles");
    pieChart->legend()->setVisible(false); // Hide legend since we have labels on slices
    pieChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
    pieChart->setBackgroundPen(Qt::NoPen);

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumHeight(200);
    pieChartView->setMaximumHeight(250);
    pieChartView->setStyleSheet("background-color: rgb(243, 249, 251); border-radius: 10px;");

    // Add pie chart to layout
    vLayout->addWidget(pieChartView);

    // === TOTALS SUMMARY ===
    QLabel *summaryLabel = new QLabel(QString("Total Employees: %1").arg(totalEmployees));
    summaryLabel->setAlignment(Qt::AlignCenter);
    summaryLabel->setStyleSheet("font-size: 14px; font-weight: bold; margin: 10px;");
    vLayout->addWidget(summaryLabel);

    // Add individual role counts with colored indicators
    QGridLayout *rolesLayout = new QGridLayout();
    int row = 0;

    for (int i = 0; i < categories.size(); ++i) {
        // Create colored indicator
        QFrame *colorBox = new QFrame();
        colorBox->setFixedSize(15, 15);
        colorBox->setStyleSheet(QString("background-color: %1; border: none;")
                                    .arg(roleColors.contains(categories[i])
                                             ? roleColors[categories[i]].name()
                                             : pieSeries->slices().at(i)->brush().color().name()));

        // Create label with role and count
        QLabel *roleLabel = new QLabel(QString("%1: %2").arg(categories[i]).arg(values[i]));

        // Add to layout
        rolesLayout->addWidget(colorBox, row, 0);
        rolesLayout->addWidget(roleLabel, row, 1);
        row++;
    }

    // Add some spacing to the grid layout
    rolesLayout->setHorizontalSpacing(10);
    rolesLayout->setVerticalSpacing(5);
    rolesLayout->setContentsMargins(50, 10, 50, 10);

    // Create a widget to hold the grid layout
    QWidget *rolesWidget = new QWidget();
    rolesWidget->setLayout(rolesLayout);
    vLayout->addWidget(rolesWidget);

    // Add stretch to push everything to the top
    vLayout->addStretch();
}
void MainWindow::on_pdfbE_clicked() {
    int row = ui->tableWidgetE->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select an employee to generate a PDF.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    // Draw title
    QFont titleFont("Arial", 40, QFont::Bold);
    painter.setFont(titleFont);
    QRect titleRect(0, 100, pageWidth, 170);
    painter.drawText(titleRect, Qt::AlignCenter, "Employee Report");

    // Draw logo if available
    QPixmap logo(":/new/prefix1/image/Adobe Express - file (5)");
    if (!logo.isNull()) {
        int logoWidth = 650;
        int logoHeight = 550;
        int logoX = pageWidth - logoWidth - 50;
        int logoY = 50;
        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }

    // Setup fonts and positioning
    QFont headerFont("Arial", 24, QFont::Bold);
    QFont contentFont("Arial", 18);
    int yPosition = pageHeight / 5;
    int rowHeight = 200; // Reduced height since we have more fields
    int padding = 100;

    // Define the employee data we want to include in the report
    QStringList headers = {"ID", "Name", "Email", "Phone", "Role", "Salary"};
    QStringList data;

    // Get data from selected row - columns 0,1,2,3,6,7 correspond to ID, Name, Email, Phone, Role, Salary
    for (int col : {0, 1, 2, 3, 6, 7}) {
        QTableWidgetItem *item = ui->tableWidgetE->item(row, col);
        QString cellText = item && !item->text().isEmpty() ? item->text() : "<Empty>";
        data.append(cellText);
    }

    // Draw employee information on first page
    for (int i = 0; i < headers.size(); ++i) {
        painter.setFont(headerFont);
        QRect headerRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(headerRect, Qt::AlignLeft, headers[i] + ":");

        yPosition += rowHeight / 2;

        painter.setFont(contentFont);
        QRect dataRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(dataRect, Qt::AlignLeft, data[i]);

        yPosition += rowHeight / 2;
        yPosition += 30; // Smaller gap between fields
    }

    // Create a second page for address and additional info
    pdfWriter.newPage();
    yPosition = 150;

    // Draw title for second page
    painter.setFont(titleFont);
    titleRect = QRect(0, 50, pageWidth, 100);
    painter.drawText(titleRect, Qt::AlignCenter, "Additional Information");

    // Draw address section
    painter.setFont(headerFont);
    QRect addressHeaderRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
    painter.drawText(addressHeaderRect, Qt::AlignLeft, "Address:");

    yPosition += rowHeight / 2;

    QFont descFont("Arial", 16);
    painter.setFont(descFont);

    // Get the address from column 4
    QTableWidgetItem *addressItem = ui->tableWidgetE->item(row, 4);
    QString address = addressItem && !addressItem->text().isEmpty() ? addressItem->text() : "No address available.";

    QRect addressRect(padding, yPosition, pageWidth - 2 * padding, rowHeight);
    painter.drawText(addressRect, Qt::AlignLeft | Qt::TextWordWrap, address);

    yPosition += rowHeight + 50;


    yPosition += rowHeight / 2;



    // Add current date to the footer
    yPosition = pageHeight - 150;
    QFont footerFont("Arial", 12);
    painter.setFont(footerFont);
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QRect dateRect(padding, yPosition, pageWidth - 2 * padding, 50);
    painter.drawText(dateRect, Qt::AlignRight, "Joined on : " + currentDate);

    painter.end();


}
void MainWindow::envoyerEmailAvecInfos(const QString &email, const QString &body) {
    SmtpMailerSecure *mailer = new SmtpMailerSecure(this);
    mailer->sendMail(
        "sahlitaher2003@gmail.com",  // Sender
        email,                       // Receiver
        "Bienvenue dans notre entreprise",  // Email subject
        body,                        // Email body
        "",                          // No file attached
        "smtp.gmail.com",           // SMTP server
        465,                        // SSL port
        "sahlitaher2003@gmail.com", // Your Gmail
        "nakr dajd ayxm orim"       // App password
        );
}
void MainWindow::handleRFID(const QString &uid)
{
    QSqlQuery query;
    query.prepare("SELECT NOME, ROLEE, EMAILE FROM EMPLOYES WHERE RFID_UID = :uid");
    query.bindValue(":uid", uid);

    if (query.exec() && query.next()) {
        // Card already exists
        QString employeeName = query.value(0).toString();
        QString employeeRole = query.value(1).toString();
        QString employeeEmail = query.value(2).toString();

        QString displayText = employeeName + " - " + employeeRole;

        // If not already logged in, proceed to auto-login
        if (!isUserLoggedIn) {
            showMainPage();
            CrudE::load_utilisateur_data(ui->tableWidgetE);

            // Show welcome message
            QMessageBox::information(this, "Bienvenue",
                                     "Bienvenue " + employeeName + " (" + employeeRole + ")");
        }

        // Send welcome message to Arduino LCD
        if (serialHandler) {
            serialHandler->sendMessage("Welcome " + employeeName + " (" + employeeRole + ")");
        }

    } else {
        // New card: fill the field for adding new employee
        currentRFID = uid;
        ui->rfidUID->setText(currentRFID);

        if (serialHandler) {
            serialHandler->sendMessage("NEW CARD");
        }
    }
}



void MainWindow::showPatientTablep()
{
    // Hide statistics and show patient table
    ui->chartLayoutp->setVisible(false);
    ui->tableWidgetp->setVisible(true);

    // Refresh the table data if needed
    Crudp crudp;
    crudp.load_patients(ui->tableWidgetp);

    // Reset the stats button text/icon if needed
    ui->StatButtonp->setText("Show Statistics");
}

void MainWindow::showStatisticsp() {
    ui->tableWidgetp->setVisible(false);
    ui->chartLayoutp->setVisible(true);
    Crudp crudp;
    crudp.load_patients(ui->tableWidgetp);
    // Nettoyer l'ancien contenu
    QLayout *layout = ui->chartLayoutp->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        layout = new QVBoxLayout();
        ui->chartLayoutp->setLayout(layout);
    }

    // Compter les hommes et femmes
    int hommeCount = 0, femmeCount = 0;
    for (int row = 0; row < ui->tableWidgetp->rowCount(); ++row) {
        QTableWidgetItem *genreItem = ui->tableWidgetp->item(row, 3);
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
    ui->chartLayoutp->layout()->addWidget(mainWidget);
}


void MainWindow::on_tableWidgetR_cellChanged(int row, int column)
{
    if (isTableBeingUpdated) return;
    QTableWidgetItem *idItem = ui->tableWidgetR->item(row, 0);
    if (!idItem) return;

    int id = idItem->text().toInt();

    // Check if the logged-in employee is the owner of the research row
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT EMPLOYE FROM RECHERCHE WHERE IDR = :IDR");
        checkQuery.bindValue(":IDR", id);

        if (checkQuery.exec() && checkQuery.next()) {
            int employeId = checkQuery.value(0).toInt();
            if (employeId != CrudE::idN) {
                isTableBeingUpdated = true;
                CrudR::load_recherche_data(ui->tableWidgetR);
                isTableBeingUpdated = false;
                return;
            }
        } else {
            qDebug() << "Échec de vérification d'EMPLOYE:" << checkQuery.lastError().text();
            return;
        }
    }


    bool shouldResetForm = false;
    if (researchEditMode && currentResearchEditId == id) {
        shouldResetForm = true;
    }
    QTableWidgetItem *changedItem = ui->tableWidgetR->item(row, column);
    if (!changedItem) return;

    QString newValue = changedItem->text();
    if (column == 0) {
        QMessageBox::warning(this, "Edit Error", "The ID field cannot be modified.");
        isTableBeingUpdated = true;
        changedItem->setText(QString::number(id));

        isTableBeingUpdated = false;
        return;
    }
    else if (column == 1) {
        if (newValue.length() < 3) {
            QMessageBox::warning(this, "Invalid Input", "Title must contain at least 3 characters.");
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT TITRER FROM RECHERCHE WHERE IDR = :IDR");
                query.bindValue(":IDR", id);

                if (query.exec() && query.next()) {
                    QString originalTitle = query.value(0).toString();

                    isTableBeingUpdated = true;
                    changedItem->setText(originalTitle);
                    isTableBeingUpdated = false;
                }
            }
            return;
        }
    }
    else if (column == 2) {
        QStringList validClassifications = {"BSL-1", "BSL-2", "BSL-3", "BSL-4"};
        if (!validClassifications.contains(newValue)) {
            QMessageBox::warning(this, "Invalid Input", "Classification must be between BSL-1 and BSL-4.");
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT CLASSR FROM RECHERCHE WHERE IDR = :IDR");
                query.bindValue(":IDR", id);

                if (query.exec() && query.next()) {
                    QString originalClass = query.value(0).toString();

                    isTableBeingUpdated = true;
                    changedItem->setText(originalClass);
                    isTableBeingUpdated = false;
                }
            }
            return;
        }
    }
    else if (column == 4 || column == 5) {
        QDate date = QDate::fromString(newValue, "yyyy-MM-dd");
        if (!date.isValid()) {
            QMessageBox::warning(this, "Invalid Input", "Date must be in yyyy-MM-dd format.");
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                QString field = (column == 4) ? "DATEDR" : "DATEFR";
                query.prepare("SELECT TO_CHAR(" + field + ", 'YYYY-MM-DD') FROM RECHERCHE WHERE IDR = :IDR");
                query.bindValue(":IDR", id);

                if (query.exec() && query.next()) {
                    QString originalDate = query.value(0).toString();

                    isTableBeingUpdated = true;
                    changedItem->setText(originalDate);
                    isTableBeingUpdated = false;
                }
            }
            return;
        }

        QDate startDate, endDate;

        if (column == 4) {
            startDate = date;
            QTableWidgetItem *endDateItem = ui->tableWidgetR->item(row, 5);
            if (endDateItem) {
                endDate = QDate::fromString(endDateItem->text(), "yyyy-MM-dd");
            }

            if (endDate.isValid() && startDate > endDate) {
                QMessageBox::warning(this, "Invalid Input", "Start date must be before end date.");
                connection c;
                QSqlDatabase db = c.get_database();
                if (db.open()) {
                    QSqlQuery query(db);
                    query.prepare("SELECT TO_CHAR(DATEDR, 'YYYY-MM-DD') FROM RECHERCHE WHERE IDR = :IDR");
                    query.bindValue(":IDR", id);

                    if (query.exec() && query.next()) {
                        QString originalDate = query.value(0).toString();

                        isTableBeingUpdated = true;
                        changedItem->setText(originalDate);
                        isTableBeingUpdated = false;
                    }
                }
                return;
            }
        }
        else if (column == 5) {
            endDate = date;
            QTableWidgetItem *startDateItem = ui->tableWidgetR->item(row, 4);
            if (startDateItem) {
                startDate = QDate::fromString(startDateItem->text(), "yyyy-MM-dd");
            }
            if (startDate.isValid() && endDate < startDate) {
                QMessageBox::warning(this, "Invalid Input", "End date must be the same as or later than the start date.");
                connection c;
                QSqlDatabase db = c.get_database();
                if (db.open()) {
                    QSqlQuery query(db);
                    query.prepare("SELECT TO_CHAR(DATEFR, 'YYYY-MM-DD') FROM RECHERCHE WHERE IDR = :IDR");
                    query.bindValue(":IDR", id);

                    if (query.exec() && query.next()) {
                        QString originalDate = query.value(0).toString();

                        isTableBeingUpdated = true;
                        changedItem->setText(originalDate);
                        isTableBeingUpdated = false;
                    }
                }
                return;
            }
        }
    }
    if (db.open()) {
        QSqlQuery query(db);
        QString field;
        switch (column) {
        case 1:
            field = "TITRER";
            break;
        case 2:
            field = "CLASSR";
            break;
        case 3:
            field = "DESCR";
            break;
        case 4:
            field = "DATEDR";
            break;
        case 5:
            field = "DATEFR";
            break;
        default:
            return;
        }

        QString queryStr;
        if (column == 4 || column == 5) {
            queryStr = "UPDATE RECHERCHE SET " + field + " = TO_DATE(:value, 'YYYY-MM-DD') WHERE IDR = :IDR";
        } else {
            queryStr = "UPDATE RECHERCHE SET " + field + " = :value WHERE IDR = :IDR";
        }

        query.prepare(queryStr);
        query.bindValue(":value", newValue);
        query.bindValue(":IDR", id);

        if (!query.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to update record: " + query.lastError().text());
            isTableBeingUpdated = true;
            CrudR::load_recherche_data(ui->tableWidgetR);
            isTableBeingUpdated = false;
        } else {
            qDebug() << "Record with ID" << id << "updated successfully. Column " << column << " changed to " << newValue;
        }
        if (shouldResetForm) {
            ui->ajouterR->setText("Add");
            researchEditMode = false;
            currentResearchEditId = -1;
            ui->titre->clear();
            ui->Classer->setCurrentIndex(0);
            ui->desc->clear();
            ui->dateD->setDate(QDate::currentDate());
            ui->dateF->setDate(QDate::currentDate());
        }
    }
}

void MainWindow::on_ajouterR_clicked()
{
    qDebug() << "ajouter button clicked";

    QString TITRER = ui->titre->text();
    QString CLASSR = ui->Classer->currentText();
    QString DESCR = ui->desc->toPlainText();
    QString DATEDR = ui->dateD->date().toString("yyyy-MM-dd");
    QString DATEFR = ui->dateF->date().toString("yyyy-MM-dd");
    int EMPLOYE = CrudE::idN;

    qDebug() << "Form values: Title=" << TITRER << ", Class=" << CLASSR
             << ", Desc length=" << DESCR.length()
             << ", DateD=" << DATEDR << ", DateF=" << DATEFR;

    if (TITRER.length() < 3) {
        QMessageBox::warning(this, "Invalid Input", "Title must contain at least 3 characters.");
        return;
    }
    if (!researchEditMode) {
        QDate currentDate = QDate::currentDate();
        if (ui->dateD->date() < currentDate) {
            QMessageBox::warning(this, "Invalid Input", "Start date must be today's date or later.");
            return;
        }
    }

    if (ui->dateF->date() < ui->dateD->date()) {
        QMessageBox::warning(this, "Invalid Input", "End date must be the same as or later than the start date.");
        return;
    }

    if (TITRER.isEmpty() || CLASSR.isEmpty() || DESCR.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Title, Classification, and Description must be filled out.");
        return;
    }

    qDebug() << "All validation passed, proceeding with " << (researchEditMode ? "update" : "add");

    if (researchEditMode) {
        int idint = currentResearchEditId;
        qDebug() << "Updating record with ID:" << idint;

        CrudR update(idint, TITRER, CLASSR, DESCR, DATEDR, DATEFR, EMPLOYE);
        update.update_recherche(idint);
        for (int row = 0; row < ui->tableWidgetR->rowCount(); ++row) {
            QTableWidgetItem* idItem = ui->tableWidgetR->item(row, 0);
            if (idItem && idItem->text().toInt() == idint) {
                ui->tableWidgetR->setItem(row, 1, new QTableWidgetItem(TITRER));
                ui->tableWidgetR->setItem(row, 2, new QTableWidgetItem(CLASSR));
                ui->tableWidgetR->setItem(row, 3, new QTableWidgetItem(DESCR));
                ui->tableWidgetR->setItem(row, 4, new QTableWidgetItem(DATEDR));
                ui->tableWidgetR->setItem(row, 5, new QTableWidgetItem(DATEFR));
                break;
            }
        }

        ui->ajouterR->setText("Add");
        researchEditMode = false;
    } else {
        qDebug() << "Adding new record";
        isTableBeingUpdated = true;
        CrudR add(0, TITRER, CLASSR, DESCR, DATEDR, DATEFR, EMPLOYE);
        bool success = add.add_recherche(ui->tableWidgetR);
        isTableBeingUpdated = false;

        if (!success) {
            qDebug() << "Failed to add record";
            QMessageBox::warning(this, "Error", "Failed to add record. Check logs for details.");
        } else {
            qDebug() << "Record added successfully";
        }
    }
    ui->titre->clear();
    ui->Classer->setCurrentIndex(0);
    ui->desc->clear();
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());

    qDebug() << "Form cleared";
}

void MainWindow::on_deletebR_clicked()
{
    int row = ui->tableWidgetR->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
        return;
    }
    QTableWidgetItem *idItem = ui->tableWidgetR->item(row, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Invalid row selected.");
        return;
    }
    int id2int = idItem->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion",
                                  "Are you sure you want to delete this entry?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }
    CrudR drop;
    drop.delete_recherche(id2int, ui->tableWidgetR);
}

void MainWindow::on_tableWidgetR_cellDoubleClicked(int row, int column)
{
    int id = ui->tableWidgetR->item(row, 0)->text().toInt();
    QString title = ui->tableWidgetR->item(row, 1)->text();
    QString classification = ui->tableWidgetR->item(row, 2)->text();
    QString description = ui->tableWidgetR->item(row, 3)->text();
    QString startDate = ui->tableWidgetR->item(row, 4)->text();
    QString endDate = ui->tableWidgetR->item(row, 5)->text();
    ui->titre->setText(title);

    int classIndex = ui->Classer->findText(classification);
    if (classIndex >= 0) {
        ui->Classer->setCurrentIndex(classIndex);
    }

    ui->desc->setPlainText(description);
    ui->dateD->setDate(QDate::fromString(startDate, "yyyy-MM-dd"));
    ui->dateF->setDate(QDate::fromString(endDate, "yyyy-MM-dd"));


    ui->ajouterR->setText("Update");
    researchEditMode = true;
    currentResearchEditId = id;
}

void MainWindow::on_cancelButtonR_clicked()
{
    ui->ajouterR->setText("Add");
    researchEditMode = false;
    ui->titre->clear();
    ui->Classer->setCurrentIndex(0);
    ui->desc->clear();
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());
}

void MainWindow::on_rechbR_clicked()
{
    isTableBeingUpdated = true;
    QString searchText = ui->rechR->text().trimmed();
    CrudR search;

    if (searchText.isEmpty()) {
        search.load_recherche_data(ui->tableWidgetR);
        return;
    }

    if (ui->Classer->findText(searchText) != -1) {
        search.load_recherche_byClass(searchText, ui->tableWidgetR);
    } else {
        search.load_recherche_byTitle(searchText, ui->tableWidgetR);
    }

    if (ui->tableWidgetR->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No matching records found.");
    }
    isTableBeingUpdated = false;
}

void MainWindow::on_rechR_textChanged(const QString &searchText)
{
    isTableBeingUpdated = true;
    CrudR search;
    QString trimmedText = searchText.trimmed();
    if (trimmedText.isEmpty()) {
        search.load_recherche_data(ui->tableWidgetR);
        return;
    }
    if (ui->Classer->findText(trimmedText) != -1) {
        search.load_recherche_byClass(trimmedText, ui->tableWidgetR);
    } else {
        search.load_recherche_byTitle(trimmedText, ui->tableWidgetR);
    }
    isTableBeingUpdated = false;
}

void MainWindow::on_sortComboBoxR_changed(const QString &sortType) {
    isTableBeingUpdated = true;
    CrudR tree;
    tree.load_sorted_recherche(ui->tableWidgetR, sortType);
    isTableBeingUpdated = false;
}

void MainWindow::on_pdfbR_clicked() {
    int row = ui->tableWidgetR->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to generate a PDF.");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();
    QFont titleFont("Arial", 40, QFont::Bold);
    painter.setFont(titleFont);
    QRect titleRect(0, 100, pageWidth, 170);
    painter.drawText(titleRect, Qt::AlignCenter, "Research Report");
    QPixmap logo(":/new/prefix1/image/Adobe Express - file (5)");
    if (!logo.isNull()) {
        int logoWidth = 650;
        int logoHeight = 550;
        int logoX = pageWidth - logoWidth - 50;
        int logoY = 50;
        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }
    QFont headerFont("Arial", 24, QFont::Bold);
    QFont contentFont("Arial", 18);
    int yPosition = pageHeight / 5;
    int rowHeight = 300;
    int padding = 100;
    QStringList headers = {"Name", "Classification", "Start Date", "End Date"};
    QStringList data;
    for (int col : {1, 2, 4, 5}) {
        QTableWidgetItem *item = ui->tableWidgetR->item(row, col);
        QString cellText = item && !item->text().isEmpty() ? item->text() : "<Empty>";
        data.append(cellText);
    }
    for (int i = 0; i < headers.size(); ++i) {
        painter.setFont(headerFont);
        QRect headerRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(headerRect, Qt::AlignLeft, headers[i] + ":");
        yPosition += rowHeight / 2;
        painter.setFont(contentFont);
        QRect dataRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(dataRect, Qt::AlignLeft, data[i]);
        yPosition += rowHeight / 2;
        yPosition += 50;
    }
    pdfWriter.newPage();
    yPosition = 200;
    QFont descFont("Arial", 16);
    painter.setFont(descFont);
    QTableWidgetItem *descItem = ui->tableWidgetR->item(row, 3);
    QString description = descItem && !descItem->text().isEmpty() ? descItem->text() : "No description available.";
    QRect descRect(padding, yPosition, pageWidth - 2 * padding, pageHeight - 300);
    painter.drawText(descRect, Qt::AlignLeft | Qt::TextWordWrap, description);
    painter.end();
}

void MainWindow::on_StatButtonR_clicked() {
    if (ui->chartLayoutR->isVisible()) {
        ui->chartLayoutR->setVisible(false);
        ui->tableWidgetR->setVisible(true);
    } else {
        ui->tableWidgetR->setVisible(false);
        ui->chartLayoutR->setVisible(true);
        QLayout *layout = ui->chartLayoutR->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
        } else {
            layout = new QHBoxLayout();
            ui->chartLayoutR->setLayout(layout);
        }
        connection c;
        QSqlDatabase db = c.get_database();

        QVector<QPair<QString, int>> stats;

        if (db.open()) {
            QSqlQuery query(db);
            QString queryString = "SELECT CLASSR, COUNT(*) FROM RECHERCHE GROUP BY CLASSR ORDER BY CLASSR";

            qDebug() << "Executing query:" << queryString;
            query.prepare(queryString);

            if (query.exec()) {
                while (query.next()) {
                    QString bslClass = query.value(0).toString();
                    int count = query.value(1).toInt();
                    qDebug() << "Class:" << bslClass << ", Count:" << count;
                    stats.append(qMakePair(bslClass, count));
                }
            } else {
                qDebug() << "Query failed:" << query.lastError().text();
                QMessageBox::critical(this, "Query Error", "Failed to execute query: " + query.lastError().text());
                ui->chartLayoutR->setVisible(false);
                ui->tableWidgetR->setVisible(true);
                return;
            }
        }

        if (stats.isEmpty()) {
            QMessageBox::information(this, "No Data", "No research data available.");
            ui->chartLayoutR->setVisible(false);
            ui->tableWidgetR->setVisible(true);
            return;
        }

        QStringList categories;
        QVector<int> values;
        int maxValue = 0;
        for (const auto &stat : stats) {
            categories.append(stat.first);
            values.append(stat.second);
            maxValue = std::max(maxValue, stat.second);
        }

        QPieSeries *pieSeries = new QPieSeries();
        for (int i = 0; i < categories.size(); ++i) {
            pieSeries->append(categories[i] + " Research", values[i]);
        }

        QChart *pieChart = new QChart();
        pieChart->addSeries(pieSeries);
        pieChart->setTitle("Distribution of Research by BSL Classification");
        pieChart->legend()->setAlignment(Qt::AlignRight);
        pieChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
        pieChart->setBackgroundPen(Qt::NoPen);

        QChartView *pieChartView = new QChartView(pieChart);
        pieChartView->setRenderHint(QPainter::Antialiasing);
        pieChartView->setMinimumSize(400, 300);
        pieChartView->setStyleSheet("background-color: rgb(243, 249, 251);");
        QGraphicsScene *scene = new QGraphicsScene();
        int barWidth = 50, gap = 30, chartHeight = 300;
        int xPos = 50, yBase = chartHeight - 70;

        for (int i = 0; i < values.size(); ++i) {
            int barHeight = (values[i] * (chartHeight - 100)) / (maxValue > 0 ? maxValue : 1);
            QColor barColor = pieSeries->slices().at(i)->brush().color();
            AnimatedBarItem *bar = new AnimatedBarItem(xPos, yBase, barWidth, barColor);
            scene->addItem(bar);

            QPropertyAnimation *anim = new QPropertyAnimation(bar, "barHeight");
            anim->setDuration(800);
            anim->setStartValue(0);
            anim->setEndValue(barHeight);
            anim->setEasingCurve(QEasingCurve::OutCubic);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
            QGraphicsTextItem *label = new QGraphicsTextItem(categories[i]);
            label->setDefaultTextColor(Qt::black);
            label->setFont(QFont("Arial", 10, QFont::Bold));
            qreal labelX = xPos + (barWidth / 2) - (label->boundingRect().width() / 2);
            qreal labelY = yBase + 5;
            label->setPos(labelX, labelY);
            scene->addItem(label);
            QGraphicsTextItem *valueLabel = new QGraphicsTextItem(QString::number(values[i]));
            valueLabel->setDefaultTextColor(Qt::black);
            valueLabel->setFont(QFont("Arial", 9));
            qreal valueLabelX = xPos + (barWidth / 2) - (valueLabel->boundingRect().width() / 2);
            qreal valueLabelY = yBase - barHeight - 20;
            valueLabel->setPos(valueLabelX, valueLabelY);
            scene->addItem(valueLabel);

            xPos += barWidth + gap;
        }

        scene->setSceneRect(0, 0, xPos + 50, chartHeight + 50);

        QGraphicsView *barView = new QGraphicsView(scene);
        barView->setRenderHint(QPainter::Antialiasing);
        barView->setMinimumSize(500, 350);
        barView->setStyleSheet("background-color: rgb(243, 249, 251);");
        ui->chartLayoutR->layout()->addWidget(barView);
        ui->chartLayoutR->layout()->addWidget(pieChartView);
    }
}

void MainWindow::on_openAIAssistantButton_clicked()
{
    QString title = ui->titre->text();
    QString classification = ui->Classer->currentText();
    QString description = ui->desc->toPlainText();
    QString startDate = ui->dateD->date().toString("yyyy-MM-dd");
    QString endDate = ui->dateF->date().toString("yyyy-MM-dd");

    openAIWindow(title, classification, description, startDate, endDate);

}

void MainWindow::on_simulationButton_clicked()
{
    SimulationDialog simDialog(this,this);
    if (simDialog.exec() == QDialog::Accepted) {

        QString recommendedBSL = simDialog.getRecommendedBSL();
        QString summary = simDialog.getSimulationSummary();

        int bslIndex = ui->Classer->findText(recommendedBSL);
        if (bslIndex >= 0) {
            ui->Classer->setCurrentIndex(bslIndex);
        }

        QString currentDesc = ui->desc->toPlainText();
        if (!currentDesc.isEmpty()) {
            currentDesc += "\n\n";
        }
        currentDesc += "SIMULATION RESULTS:\n" + summary;
        ui->desc->setPlainText(currentDesc);
    }
}

void MainWindow::openAIWindow(const QString &title,
                              const QString &classification,
                              const QString &description,
                              const QString &startDate,
                              const QString &endDate)
{
    if (!aiWindow) {
        aiWindow = new AIAssistantWindow(this);
        aiWindow->setAttribute(Qt::WA_DeleteOnClose, false);
        connect(aiWindow, &AIAssistantWindow::descriptionAccepted, this, [=](const QString &desc) {
            if (!desc.isEmpty()) {
                ui->desc->setPlainText(desc);
            }
        });
    }

    aiWindow->prepareForUse();
    aiWindow->setResearchContext(title, classification, description, startDate, endDate);

    aiWindow->show();
    aiWindow->raise();
    aiWindow->activateWindow();
}

AIAssistantWindow* MainWindow::getAIInstance()
{
    if (!aiWindow) {
        aiWindow = new AIAssistantWindow(this);
        aiWindow->setAttribute(Qt::WA_DeleteOnClose, false);
    }
    aiWindow->prepareForUse();
    connect(aiWindow, &AIAssistantWindow::descriptionAccepted, this, [=](const QString &desc) {
        if (!desc.isEmpty()) {
            ui->desc->setPlainText(desc);
        }
    });
    return aiWindow;
}


//arduino related codes
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if (!isConnected) {
        QTimer::singleShot(500, this, &MainWindow::connectArduino);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isConnected) {
        disconnectArduino();
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::connectArduino()
{
    int status = arduino->connect_arduino();

    if (status == 0) {
        isConnected = true;
        QThread::sleep(2);
        timer->start();
        updateTemperature(); // Get an initial reading
    }
    else if (status == 1) {
        QMessageBox::warning(this, "Connection Error", "Could not open serial port.");
    }
    else if (status == -1) {
        QMessageBox::warning(this, "Connection Error", "Arduino not found. Check connections.");
    }
}

void MainWindow::disconnectArduino()
{
    timer->stop();
    arduino->close_arduino();
    isConnected = false;
}

void MainWindow::updateTemperature()
{
    if (!isConnected) return;

    QByteArray data = arduino->read_from_arduino();

    if (!data.isEmpty()) {
        qDebug() << "Received data:" << data;

        QString tempStr = QString(data).trimmed();

        // Handle multiple lines (in case more than one line is read)
        QStringList lines = tempStr.split('\n', Qt::SkipEmptyParts);
        for (int i = lines.size() - 1; i >= 0; i--) {
            QString line = lines[i].trimmed();

            // Skip errors
            if (line.contains("ERROR", Qt::CaseInsensitive)) {
                return;
            }

            // Check and strip "TEMP:" prefix
            if (line.startsWith("TEMP:")) {
                QString tempValue = line.mid(5).trimmed();

                bool ok;
                float temperature = tempValue.toFloat(&ok);
                if (ok) {
                    // Check temperature threshold
                    if (temperature >= 31.0) {
                        // Send status to LCD
                        QByteArray statusCmd = "STATUS:DANGER! TOO HOT\n";
                        arduino->write_to_arduino(statusCmd);
                    } else {
                        // Send status to LCD
                        QByteArray statusCmd = "STATUS:Temperature OK\n";
                        arduino->write_to_arduino(statusCmd);
                    }

                    return;
                } else {
                    qDebug() << "Failed to convert value after TEMP:" << tempValue;
                }
            }
        }
    } else {
        qDebug() << "No data received from Arduino";
    }
}

// SerialHandler.cpp

void SerialHandler::readSerial() {
    while (serial->canReadLine()) {
        QString line = QString::fromUtf8(serial->readLine()).trimmed();
        qDebug() << "Received:" << line;

        if (line.startsWith("RFID:")) {
            QString uid = line.section(':', 1, 1).trimmed();
            emit rfidReceived(uid);  // Emit signal to handle the UID

            // Query the database for employee info based on the UID
            QString name;
            QString role;
            QSqlQuery query;
            query.prepare("SELECT NOME, ROLEE FROM EMPLOYES WHERE RFID_UID = :uid");
            query.bindValue(":uid", uid);
            query.exec();

            if (query.next()) {
                name = query.value(0).toString();
                role = query.value(1).toString();
                QString employeeInfo = name + " - " + role;

                // Send the employee information back to the Arduino
                sendMessage(employeeInfo);  // Send name and role to Arduino
            } else {
                // Handle case if UID doesn't exist in the database
                sendMessage("Unknown User");  // Notify Arduino
            }
        }
    }
}

void SerialHandler::sendMessage(const QString &message) {
    if (serial->isOpen()) {
        serial->write(message.toUtf8());
        serial->write("\n");
    }
}
//end arduino

// youssef fonctionet li kol ili yikhdmo li button w li ui kholf table w li arduino (hot commentaire win tkamil)

void MainWindow::on_StatButtonp_clicked() {
    if (showingStats) {
        showPatientTablep();
    } else {
        showStatisticsp();
    }
    showingStats = !showingStats;
}

void MainWindow::on_DNAbutton_clicked()
{
    if (!dnaWindowp) {
        dnaWindowp = new DnaWindow(this);  // Création de la fenêtre
        dnaWindowp->setAttribute(Qt::WA_DeleteOnClose);  // Gestion automatique de la mémoire
    }

    dnaWindowp->show();  // Affichage de la fenêtre
    dnaWindowp->raise();  // Mise au premier plan
    dnaWindowp->activateWindow();  // Activation de la fenêtre
}


void MainWindow::on_ajouterp_clicked() {
    // Récupérer les valeurs des champs de texte
    QString id = ui->idp->text();
    QString nom = ui->nomp->text();
    QString prenom = ui->prenomp->text();
    QString genre = ui->genrep->currentText();
    QString date = ui->date->text();
    QString tel = ui->telp->text();

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
    Crudp crudp;

    // Ajouter le patient à la base de données, en incluant le fichier (dossier de type BLOB)
    crudp.add_patient(id.toInt(), nom, prenom, genre, date, fileName, tel.toInt(), fileData);

    // Rafraîchir le tableau
    crudp.load_patients(ui->tableWidgetp);

    // Appeler une fonction pour réinitialiser les champs du formulaire
    on_cancelp_clicked();


}

void MainWindow::on_cancelp_clicked() {
    ui->idp->clear();
    ui->nomp->clear();
    ui->prenomp->clear();
    ui->genrep->setCurrentIndex(-1);
    ui->date->clear();
    ui->telp->clear();
    if (fileLabel) {
        fileLabel->clear();
    }
    currentFilePath.clear();
    selectedPatientId = -1;
}

void MainWindow::on_nom2p_textChanged(const QString &text) {
    Crudp crudp;
    crudp.search_patient(-1, text, ui->tableWidgetp);
}

void MainWindow::on_tableWidgetp_cellClicked(int row, int column) {
    Q_UNUSED(column);
    QTableWidgetItem *idItem = ui->tableWidgetp->item(row, 0); // column 0 = ID

    if (idItem) {
        selectedPatientId = idItem->text().toInt();

        // Open the detailed dialog
        PatientDetailsDialog *dialog = new PatientDetailsDialog(selectedPatientId, ui->tableWidgetp, this);
        dialog->exec();
        delete dialog;


    }
}



void MainWindow::on_sortComboBoxp_changed(const QString &sortType) {
    Crudp crudp;
    ui->tableWidgetp->setRowCount(0);  // Clear the table first
    crudp.load_sorted_recherche(ui->tableWidgetp, sortType);
}

void MainWindow::on_browseButtonp_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "All Files (*)");
    if (!filePath.isEmpty()) {
        currentFilePath = filePath;
        QFileInfo fileInfo(filePath);
        if (fileLabel) {
            fileLabel->setText(fileInfo.fileName());  // Show the file name
        }
    }
}



// ahmed fonctionet li kol ili yikhdmo li button w li ui kholf table w li arduino (hot commentaire win tkamil)



// fares nithamo fih aman




//for buttons only keep it last
void MainWindow::on_emp_clicked(){
    showMainPage();
}
void MainWindow::on_pdr_clicked(){
    researchPage();
}
void MainWindow::on_pt_clicked(){
    showPatientPage();
}

void MainWindow::on_vac_clicked(){
    showVaccinPage();
}
void MainWindow::on_eqbtn_clicked(){
    techPage();
}
//foctionaite li show w li hide lil les pages

void MainWindow::showLoginPage() {
    page = 8;

    if (!ui->loginGroupBox || !ui->pageE || !ui->pageR || !ui->pageP || !ui->pageV || !ui->pageeq) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    ui->loginGroupBox->show();
    ui->pageE->hide();
    ui->pageR->hide();
    ui->pageeq->hide();
    ui->pageV->hide();
    ui->pageP->hide();
    isUserLoggedIn = false;
}

void MainWindow::showMainPage() {
    page = 1;

    if (!ui->loginGroupBox || !ui->pageE || !ui->pageR || !ui->pageP || !ui->pageV) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    ui->loginGroupBox->hide();
    ui->pageR->hide();
    ui->pageP->hide();
    ui->pageV->hide();
    ui->page_3->hide();
    ui->pageeq->hide();
    ui->pageE->show();
    isUserLoggedIn = true;

    // Initialize employee table
    try {
        if (!ui->tableWidgetE) {
            qDebug() << "Employee table widget is null!";
            return;
        }

        // Set up the table structure if it hasn't been done already
        if (ui->tableWidgetE->columnCount() != 9) {
            ui->tableWidgetE->setColumnCount(9);
            QStringList headers;
            headers << "IDE" << "Name" << "Email" << "Phone"
                    << "Address" << "Password" << "Role"
                    << "Salary" << "RFID UID";
            ui->tableWidgetE->setHorizontalHeaderLabels(headers);
        }

        // Always load data regardless of column count
        CrudE::load_utilisateur_data(ui->tableWidgetE);
        updateRoleStatistics();

        // Connect signals only once
        disconnect(ui->rechE, &QLineEdit::textChanged, this, &MainWindow::on_rechE_textChanged);
        disconnect(ui->sortComboBoxE, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxE_changed);
        connect(ui->rechE, &QLineEdit::textChanged, this, &MainWindow::on_rechE_textChanged);
        connect(ui->sortComboBoxE, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxE_changed);
    } catch (const std::exception& e) {
        qDebug() << "Exception in showMainPage: " << e.what();
    } catch (...) {
        qDebug() << "Unknown exception in showMainPage";
    }
}

void MainWindow::researchPage() {
    page = 4;

    if (!ui->loginGroupBox || !ui->pageE || !ui->pageR || !ui->pageP || !ui->pageV) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    ui->loginGroupBox->hide();
    ui->pageE->hide();
    ui->pageP->hide();
    ui->pageV->hide();
    ui->page_3->hide();
    ui->pageeq->hide();
    ui->pageR->show();
    isUserLoggedIn = true;

    // Initialize research table
    try {
        if (!ui->tableWidgetR) {
            qDebug() << "Research table widget is null!";
            return;
        }

        // Set up the table structure if it hasn't been done already
        if (ui->tableWidgetR->columnCount() != 6) {
            ui->tableWidgetR->setColumnCount(6);
            QStringList headers;
            headers << "ID" << "Title" << "Classification" << "Description" << "Start Date" << "End Date";
            ui->tableWidgetR->setHorizontalHeaderLabels(headers);
        }

        ui->tableWidgetR->setEditTriggers(QAbstractItemView::DoubleClicked |
                                          QAbstractItemView::EditKeyPressed);

        // Create delegates if they don't exist yet
        if (!classDelegate) {
            classDelegate = new ClassificationDelegate(this);
        }
        if (!dateDelegate) {
            dateDelegate = new DateDelegate(this);
        }

        ui->tableWidgetR->setItemDelegateForColumn(2, classDelegate);
        ui->tableWidgetR->setItemDelegateForColumn(4, dateDelegate);
        ui->tableWidgetR->setItemDelegateForColumn(5, dateDelegate);

        // Always load data regardless of column count
        isTableBeingUpdated = true;
        CrudR::load_recherche_data(ui->tableWidgetR);

        // Make ID column non-editable
        for (int row = 0; row < ui->tableWidgetR->rowCount(); ++row) {
            QTableWidgetItem *idItem = ui->tableWidgetR->item(row, 0);
            if (idItem) {
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
            }
        }

        isTableBeingUpdated = false;

        // Disconnect first to avoid duplicate connections
        disconnect(ui->tableWidgetR, &QTableWidget::cellChanged, this, &MainWindow::on_tableWidgetR_cellChanged);
        disconnect(ui->sortComboBoxR, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxR_changed);
        disconnect(ui->rechR, &QLineEdit::textChanged, this, &MainWindow::on_rechR_textChanged);

        // Reconnect signals
        connect(ui->tableWidgetR, &QTableWidget::cellChanged, this, &MainWindow::on_tableWidgetR_cellChanged);
        connect(ui->sortComboBoxR, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxR_changed);
        connect(ui->rechR, &QLineEdit::textChanged, this, &MainWindow::on_rechR_textChanged);
    } catch (const std::exception& e) {
        qDebug() << "Exception in researchPage: " << e.what();
        isTableBeingUpdated = false;
    } catch (...) {
        qDebug() << "Unknown exception in researchPage";
        isTableBeingUpdated = false;
    }
}


void MainWindow::techPage() {

    page = 4;

    if (!ui->loginGroupBox || !ui->pageE || !ui->pageR || !ui->pageP || !ui->pageV) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    ui->loginGroupBox->hide();
    ui->pageE->hide();
    ui->pageP->hide();
    ui->pageV->hide();
    ui->page_3->hide();
    ui->pageR->hide();
    ui->pageeq->show();
    isUserLoggedIn = true;




    connect(ui->sortComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBox_changed);
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_rech_textChanged);

    // Database connection

    if (ui->tableWidget->columnCount() == 0) {
        ui->tableWidget->setColumnCount(8);
        QStringList headers;
        headers << "ID" << "Nom" << "Etat" << "Quantité" << "Type" << "Date Maintenance" << "Description" << "Fournisseur";
        ui->tableWidget->setHorizontalHeaderLabels(headers);
    }

    // Configure table settings
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                     QAbstractItemView::EditKeyPressed);

    // Set up custom delegates
    typeDelegate = new TypeDelegate(this);
    etatDelegate = new EtatDelegate(this);
    dateDelegate = new DateDelegate(this);

    ui->tableWidget->setItemDelegateForColumn(4, typeDelegate); // Type column
    ui->tableWidget->setItemDelegateForColumn(2, etatDelegate); // Etat column
    ui->tableWidget->setItemDelegateForColumn(5, dateDelegate); // Date column

    // Load initial data
    isTableBeingUpdated = true;
    e.load_equipement_data(ui->tableWidget);
    ui->chartLayout->setVisible(false);
    ui->tableWidget->setVisible(true);

    // Make ID column non-editable
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
        if (idItem) {
            idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        }
    }

    isTableBeingUpdated = false;

    // Connect cell changed signal
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &MainWindow::on_tableWidget_cellChangedfares);

    // Set validator for FEQ field (8 digits only)
    QRegularExpression rxPhone("^\\d{8}$");
    QValidator *validator = new QRegularExpressionValidator(rxPhone, this);
    ui->FEQ->setValidator(validator);

    // Set minimum date for TEMPMEQ to today
    ui->TEMPMEQ->setMinimumDate(QDate::currentDate());

}







//////////////////////////////////logggginnnnnnnnnnnnnnnnnnnnnn*********************************************************
// integraatttttionnnnnn

void MainWindow::on_loginButton_clicked() {
    QString email = ui->loginEmail->text();
    QString password = ui->loginPassword->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    if (CrudE::login(email, password, CrudE::idN, CrudE::roleN)) {
        qDebug() << "Logged in with ID:" << CrudE::idN << "Role:" << CrudE::roleN;

        if (CrudE::roleN == "Chercheur") {
            researchPage();

            if (ui->emp) ui->emp->hide();
            if (ui->pdr) ui->pdr->show();
            if (ui->rdvbtn) ui->rdvbtn->show();
            if (ui->pt) ui->pt->show();
            if (ui->vac) ui->vac->show();
            ui->empL->hide();
        } else if (CrudE::roleN == "Administrateur"){
            showMainPage();
            // Swap texts
            QPoint empPos = ui->emp->pos();
            QPoint homePos = ui->home->pos();
            ui->emp->move(homePos);
            ui->home->move(empPos);
            QPoint empLPos = ui->empL->pos();
            QPoint homeLPos = ui->homeL->pos();
            ui->empL->move(homeLPos);
            ui->homeL->move(empLPos);
            if (ui->emp) ui->emp->show();
            if (ui->pdr) ui->pdr->show();
            if (ui->rdvbtn) ui->rdvbtn->show();
            if (ui->pt) ui->pt->show();
            ui->vac->show();
            ui->empL->show();
        }
        else{
            techPage();

            QPoint rdvPos = ui->rdvbtn->pos();
            QPoint eqPos = ui->eqbtn->pos();
            ui->eqbtn->move(rdvPos);
            ui->rdvbtn->move(eqPos);
            QPoint rdvLPos = ui->rdvL->pos();
            QPoint eqLPos = ui->eqL->pos();
            ui->rdvL->move(eqLPos);
            ui->eqL->move(rdvLPos);
            QPoint vacPos = ui->vac->pos();
            QPoint disconnectPos = ui->disconnect->pos();
            ui->disconnect->move(vacPos);
            ui->vac->move(disconnectPos);
            QPoint logoutLPos = ui->logoutL->pos();
            QPoint vacLPos = ui->vacL->pos();
            ui->logoutL->move(vacLPos);
            ui->vacL->move(logoutLPos);

            // Cacher tous les boutons sauf eqbtn, home et logout
            if (ui->emp) ui->emp->hide();
            if (ui->pdr) ui->pdr->hide();
            if (ui->rdvbtn) ui->rdvbtn->hide();
            if (ui->vac) ui->vac->hide();
            if (ui->pt) ui->pt->hide();
            if (ui->homeL) ui->homeL->show();
            if (ui->eqL) ui->eqL->show();
            if (ui->disconnect) ui->logoutL->show();
            if (ui->rdvL) ui->rdvL->hide();
            if (ui->pdrL) ui->pdrL->hide();
            if (ui->empL) ui->empL->hide();
            if (ui->vacL) ui->vacL->hide();
            if (ui->ptL) ui->ptL->hide();




        }

    } else {
        if (QSystemTrayIcon::isSystemTrayAvailable()) {
            QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
            trayIcon->setIcon(QIcon::fromTheme("dialog-error"));
            trayIcon->show();
            trayIcon->showMessage(
                "Alerte",
                "Alerte : Une personne étrange essaie d'accéder à votre compte !",
                QSystemTrayIcon::Critical,
                5000
                );
        }
        QMessageBox::critical(this, "Erreur", "Email ou mot de passe incorrect");
    }
}






void MainWindow::showVaccinPage()
{

    page = 5;

    if (!ui->loginGroupBox || !ui->pageE || !ui->pageR || !ui->pageP || !ui->pageV ) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    ui->loginGroupBox->hide();
    ui->pageE->hide();
    ui->pageR->hide();
    ui->pageP->hide();
    ui->page_3->hide();
    ui->pageeq->hide();
    ui->pageV->show();
    isUserLoggedIn = true;




    connect(ui->id2v_2, &QLineEdit::textChanged, this, &MainWindow::filtrerVaccins);
    connect(ui->label_stat_2, &ClickableLabel::clicked, this, &MainWindow::on_StatButtonv_2_clicked);
    ClickableLabel* clickable = qobject_cast<ClickableLabel*>(ui->labelEtude_2);
    if (clickable) {
        connect(clickable, &ClickableLabel::clicked, this, &MainWindow::on_btnEtudeConcurrencev_2_clicked);
    } else {
        qDebug() << "Erreur : labelEtude n'est pas un ClickableLabel.";
    }

    connect(ui->labelEtude_2, &ClickableLabel::clicked, this, &MainWindow::on_btnEtudeConcurrencev_2_clicked);

    connect(ui->tableWidgetv_2, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::on_tableWidgetv_2_cellDoubleClicked);



    // Sélection par défaut
    ui->trierv_2->setCurrentText("Show all");
    // Charger les données initiales sans tri
    mettreAJourAffichageTriv_2();

    // Connexion automatique au changement d'option
    connect(ui->trierv_2, &QComboBox::currentTextChanged, this, &MainWindow::mettreAJourAffichageTriv_2);




    // Configuration du tableau
    ui->tableWidgetv_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetv_2->setSelectionMode(QAbstractItemView::SingleSelection);

    // Connexion pour détecter les sélections
    connect(ui->tableWidgetv_2, &QTableWidget::itemSelectionChanged, [this]() {
        auto selected = ui->tableWidgetv_2->selectedItems();
        if (!selected.isEmpty()) {
            currentSelectedId = ui->tableWidgetv_2->item(selected.first()->row(), 0)->text().toInt();
        }

    });
    chargerDonneesDansTableWidgetv(); // Au lieu de setModel

}


void MainWindow::showPatientPage()
{
    page = 3; // Numéro de page différent pour les patients

    // Vérification des composants UI critiques
    if (!ui->loginGroupBox || !ui->pageE || !ui->pageR || !ui->pageP) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    // Masquer toutes les autres pages et afficher la page patient
    ui->loginGroupBox->hide();
    ui->pageE->hide();
    ui->pageR->hide();
    ui->pageV->hide();
    ui->page_3->hide();
    ui->pageeq->hide();
    ui->pageP->show();
    isUserLoggedIn = true;

    // Initialisation du tableau des patients
    try {
        if (!ui->tableWidgetp) {
            qDebug() << "Patient table widget is null!";
            return;
        }

        // Configuration de la structure du tableau si ce n'est pas déjà fait
        if (ui->tableWidgetp->columnCount() != 7) { // Adaptez selon vos besoins
            ui->tableWidgetp->setColumnCount(7);
            QStringList headers;
            headers << "ID" << "Nom" << "Prénom" << "Genre"
                    << "Téléphone" << "Date de Naissance" << "Fichier";
            ui->tableWidgetp->setHorizontalHeaderLabels(headers);

            // Ajustement des largeurs de colonnes
            ui->tableWidgetp->setColumnWidth(0, 80);   // ID
            ui->tableWidgetp->setColumnWidth(1, 150);  // Nom
            ui->tableWidgetp->setColumnWidth(2, 150);  // Prénom
            ui->tableWidgetp->setColumnWidth(3, 100);  // Genre
            ui->tableWidgetp->setColumnWidth(4, 120);  // Téléphone
            ui->tableWidgetp->setColumnWidth(5, 150);  // Date de Naissance
            ui->tableWidgetp->setColumnWidth(6, 200);  // Fichier
        }

        // Chargement des données des patients
        Crudp crudp;
        crudp.load_patients(ui->tableWidgetp);

        // Configuration des connexions des signaux
        disconnect(ui->tableWidgetp, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidgetp_cellClicked);
        disconnect(ui->sortComboBoxp, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxp_changed);
        disconnect(ui->nom2p, &QLineEdit::textChanged, this, &MainWindow::on_nom2p_textChanged);

        connect(ui->tableWidgetp, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidgetp_cellClicked);
        connect(ui->sortComboBoxp, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBoxp_changed);
        connect(ui->nom2p, &QLineEdit::textChanged, this, &MainWindow::on_nom2p_textChanged);

        // Masquer les statistiques par défaut
        ui->chartLayoutp->setVisible(false);
        ui->tableWidgetp->setVisible(true);

    } catch (const std::exception& e) {
        qDebug() << "Exception in showPatientPage: " << e.what();
        QMessageBox::critical(this, "Error", "Failed to load patient data: " + QString(e.what()));
    } catch (...) {
        qDebug() << "Unknown exception in showPatientPage";
        QMessageBox::critical(this, "Error", "An unknown error occurred while loading patient data");
    }
}


void MainWindow::on_disconnect_clicked() {
    // Déconnexion

        qDebug() << "Logged in with ID:" << CrudE::idN << "Role:" << CrudE::roleN;
        if (CrudE::roleN == "Administrateur") {

            QPoint homePos = ui->home->pos();
            QPoint empPos = ui->emp->pos();
            ui->home->move(empPos);
            ui->emp->move(homePos);

            QPoint homeLPos = ui->homeL->pos();
            QPoint empLPos = ui->empL->pos();
            ui->homeL->move(empLPos);
            ui->empL->move(homeLPos);
        }
        else if (CrudE::roleN == "Technicien"){
            QPoint eqPos = ui->eqbtn->pos();
            QPoint rdvPos = ui->rdvbtn->pos();
            ui->rdvbtn->move(eqPos);
            ui->eqbtn->move(rdvPos);

            QPoint eqLPos = ui->eqL->pos();
            QPoint rdvLPos = ui->rdvL->pos();
            ui->eqL->move(rdvLPos);
            ui->rdvL->move(eqLPos);

            QPoint disconnectPos = ui->disconnect->pos();
            QPoint vacPos = ui->vac->pos();
            ui->vac->move(disconnectPos);
            ui->disconnect->move(vacPos);

            QPoint vacLPos = ui->vacL->pos();
            QPoint logoutLPos = ui->logoutL->pos();
            ui->vacL->move(logoutLPos);
            ui->logoutL->move(vacLPos);
            if (ui->rdvL) ui->rdvL->show();
            if (ui->pdrL) ui->pdrL->show();
            if (ui->empL) ui->empL->show();
            if (ui->vacL) ui->vacL->show();
            if (ui->ptL) ui->ptL->show();


        }











    ui->loginEmail->clear();
    ui->loginPassword->clear();
    showLoginPage();
    CrudE::idN=0;
    CrudE::roleN="";
    qDebug()<<"recieved"<<CrudE::idN<<CrudE::roleN;





}
//youfa houni li code mabado chy




//******************************************************jjjiheddddddddddddddddddd***********************************************************************************


/*
 //l9dimaa nta3 el integration

void MainWindow::chargerDonneesDansTableWidgetv()
{
    ui->chartLayoutv_2->setVisible(false);  // Masquer le chartLayout

    QSqlQueryModel *model = v.afficherv(); // Utilise votre méthode existante

    // Configure le nombre de colonnes
    ui->tableWidgetv_2->setColumnCount(model->columnCount());

    // Configure les en-têtes
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidgetv_2->setHorizontalHeaderLabels(headers);

    // Remplit les données
    ui->tableWidgetv_2->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            // QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());

            QVariant value = model->data(model->index(row, col));
            // Si la colonne actuelle est "Validation Period" (indice 5)
            if (col == 5 && value.canConvert(QMetaType::Double)) {
                double val = value.toDouble();
                QString formatted = QString::number(val, 'f', 0); // pas de décimales, pas de notation scientifique
                ui->tableWidgetv_2->setItem(row, col, new QTableWidgetItem(formatted));
            } else {
                ui->tableWidgetv_2->setItem(row, col, new QTableWidgetItem(value.toString()));
            }



            // ui->tableWidget->setItem(row, col, item);
        }
    }

    delete model; // Nettoyage mémoire
}

*/



void MainWindow::chargerDonneesDansTableWidgetv()
{
    ui->chartLayoutv_2->setVisible(false);  // Masquer le chartLayout

    QSqlQueryModel *model = v.afficherv(); // Utilise votre méthode existante

    // Configure le nombre de colonnes (en excluant la dernière colonne)
    int columnCount = model->columnCount() - 1;  // Exclure la dernière colonne
    ui->tableWidgetv_2->setColumnCount(columnCount);

    // Configure les en-têtes
    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidgetv_2->setHorizontalHeaderLabels(headers);

    // Remplit les données
    ui->tableWidgetv_2->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QVariant value = model->data(model->index(row, col));

            // Si la colonne actuelle est "Validation Period" (indice 5)
            if (col == 5 && value.canConvert(QMetaType::Double)) {
                double val = value.toDouble();
                QString formatted = QString::number(val, 'f', 0); // Pas de décimales, pas de notation scientifique
                ui->tableWidgetv_2->setItem(row, col, new QTableWidgetItem(formatted));
            } else {
                ui->tableWidgetv_2->setItem(row, col, new QTableWidgetItem(value.toString()));
            }
        }
    }

    delete model; // Nettoyage mémoire
}




void MainWindow::verifierNom()
{
    QString nom = ui->nomv_2->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$"); // Accepte uniquement les lettres avec accents

    if (nom.isEmpty()) {
        ui->nom_erreur_2->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(nom).hasMatch()) {
        ui->nom_erreur_2->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->nom_erreur_2->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}

void MainWindow::verifierValidation()
{
    QString validation = ui->validationv_2->text();
    QRegularExpression regex("^[0-9]+$"); // Accepte uniquement des chiffres

    if (validation.isEmpty()) {
        ui->validation_erreur_2->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(validation).hasMatch()) {
        ui->validation_erreur_2->setText("La validation doit contenir uniquement des chiffres.");
    } else {
        ui->validation_erreur_2->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}
void MainWindow::verifierDescription()
{
    QString description = ui->descriptionv_2->toPlainText();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$"); // Accepte uniquement des lettres (avec accents) et des espaces

    if (description.isEmpty()) {
        ui->description_erreur_2->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(description).hasMatch()) {
        ui->description_erreur_2->setText("La description ne doit contenir que des lettres et des espaces.");
    } else {
        ui->description_erreur_2->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}

/*void MainWindow::verifierDateFabrication()
{
    QString fabricationStr = ui->fabricationv_2->text();
    QDate dateFabrication = QDate::fromString(fabricationStr, "yyyy-MM-dd"); // Assurez-vous du bon format
    QString dateFabricationStr = dateFabrication.toString("MM/dd/yyyy");

    QDate dateActuelle = QDate::currentDate();
    QString date = dateActuelle.toString("MM/dd/yyyy");
    QDate dateMinimale = dateActuelle.addDays(-30); // La limite est 30 jours avant aujourd’hui
    QString dateAnglaise = dateMinimale.toString("MM/dd/yyyy");
    qDebug()<<"date min"<<dateMinimale;
    if (!dateFabrication.isValid()) {
        ui->fabrication_erreur_2->setText("Format de date invalide. Utilisez JJ-MM-AAAA.");
    }
    else
        if (dateFabricationStr < dateAnglaise || dateFabricationStr > date) {
        ui->fabrication_erreur_2->setText("La date doit être entre aujourd'hui et il y a 30 jours.");
    }
    else {
        ui->fabrication_erreur_2->clear(); // Efface l'erreur si la date est correcte
    }

}

*/

void MainWindow::verifierDateFabrication()
{
    QDate dateFabrication = ui->fabricationv_2->date();  // Directement depuis QDateEdit

    QDate dateActuelle = QDate::currentDate();
    QDate dateMinimale = dateActuelle.addDays(-30);  // 30 jours avant aujourd'hui

    if (dateFabrication < dateMinimale || dateFabrication > dateActuelle) {
        ui->fabrication_erreur_2->setText("The date must be between today and 30 days ago.");
    } else {
        ui->fabrication_erreur_2->clear();  // Tout est bon
    }

    // Si tu dois envoyer dans la base en VARCHAR("yyyy-MM-dd")
    QString dateStrToStore = dateFabrication.toString("yyyy-MM-dd");
    qDebug() << "Date to insert into DB:" << dateStrToStore;
}





void MainWindow::verifierMaladie()
{
    QString maladie = ui->maladiev_2->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$"); // Accepte uniquement les lettres avec accents

    if (maladie.isEmpty()) {
        ui->maladie_erreur_2->clear();  // Efface l'erreur si le champ est vide
    } else if (!regex.match(maladie).hasMatch()) {
        ui->maladie_erreur_2->setText("Le maladie doit contenir uniquement des lettres.");
    } else {
        ui->maladie_erreur_2->clear();  // Efface l'erreur si l'entrée devient correcte
    }
}

void MainWindow::on_pushButton_15v_2_clicked()
{
    if (isEditMode) return;
    // Validation des champs (identique à votre version originale)
    verifierNom();
    verifierValidation();
    verifierDescription();
   verifierDateFabrication();
    verifierMaladie();

    QString nom = ui->nomv_2->text();
    QString type = ui->typev_2->currentText();
    QString maladie = ui->maladiev_2->text();
    QString fabrication = ui->fabricationv_2->text();
    int validation = ui->validationv_2->text().toInt();
    QString description = ui->descriptionv_2->toPlainText();
    double temperature = ui->temperaturev_2->value();
    int EMPLOYE=CrudE::idN;

    // Connexions pour la validation en temps réel
    connect(ui->nomv_2, &QLineEdit::textChanged, this, &MainWindow::verifierNom);
    connect(ui->validationv_2, &QLineEdit::textChanged, this, &MainWindow::verifierValidation);
    connect(ui->descriptionv_2, &QTextEdit::textChanged, this, &MainWindow::verifierDescription);
    connect(ui->fabricationv_2, &QDateEdit::dateChanged, this, &MainWindow::verifierDateFabrication);
    connect(ui->maladiev_2, &QLineEdit::textChanged, this, &MainWindow::verifierMaladie);


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

    QString validationStr = ui->validationv_2->text();
    QRegularExpression regex1("^[0-9]+$");

    if (!regex1.match(validationStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La validation doit contenir uniquement des chiffres.");
        return;
    }

    QRegularExpression regex2("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$"); // Accepte uniquement des lettres (avec accents) et des espaces
    QString descriptionStr = ui->descriptionv_2->toPlainText();
    if (!regex2.match(descriptionStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La description ne doit contenir que des lettres et des espaces.");
        return;
    }

   verifierDateFabrication();
    if (!ui->fabrication_erreur_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Corrigez la date avant d'ajouter.");
        return;
    }

    // Vérification que le maladie contient uniquement des lettres
    QRegularExpression regex3("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex3.match(maladie).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "La maladie doit contenir uniquement des lettres.");
        return;
    }

    qDebug()<<EMPLOYE;

    // Création et ajout du vaccin
    vaccin newVaccin(nom, type, maladie, fabrication, validation, description,temperature,EMPLOYE);
    bool test = newVaccin.ajouterv();

    if (test) {

        chargerDonneesDansTableWidgetv();

        // Réinitialisation des champs
        ui->nomv_2->clear();
        ui->maladiev_2->clear();
        ui->fabricationv_2->clear();
        ui->validationv_2->clear();
        ui->descriptionv_2->clear();
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
        if (clickedWidget != ui->tableWidgetv_2 &&
            (clickedWidget->parentWidget() == nullptr ||
             !clickedWidget->parentWidget()->inherits("QHeaderView")))
        {
            ui->tableWidgetv_2->clearSelection();
            ui->tableWidgetv_2->clearFocus();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}



void MainWindow::on_dropv_2_clicked()
{
    if (currentSelectedId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un vaccin en cliquant sur une ligne");
        return;
    }

    if (QMessageBox::Yes == QMessageBox::question(this, "Confirmation",
                                                  "Voulez-vous vraiment supprimer ce vaccin?",
                                                  QMessageBox::Yes|QMessageBox::No))
    {
        if (v.supprimerv(currentSelectedId)) {
            // Recharger les données ou supprimer la ligne directement
            chargerDonneesDansTableWidgetv();
            currentSelectedId = -1;

        }
    }
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);

    // Ne pas effacer currentSelectedId ici, seulement la sélection visuelle
    if (!ui->tableWidgetv_2->underMouse()) {
        ui->tableWidgetv_2->clearSelection();
        currentSelectedId = -1;
    }
}


void MainWindow::on_tableWidgetv_2_cellDoubleClicked(int row, int column) {
    Q_UNUSED(row);
    Q_UNUSED(column);

    if (!enModeHistorique) {
        on_pushButton_Modifierv_2_clicked(); // Seulement en mode normal
    }
}


void MainWindow::on_pushButton_Modifierv_2_clicked()
{
    int id = ui->id2v_2->text().toInt();
    QString nom, type, maladie, fabrication, description;
    double temperature;
    int validation;
    if (currentSelectedId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un vaccin en cliquant sur une ligne");
        return;
    }

    if (v.chargerVaccinv(currentSelectedId, nom, type, maladie, fabrication, validation, description,temperature)) {
        qDebug() << "Température récupérée: " << temperature;
        ui->nomv_2->setText(nom);
        ui->typev_2->setCurrentText(type);
        ui->maladiev_2->setText(maladie);
       // ui->fabricationv_2->setDate(QDate::fromString(fabrication, "yyyy-MM-dd"));
        qDebug() << "Fabrication : " << fabrication;
        QDate fabricationDate = QDate::fromString(fabrication, "M/d/yyyy");
        ui->fabricationv_2->setDate(fabricationDate);
        ui->validationv_2->setText(QString::number(validation));
        ui->descriptionv_2->setText(description);
        ui->temperaturev_2->setValue(temperature);

        // 3. Transforme le bouton "Ajouter" en "Rafraîchir" FONCTIONNEL
        ui->pushButton_15v_2->setText("Refresh");
        isEditMode = true;

        // 4. Reconnecte dynamiquement le bouton
        disconnect(ui->pushButton_15v_2, nullptr, nullptr, nullptr); // Désactive les anciennes connexions
        connect(ui->pushButton_15v_2, &QPushButton::clicked, this, [this]() {
            on_pushButton_Rafraichirv_2_clicked(); // Appel DIRECT à votre fonction existante
        });
    } else {
        QMessageBox::critical(this, "Erreur", "Aucun vaccin trouvé avec cet ID.");
    }
}

void MainWindow::on_pushButton_Rafraichirv_2_clicked()
{
    // Logique identique à on_pushButton_15_clicked() mais avec modification
    int id = ui->id2v_2->text().toInt();
    if (isEditMode) {
        QString nom = ui->nomv_2->text();
        QString type = ui->typev_2->currentText();
        QString maladie = ui->maladiev_2->text();
        QString fabrication = ui->fabricationv_2->text();
        int validation = ui->validationv_2->text().toInt();
        QString description = ui->descriptionv_2->toPlainText();
        double temperature = ui->temperaturev_2->value();

        connect(ui->nomv_2, &QLineEdit::textChanged, this, &MainWindow::verifierNom);
        connect(ui->validationv_2, &QLineEdit::textChanged, this, &MainWindow::verifierValidation);
        connect(ui->descriptionv_2, &QTextEdit::textChanged, this, &MainWindow::verifierDescription);
       connect(ui->fabricationv_2, &QDateEdit::dateChanged, this, &MainWindow::verifierDateFabrication);
        connect(ui->maladiev_2, &QLineEdit::textChanged, this, &MainWindow::verifierMaladie);

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

        QString validationStr = ui->validationv_2->text();
        QRegularExpression regex1("^[0-9]+$");

        if (!regex1.match(validationStr).hasMatch()) {
            QMessageBox::warning(this, "Erreur", "La validation doit contenir uniquement des chiffres.");
            return;
        }

        QRegularExpression regex2("^[A-Za-zÀ-ÖØ-öø-ÿ\\s]+$"); // Accepte uniquement des lettres (avec accents) et des espaces
        QString descriptionStr = ui->descriptionv_2->toPlainText();
        if (!regex2.match(descriptionStr).hasMatch()) {
            QMessageBox::warning(this, "Erreur", "La description ne doit contenir que des lettres et des espaces.");
            return;
        }

        verifierDateFabrication();
        if (!ui->fabrication_erreur_2->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Corrigez la date avant d'ajouter.");
            return;
        }

        // Vérification que le maladie contient uniquement des lettres
        QRegularExpression regex3("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
        if (!regex3.match(maladie).hasMatch()) {
            QMessageBox::warning(this, "Erreur", "La maladie doit contenir uniquement des lettres.");
            return;
        }

        bool test = v.modifierv(currentSelectedId, nom, type, maladie, fabrication, validation, description,temperature);

        if (test) {

            chargerDonneesDansTableWidgetv();
            // 2. Réinitialise le bouton à "Ajouter"
            ui->pushButton_15v_2->setText("Add");
            isEditMode = false;

            // 3. Reconnecte à la fonction d'ajout
            disconnect(ui->pushButton_15v_2, nullptr, nullptr, nullptr);
            connect(ui->pushButton_15v_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_15v_2_clicked);
            currentEditId = -1;
            ui->nomv_2->clear();
            ui->maladiev_2->clear();
            ui->fabricationv_2->clear();
            ui->validationv_2->clear();
            ui->descriptionv_2->clear();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la modification du vaccin.");
        }
    }
}

//rechercher vaccin
void MainWindow::filtrerVaccins(const QString &term)
{
    QString critere = ui->comboBox_criterev_2->currentText();
    QSqlQueryModel* model = nullptr;

    // Si le champ est vide, charger tous les vaccins
    if (term.isEmpty()) {
        model = v.afficherv();  // Afficher tous les vaccins
        ui->label_infov_2->hide();  // Cacher le message d'erreur éventuel
    } else {
        model = v.rechercherv(term, critere);
    }

    if (!model) return;

    // Vérifier s'il y a des résultats
    if (model->rowCount() == 0) {
        // Tableau : une seule ligne avec un message
        ui->tableWidgetv_2->clear();
        ui->tableWidgetv_2->setRowCount(1);
        ui->tableWidgetv_2->setColumnCount(1);
        ui->tableWidgetv_2->setHorizontalHeaderLabels(QStringList() << "Message");
        QTableWidgetItem *item = new QTableWidgetItem("🔍 No vaccine matches your search.");
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetv_2->setItem(0, 0, item);

        // Label : message doux au-dessus du tableau
        ui->label_infov_2->setText("No results found for \"" + term + "\".");
        ui->label_infov_2->setStyleSheet("color: orange; font-weight: bold;");
        ui->label_infov_2->show();

        delete model;
        return;
    }

    // Si on a des résultats
    ui->label_infov_2->hide();  // Cacher le label d’erreur
    ui->tableWidgetv_2->clear();
    ui->tableWidgetv_2->setRowCount(0);
    ui->tableWidgetv_2->setColumnCount(model->columnCount());
    // On récupère les noms des colonnes (ex: nom, type…) et on les stocke dans headers
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidgetv_2->setHorizontalHeaderLabels(headers);

    ui->tableWidgetv_2->setRowCount(model->rowCount());

    QColor highlightColor = QColor(173, 216, 230); // Bleu clair

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());

            if (!term.isEmpty()) {
                item->setBackground(highlightColor);  // Colorer uniquement si recherche
            }

            ui->tableWidgetv_2->setItem(row, col, item);
        }
    }

    delete model;
}













void MainWindow::on_pushButton_Reinitialiserv_2_clicked()
{
    enModeHistorique = false;

    ui->tableWidgetv_2->setVisible(true);
    ui->tableWidgetv_2->clear(); // Supprime tout (colonnes + données)
    ui->tableWidgetv_2->setRowCount(0);
    ui->tableWidgetv_2->setColumnCount(0);
    // Ensuite tu ajoutes les colonnes + tu remplis avec les données du modèle si besoin

    // 1. Réinitialiser les couleurs
    for (int i = 0; i < ui->tableWidgetv_2->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidgetv_2->columnCount(); ++j) {
            if (QTableWidgetItem* item = ui->tableWidgetv_2->item(i, j)) {
                item->setBackground(Qt::white);
                item->setForeground(Qt::black);
            }
        }
    }

    // 2. Vider les champs de recherche/modification
    ui->id2v_2->clear();
    ui->nomv_2->clear();
    ui->maladiev_2->clear();
    ui->fabricationv_2->clear();
    ui->validationv_2->clear();
    ui->descriptionv_2->clear();

    // 3. Recharger toutes les données depuis la base
    chargerDonneesDansTableWidgetv();  // Votre fonction existante

    isEditMode = false;
    // 4. Remettre le bouton en mode "Ajouter" si nécessaire
    if (ui->pushButton_15v_2->text() == "Refresh") {
        ui->pushButton_15v_2->setText("Add");
    }
    disconnect(ui->pushButton_15v_2, nullptr, nullptr, nullptr);
    connect(ui->pushButton_15v_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_15v_2_clicked);
    currentEditId = -1;


}






void MainWindow::mettreAJourAffichageTriv_2() {
    QString critere = ui->trierv_2->currentText().toLower();

    // Si l'utilisateur sélectionne "show_all", on affiche tout sans tri
    if (critere == "show all") {
        chargerDonneesDansTableWidgetv(); // méthode que tu dois avoir pour l'affichage normal
        return;
    }
    if (critere == "name") {
        critere="nom";
    }
    if (critere == "production date") {
        critere="date_fabrication";
    }
    if (critere == "validation period") {
        critere="duree_validation";
    }

    if (critere == "my vaccins") {
        bool ascendant = true;
         QSqlQueryModel* model =v.trierMesVaccins();

        if (!model) return;

        ui->tableWidgetv_2->setRowCount(model->rowCount());
        ui->tableWidgetv_2->setColumnCount(model->columnCount());

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
                ui->tableWidgetv_2->setItem(row, col, item);
            }
        }
        delete model;
    }
   else{
    // Détermination de l'ordre (tu peux améliorer en lisant un autre champ)
    bool ascendant = true;

    QSqlQueryModel* model = v.trierv(critere, ascendant);
    if (!model) return;

    ui->tableWidgetv_2->setRowCount(model->rowCount());
    ui->tableWidgetv_2->setColumnCount(model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidgetv_2->setItem(row, col, item);
        }
    }
    delete model;
    }

}




QString MainWindow::getSelectedVaccinIdv() {
    QModelIndexList selectedRows = ui->tableWidgetv_2->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        return "";  // Aucun vaccin sélectionné
    }

    // Supposons que l'ID du vaccin se trouve dans la première colonne (colonne 0)
    //récupère seulement la première ligne sélectionnée
    QModelIndex index = selectedRows.first();
    return ui->tableWidgetv_2->item(index.row(), 0)->text();  // Retourne l'ID du vaccin
}





void MainWindow::exporterCSVv_2() {
    QSqlQueryModel* model = v.exporterPDFv(); // ou autre méthode qui retourne un QSqlQueryModel*
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

void MainWindow::on_pushButton_PDFv_2_clicked() {



    //À chaque fois que l’utilisateur clique sur le bouton PDF, la fonction est rappelée, mais pdfClickCount garde sa valeur d’avant.
    static int pdfClickCount = 0; // Garde en mémoire le nombre de clics

    QString idVaccin = getSelectedVaccinIdv();
    bool isVaccinSelected = !idVaccin.isEmpty();

    if (isVaccinSelected) {
        pdfClickCount = 0; // Réinitialiser le compteur
    } else {
        pdfClickCount++; // Incrémenter si aucun vaccin sélectionné
    }

    if (!isVaccinSelected && pdfClickCount >= 2) {
        pdfClickCount = 0;
        exporterCSVv_2(); // Appel à ta fonction Excel
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QSqlQueryModel* model = isVaccinSelected ? v.exporterPDFv(idVaccin) : v.exporterPDFv();
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
    enModeHistorique = true;

    QSqlQueryModel *model = v.afficherHistoriquev(idVaccin);
    if (!model) return;

    // Vider le tableau
    ui->tableWidgetv_2->clear();
    ui->tableWidgetv_2->setRowCount(0);
    ui->tableWidgetv_2->setColumnCount(model->columnCount());

    // Définir les en-têtes
    QStringList headers;
    for (int i = 0; i < model->columnCount(); ++i) {
        headers << model->headerData(i, Qt::Horizontal).toString();
    }
    ui->tableWidgetv_2->setHorizontalHeaderLabels(headers);

    // Activer le retour à la ligne
    ui->tableWidgetv_2->setWordWrap(true);

    // Remplir les données
    ui->tableWidgetv_2->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();

            QTableWidgetItem *item = new QTableWidgetItem(data);
            item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft); //en haut et à gauche
            item->setToolTip(data); // Texte complet au survol
            item->setFlags(item->flags() ^ Qt::ItemIsEditable); // Cela permet de désactiver l'édition d'un item

            ui->tableWidgetv_2->setItem(row, col, item);
        }
    }

    // Ajuster taille des colonnes et lignes au contenu
    ui->tableWidgetv_2->resizeColumnsToContents();
    ui->tableWidgetv_2->resizeRowsToContents();

    // Pour empêcher l'édition directe (sécurité visuelle)
    ui->tableWidgetv_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //rend le QTableWidget en lecture seule

    delete model;
}








void MainWindow::on_pushButton_Historiquev_2_clicked()
{
    enModeHistorique = true;

    QItemSelectionModel* selectionModel = ui->tableWidgetv_2->selectionModel(); //Récupère le modèle de sélection
    int row = -1;

    if (selectionModel && selectionModel->hasSelection()) {  //si une ou plusieurs lignes sont sélectionnées
        row = selectionModel->currentIndex().row();   //envoie le numéro de la ligne de cette cellule.
    }

    if (row >= 0) {
        // Un vaccin est sélectionné  afficher l’historique du vaccin sélectionné
        QTableWidgetItem *item = ui->tableWidgetv_2->item(row, 0); //reccuperer l id (colonne 1)
        if (item) {
            int idVaccin = item->text().toInt();
            afficherHistoriqueVaccin(idVaccin);
        }
    } else {
        // Aucun vaccin sélectionné → afficher tout l’historique (sans message)
        afficherHistoriqueVaccin(-1);  // -1 pour tous les vaccins
    }
}








void MainWindow::on_StatButtonv_2_clicked() {
    if (ui->chartLayoutv_2->isVisible()) {
        ui->chartLayoutv_2->setVisible(false);
        ui->tableWidgetv_2->setVisible(true);
        return; // Sortie directe sans exécuter le reste du code
    }
    ui->chartLayoutv_2->setVisible(true);
    ui->tableWidgetv_2->setVisible(false);

    // Nettoyer l'ancien contenu
    QLayout *layout = ui->chartLayoutv_2->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();  // Supprimer les widgets (graphiques)
            delete item;
        }
    } else {
        layout = new QHBoxLayout();  // Disposition horizontale
        ui->chartLayoutv_2->setLayout(layout);
    }

    // Récupérer les statistiques
    // QVector<QPair<int, int>> stats = v.getStatistiquesValidation();
    QVector<QPair<QString, int>> stats = v.getStatistiquesParTypev();
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
    pieChart->setTitle("Categorization of vaccines by type");
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
        AnimatedBarItemv *bar = new AnimatedBarItemv(xPos, yBase, barWidth, barColor);
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
    ui->chartLayoutv_2->layout()->addWidget(barView);       // Barres à gauche
    ui->chartLayoutv_2->layout()->addWidget(pieChartView);  // Camembert à droite
}





#include <QMessageBox>  // Ajoute l'inclusion de QMessageBox








void MainWindow::on_btnEtudeConcurrencev_2_clicked()
{
    int row = ui->tableWidgetv_2->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un vaccin.");
        return;
    }

    QString id = ui->tableWidgetv_2->item(row, 0)->text();
    QString type = ui->tableWidgetv_2->item(row, 2)->text();
    QString maladie = ui->tableWidgetv_2->item(row, 3)->text();
    QString description = ui->tableWidgetv_2->item(row, 6)->text();



    QStringList descriptionsConcurrents = v.getConcurrentsv(type, maladie, id);


    Conccurance *ai = new Conccurance(this);  // Cela signifie que this est passé comme paramètre au constructeur
    connect(ai, &Conccurance::analysisReady, this, [=](const QString &result) { //Quand tu as fini d'analyser, dis-le-moi, et moi j'affiche le résultat dans une fenêtre
        //ce slot est une fonction lambda [=](const QString &result), qui prend le résultat de l'analyse de concurrence en entrée et affiche ce résultat
        QMessageBox::information(this, "Résultat de l'analyse de concurrence", result);
    });
    ai->analyserConcurrence(type, maladie, description, descriptionsConcurrents);
}



// ahmed fonctionet li kol ili yikhdmo li button w li ui kholf table w li arduino (hot commentaire win tkamil)




void MainWindow::on_addbutton_2_clicked()
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
    QSqlQuery checkEmp;
    checkEmp.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE IDE = :id");
    checkEmp.bindValue(":id", id_employe);
    checkEmp.exec();
    checkEmp.next();
    if (checkEmp.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Erreur", "ID Employé inexistant !");
        return;
    }

    QSqlQuery checkPat;
    checkPat.prepare("SELECT COUNT(*) FROM PATIENT WHERE ID = :id");
    checkPat.bindValue(":id", id_patient);
    checkPat.exec();
    checkPat.next();
    if (checkPat.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Erreur", "ID Patient inexistant !");
        return;
    }

    // ⚠️ Empêcher un admin d’ajouter pour un autre admin ou technicien
    if (CrudE::roleN == "Admin") {
        QSqlQuery verifRole;
        verifRole.prepare("SELECT ROLEE FROM EMPLOYES WHERE ID = :id");
        verifRole.bindValue(":id", id_employe);
        if (verifRole.exec() && verifRole.next()) {
            QString role = verifRole.value(0).toString();
            if (role != "Chercheur") {
                QMessageBox::warning(this, "Accès refusé", "Vous ne pouvez ajouter un RDV que pour un chercheur.");
                return;
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Employé introuvable.");
            return;
        }
    }

    // 🔁 Conflit
    if (rendervous::isAppointmentConflict(date, heure, duree, id_employe)) {
        QMessageBox::warning(this, "Conflit détecté",
                             "Un autre rendez-vous existe déjà pour cet employé à cette heure.");
        return;
    }

    // 🔄 Création
    rendervous r(date, heure, id_employe, id_patient, duree, status);
    if (r.ajouter()) {
        QMessageBox::information(this, "Succès", "Rendez-vous ajouté avec succès.");
        r.afficher(ui->tablerdv);  // ✅ Mise à jour pour QTableWidget

        ui->date_2->clear();
        ui->heure_2->clear();
        ui->dur_2->clear();
        ui->statut_2->clear();
        ui->idp_2->clear();

        if (CrudE::roleN == "Chercheur") {
            ui->ide_2->setText(QString::number(CrudE::idN));
            ui->ide_2->setDisabled(true);
        } else {
            ui->ide_2->clear();
            ui->ide_2->setEnabled(true);
        }

    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout du rendez-vous a échoué.");
    }
}




void MainWindow::on_deletebutton_2_clicked()
{
    int selectedRow = ui->tablerdv->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Sélection manquante", "Veuillez sélectionner un rendez-vous à supprimer.");
        return;
    }

    QTableWidgetItem *itemId = ui->tablerdv->item(selectedRow, 0);  // Colonne 0 = ID
    if (!itemId) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire l'ID du rendez-vous sélectionné.");
        return;
    }

    int id = itemId->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "ID invalide", "L'ID sélectionné est invalide.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous vraiment supprimer le rendez-vous #" + QString::number(id) + " ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        rendervous r;
        if (r.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Rendez-vous supprimé avec succès.");
            r.afficher(ui->tablerdv);  // Recharge la table
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression du rendez-vous.");
        }
    }
}

void MainWindow::on_rdvRowDoubleClicked(int row, int)
{
    QString id = ui->tablerdv->item(row, 0)->text(); // colonne ID
    QString date = ui->tablerdv->item(row, 1)->text();
    QString heure = ui->tablerdv->item(row, 2)->text();
    QString duree = ui->tablerdv->item(row, 3)->text();
    QString status = ui->tablerdv->item(row, 4)->text();
    QString employe = ui->tablerdv->item(row, 5)->text();
    QString patient = ui->tablerdv->item(row, 6)->text();

    // Remplir les champs de modification (sur page_3 maintenant)
    ui->date_2->setText(date);
    ui->heure_2->setText(heure);
    ui->dur_2->setText(duree);
    ui->statut_2->setText(status);
    ui->ide_2->setText(employe);
    ui->idp_2->setText(patient);
}

void MainWindow::on_updatebutton_2_clicked()
{
    // Vérifier si une ligne est sélectionnée dans le tableWidget
    QList<QTableWidgetItem*> selectedItems = ui->tablerdv->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un rendez-vous à modifier (via double-clic).");
        return;
    }

    int row = ui->tablerdv->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune ligne sélectionnée.");
        return;
    }

    // Récupérer l'ID du rendez-vous à partir de la première colonne
    QTableWidgetItem *idItem = ui->tablerdv->item(row, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer l'ID du rendez-vous.");
        return;
    }
    int id = idItem->text().toInt();

    // Lire les champs de modification (remplis via double clic normalement)
    QString date = ui->date_2->text().trimmed();
    QString heureStr = ui->heure_2->text().trimmed();
    QString dureeStr = ui->dur_2->text().trimmed();
    QString status = ui->statut_2->text().trimmed();
    QString id_employeStr = ui->ide_2->text().trimmed();
    QString id_patientStr = ui->idp_2->text().trimmed();

    bool ok1, ok2, ok3, ok4;
    int heure = heureStr.toInt(&ok1);
    int duree = dureeStr.toInt(&ok2);
    int id_employe = id_employeStr.toInt(&ok3);
    int id_patient = id_patientStr.toInt(&ok4);
   //|| heure < 0   ||duree <= 0
    if ( !ok1 || !ok2 || !ok3 || !ok4 || heure > 23 ) {
        QMessageBox::warning(this, "Erreur", "Veuillez vérifier les champs numériques.");
        return;
    }

    // Restriction pour les chercheurs : ne peuvent modifier que leurs propres rendez-vous
    if (CrudE::roleN == "Chercheur" && id_employe != CrudE::idN) {
        QMessageBox::critical(this, "Refus", "Vous ne pouvez modifier que vos propres rendez-vous.");
        return;
    }
    QSqlQuery checkEmp;
    checkEmp.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE IDE = :id");
    checkEmp.bindValue(":id", id_employe);
    checkEmp.exec();
    checkEmp.next();
    if (checkEmp.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Erreur", "ID Employé inexistant !");
        return;
    }

    QSqlQuery checkPat;
    checkPat.prepare("SELECT COUNT(*) FROM PATIENT WHERE ID = :id");
    checkPat.bindValue(":id", id_patient);
    checkPat.exec();
    checkPat.next();
    if (checkPat.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Erreur", "ID Patient inexistant !");
        return;
    }


    // Mise à jour SQL
    QSqlQuery query;
    query.prepare("UPDATE rendezvous SET "
                  "date_rdv = :date, "
                  "heure = :heure, "
                  "duree = :duree, "
                  "status = :status, "
                  "EMPLOYE = :employe, "
                  "PATIENT = :patient "
                  "WHERE id = :id");

    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":duree", duree);
    query.bindValue(":status", status);
    query.bindValue(":employe", id_employe);
    query.bindValue(":patient", id_patient);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Rendez-vous mis à jour !");
        rendervous r;
        r.afficher(ui->tablerdv); // Actualiser l'affichage
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur SQL : " + query.lastError().text());
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    QTableWidget *table = ui->tablerdv;
    if (table->rowCount() == 0) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty())
        return;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fileName);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF !");
        return;
    }

    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);
    QFontMetrics fontMetrics(font);

    int rowCount = table->rowCount();
    int columnCount = table->columnCount();
    const int margin = 20;
    const int spacing = 10;

    int totalWidth = 0;
    QVector<int> columnWidths(columnCount);
    for (int col = 0; col < columnCount; ++col) {
        int width = fontMetrics.horizontalAdvance(table->horizontalHeaderItem(col)->text()) + spacing;
        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *item = table->item(row, col);
            if (item)
                width = qMax(width, fontMetrics.horizontalAdvance(item->text()) + spacing);
        }
        columnWidths[col] = width;
        totalWidth += width;
    }

    int x = margin;
    int y = margin;
    const int rowHeight = fontMetrics.height() + spacing;

    // En-tête
    painter.setPen(Qt::black);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(x, y, totalWidth, rowHeight);

    for (int col = 0; col < columnCount; ++col) {
        QString header = table->horizontalHeaderItem(col)->text();
        painter.drawText(x + spacing/2, y + spacing/2, columnWidths[col] - spacing, rowHeight - spacing,
                         Qt::AlignLeft | Qt::AlignVCenter, header);
        x += columnWidths[col];
    }

    // Données
    y += rowHeight;
    for (int row = 0; row < rowCount; ++row) {
        x = margin;
        for (int col = 0; col < columnCount; ++col) {
            QString text;
            QTableWidgetItem *item = table->item(row, col);
            if (item)
                text = item->text();
            painter.setBrush(Qt::white);
            painter.drawRect(x, y, columnWidths[col], rowHeight);
            painter.drawText(x + spacing/2, y + spacing/2, columnWidths[col] - spacing, rowHeight - spacing,
                             Qt::AlignLeft | Qt::AlignVCenter, text);
            x += columnWidths[col];
        }
        y += rowHeight;
    }

    painter.end();

    QMessageBox::information(this, "Succès", "Table exportée en PDF avec succès !");
}

void MainWindow::on_searchbutton_2_clicked()
{
    QString id = ui->search->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID à rechercher.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, date_rdv, heure, duree, status, EMPLOYE, PATIENT FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche: " + query.lastError().text());
        return;
    }

    ui->tablerdv->clearContents();
    ui->tablerdv->setRowCount(0);

    if (query.next()) {
        ui->tablerdv->setRowCount(1);
        for (int col = 0; col < 7; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tablerdv->setItem(0, col, item);
        }
    } else {
        QMessageBox::information(this, "Recherche", "Aucun rendez-vous trouvé avec cet ID.");
    }
}

void MainWindow::remplirTableAvecQuery(QSqlQuery &query)
{
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec d'exécution : " + query.lastError().text());
        return;
    }

    ui->tablerdv->clearContents();
    ui->tablerdv->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tablerdv->insertRow(row);
        for (int col = 0; col < 7; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tablerdv->setItem(row, col, item);
        }
        row++;
    }
}


void MainWindow::on_sort_clicked()
{
    QMenu menu(this);
    QAction *action = menu.addAction("Tri croissant");
    QAction *actiond = menu.addAction("Tri décroissant");
    QAction *actionrdv = menu.addAction("Mes rendez-vous");

    // Tri croissant
    connect(action, &QAction::triggered, [this]() {
        rendervous::sort(ui->tablerdv, true);  // Tri croissant
    });

    connect(actiond, &QAction::triggered, [this]() {
        rendervous::sort(ui->tablerdv, false); // Tri décroissant
    });

    // Mes rendez-vous (employé connecté)
    connect(actionrdv, &QAction::triggered, [this]() {
        QSqlQuery query;
        query.prepare("SELECT id, date_rdv, heure, duree, status, EMPLOYE, PATIENT FROM rendezvous WHERE EMPLOYE = :id ORDER BY date_rdv, heure");
        query.bindValue(":id", CrudE::idN);
        remplirTableAvecQuery(query);
    });

    menu.exec(QCursor::pos());
}



void MainWindow::on_qr_clicked()
{
    // Vérifie s'il y a une ligne sélectionnée dans le QTableWidget
    int currentRow = ui->tablerdv->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un rendez-vous dans le tableau.");
        return;
    }

    // Récupère l'ID depuis la première colonne (supposée être l'ID)
    QString id = ui->tablerdv->item(currentRow, 0)->text();  // colonne 0 = ID
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire l'ID du rendez-vous.");
        return;
    }

    // Génère un chemin par défaut pour le fichier PNG
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                          QString("/appointment_%1.png").arg(id);

    // Demande où enregistrer le fichier
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le QR Code",
                                                    defaultPath,
                                                    "Images PNG (*.png)");

    if (!fileName.isEmpty()) {
        // Appelle la fonction pour générer le QR Code
        generateQRCode(id.toInt(), fileName);
        QMessageBox::information(this, "Succès",
                                 "QR code enregistré avec succès !\n\nFichier : " + fileName);

    }
}

void MainWindow::generateQRCode(int id, const QString &outputPath)
{
    // Étape 1 : récupérer les données du rendez-vous
    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur lors de la récupération des données pour le QR code";
        return;
    }

    QString date = query.value("date_rdv").toString();
    int heure = query.value("heure").toInt();
    QString status = query.value("status").toString();
    int id_patient = query.value("PATIENT").toInt();

    // Étape 2 : contenu du QR code
    QString content = QString(
                          "This QR code contains your appointment summary.\n\n"
                          "Appointment ID = %1\n"
                          "Date = %2\n"
                          "Time = %3:00\n"
                          "Patient ID = %4\n"
                          "Status = %5")
                          .arg(id)
                          .arg(date)
                          .arg(heure)
                          .arg(id_patient)
                          .arg(status);

    // Étape 3 : génération image PNG
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

    // Étape 4 : demander adresse e-mail
    QString email = QInputDialog::getText(this, "Envoyer par Email", "Adresse e-mail du patient :");
    if (email.isEmpty()) {
        QMessageBox::information(this, "Info", "Aucune adresse e-mail saisie. Le fichier PNG a été sauvegardé localement.");
        return;
    }

    // Étape 5 : envoyer l'e-mail
    envoyerEmailAvecQRCode(email, outputPath);
}

void MainWindow::on_statsButton_clicked() {
    if (statistiquesAffichees) {
        // Si les stats sont affichées, on revient au tableau
        retournerAuTableau();
        statistiquesAffichees = false;
    } else {
        // Sinon, on affiche les stats
        afficherStatistiques();
        statistiquesAffichees = true;
    }
}



void MainWindow::on_btnPrioriser_clicked()
{
    QSqlQueryModel *model = rendervous::prioriserPatients();

    if (!model) {
        QMessageBox::warning(this, "Erreur", "Impossible d'obtenir la liste des absents.");
        return;
    }

    // Préparer tablerdv
    ui->tablerdv->clear();
    ui->tablerdv->setRowCount(0);
    ui->tablerdv->setColumnCount(model->columnCount());

    // Définir les en-têtes de colonnes
    for (int col = 0; col < model->columnCount(); ++col) {
        ui->tablerdv->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
    }

    // Remplir les lignes avec les données
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tablerdv->insertRow(row);
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tablerdv->setItem(row, col, new QTableWidgetItem(data));
        }
    }

    QMessageBox::information(this, "Résultat", "Patients priorisés par nombre d'absences !");
    delete model; // nettoyage mémoire
}


void MainWindow::on_btnGenererAuto_clicked()
{
    rendervous::genererAutoRendezVousPourAbsents();

    rendervous r;
    r.afficher(ui->tablerdv); // mettre à jour le tableau après génération
}


void MainWindow::generatePDF(int id, const QString &pdfPath) {
    QSqlQuery query;
    query.prepare("SELECT * FROM rendezvous WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données du rendez-vous.");
        return;
    }

    QString date = query.value("date_rdv").toString();
    int heure = query.value("heure").toInt();
    QString status = query.value("status").toString();
    int id_patient = query.value("PATIENT").toInt();
    QString code_patient = query.value("code_patient").toString();

    QString content = QString(R"(
        <div style='font-family:Arial; padding: 20px;'>
        <h2 style='color:#2E86C1;'>Vaccination & Research Center</h2>
        <hr>
        <p><b>Appointment ID:</b> %1</p>
        <p><b>Date:</b> %2</p>
        <p><b>Time:</b> %3:00</p>
        <p><b>Patient ID:</b> %4</p>
        <p><b>Unique Code:</b> %5</p>
        <p><b>Status:</b> %6</p>
        <hr>
        <p style='font-size:10pt;'>Please present this document at the center reception.</p>
        </div>
    )").arg(id).arg(date).arg(heure).arg(id_patient).arg(code_patient).arg(status);

    QTextDocument document;
    document.setHtml(content);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfPath);
    printer.setPageSize(QPageSize::A4);
    printer.setFullPage(false);

    document.print(&printer);

    QMessageBox::information(this, "PDF généré", "Le fichier PDF a été créé avec succès à :\n" + pdfPath);
}

void MainWindow::envoyerEmailAvecQRCode(const QString &email, const QString &pathFichierPNG)
{
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
    QString id_patient = query.value("PATIENT").toString();
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
        "ahmedbrahmi530@gmail.com",   // ⚠️ adresse de connexion SMTP
        "fnhr islt fzsy fvlk"         // ⚠️ mot de passe d'application Gmail
        );
}

void MainWindow::afficherStatistiques()
{
    // Masquer le tableau principal
    ui->tablerdv->hide();

    // Créer ou réutiliser un layout pour afficher les graphiques
    QLayout *layout = ui->chartLayoutE_2->layout();
    if (!layout) {
        layout = new QHBoxLayout();
        ui->chartLayoutE_2->setLayout(layout);
    } else {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

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

    layout->addWidget(barView);
    layout->addWidget(pieChartView);
}


// ma yhemesh ahmed tsarref cbn


void MainWindow::showRendezVousPage()
{
    page = 5;

    if (!ui->loginGroupBox || !ui->pageV || !ui->pageE || !ui->pageR || !ui->pageP || !ui->page_3) {
        qDebug() << "Critical UI components missing!";
        return;
    }

    ui->loginGroupBox->hide();
    ui->pageE->hide();
    ui->pageR->hide();
    ui->pageP->hide();
    ui->pageV->hide();


    ui->page_3->show();
    isUserLoggedIn = true;

}

void MainWindow::retournerAuTableau()
{
    ui->tablerdv->show();

    // Supprimer les graphiques de statChartLayout s’il y en a
    QLayout *layout = ui->chartLayoutE_2->layout();

    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }
}

void MainWindow::on_displaybutton_2_clicked()
{
    rendervous r;
    r.afficher(ui->tablerdv); // ← Assure-toi que `tablerdv` est ton QTableWidget actuel
}


void MainWindow::on_rdvbtn_clicked(){
    showRendezVousPage();
}








//*************************fffffffffffaaaaaaaaaaaaaaareeeeeeeeeeeesssssssssssssssssssssssssssss
void MainWindow::on_tableWidget_cellChangedfares(int row, int column)
{
    if (isTableBeingUpdated) return;

    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
    if (!idItem) return;

    int id = idItem->text().toInt();

    bool shouldResetForm = false;
    if (isEditModeequipment && currentEditIdequipment == id) {
        shouldResetForm = true;
    }

    QTableWidgetItem *changedItem = ui->tableWidget->item(row, column);
    if (!changedItem) return;

    QString newValue = changedItem->text();

    // Validate different columns
    if (column == 0) {
        QMessageBox::warning(this, "Edit Error", "The ID field cannot be modified.");
        isTableBeingUpdated = true;
        changedItem->setText(QString::number(id));
        isTableBeingUpdated = false;
        return;
    }
    else if (column == 1) {  // Nom
        if (newValue.length() < 3) {
            QMessageBox::warning(this, "Invalid Input", "Name must contain at least 3 characters.");
            isTableBeingUpdated = true;
            // Reload original value from DB
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT NOMEQ FROM EQUIPEMENTS WHERE IDEQ = :ID");
                query.bindValue(":ID", id);

                if (query.exec() && query.next()) {
                    QString originalValue = query.value(0).toString();
                    changedItem->setText(originalValue);
                }
            }
            isTableBeingUpdated = false;
            return;
        }
    }
    else if (column == 2) {  // Etat
        QStringList validStates = {"Priority", "Damaged", "Functional"};
        if (!validStates.contains(newValue)) {
            QMessageBox::warning(this, "Invalid Input", "Status must be one of: Priority, Damaged, Functional");
            isTableBeingUpdated = true;
            // Reload original value from DB
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT ETATEQ FROM EQUIPEMENTS WHERE IDEQ = :ID");
                query.bindValue(":ID", id);

                if (query.exec() && query.next()) {
                    QString originalValue = query.value(0).toString();
                    changedItem->setText(originalValue);
                }
            }
            isTableBeingUpdated = false;
            return;
        }
    }
    else if (column == 3) {  // Quantity
        bool ok;
        int qty = newValue.toInt(&ok);
        if (!ok || qty <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Quantity must be a positive integer.");
            isTableBeingUpdated = true;
            // Reload original value from DB
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT NBEQ FROM EQUIPEMENTS WHERE IDEQ = :ID");
                query.bindValue(":ID", id);

                if (query.exec() && query.next()) {
                    int originalValue = query.value(0).toInt();
                    changedItem->setText(QString::number(originalValue));
                }
            }
            isTableBeingUpdated = false;
            return;
        }
    }
    else if (column == 4) {  // Type
        QStringList validTypes = {"Consomable", "Machine"};
        if (!validTypes.contains(newValue)) {
            QMessageBox::warning(this, "Invalid Input", "Type must be either Consomable or Machine.");
            isTableBeingUpdated = true;
            // Reload original value from DB
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT TYPEEQ FROM EQUIPEMENTS WHERE IDEQ = :ID");
                query.bindValue(":ID", id);

                if (query.exec() && query.next()) {
                    QString originalValue = query.value(0).toString();
                    changedItem->setText(originalValue);
                }
            }
            isTableBeingUpdated = false;
            return;
        }
    }
    else if (column == 5) {  // Maintenance Date
        QDate date = QDate::fromString(newValue, "yyyy-MM-dd");
        if (!date.isValid() || date < QDate::currentDate()) {
            QMessageBox::warning(this, "Invalid Input", "Maintenance date must be today or later and in yyyy-MM-dd format.");
            isTableBeingUpdated = true;
            // Reload original value from DB
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT TO_CHAR(TEMPMEQ, 'YYYY-MM-DD') FROM EQUIPEMENTS WHERE IDEQ = :ID");
                query.bindValue(":ID", id);

                if (query.exec() && query.next()) {
                    QString originalValue = query.value(0).toString();
                    changedItem->setText(originalValue);
                }
            }
            isTableBeingUpdated = false;
            return;
        }
    }
    else if (column == 7) {  // Supplier Phone
        QRegularExpression rx("^\\d{8}$");
        if (!rx.match(newValue).hasMatch()) {
            QMessageBox::warning(this, "Invalid Input", "Supplier phone number must be 8 digits.");
            isTableBeingUpdated = true;
            // Reload original value from DB
            connection c;
            QSqlDatabase db = c.get_database();
            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("SELECT FEQ FROM EQUIPEMENTS WHERE IDEQ = :ID");
                query.bindValue(":ID", id);

                if (query.exec() && query.next()) {
                    QString originalValue = query.value(0).toString();
                    changedItem->setText(originalValue);
                }
            }
            isTableBeingUpdated = false;
            return;
        }
    }

    // Update the database if validation passed
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        QString field;
        switch (column) {
        case 1: field = "NOMEQ"; break;
        case 2: field = "ETATEQ"; break;
        case 3: field = "NBEQ"; break;
        case 4: field = "TYPEEQ"; break;
        case 5: field = "TEMPMEQ"; break;
        case 6: field = "DESCEQ"; break;
        case 7: field = "FEQ"; break;
        default: return;
        }

        QString queryStr;
        if (column == 5) {  // Date field
            queryStr = "UPDATE EQUIPEMENTS SET " + field + " = TO_DATE(:value, 'YYYY-MM-DD') WHERE IDEQ = :ID";
        } else {
            queryStr = "UPDATE EQUIPEMENTS SET " + field + " = :value WHERE IDEQ = :ID";
        }

        query.prepare(queryStr);
        query.bindValue(":value", newValue);
        query.bindValue(":ID", id);

        if (!query.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to update record: " + query.lastError().text());
            isTableBeingUpdated = true;
            e.load_equipement_data(ui->tableWidget);
            isTableBeingUpdated = false;
        } else {
            qDebug() << "Record with ID" << id << "updated successfully. Column " << column << " changed to " << newValue;
        }

        if (shouldResetForm) {
            ui->ajouter->setText("Ajouter");
            isEditModeequipment = false;
            currentEditIdequipment = -1;
            ui->NOMEQ->clear();
            ui->TYPEEQ->setCurrentIndex(0);
            ui->NBEQ->clear();
            ui->TEMPMEQ->setDate(QDate::currentDate());
            ui->ETATEQ->setCurrentIndex(0);
            ui->DESCEQ->clear();
            ui->FEQ->clear();
        }
    }
}

void MainWindow::on_ajouter_clicked()
{
    qDebug() << "ajouter button clicked";

    // Get form values
    QString NOMEQ = ui->NOMEQ->text();
    QString ETATEQ = ui->ETATEQ->currentText();
    QString NBEQ_str = ui->NBEQ->text();
    QString TYPEEQ = ui->TYPEEQ->currentText();
    QDate TEMPMEQ = ui->TEMPMEQ->date();
    QString DESCEQ = ui->DESCEQ->toPlainText();
    QString FEQ = ui->FEQ->text();

    qDebug() << "Form values: Name=" << NOMEQ << ", Status=" << ETATEQ
             << ", Quantity=" << NBEQ_str << ", Type=" << TYPEEQ
             << ", Maintenance Date=" << TEMPMEQ.toString("yyyy-MM-dd")
             << ", Description length=" << DESCEQ.length()
             << ", Supplier Phone=" << FEQ;

    // Validate form input
    if (NOMEQ.length() < 3) {
        QMessageBox::warning(this, "Invalid Input", "Name must contain at least 3 characters.");
        return;
    }

    bool ok;
    int NBEQ = NBEQ_str.toInt(&ok);
    if (!ok || NBEQ <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Quantity must be a positive integer.");
        return;
    }

    if (TEMPMEQ < QDate::currentDate()) {
        QMessageBox::warning(this, "Invalid Input", "Maintenance date must be today or later.");
        return;
    }

    QRegularExpression rxPhone("^\\d{8}$");
    if (!rxPhone.match(FEQ).hasMatch()) {
        QMessageBox::warning(this, "Invalid Input", "Supplier phone number must be 8 digits.");
        return;
    }

    if (NOMEQ.isEmpty() || ETATEQ.isEmpty() || TYPEEQ.isEmpty() || DESCEQ.isEmpty() || FEQ.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "All fields must be filled out.");
        return;
    }

    qDebug() << "All validation passed, proceeding with " << (isEditModeequipment ? "update" : "add");

    if (isEditModeequipment) {
        // Update existing record
        qDebug() << "Updating record with ID:" << currentEditIdequipment;

        equipement update(NOMEQ, ETATEQ, NBEQ, TYPEEQ, TEMPMEQ, DESCEQ, FEQ);
        update.update_equipement(currentEditIdequipment);

        // Update table row
        isTableBeingUpdated = true;
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem* idItem = ui->tableWidget->item(row, 0);
            if (idItem && idItem->text().toInt() == currentEditIdequipment) {
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(NOMEQ));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(ETATEQ));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(NBEQ)));
                ui->tableWidget->setItem(row, 4, new QTableWidgetItem(TYPEEQ));
                ui->tableWidget->setItem(row, 5, new QTableWidgetItem(TEMPMEQ.toString("yyyy-MM-dd")));
                ui->tableWidget->setItem(row, 6, new QTableWidgetItem(DESCEQ));
                ui->tableWidget->setItem(row, 7, new QTableWidgetItem(FEQ));
                break;
            }
        }
        isTableBeingUpdated = false;

        ui->ajouter->setText("Ajouter");
        isEditModeequipment = false;
        currentEditIdequipment = -1;
    } else {
        // Add new record
        qDebug() << "Adding new record";
        isTableBeingUpdated = true;
        equipement add(NOMEQ, ETATEQ, NBEQ, TYPEEQ, TEMPMEQ, DESCEQ, FEQ);
        bool success = add.ajouter(ui->tableWidget);
        isTableBeingUpdated = false;

        if (!success) {
            qDebug() << "Failed to add record";
            QMessageBox::warning(this, "Error", "Failed to add record. Check logs for details.");
        } else {
            qDebug() << "Record added successfully";
        }
    }

    // Clear form
    ui->NOMEQ->clear();
    ui->ETATEQ->setCurrentIndex(0);
    ui->NBEQ->clear();
    ui->TYPEEQ->setCurrentIndex(0);
    ui->TEMPMEQ->setDate(QDate::currentDate());
    ui->DESCEQ->clear();
    ui->FEQ->clear();

    qDebug() << "Form cleared";
}

void MainWindow::on_deleteb_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
        return;
    }

    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Invalid row selected.");
        return;
    }

    int id = idItem->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion",
                                  "Are you sure you want to delete this equipment?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    e.delete_equipement(id, ui->tableWidget);
}

void MainWindow::on_tableWidget_cellDoubleClickedfares(int row, int column)
{
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
    if (!idItem) return;

    int id = idItem->text().toInt();
    QString name = ui->tableWidget->item(row, 1)->text();
    QString status = ui->tableWidget->item(row, 2)->text();
    QString quantity = ui->tableWidget->item(row, 3)->text();
    QString type = ui->tableWidget->item(row, 4)->text();
    QString maintenanceDate = ui->tableWidget->item(row, 5)->text();
    QString description = ui->tableWidget->item(row, 6)->text();
    QString supplierPhone = ui->tableWidget->item(row, 7)->text();

    // Fill the form with data
    ui->NOMEQ->setText(name);

    int statusIndex = ui->ETATEQ->findText(status);
    if (statusIndex >= 0) {
        ui->ETATEQ->setCurrentIndex(statusIndex);
    }

    ui->NBEQ->setText(quantity);

    int typeIndex = ui->TYPEEQ->findText(type);
    if (typeIndex >= 0) {
        ui->TYPEEQ->setCurrentIndex(typeIndex);
    }

    ui->TEMPMEQ->setDate(QDate::fromString(maintenanceDate, "yyyy-MM-dd"));
    ui->DESCEQ->setPlainText(description);
    ui->FEQ->setText(supplierPhone);

    // Change button text and set edit mode
    ui->ajouter->setText("Modifier");
    isEditModeequipment = true;
    currentEditIdequipment = id;
}

void MainWindow::on_cancelButton_clicked()
{
    // Reset form and edit mode
    ui->ajouter->setText("Ajouter");
    isEditModeequipment = false;
    currentEditIdequipment = -1;

    ui->NOMEQ->clear();
    ui->ETATEQ->setCurrentIndex(0);
    ui->NBEQ->clear();
    ui->TYPEEQ->setCurrentIndex(0);
    ui->TEMPMEQ->setDate(QDate::currentDate());
    ui->DESCEQ->clear();
    ui->FEQ->clear();
}

void MainWindow::on_rechb_clicked()
{
    isTableBeingUpdated = true;
    QString searchText = ui->rech->text().trimmed();

    if (searchText.isEmpty()) {
        e.load_equipement_data(ui->tableWidget);
        isTableBeingUpdated = false;
        return;
    }

    QStringList states = {"Priority", "Damaged", "Functional"};
    QStringList types = {"Consomable", "Machine"};

    // Check if search text matches an Etat
    if (states.contains(searchText, Qt::CaseInsensitive)) {
        e.load_equipement_byEtat(searchText, ui->tableWidget);
    }
    // Check if search text matches a Type
    else if (types.contains(searchText, Qt::CaseInsensitive)) {
        e.load_equipement_byType(searchText, ui->tableWidget);
    }
    // Otherwise search by name
    else {
        e.load_equipement_byNom(searchText, ui->tableWidget);
    }

    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No matching records found.");
    }

    isTableBeingUpdated = false;
}

void MainWindow::on_rech_textChanged(const QString &searchText)
{
    isTableBeingUpdated = true;
    QString trimmedText = searchText.trimmed();

    if (trimmedText.isEmpty()) {
        e.load_equipement_data(ui->tableWidget);
        isTableBeingUpdated = false;
        return;
    }

    QStringList states = {"Priority", "Damaged", "Functional"};
    QStringList types = {"Consomable", "Machine"};

    // Check if search text matches an Etat
    if (states.contains(trimmedText, Qt::CaseInsensitive)) {
        e.load_equipement_byEtat(trimmedText, ui->tableWidget);
    }
    // Check if search text matches a Type
    else if (types.contains(trimmedText, Qt::CaseInsensitive)) {
        e.load_equipement_byType(trimmedText, ui->tableWidget);
    }
    // Otherwise search by name
    else {
        e.load_equipement_byNom(trimmedText, ui->tableWidget);
    }

    isTableBeingUpdated = false;
}

void MainWindow::on_sortComboBox_changed(const QString &sortType)
{
    isTableBeingUpdated = true;
    e.load_sorted_equipement(ui->tableWidget, sortType);
    isTableBeingUpdated = false;
}

void MainWindow::on_pdfb_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to generate a PDF.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    // Title
    QFont titleFont("Arial", 40, QFont::Bold);
    painter.setFont(titleFont);
    QRect titleRect(0, 100, pageWidth, 170);
    painter.drawText(titleRect, Qt::AlignCenter, "Equipment Report");

    // Logo - Replace with your own logo path
    QPixmap logo(":/new/prefix1/image/Adobe Express - file (5)");
    if (!logo.isNull()) {
        int logoWidth = 650;
        int logoHeight = 550;
        int logoX = pageWidth - logoWidth - 50;
        int logoY = 50;
        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }

    // Content
    QFont headerFont("Arial", 24, QFont::Bold);
    QFont contentFont("Arial", 18);
    int yPosition = pageHeight / 5;
    int rowHeight = 300;
    int padding = 100;

    QStringList headers = {"Name", "Status", "Type", "Maintenance Date"};
    QStringList data;

    // Get data from the selected row - columns 1, 2, 4, 5 which correspond to Name, Status, Type, Maintenance Date
    for (int col : {1, 2, 4, 5}) {
        QTableWidgetItem *item = ui->tableWidget->item(row, col);
        QString cellText = item && !item->text().isEmpty() ? item->text() : "<Empty>";
        data.append(cellText);
    }

    // Display each header and its data
    for (int i = 0; i < headers.size(); ++i) {
        painter.setFont(headerFont);
        QRect headerRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(headerRect, Qt::AlignLeft, headers[i] + ":");

        yPosition += rowHeight / 2;

        painter.setFont(contentFont);
        QRect dataRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(dataRect, Qt::AlignLeft, data[i]);

        yPosition += rowHeight / 2;
        yPosition += 50;
    }

    // Description
    painter.setFont(headerFont);
    QRect descHeaderRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
    painter.drawText(descHeaderRect, Qt::AlignLeft, "Description:");

    yPosition += rowHeight / 2;

    QFont descFont("Arial", 16);
    painter.setFont(descFont);
    QTableWidgetItem *descItem = ui->tableWidget->item(row, 6); // Column 6 is description
    QString description = descItem && !descItem->text().isEmpty() ? descItem->text() : "No description available.";
    QRect descRect(padding, yPosition, pageWidth - 2 * padding, rowHeight);
    painter.drawText(descRect, Qt::AlignLeft | Qt::TextWordWrap, description);

    // Add today's date at the footer
    yPosition = pageHeight - 100;
    QFont footerFont("Arial", 12);
    painter.setFont(footerFont);
    QRect footerRect(0, yPosition, pageWidth, 50);
    painter.drawText(footerRect, Qt::AlignCenter, "Report generated on: " + QDate::currentDate().toString("yyyy-MM-dd"));

    painter.end();
}

void MainWindow::on_StatButton_clicked() {
    // Toggle between chart and table views
    if (ui->chartLayout->isVisible()) {
        // Switch back to table view
        ui->chartLayout->setVisible(false);
        ui->tableWidget->setVisible(true);
        return;
    }

    // Switch to chart view
    ui->chartLayout->setVisible(true);
    ui->tableWidget->setVisible(false);

    // Clear any existing content in the chart layout
    QLayout *layout = ui->chartLayout->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    // Create a fresh horizontal layout
    QHBoxLayout *mainLayout = new QHBoxLayout(ui->chartLayout);
    ui->chartLayout->setLayout(mainLayout);

    // Create vertical layout for the two bar charts
    QVBoxLayout *barLayout = new QVBoxLayout();

    // Get statistics data
    QVector<QPair<QString, int>> statsEtat = e.getStatistiquesByEtat();
    QVector<QPair<QString, int>> statsType = e.getStatistiquesByType();
    QVector<QPair<QString, int>> statsQuantity = e.getStatistiquesByQuantity();

    if (statsEtat.isEmpty() && statsType.isEmpty() && statsQuantity.isEmpty()) {
        QMessageBox::warning(this, "Statistics Error", "No data available for statistics.");
        ui->chartLayout->setVisible(false);
        ui->tableWidget->setVisible(true);
        return;
    }

    // Create container widgets for the charts
    QWidget *pieContainer = new QWidget();
    QVBoxLayout *pieLayout = new QVBoxLayout(pieContainer);
    pieContainer->setLayout(pieLayout);

    QWidget *barContainer = new QWidget();
    barLayout = new QVBoxLayout(barContainer);
    barContainer->setLayout(barLayout);

    //=============== PIE CHART FOR STATUS (ETAT) ===============//
    if (!statsEtat.isEmpty()) {
        QPieSeries *pieSeries = new QPieSeries();

        // Fill the series with data
        for (const auto &stat : statsEtat) {
            pieSeries->append(stat.first + " (" + QString::number(stat.second) + ")", stat.second);
        }

        // Make slices look better
        for (auto slice : pieSeries->slices()) {
            slice->setLabelVisible(true);
            slice->setPen(QPen(Qt::white, 1));
            slice->setLabelFont(QFont("Arial", 10));
        }

        // Create pie chart
        QChart *pieChart = new QChart();
        pieChart->addSeries(pieSeries);
        pieChart->setTitle("Equipment by Status");
        pieChart->legend()->setAlignment(Qt::AlignRight);
        pieChart->legend()->setFont(QFont("Arial", 9));
        pieChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
        pieChart->setBackgroundPen(Qt::NoPen);

        // Create chart view
        QChartView *pieChartView = new QChartView(pieChart);
        pieChartView->setRenderHint(QPainter::Antialiasing);
        pieChartView->setMinimumSize(400, 350);

        // Add to layout
        pieLayout->addWidget(pieChartView);
    }

    //=============== CHART FOR EQUIPMENT BY TYPE ===============//
    if (!statsType.isEmpty()) {
        // Create bar series for type counts
        QBarSeries *typeSeries = new QBarSeries();
        QBarSet *typeSet = new QBarSet("Equipment Count");

        QStringList typeCategories;

        for (const auto &stat : statsType) {
            *typeSet << stat.second;
            typeCategories << stat.first;
        }

        typeSeries->append(typeSet);

        // Create chart
        QChart *typeChart = new QChart();
        typeChart->addSeries(typeSeries);
        typeChart->setTitle("Equipment Count by Type");
        typeChart->setAnimationOptions(QChart::SeriesAnimations);

        // Add axes
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(typeCategories);
        typeChart->addAxis(axisX, Qt::AlignBottom);
        typeSeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, typeSet->at(typeSet->count()-1) * 1.2); // Add some headroom
        typeChart->addAxis(axisY, Qt::AlignLeft);
        typeSeries->attachAxis(axisY);

        typeChart->legend()->setVisible(false);
        typeChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
        typeChart->setBackgroundPen(Qt::NoPen);

        // Create chart view
        QChartView *typeChartView = new QChartView(typeChart);
        typeChartView->setRenderHint(QPainter::Antialiasing);
        typeChartView->setMinimumSize(400, 200);

        // Add to layout
        barLayout->addWidget(typeChartView);
    }

    //=============== CHART FOR TOTAL QUANTITY BY TYPE ===============//
    if (!statsQuantity.isEmpty()) {
        // Create bar series for quantity totals
        QBarSeries *quantitySeries = new QBarSeries();
        QBarSet *quantitySet = new QBarSet("Total Quantity");

        QStringList qtyCategories;

        for (const auto &stat : statsQuantity) {
            *quantitySet << stat.second;
            qtyCategories << stat.first;
        }

        quantitySeries->append(quantitySet);

        // Create chart
        QChart *qtyChart = new QChart();
        qtyChart->addSeries(quantitySeries);
        qtyChart->setTitle("Total Quantity by Type");
        qtyChart->setAnimationOptions(QChart::SeriesAnimations);

        // Add axes
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(qtyCategories);
        qtyChart->addAxis(axisX, Qt::AlignBottom);
        quantitySeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, quantitySet->at(quantitySet->count()-1) * 1.2); // Add some headroom
        qtyChart->addAxis(axisY, Qt::AlignLeft);
        quantitySeries->attachAxis(axisY);

        qtyChart->legend()->setVisible(false);
        qtyChart->setBackgroundBrush(QBrush(QColor(243, 249, 251)));
        qtyChart->setBackgroundPen(Qt::NoPen);

        // Create chart view
        QChartView *qtyChartView = new QChartView(qtyChart);
        qtyChartView->setRenderHint(QPainter::Antialiasing);
        qtyChartView->setMinimumSize(400, 200);

        // Add to layout
        barLayout->addWidget(qtyChartView);
    }

    // Add the layouts to the main layout
    mainLayout->addWidget(barContainer);
    mainLayout->addWidget(pieContainer);
}

void MainWindow::on_checkb_clicked()
{
    PredictiveMaintenanceDialog dialog(this);
    dialog.exec();
}








