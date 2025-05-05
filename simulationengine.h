#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QVector>
#include "patientdata.h"
#include "viraldata.h"

// Structure to hold simulation parameters
struct SimulationParameters {
    PatientData patientData;
    QString viralType;
    int simulationDepth;
    double parameterIntensity;
};

// Structure to hold simulation results for a single time point
struct SimulationResult {
    double viralLoad;
    double immuneResponse;
    double cellDamage;
    double inflammationLevel;
    double antibodyLevel;
    double tcellActivity;
    double cytokineLevel;
};

class SimulationEngine : public QObject
{
    Q_OBJECT

public:
    explicit SimulationEngine(QObject *parent = nullptr);

    // Run simulation with given parameters
    QVector<SimulationResult> runSimulation(const SimulationParameters &params);

    // Process raw DNA data for analysis
    bool processDNAData(const QByteArray &dnaData, PatientData &patientData);

    // Process viral sequence data
    bool processViralData(const QByteArray &viralData, ViralData &viralDataObj);

signals:
    void progressUpdated(int progress);
    void simulationCompleted(const QVector<SimulationResult> &results);
    void simulationError(const QString &errorMessage);

private:
    // Helper functions for simulation
    void simulateViralReplication(double susceptibility, double &viralLoad, double immuneResponse);
    void simulateImmuneResponse(double baseResponse, double viralLoad, double &immuneResponse);
    void simulateCellularDamage(double viralLoad, double immuneResponse, double &cellDamage);
    void simulateInflammation(double viralLoad, double cellDamage, double &inflammation);

    // Calculate specific immune components
    double calculateAntibodyResponse(double immuneResponse, int day);
    double calculateTCellResponse(double immuneResponse, int day);
    double calculateCytokineResponse(double immuneResponse, double inflammation, int day);
};

#endif // SIMULATIONENGINE_H
