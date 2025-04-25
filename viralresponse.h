#ifndef VIRALRESPONSE_H
#define VIRALRESPONSE_H

#include <QString>
#include <QStringList>

// Forward declarations
class PatientData;
class ViralData;
struct SimulationResult;

// This is a utility class to analyze viral response patterns
class ViralResponse
{
public:
    // Response types
    enum ResponseType {
        Ideal,             // Fast clearance, minimal damage
        Effective,         // Good clearance, moderate inflammation
        Delayed,           // Slow clearance, prolonged symptoms
        Hyperinflammatory, // Excessive immune response, high tissue damage
        Ineffective,       // Poor viral clearance, persistent infection
        Unknown            // Cannot determine pattern
    };

    // Calculate response pattern from simulation results
    static ResponseType analyzeResponsePattern(const QVector<SimulationResult> &results);

    // Calculate clearance efficiency (how well the patient cleared the virus)
    static double calculateClearanceEfficiency(const QVector<SimulationResult> &results);

    // Calculate inflammation severity (area under inflammation curve)
    static double calculateInflammationSeverity(const QVector<SimulationResult> &results);

    // Calculate immune activation profile (ratio of components)
    static double calculateImmuneBalance(const QVector<SimulationResult> &results);

    // Get recommendations based on patient data and response type
    static QStringList getRecommendations(const PatientData &patientData,
                                          const ViralData &viralData,
                                          ResponseType responseType);

    // Get string representation of response type
    static QString responseTypeToString(ResponseType type);
};

#endif // VIRALRESPONSE_H
