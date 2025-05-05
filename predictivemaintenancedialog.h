#ifndef PREDICTIVEMAINTENANCEDIALOG_H
#define PREDICTIVEMAINTENANCEDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "PredictionModel.h"

namespace Ui {
class PredictiveMaintenanceDialog;
}

class PredictiveMaintenanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PredictiveMaintenanceDialog(QWidget *parent = nullptr);
    ~PredictiveMaintenanceDialog();

private slots:
    void on_checkPredictionsBtn_clicked();
    void on_generateOrdersBtn_clicked();
    void on_recordMaintenanceBtn_clicked();
    void on_runPredictionsBtn_clicked();
    void on_closeBtn_clicked();
    void on_predictionsTable_itemSelectionChanged();
    void on_equipmentFilterCombo_currentIndexChanged(int index);
    void on_viewMaintenanceHistoryBtn_clicked();

private:
    Ui::PredictiveMaintenanceDialog *ui;
    PredictionModel predictionModel;

    void initializeUI();
    void loadEquipmentCombo();
    void updateEquipmentStats();
    void refreshPredictionsTable(int daysThreshold);
    void loadMaintenanceHistory(int equipmentId = -1); // -1 means all equipment
    void populateSelectedEquipmentInfo(int row);
    void clearMaintenanceForm();
};

#endif // PREDICTIVEMAINTENANCEDIALOG_H
