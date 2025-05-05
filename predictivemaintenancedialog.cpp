#include "PredictiveMaintenanceDialog.h"
#include "ui_PredictiveMaintenanceDialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "connection.h"

PredictiveMaintenanceDialog::PredictiveMaintenanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PredictiveMaintenanceDialog)
{
    ui->setupUi(this);
    initializeUI();

    // Run initial predictions
    predictionModel.predictFailures();

    // Update UI with current data
    updateEquipmentStats();
    loadEquipmentCombo();
    refreshPredictionsTable(30); // Default to 30 days
}

PredictiveMaintenanceDialog::~PredictiveMaintenanceDialog()
{
    delete ui;
}

void PredictiveMaintenanceDialog::initializeUI()
{
    // Set window properties
    setWindowTitle("Equipment Predictive Maintenance");
    setModal(true);

    // Set validators
    QRegularExpression rxCost("^\\d*\\.?\\d+$");
    QValidator *costValidator = new QRegularExpressionValidator(rxCost, this);
    ui->maintenanceCostEdit->setValidator(costValidator);

    // Set up the threshold combo box values
    ui->thresholdComboBox->clear();
    ui->thresholdComboBox->addItem("7 days", 7);
    ui->thresholdComboBox->addItem("14 days", 14);
    ui->thresholdComboBox->addItem("30 days", 30);
    ui->thresholdComboBox->addItem("60 days", 60);
    ui->thresholdComboBox->addItem("90 days", 90);
    ui->thresholdComboBox->setCurrentIndex(2); // Default to 30 days

    // Connect signals and slots
    connect(ui->predictionsTable, &QTableWidget::itemSelectionChanged, this, &PredictiveMaintenanceDialog::on_predictionsTable_itemSelectionChanged);

    // Initially show the Predictions tab
    ui->mainTabWidget->setCurrentIndex(0);

    // Clear maintenance form
    clearMaintenanceForm();
}

void PredictiveMaintenanceDialog::updateEquipmentStats()
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        int total = 0, functional = 0, damaged = 0, atRisk = 0;

        // Get total equipment count
        query.prepare("SELECT COUNT(*) FROM EQUIPEMENTS");
        if (query.exec() && query.next()) {
            total = query.value(0).toInt();
        }

        // Get functional equipment count
        query.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE ETATEQ = 'Functional'");
        if (query.exec() && query.next()) {
            functional = query.value(0).toInt();
        }

        // Get damaged equipment count
        query.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE ETATEQ = 'Damaged'");
        if (query.exec() && query.next()) {
            damaged = query.value(0).toInt();
        }

        // Get at-risk equipment count (predicted to fail within 30 days)
        QDate thresholdDate = QDate::currentDate().addDays(30);
        query.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE ETATEQ = 'Functional' AND "
                      "TEMPMEQ IS NOT NULL AND "
                      "TEMPMEQ <= TO_DATE(:thresholdDate, 'YYYY-MM-DD')");
        query.bindValue(":thresholdDate", thresholdDate.toString("yyyy-MM-dd"));
        if (query.exec() && query.next()) {
            atRisk = query.value(0).toInt();
        }

        // Update the UI labels
        ui->totalLabel->setText("Total: " + QString::number(total));
        ui->functionalLabel->setText("Functional: " + QString::number(functional));
        ui->damagedLabel->setText("Damaged: " + QString::number(damaged));
        ui->atRiskLabel->setText("At Risk (30d): " + QString::number(atRisk));
    }
}

void PredictiveMaintenanceDialog::loadEquipmentCombo()
{
    // Save current selection if any
    QString currentSelection = ui->equipmentFilterCombo->currentText();

    // Clear and add default "All Equipment" option
    ui->equipmentFilterCombo->clear();
    ui->equipmentFilterCombo->addItem("All Equipment", -1);

    // Load equipment from database
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDEQ, NOMEQ FROM EQUIPEMENTS ORDER BY NOMEQ");

        if (query.exec()) {
            while (query.next()) {
                int id = query.value(0).toInt();
                QString name = query.value(1).toString();
                ui->equipmentFilterCombo->addItem(name, id);
            }
        }
    }

    // Restore previous selection if it exists
    int index = ui->equipmentFilterCombo->findText(currentSelection);
    if (index >= 0) {
        ui->equipmentFilterCombo->setCurrentIndex(index);
    }
}

void PredictiveMaintenanceDialog::refreshPredictionsTable(int daysThreshold)
{
    // Clear the table
    ui->predictionsTable->setRowCount(0);

    // Run predictions to ensure data is up to date
    predictionModel.predictFailures();

    // Get at-risk equipment
    QVector<QPair<int, QDate>> atRiskEquipment = predictionModel.getEquipmentAtRisk(daysThreshold);

    if (atRiskEquipment.isEmpty()) {
        QMessageBox::information(this, "Predictions", "No equipment predicted to fail within " +
                                                          QString::number(daysThreshold) + " days.");
        return;
    }

    // Fill predictions table
    ui->predictionsTable->setRowCount(atRiskEquipment.size());

    for (int row = 0; row < atRiskEquipment.size(); ++row) {
        int equipmentId = atRiskEquipment[row].first;
        QDate failureDate = atRiskEquipment[row].second;

        // Get equipment details
        connection c;
        QSqlDatabase db = c.get_database();

        if (db.open()) {
            QSqlQuery query(db);
            query.prepare("SELECT NOMEQ, TYPEEQ, ETATEQ FROM EQUIPEMENTS WHERE IDEQ = :id");
            query.bindValue(":id", equipmentId);

            if (query.exec() && query.next()) {
                QString name = query.value(0).toString();
                QString type = query.value(1).toString();
                QString status = query.value(2).toString();

                // Calculate days remaining
                int daysRemaining = QDate::currentDate().daysTo(failureDate);

                // Determine risk level
                QString riskLevel;
                QColor rowColor;

                if (daysRemaining <= 7) {
                    riskLevel = "High";
                    rowColor = QColor(255, 200, 200); // Red for high risk
                } else if (daysRemaining <= 14) {
                    riskLevel = "Medium";
                    rowColor = QColor(255, 255, 200); // Yellow for medium risk
                } else {
                    riskLevel = "Low";
                    rowColor = QColor(200, 255, 200); // Green for low risk
                }

                // Set table items
                QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(equipmentId));
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *nameItem = new QTableWidgetItem(name);
                nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *typeItem = new QTableWidgetItem(type);
                typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *statusItem = new QTableWidgetItem(status);
                statusItem->setFlags(statusItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *failureDateItem = new QTableWidgetItem(failureDate.toString("yyyy-MM-dd"));
                failureDateItem->setFlags(failureDateItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *daysRemainingItem = new QTableWidgetItem(QString::number(daysRemaining));
                daysRemainingItem->setFlags(daysRemainingItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *riskLevelItem = new QTableWidgetItem(riskLevel);
                riskLevelItem->setFlags(riskLevelItem->flags() & ~Qt::ItemIsEditable);

                ui->predictionsTable->setItem(row, 0, idItem);
                ui->predictionsTable->setItem(row, 1, nameItem);
                ui->predictionsTable->setItem(row, 2, typeItem);
                ui->predictionsTable->setItem(row, 3, statusItem);
                ui->predictionsTable->setItem(row, 4, failureDateItem);
                ui->predictionsTable->setItem(row, 5, daysRemainingItem);
                ui->predictionsTable->setItem(row, 6, riskLevelItem);

                // Apply color to the row
                for (int col = 0; col < ui->predictionsTable->columnCount(); ++col) {
                    ui->predictionsTable->item(row, col)->setBackground(rowColor);
                }
            }
        }
    }

    ui->predictionsTable->resizeColumnsToContents();
}

void PredictiveMaintenanceDialog::loadMaintenanceHistory(int equipmentId)
{
    // Clear the table
    ui->historyTable->setRowCount(0);

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        QString queryStr = "SELECT h.ID_HISTORY, e.NOMEQ, TO_CHAR(h.CHANGE_DATE, 'YYYY-MM-DD') as CHANGE_DATE, "
                           "h.OLD_STATUS, h.NEW_STATUS, h.MAINTENANCE_COST, h.REPAIR_DETAILS "
                           "FROM EQUIPMENT_HISTORY h "
                           "JOIN EQUIPEMENTS e ON h.IDEQ = e.IDEQ ";

        if (equipmentId > 0) {
            queryStr += "WHERE h.IDEQ = :equipmentId ";
        }

        queryStr += "ORDER BY h.CHANGE_DATE DESC, h.ID_HISTORY DESC";

        query.prepare(queryStr);

        if (equipmentId > 0) {
            query.bindValue(":equipmentId", equipmentId);
        }

        if (query.exec()) {
            int row = 0;
            while (query.next()) {
                ui->historyTable->insertRow(row);

                int historyId = query.value(0).toInt();
                QString equipName = query.value(1).toString();
                QString changeDate = query.value(2).toString();
                QString oldStatus = query.value(3).toString();
                QString newStatus = query.value(4).toString();
                double maintCost = query.value(5).toDouble();
                QString details = query.value(6).toString();

                QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(historyId));
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *nameItem = new QTableWidgetItem(equipName);
                nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *dateItem = new QTableWidgetItem(changeDate);
                dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *oldStatusItem = new QTableWidgetItem(oldStatus);
                oldStatusItem->setFlags(oldStatusItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *newStatusItem = new QTableWidgetItem(newStatus);
                newStatusItem->setFlags(newStatusItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *costItem = new QTableWidgetItem(maintCost > 0 ? QString::number(maintCost, 'f', 2) : "");
                costItem->setFlags(costItem->flags() & ~Qt::ItemIsEditable);

                QTableWidgetItem *detailsItem = new QTableWidgetItem(details);
                detailsItem->setFlags(detailsItem->flags() & ~Qt::ItemIsEditable);

                ui->historyTable->setItem(row, 0, idItem);
                ui->historyTable->setItem(row, 1, nameItem);
                ui->historyTable->setItem(row, 2, dateItem);
                ui->historyTable->setItem(row, 3, oldStatusItem);
                ui->historyTable->setItem(row, 4, newStatusItem);
                ui->historyTable->setItem(row, 5, costItem);
                ui->historyTable->setItem(row, 6, detailsItem);

                row++;
            }
        }
    }

    ui->historyTable->resizeColumnsToContents();
}

void PredictiveMaintenanceDialog::populateSelectedEquipmentInfo(int row)
{
    if (row < 0 || row >= ui->predictionsTable->rowCount()) {
        // Clear the selection information
        ui->selectedIdValue->setText("(None selected)");
        ui->selectedNameValue->setText("(None selected)");
        ui->selectedTypeValue->setText("(None selected)");
        ui->selectedStatusValue->setText("(None selected)");
        ui->predFailureValue->setText("(None selected)");
        return;
    }

    // Get values from the selected row
    QString id = ui->predictionsTable->item(row, 0)->text();
    QString name = ui->predictionsTable->item(row, 1)->text();
    QString type = ui->predictionsTable->item(row, 2)->text();
    QString status = ui->predictionsTable->item(row, 3)->text();
    QString predFailure = ui->predictionsTable->item(row, 4)->text();

    // Update the UI
    ui->selectedIdValue->setText(id);
    ui->selectedNameValue->setText(name);
    ui->selectedTypeValue->setText(type);
    ui->selectedStatusValue->setText(status);
    ui->predFailureValue->setText(predFailure);
}

void PredictiveMaintenanceDialog::clearMaintenanceForm()
{
    ui->maintenanceCostEdit->clear();
    ui->maintenanceDetailsEdit->clear();
}

// Slot implementations

void PredictiveMaintenanceDialog::on_checkPredictionsBtn_clicked()
{
    int daysThreshold = ui->thresholdComboBox->currentData().toInt();
    refreshPredictionsTable(daysThreshold);
}

void PredictiveMaintenanceDialog::on_generateOrdersBtn_clicked()
{
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Generate Orders",
                                                              "This will automatically generate and send order messages for all damaged equipment. Continue?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    // Generate orders
    bool success = predictionModel.generateOrders();

    if (success) {
        QMessageBox::information(this, "Orders Generated",
                                 "Orders have been generated and sent to suppliers.");

        // Refresh stats
        updateEquipmentStats();
    } else {
        QMessageBox::warning(this, "Order Generation Failed",
                             "Some or all orders could not be generated. Check the log for details.");
    }
}

void PredictiveMaintenanceDialog::on_recordMaintenanceBtn_clicked()
{
    // Check if equipment is selected
    if (ui->selectedIdValue->text() == "(None selected)") {
        QMessageBox::warning(this, "Selection Error", "Please select equipment to record maintenance for.");
        return;
    }

    // Get equipment ID
    int equipmentId = ui->selectedIdValue->text().toInt();

    // Validate maintenance cost
    bool ok;
    double cost = ui->maintenanceCostEdit->text().toDouble(&ok);
    if (!ok || cost < 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid maintenance cost.");
        return;
    }

    // Get maintenance details
    QString details = ui->maintenanceDetailsEdit->toPlainText();
    if (details.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter maintenance details.");
        return;
    }

    // Record maintenance
    bool success = predictionModel.recordMaintenance(equipmentId, cost, details);

    if (success) {
        QMessageBox::information(this, "Maintenance Recorded",
                                 "Maintenance has been recorded for " + ui->selectedNameValue->text() +
                                     ".\nStatus has been set to Functional.");

        // Clear input fields
        clearMaintenanceForm();

        // Update UI
        updateEquipmentStats();
        int daysThreshold = ui->thresholdComboBox->currentData().toInt();
        refreshPredictionsTable(daysThreshold);

        // Switch to the predictions tab
        ui->mainTabWidget->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Record Failed",
                             "Failed to record maintenance. Check the log for details.");
    }
}

void PredictiveMaintenanceDialog::on_runPredictionsBtn_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    predictionModel.predictFailures();
    QApplication::restoreOverrideCursor();

    int daysThreshold = ui->thresholdComboBox->currentData().toInt();
    refreshPredictionsTable(daysThreshold);
    updateEquipmentStats();

    QMessageBox::information(this, "Predictions Updated",
                             "Equipment failure predictions have been updated.");
}

void PredictiveMaintenanceDialog::on_closeBtn_clicked()
{
    accept(); // Close the dialog with accept() result
}

void PredictiveMaintenanceDialog::on_predictionsTable_itemSelectionChanged()
{
    QList<QTableWidgetItem*> selectedItems = ui->predictionsTable->selectedItems();
    if (!selectedItems.isEmpty()) {
        int row = selectedItems.first()->row();
        populateSelectedEquipmentInfo(row);

        // Switch to maintenance tab if equipment is damaged
        if (ui->selectedStatusValue->text() == "Damaged") {
            ui->mainTabWidget->setCurrentIndex(1); // Maintenance tab
        }
    } else {
        populateSelectedEquipmentInfo(-1); // Clear selection info
    }
}

void PredictiveMaintenanceDialog::on_equipmentFilterCombo_currentIndexChanged(int index)
{
    int equipmentId = ui->equipmentFilterCombo->currentData().toInt();
    loadMaintenanceHistory(equipmentId);
}

void PredictiveMaintenanceDialog::on_viewMaintenanceHistoryBtn_clicked()
{
    // Load full maintenance history
    loadMaintenanceHistory();

    // Switch to history tab
    ui->mainTabWidget->setCurrentIndex(2);
}
