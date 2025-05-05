#include "dnaanalyzer.h"
#include "simulationengine.h"
#include "viralresponse.h"
#include <QDebug>
#include "dnawindow.h"

DNAAnalyzer::DNAAnalyzer(QObject *parent)
    : QObject(parent)
{
    initializeReferenceData();
}

DNAAnalyzer::~DNAAnalyzer()
{
}

ViralResponseProfile DNAAnalyzer::analyzeViralResponse(const PatientData &patientData,
                                                       const QVector<SimulationResult> &results)
{
    ViralResponseProfile profile;

    // Determine response type using the ViralResponse utility
    ViralResponse::ResponseType responseType = ViralResponse::analyzeResponsePattern(results);
    profile.responseType = ViralResponse::responseTypeToString(responseType);

    // Calculate metrics
    profile.clearanceEfficiency = ViralResponse::calculateClearanceEfficiency(results) * 100.0; // Convert to percentage

    // Calculate peak viral load and time to peak
    calculatePeakMetrics(results, profile.peakViralLoad, profile.timeToPeak);

    // Calculate immune response metrics
    profile.immuneActivationScore = analyzeImmuneResponse(patientData);

    // Generate recommendations
    ViralData viralData; // Create a dummy viral data object
    viralData.setVirusType("SARS-CoV-2"); // Assuming this type, would be set from simulation params

    profile.recommendations = ViralResponse::getRecommendations(patientData, viralData, responseType);

    // Emit signal that analysis is complete
    emit analysisCompleted(profile);

    return profile;
}

double DNAAnalyzer::analyzeSusceptibility(const PatientData &patientData, const QString &virusType)
{
    // Use the PatientData model's calculation
    double baseSusceptibility = patientData.calculateSusceptibility(virusType);

    // Apply blood type factors
    double bloodTypeFactor = analyzeBloodTypeCompatibility(patientData.getBloodType(), virusType);

    // Combined susceptibility score
    return baseSusceptibility * bloodTypeFactor;
}

double DNAAnalyzer::analyzeImmuneResponse(const PatientData &patientData)
{
    // Base score from patient data model
    double baseScore = patientData.calculateImmuneResponse();

    // Analyze HLA diversity (more diversity = better response)
    const QStringList hlaTypes = patientData.getHLATypes();

    // Calculate diversity score (simplified)
    double diversityScore = qMin(1.0, hlaTypes.size() / 8.0); // Normalize to 0-1 range

    // Analyze genetic markers
    const QMap<QString, QString> markers = patientData.getGeneticMarkers();
    double markerScore = 0.5; // Default neutral score

    // Check for specific markers that affect immune function
    if (markers.contains("IFNL3") && markers["IFNL3"] == "C/C genotype") {
        markerScore += 0.2; // Better interferon response
    }

    if (markers.contains("TLR4") && markers["TLR4"].contains("rs4986790")) {
        markerScore -= 0.1; // TLR4 variant might reduce response
    }

    // Combine scores
    return (baseScore * 0.5) + (diversityScore * 0.3) + (markerScore * 0.2);
}

QStringList DNAAnalyzer::generateRecommendations(const PatientData &patientData,
                                                 const ViralResponseProfile &profile)
{
    // This would be a complex function with medical knowledge
    // For demo purposes, we'll return some generic recommendations

    QStringList recommendations;

    // Basic recommendations based on response type
    if (profile.responseType == "Ideal Response") {
        recommendations << "Continue with standard protocols";
        recommendations << "Monitor for any changes in symptoms";
    } else if (profile.responseType == "Hyperinflammatory Response") {
        recommendations << "Consider anti-inflammatory interventions";
        recommendations << "Monitor for cytokine storm";
        recommendations << "Immune modulation may be necessary";
    } else if (profile.responseType == "Ineffective Response") {
        recommendations << "Consider alternative antiviral therapy";
        recommendations << "Extended treatment duration recommended";
        recommendations << "Monitor for chronic infection";
    }

    // Add age-specific recommendations
    int age = patientData.getAge();
    if (age > 60) {
        recommendations << "Additional monitoring due to age-related risk factors";
    }

    // Add blood type specific recommendations
    QString bloodType = patientData.getBloodType();
    if (bloodType.startsWith("A")) {
        recommendations << "Type A blood may have increased susceptibility to certain viruses";
    }

    return recommendations;
}

double DNAAnalyzer::analyzeBloodTypeCompatibility(const QString &bloodType, const QString &virusType)
{
    // Check if we have data for this virus
    if (!m_bloodTypeFactors.contains(virusType)) {
        return 1.0; // Neutral factor
    }

    // Get blood type factors for this virus
    const QMap<QString, double> &factors = m_bloodTypeFactors[virusType];

    // Check if we have data for this blood type
    if (!factors.contains(bloodType)) {
        return 1.0; // Neutral factor
    }

    return factors[bloodType];
}

void DNAAnalyzer::initializeReferenceData()
{
    // Initialize blood type compatibility factors for different viruses
    // These would be based on scientific studies

    // SARS-CoV-2 (COVID-19)
    QMap<QString, double> covidFactors;
    covidFactors["A+"] = 1.2;  // Type A may be more susceptible
    covidFactors["A-"] = 1.2;
    covidFactors["B+"] = 1.0;
    covidFactors["B-"] = 1.0;
    covidFactors["AB+"] = 1.1;
    covidFactors["AB-"] = 1.1;
    covidFactors["O+"] = 0.8;  // Type O may be less susceptible
    covidFactors["O-"] = 0.8;
    m_bloodTypeFactors["SARS-CoV-2"] = covidFactors;

    // Influenza A
    QMap<QString, double> fluFactors;
    fluFactors["A+"] = 1.0;
    fluFactors["A-"] = 1.0;
    fluFactors["B+"] = 0.9;
    fluFactors["B-"] = 0.9;
    fluFactors["AB+"] = 1.0;
    fluFactors["AB-"] = 1.0;
    fluFactors["O+"] = 1.1;
    fluFactors["O-"] = 1.1;
    m_bloodTypeFactors["Influenza A"] = fluFactors;

    // Initialize genetic marker factors (simplified)
    QMap<QString, double> covidMarkers;
    covidMarkers["ACE2_Variant"] = 1.3;  // ACE2 variants may increase susceptibility
    covidMarkers["TLR4_rs4986790"] = 1.2;
    m_geneticMarkerFactors["SARS-CoV-2"] = covidMarkers;
}

void DNAAnalyzer::calculatePeakMetrics(const QVector<SimulationResult> &results,
                                       double &peakLoad, int &timeToPeak)
{
    peakLoad = 0.0;
    timeToPeak = 0;

    // Find peak viral load and when it occurred
    for (int i = 0; i < results.size(); ++i) {
        if (results[i].viralLoad > peakLoad) {
            peakLoad = results[i].viralLoad;
            timeToPeak = i;
        }
    }
}

double DNAAnalyzer::calculateClearanceEfficiency(const QVector<SimulationResult> &results)
{
    if (results.size() < 2) {
        return 0.0;
    }

    // Find peak viral load
    double peakLoad = 0.0;
    int peakDay = 0;
    for (int i = 0; i < results.size(); ++i) {
        if (results[i].viralLoad > peakLoad) {
            peakLoad = results[i].viralLoad;
            peakDay = i;
        }
    }

    // No significant viral load detected
    if (peakLoad < 0.1) {
        return 1.0; // Perfect clearance
    }

    // Final viral load
    double finalLoad = results.last().viralLoad;

    // Calculate reduction ratio from peak
    double reduction = (peakLoad - finalLoad) / peakLoad;

    // Calculate clearance rate
    double clearanceRate = 0.0;
    if (peakDay < results.size() - 1) {
        int daysSincePeak = results.size() - 1 - peakDay;
        clearanceRate = reduction / daysSincePeak;
    }

    // Combine factors (70% reduction, 30% rate)
    return (reduction * 0.7) + (clearanceRate * 10.0 * 0.3);
}
