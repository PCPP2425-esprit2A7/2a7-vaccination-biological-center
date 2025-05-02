#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "crud.h"
#include <QString>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QIcon>
#include "mainwindow.h"
#include "AnimatedBarItem.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QRect>
#include <QDate>
#include <QPageSize>
#include "smtp_mailer_secure.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rfidUID->setReadOnly(true);
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_rech_textChanged);
    connect(ui->sortComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBox_changed);
    
    
    connection c;
    if (!c.set_connection()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database!");
        return;
    }
    
    // Set up table with 9 columns for utilisateur data
    if (ui->tableWidget->columnCount() == 0) {
        ui->tableWidget->setColumnCount(9);
        QStringList headers;
        headers << "IDE" << "Name" << "Email" << "Phone"
                << "Address" << "Password" << "Role"
                << "Salary";
        ui->tableWidget->setHorizontalHeaderLabels(headers);
    }

    // Initialiser l'interface avec la page de login
    showLoginPage();
    updateRoleStatistics();
    SerialHandler *serialHandler = new SerialHandler();
    connect(serialHandler, &SerialHandler::rfidReceived, this, &MainWindow::handleRFID);


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
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

    if (isEditMode) {
        // Update existing utilisateur
        Crud update(ide, nome, email, tele, adresse, mdp, role, salaire, RFID_UID); // Use RFID_UID
        update.update_utilisateur(ide);

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            if (ui->tableWidget->item(row, 0)->text().toInt() == ide) {
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nome));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(email));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(tele)));
                ui->tableWidget->setItem(row, 4, new QTableWidgetItem(adresse));
                ui->tableWidget->setItem(row, 5, new QTableWidgetItem(mdp));
                ui->tableWidget->setItem(row, 6, new QTableWidgetItem(role));
                ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(salaire)));
                ui->tableWidget->setItem(row, 8, new QTableWidgetItem(RFID_UID)); // Update RFID_UID
                break;
            }
        }
        QMessageBox::information(this, "Success", "Utilisateur updated successfully!");
        isEditMode = false;
        ui->ajouter->setText("Add");
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
        Crud add(ide, nome, email, tele, adresse, mdp, role, salaire, RFID_UID); // Use RFID_UID
        add.add_utilisateur(ui->tableWidget);
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






void MainWindow::on_deleteb_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
        return;
    }

    // Get the IDE and RFID_UID of the selected row
    int ide = ui->tableWidget->item(row, 0)->text().toInt();
    QString RFID_UID = ui->tableWidget->item(row, 8)->text();  // Assuming RFID_UID is in the 8th column

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Deletion",
        QString("Are you sure you want to delete the utilisateur with ID %1 and RFID UID %2?").arg(ide).arg(RFID_UID),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Call the constructor with appropriate arguments for deletion
        // We pass empty values for fields not required for deletion
        Crud deleteOp(ide, "", "", 0, "", "", "", 0, RFID_UID); // Passing RFID_UID as well
        deleteOp.delete_utilisateur(ide, ui->tableWidget); // Pass the IDE to delete the user
        QMessageBox::information(this, "Success", "Utilisateur deleted successfully!");
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    // Get data from selected row
    int ide = ui->tableWidget->item(row, 0)->text().toInt();
    QString nome = ui->tableWidget->item(row, 1)->text();
    QString email = ui->tableWidget->item(row, 2)->text();
    int tele = ui->tableWidget->item(row, 3)->text().toInt();
    QString adresse = ui->tableWidget->item(row, 4)->text();
    QString mdp = ui->tableWidget->item(row, 5)->text();
    QString role = ui->tableWidget->item(row, 6)->text();
    int salaire = ui->tableWidget->item(row, 7)->text().toInt();

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
    isEditMode = true;
    ui->ajouter->setText("Update");
    currentEditId = ide;
}

void MainWindow::on_cancelButton_clicked()
{
    ui->ajouter->setText("Add");
    ui->id->setReadOnly(false);
    isEditMode = false;
    currentEditId = -1;

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

void MainWindow::on_rechb_clicked()
{
    QString searchText = ui->rech->text().trimmed();
    Crud search;
    if (searchText.isEmpty()) {
        search.load_utilisateur_data(ui->tableWidget); // Load all data if search field is empty
        return;
    }
    if (ui->nom->text().contains(searchText, Qt::CaseInsensitive)) {
        search.load_utilisateur_byName(searchText, ui->tableWidget);
    } else {
        search.load_utilisateur_byRole(searchText, ui->tableWidget);
    }
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No matching records found.");
    }
}

void MainWindow::on_rech_textChanged(const QString &searchText)
{
    Crud search;

    // Trim the search text
    QString trimmedText = searchText.trimmed();
    if (trimmedText.isEmpty()) {
        search.load_utilisateur_data(ui->tableWidget);
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
        search.load_utilisateur_byRole(trimmedText, ui->tableWidget);
    } else {
        search.load_utilisateur_byName(trimmedText, ui->tableWidget);
    }
}

void MainWindow::on_sortComboBox_changed(const QString &sortType) {
    Crud tree;
    tree.load_sorted_utilisateur(ui->tableWidget, sortType);
}

void MainWindow::showLoginPage() {
    ui->loginGroupBox->show();
    ui->groupBox_2->hide();
    isLoggedIn = false;
}

void MainWindow::showMainPage() {
    ui->loginGroupBox->hide();
    ui->groupBox_2->show();
    isLoggedIn = true;
}

void MainWindow::on_loginButton_clicked() {
    QString email = ui->loginEmail->text();
    QString password = ui->loginPassword->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    if (Crud::login(email, password)) {
        showMainPage();
        // Charger les données des employés
        Crud::load_utilisateur_data(ui->tableWidget);
    } else {
        // Notification système Windows
        if (QSystemTrayIcon::isSystemTrayAvailable()) {
            QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
            trayIcon->setIcon(QIcon::fromTheme("dialog-error")); // Utilise une icône système ou personnalise ici
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

void MainWindow::on_pushButton_8_clicked() {
    // Déconnexion
    ui->loginEmail->clear();
    ui->loginPassword->clear();
    showLoginPage();
}




void MainWindow::updateRoleStatistics() {
    // Clear existing content in chart layout
    if (ui->chartLayout->layout()) {
        QLayout* oldLayout = ui->chartLayout->layout();
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
    QVBoxLayout* vLayout = new QVBoxLayout(ui->chartLayout);
    ui->chartLayout->setLayout(vLayout);

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
void MainWindow::on_pdfb_clicked() {
    int row = ui->tableWidget->currentRow();
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
        QTableWidgetItem *item = ui->tableWidget->item(row, col);
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
    QTableWidgetItem *addressItem = ui->tableWidget->item(row, 4);
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
        if (!isLoggedIn) {
            showMainPage();
            Crud::load_utilisateur_data(ui->tableWidget);

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
        serial->write(message.toUtf8());  // Send the employee info to the Arduino
        serial->write("\n");  // Add newline character
    }
}
