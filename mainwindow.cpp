#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QLayout>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "Crud.h"
#include <QString>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sortComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBox_changed);
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_rech_textChanged);
    connect(ui->statComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_statComboBox_changed);
    connection c;
    if (!c.set_connection()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database!");
        return;
    }
    if (ui->tableWidget->columnCount() == 0) {
        ui->tableWidget->setColumnCount(6);
        QStringList headers;
        headers << "ID" << "Title" << "Classification" << "Description" << "Start Date" << "End Date";
        ui->tableWidget->setHorizontalHeaderLabels(headers);
    }
    Crud::load_recherche_data(ui->tableWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    QString IDR = ui->ID->text();
    QString TITRER = ui->titre->text();
    QString CLASSR = ui->Classer->currentText();
    QString DESCR = ui->desc->toPlainText();
    QString DATEDR = ui->dateD->date().toString("yyyy-MM-dd");
    QString DATEFR = ui->dateF->date().toString("yyyy-MM-dd");
    bool idConversionSuccess;
    int idint = IDR.toInt(&idConversionSuccess);
    if (!idConversionSuccess) {
        QMessageBox::warning(this, "Invalid Input", "ID must be a valid integer.");
        return;
    }
    bool idExists = false;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* idItem = ui->tableWidget->item(row, 0);
        if (idItem && idItem->text().toInt() == idint) {
            idExists = true;
            break;
        }
    }
    if (idExists && !isEditMode) {
        QMessageBox::warning(this, "Invalid Input", "ID must be unique.");
        return;
    }
    if (TITRER.length() < 3) {
        QMessageBox::warning(this, "Invalid Input", "Title must contain at least 3 characters.");
        return;
    }
    QDate currentDate = QDate::currentDate();
    if (ui->dateD->date() < currentDate) {
        QMessageBox::warning(this, "Invalid Input", "Start date must be today's date or later.");
        return;
    }
    if (ui->dateF->date() < ui->dateD->date()) {
        QMessageBox::warning(this, "Invalid Input", "End date must be the same as or later than the start date.");
        return;
    }
    if (IDR.isEmpty() || TITRER.isEmpty() || CLASSR.isEmpty() || DESCR.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "All fields except DateF must be filled out.");
        return;
    }
    if (isEditMode) {
        Crud update(idint, TITRER, CLASSR, DESCR, DATEDR, DATEFR);
        update.update_recherche(idint);

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QTableWidgetItem* idItem = ui->tableWidget->item(row, 0);
            if (idItem && idItem->text().toInt() == idint) {
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(TITRER));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(CLASSR));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(DESCR));
                ui->tableWidget->setItem(row, 4, new QTableWidgetItem(DATEDR));
                ui->tableWidget->setItem(row, 5, new QTableWidgetItem(DATEFR));
                break;
            }
        }

        ui->ajouter->setText("Add");
        ui->ID->setReadOnly(false);
        isEditMode = false;
        QMessageBox::information(this, "Success", "Recherche updated successfully!");
    } else {
        Crud add(idint, TITRER, CLASSR, DESCR, DATEDR, DATEFR);
        add.add_recherche(ui->tableWidget);
        QMessageBox::information(this, "Success", "Recherche added successfully!");
    }
    ui->ID->clear();
    ui->titre->clear();
    ui->Classer->setCurrentIndex(0);
    ui->desc->clear();
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());
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
    int id2int = idItem->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion",
                                  "Are you sure you want to delete this entry?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }
    Crud drop;
    drop.delete_recherche(id2int, ui->tableWidget);

    QMessageBox::information(this, "Success", "Recherche deleted successfully!");
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    int id = ui->tableWidget->item(row, 0)->text().toInt();
    QString title = ui->tableWidget->item(row, 1)->text();
    QString classification = ui->tableWidget->item(row, 2)->text();
    QString description = ui->tableWidget->item(row, 3)->text();
    QString startDate = ui->tableWidget->item(row, 4)->text();
    QString endDate = ui->tableWidget->item(row, 5)->text();

    ui->ID->setText(QString::number(id));
    ui->ID->setReadOnly(true);
    ui->titre->setText(title);

    int classIndex = ui->Classer->findText(classification);
    if (classIndex >= 0) {
        ui->Classer->setCurrentIndex(classIndex);
    }

    ui->desc->setPlainText(description);
    ui->dateD->setDate(QDate::fromString(startDate, "yyyy-MM-dd"));
    ui->dateF->setDate(QDate::fromString(endDate, "yyyy-MM-dd"));


    ui->ajouter->setText("Update");
    isEditMode = true;
    currentEditId = id;
}

void MainWindow::on_cancelButton_clicked()
{
    ui->ajouter->setText("Add");
    ui->ID->setReadOnly(false);
    isEditMode = false;
    ui->ID->clear();
    ui->titre->clear();
    ui->Classer->setCurrentIndex(0);
    ui->desc->clear();
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());
}

void MainWindow::on_rechb_clicked()
{
    QString searchText = ui->rech->text().trimmed();
    Crud search;

    if (searchText.isEmpty()) {
        search.load_recherche_data(ui->tableWidget);
        return;
    }

    if (ui->Classer->findText(searchText) != -1) {
        search.load_recherche_byClass(searchText, ui->tableWidget);
    } else {
        search.load_recherche_byTitle(searchText, ui->tableWidget);
    }

    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No matching records found.");
    }
}

void MainWindow::on_rech_textChanged(const QString &searchText)
{
    Crud search;
    QString trimmedText = searchText.trimmed();
    if (trimmedText.isEmpty()) {
        search.load_recherche_data(ui->tableWidget);
        return;
    }
    if (ui->Classer->findText(trimmedText) != -1) {
        search.load_recherche_byClass(trimmedText, ui->tableWidget);
    } else {
        search.load_recherche_byTitle(trimmedText, ui->tableWidget);
    }
}

void MainWindow::on_sortComboBox_changed(const QString &sortType) {
    Crud tree;
    tree.load_sorted_recherche(ui->tableWidget, sortType);
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
        QTableWidgetItem *item = ui->tableWidget->item(row, col);
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
    QTableWidgetItem *descItem = ui->tableWidget->item(row, 3);
    QString description = descItem && !descItem->text().isEmpty() ? descItem->text() : "No description available.";
    QRect descRect(padding, yPosition, pageWidth - 2 * padding, pageHeight - 300);
    painter.drawText(descRect, Qt::AlignLeft | Qt::TextWordWrap, description);
    painter.end();
    QMessageBox::information(this, "Success", "PDF generated successfully!");
}

void MainWindow::on_statComboBox_changed(const QString &selectedOption) {
    if (ui->chartLayout->layout()) {
        QLayoutItem *item;
        while ((item = ui->chartLayout->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }
    QChart *chart = new QChart();
    chart->setTitle("Research Classification Statistics");
    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    connection c;
    QSqlDatabase db = c.get_database();
    if (db.open()) {
        QSqlQuery query(db);
        QString timeCondition;
        if (selectedOption == "Weekly") {
            timeCondition = "DATEDR >= SYSDATE - INTERVAL '7' DAY";
        } else if (selectedOption == "Monthly") {
            timeCondition = "DATEDR >= SYSDATE - INTERVAL '30' DAY";
        } else if (selectedOption == "Last 24 Hours") {
            timeCondition = "DATEDR >= SYSDATE - INTERVAL '1' DAY";
        } else {
            timeCondition = "";
        }
        QString queryString = "SELECT CLASSR, COUNT(*) FROM RECHERCHE";
        if (!timeCondition.isEmpty()) {
            queryString += " WHERE " + timeCondition;
        }
        queryString += " GROUP BY CLASSR";

        qDebug() << "Executing query:" << queryString;
        query.prepare(queryString);

        if (query.exec()) {
            QBarSet *set = new QBarSet("Research Count");
            QStringList categories;

            while (query.next()) {
                QString classr = query.value(0).toString();
                int count = query.value(1).toInt();
                qDebug() << "Class:" << classr << ", Count:" << count;
                *set << count;
                categories.prepend(classr);
            }

            if (categories.isEmpty()) {
                qDebug() << "No data available for the selected time range.";
                QMessageBox::information(this, "No Data", "No research data available for the selected time range.");
                return;
            }
            series->append(set);
            QCategoryAxis *axisY = new QCategoryAxis();
            int position = 0;
            for (const QString &category : categories) {
                axisY->append(category, position++);
            }

            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setAxisY(axisY, series);
        } else {
            qDebug() << "Query failed:" << query.lastError().text();
            QMessageBox::critical(this, "Query Error", "Failed to execute query: " + query.lastError().text());
            return;
        }
    }
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setMargins(QMargins(5, 5, 5, 5));
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(1211, 181);
    chartView->chart()->legend()->setFont(QFont("Arial", 7));
    if (!ui->chartLayout->layout()) {
        ui->chartLayout->setLayout(new QVBoxLayout());
    }
    ui->chartLayout->layout()->addWidget(chartView);
}

