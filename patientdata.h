#ifndef PATIENTDATA_H
#define PATIENTDATA_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QDateTime>

class PatientData
{
public:
    PatientData();

    // Basic patient information
    QString getBloodType() const;
    void setBloodType(const QString &bloodType);

    int getAge() const;
    void setAge(int age);

    QString getGender() const;
    void setGender(const QString &gender);

    // Genetic information
    QStringList getHLATypes() const;
    void setHLATypes(const QStringList &hlaTypes);
    void addHLAType(const QString &hlaType);

    QMap<QString, QString> getGeneticMarkers() const;
    void setGeneticMarkers(const QMap<QString, QString> &markers);
    void addGeneticMarker(const QString &marker, const QString &value);

    // File information
    QString getFileName() const;
    void setFileName(const QString &fileName);

    QDateTime getImportDate() const;
    void setImportDate(const QDateTime &importDate);

    // Calculate susceptibility based on genetic factors
    double calculateSusceptibility(const QString &virusType) const;

    // Calculate immune response strength
    double calculateImmuneResponse() const;

private:
    QString m_bloodType;
    int m_age;
    QString m_gender;
    QStringList m_hlaTypes;
    QMap<QString, QString> m_geneticMarkers;
    QString m_fileName;
    QDateTime m_importDate;
};

#endif // PATIENTDATA_H
