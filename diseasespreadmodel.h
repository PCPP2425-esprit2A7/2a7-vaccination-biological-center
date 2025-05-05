#ifndef DISEASESPREADMODEL_H
#define DISEASESPREADMODEL_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QDate>
#include <QString>
#include <QtMath>

class DiseaseSpreadModel : public QObject {
    Q_OBJECT

public:
    explicit DiseaseSpreadModel(QObject *parent = nullptr);
    void setRegion(const QString &region, double populationSize, double populationDensity);
    void setDiseaseParameters(double r0, int incubationDays, int infectiousPeriodDays, double fatalityRate);
    void setInitialConditions(int initialInfections);
    void setInterventionMeasures(double socialDistancingFactor, double vaccinationRate, int vaccinationStartDay);
    bool runSimulation(int daysToSimulate);
    QVector<double> getSusceptibleCurve() const;
    QVector<double> getInfectedCurve() const;
    QVector<double> getRecoveredCurve() const;
    QVector<double> getDeathsCurve() const;
    int getDaysToPeak() const;
    int getDaysToThreshold(double infectionRateThreshold) const;
    int getTotalInfections() const;
    QString recommendedBSLLevel() const;
    QString getAnalysisSummary() const;

private:
    QString regionName;
    double population;
    double density;
    double reproductionNumber;
    int incubationPeriod;
    int infectiousPeriod;
    double mortalityRate;
    int initialInfected;
    double socialDistancing;
    double vaccineRate;
    int vaccineDay;
    QVector<double> susceptible;
    QVector<double> infected;
    QVector<double> recovered;
    QVector<double> deaths;
    double calculateTransmissionRate() const;
    double adjustForInterventions(double rate, int day) const;
    QString determineBSLLevel(double peakInfectionRate, double spreadRate) const;
};

#endif // DISEASESPREADMODEL_H
