#include "simulationenginep.h"
#include <QThread>
#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>

SimulationEngine::SimulationEngine(QObject *parent)
    : QObject(parent)
{
}

QVector<SimulationResult> SimulationEngine::runSimulation(const SimulationParameters &params)
{
    QVector<SimulationResult> results;

    // Determine initial conditions based on patient data and virus
    const PatientData &patientData = params.patientData;

    // Calculate patient susceptibility to this virus
    double susceptibility = patientData.calculateSusceptibility(params.viralType);

    // Calculate base immune response capability
    double baseImmuneResponse = patientData.calculateImmuneResponse();

    // Create virus data
    ViralData viralData;
    viralData.setVirusType(params.viralType);

    // Starting conditions
    double initialViralLoad = 0.1; // Initial viral presence

    // Scale parameters based on intensity
    double parameterScale = 0.5 + (params.parameterIntensity * 1.0);

    // Adjust initial viral load based on parameters
    initialViralLoad *= parameterScale;

    // Initialize state variables
    double viralLoad = initialViralLoad;
    double immuneResponse = 0.0;
    double cellDamage = 0.0;
    double inflammation = 0.0;

    // Run simulation for specified number of days
    for (int day = 0; day < params.simulationDepth; ++day) {
        // Simulate viral replication
        simulateViralReplication(susceptibility, viralLoad, immuneResponse);

        // Simulate immune response (with delay in early days)
        // Immune response builds up over time
        simulateImmuneResponse(baseImmuneResponse, viralLoad, immuneResponse);

        // Simulate cellular damage
        simulateCellularDamage(viralLoad, immuneResponse, cellDamage);

        // Simulate inflammation (a side effect of immune response)
        simulateInflammation(viralLoad, cellDamage, inflammation);

        // Calculate specific immune components
        double antibodyLevel = calculateAntibodyResponse(immuneResponse, day);
        double tcellActivity = calculateTCellResponse(immuneResponse, day);
        double cytokineLevel = calculateCytokineResponse(immuneResponse, inflammation, day);

        // Create result for this time point
        SimulationResult result;
        result.viralLoad = viralLoad;
        result.immuneResponse = immuneResponse;
        result.cellDamage = cellDamage;
        result.inflammationLevel = inflammation;
        result.antibodyLevel = antibodyLevel;
        result.tcellActivity = tcellActivity;
        result.cytokineLevel = cytokineLevel;

        // Add to results
        results.append(result);

        // Update progress
        int progress = (day + 1) * 100 / params.simulationDepth;
        emit progressUpdated(progress);

        // Brief pause to show progress (in a real app, this would be removed)
        QThread::msleep(50);
    }

    emit simulationCompleted(results);
    return results;
}

bool SimulationEngine::processDNAData(const QByteArray &dnaData, PatientData &patientData)
{
    // In a real application, this would parse actual DNA sequence data
    // For demonstration purposes, we'll just simulate the process

    // Simulate processing time
    emit progressUpdated(0);
    QThread::msleep(300);
    emit progressUpdated(30);

    // Simulate finding genetic markers
    QMap<QString, QString> markers;
    markers["ACE2"] = "Standard"; // Random marker
    markers["TLR4"] = "Variant rs4986790"; // Random marker
    markers["IFNL3"] = "C/C genotype"; // Random marker
    markers["CCR5"] = "Standard"; // Random marker

    // Set the extracted data
    patientData.setGeneticMarkers(markers);

    // Simulate finding HLA types
    QStringList hlaTypes;
    hlaTypes << "A*02:01" << "B*07:02" << "C*07:02" << "DRB1*15:01";
    patientData.setHLATypes(hlaTypes);

    emit progressUpdated(100);
    return true;
}

bool SimulationEngine::processViralData(const QByteArray &viralData, ViralData &viralDataObj)
{
    // In a real application, this would parse actual viral sequence data
    // For demonstration purposes, we'll just simulate the process

    // Simulate processing time
    emit progressUpdated(0);
    QThread::msleep(200);
    emit progressUpdated(50);

    // Set a default virus type
    viralDataObj.setVirusType("SARS-CoV-2");

    // Set viral load based on sequence data size
    double viralLoad = 1.0 + (viralData.size() % 10) / 10.0;
    viralDataObj.setViralLoad(viralLoad);

    emit progressUpdated(100);
    return true;
}

void SimulationEngine::simulateViralReplication(double susceptibility, double &viralLoad, double immuneResponse)
{
    // Basic viral replication model:
    // - Viruses replicate exponentially until they hit limits
    // - Immune response suppresses replication
    // - Patient susceptibility affects replication rate

    // Calculate replication rate (higher susceptibility = faster replication)
    double replicationRate = 0.4 * susceptibility;

    // Calculate immune suppression (higher immune response = more suppression)
    double immuneSuppression = 0.5 * immuneResponse;

    // Calculate viral carrying capacity (maximum viral load)
    double carryingCapacity = 10.0;

    // Calculate logistic growth with immune suppression
    double growth = replicationRate * viralLoad * (1.0 - viralLoad / carryingCapacity) - immuneSuppression * viralLoad;

    // Update viral load
    viralLoad = qMax(0.0, viralLoad + growth);
}

void SimulationEngine::simulateImmuneResponse(double baseResponse, double viralLoad, double &immuneResponse)
{
    // Basic immune response model:
    // - Immune response increases in response to viral load
    // - Response has inertia and doesn't decrease immediately when virus is gone
    // - Base response affects how quickly and strongly the immune system reacts

    // Calculate target immune response based on viral load and base capability
    double targetResponse = baseResponse * (1.0 - qExp(-viralLoad));

    // Calculate response rate (how quickly immune system responds)
    double responseRate = 0.2;

    // Calculate change in immune response (with inertia)
    double responseChange = responseRate * (targetResponse - immuneResponse);

    // Update immune response
    immuneResponse = qMax(0.0, qMin(1.0, immuneResponse + responseChange));
}

void SimulationEngine::simulateCellularDamage(double viralLoad, double immuneResponse, double &cellDamage)
{
    // Basic cell damage model:
    // - Damage is caused by both virus and excessive immune response
    // - Damage repairs slowly over time

    // Calculate viral damage
    double viralDamage = 0.1 * viralLoad;

    // Calculate immune-mediated damage (immunopathology)
    // High immune response can cause damage through inflammation, etc.
    double immuneDamage = 0.05 * qPow(immuneResponse, 2);

    // Calculate repair rate (damaged cells being replaced)
    double repairRate = 0.05;

    // Calculate net damage change
    double damageChange = viralDamage + immuneDamage - repairRate * cellDamage;

    // Update cell damage (capped at 1.0)
    cellDamage = qMax(0.0, qMin(1.0, cellDamage + damageChange));
}

void SimulationEngine::simulateInflammation(double viralLoad, double cellDamage, double &inflammation)
{
    // Basic inflammation model:
    // - Inflammation increases with viral load and cell damage
    // - Inflammation subsides slowly over time

    // Calculate inflammation stimulus
    double inflammationStimulus = 0.1 * viralLoad + 0.2 * cellDamage;

    // Calculate resolution rate (how quickly inflammation resolves)
    double resolutionRate = 0.1;

    // Calculate net inflammation change
    double inflammationChange = inflammationStimulus - resolutionRate * inflammation;

    // Update inflammation (capped at 1.0)
    inflammation = qMax(0.0, qMin(1.0, inflammation + inflammationChange));
}

double SimulationEngine::calculateAntibodyResponse(double immuneResponse, int day)
{
    // Antibody response typically starts after 7-10 days and then remains high
    double delayFactor = 1.0 - qExp(-qMax(0, day - 5) / 3.0);

    // Calculate antibody level
    return immuneResponse * delayFactor * 0.8;
}

double SimulationEngine::calculateTCellResponse(double immuneResponse, int day)
{
    // T-cell response typically starts after 3-5 days
    double delayFactor = 1.0 - qExp(-qMax(0, day - 2) / 2.0);

    // Calculate T-cell activity
    return immuneResponse * delayFactor * 0.7;
}

double SimulationEngine::calculateCytokineResponse(double immuneResponse, double inflammation, int day)
{
    // Cytokine response is fast but can be excessive (cytokine storm)
    double baseResponse = immuneResponse * 0.5;

    // Potential for cytokine storm when both immune response and inflammation are high
    double stormFactor = (immuneResponse > 0.7 && inflammation > 0.7) ? 0.5 : 0.0;

    // Calculate cytokine level
    return qMin(1.0, baseResponse + stormFactor * inflammation);
}
