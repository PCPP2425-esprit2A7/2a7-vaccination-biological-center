#ifndef DNAANALYZER_H
#define DNAANALYZER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "patientdata.h"
#include "viralresponse.h"

// Forward declaration
class SimulationResult;

// Structure to hold viral response analysis results
struct ViralResponseProfile {
    QString responseType;
    double clearanceEfficiency;
    double peakViralLoad;
    int timeToPeak;
    double immuneActivationScore;
    QStringList recommendations;
};

class DNAAnalyzer : public QObject
{
    Q_OBJECT

public:
    explicit DNAAnalyzer(QObject *parent = nullptr);
    ~DNAAnalyzer();

    // Analyze viral response based on patient data and simulation results
    ViralResponseProfile analyzeViralResponse(const PatientData &patientData,
                                              const QVector<SimulationResult> &results);

    // Analyze genetic markers for susceptibility
    double analyzeSusceptibility(const PatientData &patientData, const QString &virusType);

    // Analyze HLA types for immune response effectiveness
    double analyzeImmuneResponse(const PatientData &patientData);

    // Generate recommendations based on analysis
    QStringList generateRecommendations(const PatientData &patientData,
                                        const ViralResponseProfile &profile);

    // Analyze blood type compatibility with virus
    double analyzeBloodTypeCompatibility(const QString &bloodType, const QString &virusType);

signals:
    void analysisCompleted(const ViralResponseProfile &profile);
    void analysisError(const QString &errorMessage);

private:
    // Mapping of blood types to virus susceptibility factors
    QMap<QString, QMap<QString, double>> m_bloodTypeFactors;

    // Mapping of genetic markers to susceptibility factors
    QMap<QString, QMap<QString, double>> m_geneticMarkerFactors;

    // Initialize reference data
    void initializeReferenceData();

    // Calculate peak viral load from simulation results
    void calculatePeakMetrics(const QVector<SimulationResult> &results,
                              double &peakLoad, int &timeToPeak);

    // Calculate clearance efficiency
    double calculateClearanceEfficiency(const QVector<SimulationResult> &results);

    // Determine response type based on profile
    QString determineResponseType(double peakLoad, double clearanceEfficiency, double immuneActivation);
};

#endif // DNAANALYZER_H
