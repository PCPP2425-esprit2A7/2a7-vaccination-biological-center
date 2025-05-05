#ifndef PREDICTIONMODEL_H
#define PREDICTIONMODEL_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QList>
#include <QPair>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include "connection.h"

class PredictionModel
{
public:
    PredictionModel();

    // Log a status change to the history table
    bool logStatusChange(int equipmentId, const QString &oldStatus,
                         const QString &newStatus, const QString &reason = "");

    // Predict when equipment will likely fail based on history
    QMap<int, QDate> predictFailures();

    // Get equipment predicted to fail within the specified days
    QVector<QPair<int, QDate>> getEquipmentAtRisk(int daysThreshold);

    // Generate and send order message via WhatsApp for damaged equipment
    bool generateOrders();

    // Calculate the mean time between failures for a specific equipment
    int calculateMTBF(int equipmentId);

    // Calculate the mean time between failures for an equipment type
    int calculateTypeMTBF(const QString &equipmentType);

    // Record a maintenance event
    bool recordMaintenance(int equipmentId, double cost, const QString &details);

private:
    // Calculate average days between transitions from "Functional" to "Damaged"
    int calculateAverageDaysToFailure(const QString &equipmentType);

    // Send WhatsApp message using Twilio API
    bool sendWhatsAppMessage(const QString &to, const QString &message);

    // Get supplier phone for a specific equipment
    QString getSupplierPhone(int equipmentId);

    // Get details about equipment
    QPair<QString, QString> getEquipmentDetails(int equipmentId); // Returns <Name, Type>

    // Create an order message template
    QString createOrderMessage(int equipmentId, const QString &equipmentName,
                               const QString &equipmentType, int quantity);
};

#endif // PREDICTIONMODEL_H
