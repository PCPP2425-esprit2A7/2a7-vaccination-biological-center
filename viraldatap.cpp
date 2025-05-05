#include "viraldatap.h"

ViralData::ViralData()
    : m_virusType("SARS-CoV-2")
    , m_viralLoad(1.0)
{
}

QString ViralData::getVirusType() const
{
    return m_virusType;
}

void ViralData::setVirusType(const QString &virusType)
{
    m_virusType = virusType;
}

double ViralData::getViralLoad() const
{
    return m_viralLoad;
}

void ViralData::setViralLoad(double viralLoad)
{
    m_viralLoad = viralLoad;
}

double ViralData::getInfectionRate() const
{
    return lookupInfectionRate();
}

int ViralData::getIncubationPeriod() const
{
    return lookupIncubationPeriod();
}

int ViralData::getIllnessDuration() const
{
    return lookupIllnessDuration();
}

double ViralData::getMortalityRate() const
{
    return lookupMortalityRate();
}

QString ViralData::getFileName() const
{
    return m_fileName;
}

void ViralData::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

QDateTime ViralData::getImportDate() const
{
    return m_importDate;
}

void ViralData::setImportDate(const QDateTime &importDate)
{
    m_importDate = importDate;
}

double ViralData::calculateBloodTypeInteraction(const QString &bloodType) const
{
    // This is a simplified model of how viruses might interact with blood types
    // In a real application, this would be based on scientific data

    // Default: neutral interaction
    double interactionFactor = 1.0;

    if (m_virusType == "SARS-CoV-2") {
        // COVID-19 theoretical blood type interactions
        // Research suggests type A more susceptible, type O less susceptible
        if (bloodType.startsWith("A")) {
            interactionFactor = 1.2; // 20% worse outcomes
        } else if (bloodType.startsWith("O")) {
            interactionFactor = 0.8; // 20% better outcomes
        }
    } else if (m_virusType == "Influenza A") {
        // Influenza theoretical interactions
        if (bloodType.startsWith("B")) {
            interactionFactor = 0.9; // Slightly better outcomes
        }
    } else if (m_virusType == "Hepatitis C") {
        // Hepatitis C theoretical interactions
        if (bloodType == "AB+") {
            interactionFactor = 1.1; // Slightly worse outcomes
        }
    }

    return interactionFactor;
}

double ViralData::calculateGeneticInteraction(const QMap<QString, QString> &geneticMarkers) const
{
    // Default: neutral interaction
    double interactionFactor = 1.0;

    // Check genetic markers that affect viral interactions
    if (m_virusType == "SARS-CoV-2") {
        // ACE2 receptor variants affect COVID-19 infection
        if (geneticMarkers.contains("ACE2")) {
            if (geneticMarkers["ACE2"] == "Variant") {
                interactionFactor *= 1.3; // 30% worse outcomes
            }
        }

        // Interferon lambda gene affects immune response to many viruses
        if (geneticMarkers.contains("IFNL3")) {
            if (geneticMarkers["IFNL3"] == "C/C genotype") {
                interactionFactor *= 0.8; // 20% better outcomes
            }
        }
    } else if (m_virusType == "HIV") {
        // CCR5-Delta32 mutation provides HIV resistance
        if (geneticMarkers.contains("CCR5")) {
            if (geneticMarkers["CCR5"] == "Delta32") {
                interactionFactor *= 0.5; // 50% better outcomes
            }
        }
    } else if (m_virusType == "Hepatitis C") {
        // IL28B gene affects response to Hepatitis C
        if (geneticMarkers.contains("IL28B")) {
            if (geneticMarkers["IL28B"].contains("rs12979860-C")) {
                interactionFactor *= 0.7; // 30% better outcomes
            }
        }
    }

    return interactionFactor;
}

double ViralData::lookupInfectionRate() const
{
    // Returns R0 (basic reproduction number)
    if (m_virusType == "SARS-CoV-2") {
        return 2.5; // COVID-19 estimate
    } else if (m_virusType == "Influenza A") {
        return 1.5; // Seasonal flu estimate
    } else if (m_virusType == "HIV") {
        return 4.0; // HIV estimate
    } else if (m_virusType == "Hepatitis C") {
        return 2.0; // HCV estimate
    } else if (m_virusType == "Epstein-Barr") {
        return 5.0; // EBV estimate
    }

    return 2.0; // Default value
}

int ViralData::lookupIncubationPeriod() const
{
    // Returns incubation period in days
    if (m_virusType == "SARS-CoV-2") {
        return 5; // COVID-19 estimate
    } else if (m_virusType == "Influenza A") {
        return 2; // Seasonal flu estimate
    } else if (m_virusType == "HIV") {
        return 21; // HIV estimate (acute symptoms)
    } else if (m_virusType == "Hepatitis C") {
        return 45; // HCV estimate
    } else if (m_virusType == "Epstein-Barr") {
        return 30; // EBV estimate
    }

    return 7; // Default value
}

int ViralData::lookupIllnessDuration() const
{
    // Returns typical illness duration in days
    if (m_virusType == "SARS-CoV-2") {
        return 14; // COVID-19 estimate
    } else if (m_virusType == "Influenza A") {
        return 7; // Seasonal flu estimate
    } else if (m_virusType == "HIV") {
        return 0; // Chronic (0 means chronic)
    } else if (m_virusType == "Hepatitis C") {
        return 0; // Often chronic
    } else if (m_virusType == "Epstein-Barr") {
        return 21; // EBV/mono estimate
    }

    return 10; // Default value
}

double ViralData::lookupMortalityRate() const
{
    // Returns mortality rate (0.0-1.0)
    if (m_virusType == "SARS-CoV-2") {
        return 0.02; // COVID-19 estimate (2%)
    } else if (m_virusType == "Influenza A") {
        return 0.001; // Seasonal flu estimate (0.1%)
    } else if (m_virusType == "HIV") {
        return 0.8; // Untreated HIV estimate
    } else if (m_virusType == "Hepatitis C") {
        return 0.03; // HCV long-term estimate
    } else if (m_virusType == "Epstein-Barr") {
        return 0.0001; // EBV estimate (very low)
    }

    return 0.01; // Default value
}
