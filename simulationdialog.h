#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include "DiseaseSpreadModel.h"

class AIAssistantWindow;

namespace Ui {
class SimulationDialog;
}

class SimulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationDialog(QWidget *parent = nullptr);
    ~SimulationDialog();

    QString getRecommendedBSL() const;
    QString getSimulationSummary() const;

private slots:
    void on_runSimulationButton_clicked();
    void on_saveResultsButton_clicked();
    void on_populationDensitySlider_valueChanged(int value);
    void on_r0Slider_valueChanged(int value);
    void on_socialDistancingSlider_valueChanged(int value);
    void on_applyRecommendationButton_clicked();
    void on_aiEnhanceButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::SimulationDialog *ui;
    DiseaseSpreadModel *model;
    QChartView *chartView;

    void setupChart();
    void updateChart();
    void updateSummary();
    void enableResultControls(bool enable);
    AIAssistantWindow *aiAssistantWindow;
};

#endif // SIMULATIONDIALOG_H
