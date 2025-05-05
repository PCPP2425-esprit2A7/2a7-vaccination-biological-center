#include "viralresponsep.h"
#include "patientdatap.h"
#include "viraldatap.h"
#include "simulationenginep.h"
#include <QtMath>

ViralResponse::ResponseType ViralResponse::analyzeResponsePattern(const QVector<SimulationResult> &results)
{
    if (results.isEmpty()) {
        return Unknown;
    }

    // Calculate key metrics
    double clearanceEfficiency = calculateClearanceEfficiency(results);
    double inflammationSeverity = calculateInflammationSeverity(results);
    double immuneBalance = calculateImmuneBalance(results);

    // Determine peak viral load and day
    double peakViralLoad = 0.0;
    int peakDay = 0;
    for (int i = 0; i < results.size(); ++i) {
        if (results[i].viralLoad > peakViralLoad) {
            peakViralLoad = results[i].viralLoad;
            peakDay = i;
        }
    }

    // Check final viral load
    double finalViralLoad = results.last().viralLoad;

    // Decision tree for response type determination

    // Ideal response: high clearance, low inflammation, balanced immune response, viral load eliminated
    if (clearanceEfficiency > 0.8 && inflammationSeverity < 0.3 && finalViralLoad < 0.1) {
        return Ideal;
    }

    // Effective response: good clearance, moderate inflammation
    if (clearanceEfficiency > 0.6 && inflammationSeverity < 0.5 && finalViralLoad < 0.2) {
        return Effective;
    }

    // Hyperinflammatory response: high inflammation, potentially high tissue damage
    if (inflammationSeverity > 0.7) {
        return Hyperinflammatory;
    }

    // Delayed response: slow clearance but eventually effective
    if (clearanceEfficiency > 0.4 && peakDay > results.size() / 2) {
        return Delayed;
    }

    // Ineffective response: poor viral clearance
    if (clearanceEfficiency < 0.4 || finalViralLoad > 0.3) {
        return Ineffective;
    }

    // Default fall-through case
    return Unknown;
}

double ViralResponse::calculateClearanceEfficiency(const QVector<SimulationResult> &results)
{
    if (results.isEmpty()) {
        return 0.0;
    }

    // Find peak viral load
    double peakViralLoad = 0.0;
    for (const SimulationResult &result : results) {
        peakViralLoad = qMax(peakViralLoad, result.viralLoad);
    }

    // If no significant viral load was found
    if (peakViralLoad < 0.1) {
        return 1.0;
    }

    // Final viral load
    double finalViralLoad = results.last().viralLoad;

    // Calculate reduction from peak
    double reduction = (peakViralLoad - finalViralLoad) / peakViralLoad;

    // Scaling factor for time-to-clearance
    double timeFactor = 1.0;

    // If the simulation ran for enough days to show clearance
    if (results.size() >= 14) {
        // Find time to reduce viral load by 90%
        int daysToClearance = results.size(); // Default to full simulation length

        for (int i = 0; i < results.size(); ++i) {
            if (results[i].viralLoad <= 0.1 * peakViralLoad) {
                daysToClearance = i;
                break;
            }
        }

        // Adjust efficiency based on clearance time (faster is better)
        timeFactor = qExp(-0.05 * daysToClearance);
    }

    // Combine factors
    return reduction * timeFactor;
}

double ViralResponse::calculateInflammationSeverity(const QVector<SimulationResult> &results)
{
    if (results.isEmpty()) {
        return 0.0;
    }

    // Calculate area under the inflammation curve
    double totalInflammation = 0.0;
    for (const SimulationResult &result : results) {
        totalInflammation += result.inflammationLevel;
    }

    // Normalize by duration
    double averageInflammation = totalInflammation / results.size();

    // Peak inflammation
    double peakInflammation = 0.0;
    for (const SimulationResult &result : results) {
        peakInflammation = qMax(peakInflammation, result.inflammationLevel);
    }

    // Weight the peak heavily in the severity calculation
    return 0.6 * averageInflammation + 0.4 * peakInflammation;
}

double ViralResponse::calculateImmuneBalance(const QVector<SimulationResult> &results)
{
    if (results.isEmpty()) {
        return 0.5; // Neutral balance
    }

    // Calculate averages of immune components
    double totalAntibody = 0.0;
    double totalTCell = 0.0;
    double totalCytokine = 0.0;

    for (const SimulationResult &result : results) {
        totalAntibody += result.antibodyLevel;
        totalTCell += result.tcellActivity;
        totalCytokine += result.cytokineLevel;
    }

    double avgAntibody = totalAntibody / results.size();
    double avgTCell = totalTCell / results.size();
    double avgCytokine = totalCytokine / results.size();

    // Calculate balance metric
    // Higher ratio of antibody/tcell to cytokine is better (less inflammatory)
    double adaptiveResponse = (avgAntibody + avgTCell) / 2.0;

    // If either component is zero, avoid division by zero
    if (adaptiveResponse < 0.0001 || avgCytokine < 0.0001) {
        return 0.5;
    }

    // Calculate ratio
    double ratio = adaptiveResponse / avgCytokine;

    // Normalize to 0-1 range
    return qMin(1.0, ratio / 3.0);
}

QStringList ViralResponse::getRecommendations(const PatientData &patientData,
                                              const ViralData &viralData,
                                              ResponseType responseType)
{
    QStringList recommendations;

    // Get patient characteristics
    int age = patientData.getAge();
    QString bloodType = patientData.getBloodType();

    // Get virus characteristics
    QString virusType = viralData.getVirusType();

    // Common recommendations
    recommendations << "Regular monitoring of vital signs and symptoms";
    recommendations << "Stay well hydrated";

    // Add specific recommendations based on response type
    switch (responseType) {
    case Ideal:
        recommendations << "Continue current healthy practices";
        recommendations << "Follow standard recovery protocols";
        break;

    case Effective:
        recommendations << "Monitor for secondary symptoms";
        recommendations << "Moderate rest to support recovery";

        if (age > 60) {
            recommendations << "Consider supportive care to prevent complications";
        }
        break;

    case Delayed:
        recommendations << "Extended monitoring period recommended";
        recommendations << "Consider antiviral treatment options";
        recommendations << "Immune support may be beneficial";

        if (virusType == "Influenza A") {
            recommendations << "Consider neuraminidase inhibitors if within 48 hours of symptom onset";
        } else if (virusType == "SARS-CoV-2") {
            recommendations << "Consider monoclonal antibody treatment for high-risk individuals";
        }
        break;

    case Hyperinflammatory:
        recommendations << "Close monitoring for cytokine storm indicators";
        recommendations << "Anti-inflammatory intervention may be necessary";
        recommendations << "Consider immunomodulatory treatment";

        if (age > 50) {
            recommendations << "Higher risk of severe outcomes, consider hospital monitoring";
        }
        break;

    case Ineffective:
        recommendations << "Aggressive treatment approach recommended";
        recommendations << "Extended antiviral therapy may be necessary";
        recommendations << "Consider combination therapy approaches";
        recommendations << "Monitor for chronic infection development";

        if (virusType == "HIV" || virusType == "Hepatitis C") {
            recommendations << "Long-term management protocol should be implemented";
        }
        break;

    case Unknown:
        recommendations << "Additional testing recommended to determine response pattern";
        recommendations << "Consider specialist consultation";
        break;
    }

    // Add blood type specific recommendations if applicable
    if (bloodType.startsWith("A") && virusType == "SARS-CoV-2") {
        recommendations << "Type A blood may be associated with higher risk, consider more intensive monitoring";
    } else if (bloodType.startsWith("O") && virusType == "SARS-CoV-2") {
        recommendations << "Type O blood may be associated with lower risk, but standard protocols still apply";
    }

    // Age-specific recommendations
    if (age < 18) {
        recommendations << "Pediatric dosing and monitoring protocols should be followed";
    } else if (age > 65) {
        recommendations << "Geriatric considerations should be applied to treatment protocols";
    }

    return recommendations;
}

QString ViralResponse::responseTypeToString(ResponseType type)
{
    switch (type) {
    case Ideal:
        return "Ideal Response";
    case Effective:
        return "Effective Response";
    case Delayed:
        return "Delayed Response";
    case Hyperinflammatory:
        return "Hyperinflammatory Response";
    case Ineffective:
        return "Ineffective Response";
    case Unknown:
    default:
        return "Unknown Response Pattern";
    }
}
