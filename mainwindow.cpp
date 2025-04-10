#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "Crud.h"
#include <QString>
#include <QMessageBox>
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
#include <QDateEdit>
#include <QScopedPointer>
#include "SimulationDialog.h"



ClassificationDelegate::ClassificationDelegate(QObject *parent) : QStyledItemDelegate(parent) {}
AIAssistantWindow* MainWindow::aiAssistantInstance = nullptr;
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sortComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_sortComboBox_changed);
    connect(ui->rech, &QLineEdit::textChanged, this, &MainWindow::on_rech_textChanged);
    connect(ui->StatComboBox, &QComboBox::currentTextChanged, this, &MainWindow::on_StatComboBox_changed);
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
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                     QAbstractItemView::EditKeyPressed);
    classDelegate = new ClassificationDelegate(this);
    dateDelegate = new DateDelegate(this);

    ui->tableWidget->setItemDelegateForColumn(2, classDelegate);
    ui->tableWidget->setItemDelegateForColumn(4, dateDelegate);
    ui->tableWidget->setItemDelegateForColumn(5, dateDelegate);
    isTableBeingUpdated = true;
    Crud::load_recherche_data(ui->tableWidget);
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
        if (idItem) {
            idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        }
    }

    isTableBeingUpdated = false;
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &MainWindow::on_tableWidget_cellChanged);
}

MainWindow::~MainWindow()
{
    if (aiAssistantInstance) {
        delete aiAssistantInstance;
        aiAssistantInstance = nullptr;
    }
    delete ui;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if (isTableBeingUpdated) return;
    QTableWidgetItem *idItem = ui->tableWidget->item(row, 0);
    if (!idItem) return;

    int id = idItem->text().toInt();

    bool shouldResetForm = false;
    if (isEditMode && currentEditId == id) {
        shouldResetForm = true;
    }
    QTableWidgetItem *changedItem = ui->tableWidget->item(row, column);
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
            QTableWidgetItem *endDateItem = ui->tableWidget->item(row, 5);
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
            QTableWidgetItem *startDateItem = ui->tableWidget->item(row, 4);
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
    connection c;
    QSqlDatabase db = c.get_database();
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
            Crud::load_recherche_data(ui->tableWidget);
            isTableBeingUpdated = false;
        } else {
            qDebug() << "Record with ID" << id << "updated successfully. Column " << column << " changed to " << newValue;
        }
        if (shouldResetForm) {
            ui->ajouter->setText("Add");
            isEditMode = false;
            currentEditId = -1;
            ui->titre->clear();
            ui->Classer->setCurrentIndex(0);
            ui->desc->clear();
            ui->dateD->setDate(QDate::currentDate());
            ui->dateF->setDate(QDate::currentDate());
        }
    }
}

void MainWindow::on_ajouter_clicked()
{
    qDebug() << "ajouter button clicked";

    QString TITRER = ui->titre->text();
    QString CLASSR = ui->Classer->currentText();
    QString DESCR = ui->desc->toPlainText();
    QString DATEDR = ui->dateD->date().toString("yyyy-MM-dd");
    QString DATEFR = ui->dateF->date().toString("yyyy-MM-dd");

    qDebug() << "Form values: Title=" << TITRER << ", Class=" << CLASSR
             << ", Desc length=" << DESCR.length()
             << ", DateD=" << DATEDR << ", DateF=" << DATEFR;

    if (TITRER.length() < 3) {
        QMessageBox::warning(this, "Invalid Input", "Title must contain at least 3 characters.");
        return;
    }
    if (!isEditMode) {
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

    qDebug() << "All validation passed, proceeding with " << (isEditMode ? "update" : "add");

    if (isEditMode) {
        int idint = currentEditId;
        qDebug() << "Updating record with ID:" << idint;

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
        isEditMode = false;
    } else {
        qDebug() << "Adding new record";
        isTableBeingUpdated = true;
        Crud add(0, TITRER, CLASSR, DESCR, DATEDR, DATEFR);
        bool success = add.add_recherche(ui->tableWidget);
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
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    int id = ui->tableWidget->item(row, 0)->text().toInt();
    QString title = ui->tableWidget->item(row, 1)->text();
    QString classification = ui->tableWidget->item(row, 2)->text();
    QString description = ui->tableWidget->item(row, 3)->text();
    QString startDate = ui->tableWidget->item(row, 4)->text();
    QString endDate = ui->tableWidget->item(row, 5)->text();
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
    isEditMode = false;
    ui->titre->clear();
    ui->Classer->setCurrentIndex(0);
    ui->desc->clear();
    ui->dateD->setDate(QDate::currentDate());
    ui->dateF->setDate(QDate::currentDate());
}

void MainWindow::on_rechb_clicked()
{
    isTableBeingUpdated = true;
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
    isTableBeingUpdated = false;
}

void MainWindow::on_rech_textChanged(const QString &searchText)
{
    isTableBeingUpdated = true;
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
    isTableBeingUpdated = false;
}

void MainWindow::on_sortComboBox_changed(const QString &sortType) {
    isTableBeingUpdated = true;
    Crud tree;
    tree.load_sorted_recherche(ui->tableWidget, sortType);
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
}

void MainWindow::on_StatComboBox_changed(const QString &selectedOption) {
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

void MainWindow::on_openAIAssistantButton_clicked()
{
    if (!aiAssistantInstance) {
        aiAssistantInstance = new AIAssistantWindow(this);
    }
    aiAssistantInstance->setResearchContext(
        ui->titre->text(),
        ui->Classer->currentText(),
        ui->desc->toPlainText(),
        ui->dateD->date().toString("yyyy-MM-dd"),
        ui->dateF->date().toString("yyyy-MM-dd")
        );
    if (aiAssistantInstance->exec() == QDialog::Accepted) {
        QString newDescription = aiAssistantInstance->getGeneratedDescription();
        if (!newDescription.isEmpty()) {
            ui->desc->setPlainText(newDescription);
        }
    }
}

void MainWindow::on_simulationButton_clicked()
{
    SimulationDialog simDialog(this);
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
