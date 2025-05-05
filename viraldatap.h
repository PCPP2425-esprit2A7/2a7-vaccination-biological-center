#ifndef VIRALDATAP_H
#define VIRALDATAP_H

#include <QString>
#include <QDateTime>
#include <QMap>

class ViralData
{
public:
    ViralData();

    // Getters and setters for viral data
    QString getVirusType() const;
    void setVirusType(const QString &virusType);

    double getViralLoad() const;
    void setViralLoad(double viralLoad);

    // Get infection rate/R0 for the virus
    double getInfectionRate() const;

    // Get incubation period in days
    int getIncubationPeriod() const;

    // Get average duration of illness
    int getIllnessDuration() const;

    // Get mortality rate (0.0-1.0)
    double getMortalityRate() const;

    // File information
    QString getFileName() const;
    void setFileName(const QString &fileName);

    QDateTime getImportDate() const;
    void setImportDate(const QDateTime &importDate);

    // Calculate viral interactions with specific blood types
    // Returns a factor that modifies infection severity (< 1.0 means less severe)
    double calculateBloodTypeInteraction(const QString &bloodType) const;

    // Calculate interaction with genetic factors
    double calculateGeneticInteraction(const QMap<QString, QString> &geneticMarkers) const;

private:
    QString m_virusType;
    double m_viralLoad;
    QString m_fileName;
    QDateTime m_importDate;

    // Lookup reference data based on virus type
    double lookupInfectionRate() const;
    int lookupIncubationPeriod() const;
    int lookupIllnessDuration() const;
    double lookupMortalityRate() const;
};

#endif // VIRALDATAP_H
