#ifndef DNAWINDOW_H
#define DNAWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QPrinter>
#include <QPainter>
#include <QPageSize>
#include <QPageLayout>
#include "dnaanalyzer.h"
#include "patientdata.h"
#include "viralresponse.h"
#include "simulationengine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DnaWindow; }
QT_END_NAMESPACE

class DnaWindow : public QMainWindow
{
    Q_OBJECT

public:
    DnaWindow(QWidget *parent = nullptr);
    ~DnaWindow();
    struct ViralResponseProfile {
        QString responseType;
        double clearanceEfficiency;
        double peakViralLoad;
        int timeToPeak;
        double immuneActivationScore;
        QStringList recommendations;
    };

private slots:
    void on_actionImportPatientData_triggered();
     void on_importViralDataButtonp_clicked();
    void on_actionExportResults_triggered();
    void on_actionQuit_triggered();

    void onAgeChanged(int age);
    void onGenderChanged(int index);
    void exportAnalysisToPdfp();
    void on_runSimulationButtonp_clicked();
    void on_clearDataButton_clicked();
    void on_analyzeResponseButtonp_clicked();

    void on_bloodTypeComboBox_currentIndexChanged(int index);
    void on_virusTypeComboBox_currentIndexChanged(int index);

    void on_parametersSlider_valueChanged(int value);
    void on_simulationDepthSpinBox_valueChanged(int value);
    void on_importPatientDataButtonp_clicked();
    void on_virusParametersChanged();
    void updatePatientDataDisplay();
    void updateSimulationResults();
    void generateViralResponseChart();
    void generateImmuneResponseChart();
    void determineResponseType();
    void calculateBasicMetrics();
    void updateViralLoadChart(const QVector<double>& viralLoadData);
    void updateImmuneResponseChart(const QVector<double>& immuneResponseData);
private:
    Ui::DnaWindow *ui;
    ViralResponseProfile m_responseProfile;  // Changed from ResponseProfile
    QString determineResponseType(const QVector<SimulationResult>& results);
    QStringList generateRecommendations(const QString& responseType);
    QString detectVirusType(const QString& content);
    QString extractGeneVariant(const QString& content, const QString& gene);
    // Updated parameter type
    void updateAnalysisResultsDisplay();

    // Core data models
    PatientData m_patientData;
    ViralData m_viralData;

    // Analysis engines
    DNAAnalyzer m_dnaAnalyzer;
    SimulationEngine m_simulationEngine;

    // Results storage
    QVector<SimulationResult> m_simulationResults;


    // Chart components
    QChart *m_viralLoadChart;
    QChartView *m_viralLoadChartView;
    QChart *m_immuneResponseChart;
    QChartView *m_immuneResponseChartView;
    QChart* generateImmuneResponseMiniChart();
    // Utility methods
    void setupCharts();
    void setupConnections();
    void loadDefaultData();
    bool validateInputs();
    void displayErrorMessage(const QString &title, const QString &message);
};

#endif // DNAWINDOW_H
