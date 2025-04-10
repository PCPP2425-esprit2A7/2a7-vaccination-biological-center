#include "DiseaseSpreadModel.h"

DiseaseSpreadModel::DiseaseSpreadModel(QObject *parent)
    : QObject(parent),
    population(0),
    density(0),
    reproductionNumber(0),
    incubationPeriod(0),
    infectiousPeriod(0),
    mortalityRate(0),
    initialInfected(0),
    socialDistancing(0),
    vaccineRate(0),
    vaccineDay(0)
{
}

void DiseaseSpreadModel::setRegion(const QString &region, double populationSize, double populationDensity)
{
    regionName = region;
    population = populationSize;
    density = populationDensity;
}

void DiseaseSpreadModel::setDiseaseParameters(double r0, int incubationDays, int infectiousPeriodDays, double fatalityRate)
{
    reproductionNumber = r0;
    incubationPeriod = incubationDays;
    infectiousPeriod = infectiousPeriodDays;
    mortalityRate = fatalityRate;
}

void DiseaseSpreadModel::setInitialConditions(int initialInfections)
{
    initialInfected = initialInfections;
}

void DiseaseSpreadModel::setInterventionMeasures(double socialDistancingFactor, double vaccinationRate, int vaccinationStartDay)
{
    socialDistancing = socialDistancingFactor;
    vaccineRate = vaccinationRate;
    vaccineDay = vaccinationStartDay;
}

bool DiseaseSpreadModel::runSimulation(int daysToSimulate)
{
    susceptible.clear();
    infected.clear();
    recovered.clear();
    deaths.clear();
    double S = population - initialInfected;
    double I = initialInfected;
    double R = 0;
    double D = 0;

    susceptible.append(S);
    infected.append(I);
    recovered.append(R);
    deaths.append(D);
    double baseTransmissionRate = reproductionNumber / infectiousPeriod;
    for (int day = 1; day <= daysToSimulate; day++) {
        double adjustedTransmissionRate = baseTransmissionRate *
                                          (1.0 - adjustForInterventions(socialDistancing, day));

        if (day >= vaccineDay) {
            double newVaccinated = S * (vaccineRate / 100.0);
            S -= newVaccinated;
            R += newVaccinated;
        }
        double newInfected = adjustedTransmissionRate * S * (I / population) * (1.0 + density/100.0);
        double newRecovered = (I / infectiousPeriod) * (1.0 - mortalityRate);
        double newDeaths = (I / infectiousPeriod) * mortalityRate;

        S -= newInfected;
        I += newInfected - newRecovered - newDeaths;
        R += newRecovered;
        D += newDeaths;
        S = qMax(0.0, S);
        I = qMax(0.0, I);
        R = qMax(0.0, R);
        susceptible.append(S);
        infected.append(I);
        recovered.append(R);
        deaths.append(D);
    }

    return true;
}

QVector<double> DiseaseSpreadModel::getSusceptibleCurve() const
{
    return susceptible;
}

QVector<double> DiseaseSpreadModel::getInfectedCurve() const
{
    return infected;
}

QVector<double> DiseaseSpreadModel::getRecoveredCurve() const
{
    return recovered;
}

QVector<double> DiseaseSpreadModel::getDeathsCurve() const
{
    return deaths;
}

int DiseaseSpreadModel::getDaysToPeak() const
{
    if (infected.isEmpty()) return -1;

    int peakDay = 0;
    double peakValue = infected[0];

    for (int i = 1; i < infected.size(); i++) {
        if (infected[i] > peakValue) {
            peakValue = infected[i];
            peakDay = i;
        }
    }

    return peakDay;
}

int DiseaseSpreadModel::getDaysToThreshold(double infectionRateThreshold) const
{
    if (infected.isEmpty()) return -1;

    double threshold = population * (infectionRateThreshold / 100.0);

    for (int i = 0; i < infected.size(); i++) {
        if (infected[i] >= threshold) {
            return i;
        }
    }

    return -1;
}

int DiseaseSpreadModel::getTotalInfections() const
{
    if (recovered.isEmpty() || deaths.isEmpty()) return 0;
    return recovered.last() + deaths.last();
}

QString DiseaseSpreadModel::recommendedBSLLevel() const
{
    if (infected.isEmpty()) return "Unknown";
    double peakInfection = 0;
    for (double i : infected) {
        peakInfection = qMax(peakInfection, i);
    }
    double peakRate = (peakInfection / population) * 100.0;
    int daysTo1Percent = getDaysToThreshold(1.0);
    double spreadRate = daysTo1Percent > 0 ? 1.0 / daysTo1Percent : 1.0;

    return determineBSLLevel(peakRate, spreadRate);
}

QString DiseaseSpreadModel::getAnalysisSummary() const
{
    if (infected.isEmpty()) return "No simulation data available. Please run a simulation first.";

    int peakDay = getDaysToPeak();
    double peakInfections = infected[peakDay];
    double peakPercentage = (peakInfections / population) * 100.0;
    int totalInfected = getTotalInfections();
    double totalPercentage = (totalInfected / population) * 100.0;

    QString summary = QString("Region: %1\n\n").arg(regionName);
    summary += QString("Population: %1\n\n").arg(int(population));
    summary += QString("Disease Parameters:\n");
    summary += QString("- R0 Value: %1\n").arg(reproductionNumber, 0, 'f', 2);
    summary += QString("- Incubation Period: %1 days\n").arg(incubationPeriod);
    summary += QString("- Infectious Period: %1 days\n\n").arg(infectiousPeriod);

    summary += QString("Simulation Results:\n");
    summary += QString("- Peak Infections: Day %1 with %2 cases (%3% of population)\n")
                   .arg(peakDay)
                   .arg(int(peakInfections))
                   .arg(peakPercentage, 0, 'f', 2);
    summary += QString("- Total Infections: %1 (%2% of population)\n")
                   .arg(int(totalInfected))
                   .arg(totalPercentage, 0, 'f', 2);
    summary += QString("- Estimated Deaths: %1 (%2% of population)\n\n")
                   .arg(int(deaths.last()))
                   .arg((deaths.last() / population) * 100.0, 0, 'f', 3);

    summary += QString("Recommended Biosafety Level: %1\n\n").arg(recommendedBSLLevel());

    summary += "BSL Level Explanation:\n";
    if (recommendedBSLLevel() == "BSL-1") {
        summary += "BSL-1 is appropriate for work with well-characterized agents not known to consistently cause disease in immunocompetent adult humans, and present minimal potential hazard to laboratory personnel and the environment.";
    } else if (recommendedBSLLevel() == "BSL-2") {
        summary += "BSL-2 is suitable for work involving agents that pose moderate hazards to personnel and the environment. It differs from BSL-1 in that laboratory personnel have specific training in handling pathogenic agents.";
    } else if (recommendedBSLLevel() == "BSL-3") {
        summary += "BSL-3 is applicable to clinical, diagnostic, teaching, research, or production facilities where work is performed with indigenous or exotic agents that may cause serious or potentially lethal disease through respiratory transmission.";
    } else if (recommendedBSLLevel() == "BSL-4") {
        summary += "BSL-4 is required for work with dangerous and exotic agents that pose a high individual risk of aerosol-transmitted laboratory infections and life-threatening disease that is frequently fatal, for which there are no vaccines or treatments.";
    }

    return summary;
}

double DiseaseSpreadModel::adjustForInterventions(double rate, int day) const
{
    if (day < 7) return 0;
    return rate * (1.0 - 1.0 / (1.0 + qExp(0.1 * (day - 14))));
}

QString DiseaseSpreadModel::determineBSLLevel(double peakInfectionRate, double spreadRate) const
{
    const double BSL2_PEAK_THRESHOLD = 5.0;
    const double BSL3_PEAK_THRESHOLD = 20.0;
    const double BSL4_PEAK_THRESHOLD = 40.0;

    const double BSL2_SPREAD_THRESHOLD = 0.05;
    const double BSL3_SPREAD_THRESHOLD = 0.1;
    const double BSL4_SPREAD_THRESHOLD = 0.2;

    if (peakInfectionRate >= BSL4_PEAK_THRESHOLD || spreadRate >= BSL4_SPREAD_THRESHOLD) {
        return "BSL-4";
    } else if (peakInfectionRate >= BSL3_PEAK_THRESHOLD || spreadRate >= BSL3_SPREAD_THRESHOLD) {
        return "BSL-3";
    } else if (peakInfectionRate >= BSL2_PEAK_THRESHOLD || spreadRate >= BSL2_SPREAD_THRESHOLD) {
        return "BSL-2";
    } else {
        return "BSL-1";
    }
}
