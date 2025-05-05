#include "patientdata.h"
#include <QRandomGenerator>
#include "dnaanalyzer.h"
#include "dnawindow.h"

PatientData::PatientData()
    : m_age(35)
    , m_gender("Male")
{
}

QString PatientData::getBloodType() const
{
    return m_bloodType;
}

void PatientData::setBloodType(const QString &bloodType)
{
    m_bloodType = bloodType;
}

int PatientData::getAge() const
{
    return m_age;
}

void PatientData::setAge(int age)
{
    m_age = age;
}

QString PatientData::getGender() const
{
    return m_gender;
}

void PatientData::setGender(const QString &gender)
{
    m_gender = gender;
}

QStringList PatientData::getHLATypes() const
{
    return m_hlaTypes;
}

void PatientData::setHLATypes(const QStringList &hlaTypes)
{
    m_hlaTypes = hlaTypes;
}

void PatientData::addHLAType(const QString &hlaType)
{
    if (!m_hlaTypes.contains(hlaType)) {
        m_hlaTypes.append(hlaType);
    }
}

QMap<QString, QString> PatientData::getGeneticMarkers() const
{
    return m_geneticMarkers;
}

void PatientData::setGeneticMarkers(const QMap<QString, QString> &markers)
{
    m_geneticMarkers = markers;
}

void PatientData::addGeneticMarker(const QString &marker, const QString &value)
{
    m_geneticMarkers[marker] = value;
}

QString PatientData::getFileName() const
{
    return m_fileName;
}

void PatientData::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

QDateTime PatientData::getImportDate() const
{
    return m_importDate;
}

void PatientData::setImportDate(const QDateTime &importDate)
{
    m_importDate = importDate;
}

double PatientData::calculateSusceptibility(const QString &virusType) const
{
    // In a real application, this would implement a complex model based on
    // genetic markers, blood type, HLA types, and other factors
    // For demo purposes, we'll calculate a random but deterministic value

    double baseSusceptibility = 0.5; // Base susceptibility

    // Factor in blood type - some blood types may be more susceptible to certain viruses
    if (m_bloodType == "A+" || m_bloodType == "A-") {
        if (virusType == "SARS-CoV-2") {
            baseSusceptibility += 0.1; // A blood types may be more susceptible to COVID-19
        }
    } else if (m_bloodType == "O+" || m_bloodType == "O-") {
        if (virusType == "SARS-CoV-2") {
            baseSusceptibility -= 0.1; // O blood types may be less susceptible to COVID-19
        }
    }

    // Factor in genetic markers
    if (m_geneticMarkers.contains("ACE2")) {
        if (m_geneticMarkers["ACE2"] == "Variant" && virusType == "SARS-CoV-2") {
            baseSusceptibility += 0.15; // ACE2 receptor variants affect COVID-19 susceptibility
        }
    }

    if (m_geneticMarkers.contains("CCR5")) {
        if (m_geneticMarkers["CCR5"] == "Delta32" && virusType == "HIV") {
            baseSusceptibility -= 0.3; // CCR5-Delta32 provides some HIV resistance
        }
    }

    // Age factor - older people generally more susceptible
    if (m_age > 60) {
        baseSusceptibility += 0.2;
    } else if (m_age < 18) {
        baseSusceptibility -= 0.1;
    }

    // Add some deterministic randomness based on all factors combined
    QByteArray hashData;
    hashData.append(m_bloodType.toUtf8());
    hashData.append(QByteArray::number(m_age));
    hashData.append(virusType.toUtf8());

    // Generate a deterministic random variation between -0.1 and +0.1
    uint hashValue = qHash(hashData);
    double randomFactor = (hashValue % 200 - 100) / 1000.0; // -0.1 to +0.1

    // Ensure final value is between 0.1 and 0.9
    double finalSusceptibility = qBound(0.1, baseSusceptibility + randomFactor, 0.9);

    return finalSusceptibility;
}

double PatientData::calculateImmuneResponse() const
{
    // In a real application, this would implement a complex model
    // For demo purposes, we'll calculate a simple value

    double baseResponse = 0.5; // Base immune response

    // HLA diversity generally improves immune response
    baseResponse += m_hlaTypes.size() * 0.05;

    // Age factors - immune response typically strongest in young adults
    if (m_age < 12) {
        baseResponse -= 0.1; // Children have developing immune systems
    } else if (m_age > 65) {
        baseResponse -= 0.2; // Elderly have declining immune systems
    } else if (m_age >= 18 && m_age <= 35) {
        baseResponse += 0.1; // Prime immune age
    }

    // Genetic factor examples
    if (m_geneticMarkers.contains("IFNL3")) {
        if (m_geneticMarkers["IFNL3"] == "C/C genotype") {
            baseResponse += 0.15; // Better interferon response
        }
    }

    if (m_geneticMarkers.contains("IL28B")) {
        if (m_geneticMarkers["IL28B"].contains("rs12979860-C")) {
            baseResponse += 0.1; // Better antiviral response
        }
    }

    // Add some deterministic variation
    QByteArray hashData;
    hashData.append(m_bloodType.toUtf8());
    hashData.append(QByteArray::number(m_age));
    hashData.append(m_gender.toUtf8());

    // Generate a deterministic random variation between -0.15 and +0.15
    uint hashValue = qHash(hashData);
    double randomFactor = (hashValue % 300 - 150) / 1000.0; // -0.15 to +0.15

    // Ensure final value is between 0.2 and 0.95
    double finalResponse = qBound(0.2, baseResponse + randomFactor, 0.95);

    return finalResponse;
}
