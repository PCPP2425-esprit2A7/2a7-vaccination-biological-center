#include "PredictionModel.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QUrlQuery>
#include <QEventLoop>

PredictionModel::PredictionModel()
{
}

bool PredictionModel::logStatusChange(int equipmentId, const QString &oldStatus,
                                      const QString &newStatus, const QString &reason)
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO EQUIPMENT_HISTORY (IDEQ, OLD_STATUS, NEW_STATUS, REASON) "
                      "VALUES (:equipmentId, :oldStatus, :newStatus, :reason)");
        query.bindValue(":equipmentId", equipmentId);
        query.bindValue(":oldStatus", oldStatus);
        query.bindValue(":newStatus", newStatus);
        query.bindValue(":reason", reason);

        if (query.exec()) {
            qDebug() << "Status change logged successfully for equipment ID:" << equipmentId;

            // If equipment becomes damaged, consider generating an order
            if (newStatus == "Damaged") {
                // Check if we should place an order
                QPair<QString, QString> details = getEquipmentDetails(equipmentId);
                QString supplierPhone = getSupplierPhone(equipmentId);

                if (!supplierPhone.isEmpty()) {
                    QString message = createOrderMessage(equipmentId, details.first, details.second, 1);
                    return sendWhatsAppMessage(supplierPhone, message);
                }
            }

            return true;
        } else {
            qDebug() << "Failed to log status change:" << query.lastError().text();
            return false;
        }
    } else {
        qDebug() << "Failed to open database for logging status change";
        return false;
    }
}

QMap<int, QDate> PredictionModel::predictFailures()
{
    QMap<int, QDate> predictions;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // Get all currently functional equipment
        QSqlQuery equipmentQuery(db);
        equipmentQuery.prepare("SELECT IDEQ, TYPEEQ FROM EQUIPEMENTS WHERE ETATEQ = 'Functional'");

        if (equipmentQuery.exec()) {
            // For each equipment, calculate predicted failure date based on equipment type's MTBF
            while (equipmentQuery.next()) {
                int equipmentId = equipmentQuery.value(0).toInt();
                QString equipmentType = equipmentQuery.value(1).toString();

                // Calculate average days until failure for this type of equipment
                int avgDaysToFailure = calculateAverageDaysToFailure(equipmentType);

                if (avgDaysToFailure > 0) {
                    // Get the last maintenance date or installation date
                    QSqlQuery lastMaintenanceQuery(db);
                    lastMaintenanceQuery.prepare(
                        "SELECT MAX(CHANGE_DATE) FROM EQUIPMENT_HISTORY "
                        "WHERE IDEQ = :equipmentId AND "
                        "(NEW_STATUS = 'Functional' OR OLD_STATUS = 'Damaged')");
                    lastMaintenanceQuery.bindValue(":equipmentId", equipmentId);

                    QDate lastMaintenance = QDate::currentDate(); // Default to today if no record

                    if (lastMaintenanceQuery.exec() && lastMaintenanceQuery.next() &&
                        !lastMaintenanceQuery.value(0).isNull()) {
                        lastMaintenance = lastMaintenanceQuery.value(0).toDate();
                    }

                    // Calculate predicted failure date
                    QDate predictedFailure = lastMaintenance.addDays(avgDaysToFailure);

                    // Save the prediction
                    predictions[equipmentId] = predictedFailure;

                    // Update the predicted failure date in the database for this equipment
                    QSqlQuery updateQuery(db);
                    updateQuery.prepare(
                        "UPDATE EQUIPEMENTS SET PREDICTED_FAILURE = TO_DATE(:failureDate, 'YYYY-MM-DD') "
                        "WHERE IDEQ = :equipmentId");
                    updateQuery.bindValue(":failureDate", predictedFailure.toString("yyyy-MM-dd"));
                    updateQuery.bindValue(":equipmentId", equipmentId);

                    if (!updateQuery.exec()) {
                        qDebug() << "Failed to update predicted failure date:" << updateQuery.lastError().text();
                    }
                }
            }
        } else {
            qDebug() << "Failed to query equipment:" << equipmentQuery.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for failure prediction";
    }

    return predictions;
}

QVector<QPair<int, QDate>> PredictionModel::getEquipmentAtRisk(int daysThreshold)
{
    QVector<QPair<int, QDate>> atRiskEquipment;
    QDate thresholdDate = QDate::currentDate().addDays(daysThreshold);

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT IDEQ, TO_CHAR(PREDICTED_FAILURE, 'YYYY-MM-DD') "
                      "FROM EQUIPEMENTS "
                      "WHERE ETATEQ = 'Functional' AND "
                      "PREDICTED_FAILURE <= TO_DATE(:thresholdDate, 'YYYY-MM-DD') "
                      "ORDER BY PREDICTED_FAILURE ASC");
        query.bindValue(":thresholdDate", thresholdDate.toString("yyyy-MM-dd"));

        if (query.exec()) {
            while (query.next()) {
                int equipmentId = query.value(0).toInt();
                QDate failureDate = QDate::fromString(query.value(1).toString(), "yyyy-MM-dd");

                atRiskEquipment.append(qMakePair(equipmentId, failureDate));
            }
        } else {
            qDebug() << "Failed to query at-risk equipment:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for at-risk equipment query";
    }

    return atRiskEquipment;
}

bool PredictionModel::generateOrders()
{
    bool success = true;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // Get all damaged equipment that hasn't been ordered yet
        QSqlQuery damagedQuery(db);
        damagedQuery.prepare("SELECT IDEQ, NOMEQ, TYPEEQ, NBEQ FROM EQUIPEMENTS "
                             "WHERE ETATEQ = 'Damaged' AND NOT EXISTS ("
                             "  SELECT 1 FROM EQUIPMENT_HISTORY "
                             "  WHERE EQUIPMENT_HISTORY.IDEQ = EQUIPEMENTS.IDEQ "
                             "  AND REASON = 'Order placed'"
                             ")");

        if (damagedQuery.exec()) {
            while (damagedQuery.next()) {
                int equipmentId = damagedQuery.value(0).toInt();
                QString equipmentName = damagedQuery.value(1).toString();
                QString equipmentType = damagedQuery.value(2).toString();
                int quantity = damagedQuery.value(3).toInt();

                // Get supplier phone
                QString supplierPhone = getSupplierPhone(equipmentId);

                if (!supplierPhone.isEmpty()) {
                    // Create order message
                    QString message = createOrderMessage(equipmentId, equipmentName,
                                                         equipmentType, quantity);

                    // Send WhatsApp message
                    bool messageSent = sendWhatsAppMessage(supplierPhone, message);

                    if (messageSent) {
                        // Log the order in history
                        logStatusChange(equipmentId, "Damaged", "Damaged", "Order placed");
                    } else {
                        success = false;
                        qDebug() << "Failed to send order message for equipment ID:" << equipmentId;
                    }
                } else {
                    success = false;
                    qDebug() << "No supplier phone found for equipment ID:" << equipmentId;
                }
            }
        } else {
            success = false;
            qDebug() << "Failed to query damaged equipment:" << damagedQuery.lastError().text();
        }
    } else {
        success = false;
        qDebug() << "Failed to open database for generating orders";
    }

    return success;
}

int PredictionModel::calculateMTBF(int equipmentId)
{
    int mtbf = 0;
    int totalDays = 0;
    int failureCount = 0;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT h1.CHANGE_DATE, h2.CHANGE_DATE "
                      "FROM EQUIPMENT_HISTORY h1 "
                      "JOIN EQUIPMENT_HISTORY h2 ON h1.IDEQ = h2.IDEQ "
                      "WHERE h1.IDEQ = :equipmentId "
                      "AND h1.NEW_STATUS = 'Functional' "
                      "AND h2.NEW_STATUS = 'Damaged' "
                      "AND h2.CHANGE_DATE > h1.CHANGE_DATE "
                      "AND NOT EXISTS ("
                      "  SELECT 1 FROM EQUIPMENT_HISTORY h3 "
                      "  WHERE h3.IDEQ = h1.IDEQ "
                      "  AND h3.CHANGE_DATE > h1.CHANGE_DATE "
                      "  AND h3.CHANGE_DATE < h2.CHANGE_DATE"
                      ")");
        query.bindValue(":equipmentId", equipmentId);

        if (query.exec()) {
            while (query.next()) {
                QDate startDate = query.value(0).toDate();
                QDate endDate = query.value(1).toDate();

                int days = startDate.daysTo(endDate);
                totalDays += days;
                failureCount++;
            }

            if (failureCount > 0) {
                mtbf = totalDays / failureCount;
            }
        } else {
            qDebug() << "Failed to calculate MTBF:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for MTBF calculation";
    }

    return mtbf;
}

int PredictionModel::calculateTypeMTBF(const QString &equipmentType)
{
    int mtbf = 0;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // Get all equipment of this type
        QSqlQuery equipmentQuery(db);
        equipmentQuery.prepare("SELECT IDEQ FROM EQUIPEMENTS WHERE TYPEEQ = :equipmentType");
        equipmentQuery.bindValue(":equipmentType", equipmentType);

        int totalDays = 0;
        int totalFailures = 0;

        if (equipmentQuery.exec()) {
            while (equipmentQuery.next()) {
                int equipmentId = equipmentQuery.value(0).toInt();
                int equipmentMTBF = calculateMTBF(equipmentId);

                if (equipmentMTBF > 0) {
                    // Count the failures for this equipment
                    QSqlQuery failureQuery(db);
                    failureQuery.prepare("SELECT COUNT(*) FROM EQUIPMENT_HISTORY "
                                         "WHERE IDEQ = :equipmentId AND NEW_STATUS = 'Damaged'");
                    failureQuery.bindValue(":equipmentId", equipmentId);

                    if (failureQuery.exec() && failureQuery.next()) {
                        int failures = failureQuery.value(0).toInt();
                        totalFailures += failures;
                        totalDays += equipmentMTBF * failures;
                    }
                }
            }

            if (totalFailures > 0) {
                mtbf = totalDays / totalFailures;
            }
        } else {
            qDebug() << "Failed to query equipment for type MTBF:" << equipmentQuery.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for type MTBF calculation";
    }

    return mtbf;
}

bool PredictionModel::recordMaintenance(int equipmentId, double cost, const QString &details)
{
    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        // First, get current status
        QSqlQuery statusQuery(db);
        statusQuery.prepare("SELECT ETATEQ FROM EQUIPEMENTS WHERE IDEQ = :equipmentId");
        statusQuery.bindValue(":equipmentId", equipmentId);

        if (statusQuery.exec() && statusQuery.next()) {
            QString currentStatus = statusQuery.value(0).toString();

            // Record maintenance in history
            QSqlQuery maintenanceQuery(db);
            maintenanceQuery.prepare("INSERT INTO EQUIPMENT_HISTORY "
                                     "(IDEQ, OLD_STATUS, NEW_STATUS, REASON, MAINTENANCE_COST, REPAIR_DETAILS) "
                                     "VALUES (:equipmentId, :oldStatus, 'Functional', 'Maintenance performed', "
                                     ":cost, :details)");
            maintenanceQuery.bindValue(":equipmentId", equipmentId);
            maintenanceQuery.bindValue(":oldStatus", currentStatus);
            maintenanceQuery.bindValue(":cost", cost);
            maintenanceQuery.bindValue(":details", details);

            if (maintenanceQuery.exec()) {
                // Update equipment status to Functional
                QSqlQuery updateQuery(db);
                updateQuery.prepare("UPDATE EQUIPEMENTS SET ETATEQ = 'Functional' WHERE IDEQ = :equipmentId");
                updateQuery.bindValue(":equipmentId", equipmentId);

                if (updateQuery.exec()) {
                    qDebug() << "Maintenance recorded successfully for equipment ID:" << equipmentId;
                    return true;
                } else {
                    qDebug() << "Failed to update equipment status:" << updateQuery.lastError().text();
                }
            } else {
                qDebug() << "Failed to record maintenance:" << maintenanceQuery.lastError().text();
            }
        } else {
            qDebug() << "Failed to get current status:" << statusQuery.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for maintenance recording";
    }

    return false;
}

int PredictionModel::calculateAverageDaysToFailure(const QString &equipmentType)
{
    int avgDays = 0;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);

        // Get all transitions from Functional to Damaged for this equipment type
        query.prepare(
            "SELECT AVG(h2.CHANGE_DATE - h1.CHANGE_DATE) AS avg_days "
            "FROM EQUIPMENT_HISTORY h1 "
            "JOIN EQUIPMENT_HISTORY h2 ON h1.IDEQ = h2.IDEQ "
            "JOIN EQUIPEMENTS e ON e.IDEQ = h1.IDEQ "
            "WHERE e.TYPEEQ = :equipmentType "
            "AND h1.NEW_STATUS = 'Functional' "
            "AND h2.NEW_STATUS = 'Damaged' "
            "AND h2.CHANGE_DATE > h1.CHANGE_DATE "
            "AND NOT EXISTS ("
            "  SELECT 1 FROM EQUIPMENT_HISTORY h3 "
            "  WHERE h3.IDEQ = h1.IDEQ "
            "  AND h3.CHANGE_DATE > h1.CHANGE_DATE "
            "  AND h3.CHANGE_DATE < h2.CHANGE_DATE"
            ")"
            );
        query.bindValue(":equipmentType", equipmentType);

        if (query.exec() && query.next() && !query.value(0).isNull()) {
            avgDays = query.value(0).toInt();

            // If we don't have enough data, use a default value
            if (avgDays <= 0) {
                // Default values based on equipment type
                if (equipmentType == "Machine") {
                    avgDays = 180; // 6 months for machines
                } else if (equipmentType == "Consomable") {
                    avgDays = 90;  // 3 months for consumables
                } else {
                    avgDays = 120; // 4 months default
                }
            }
        } else {
            // No data available, use defaults
            if (equipmentType == "Machine") {
                avgDays = 180; // 6 months for machines
            } else if (equipmentType == "Consomable") {
                avgDays = 90;  // 3 months for consumables
            } else {
                avgDays = 120; // 4 months default
            }

            qDebug() << "No failure data available for equipment type:" << equipmentType
                     << ". Using default value:" << avgDays << "days";
        }
    } else {
        qDebug() << "Failed to open database for average days calculation";
    }

    return avgDays;
}

bool PredictionModel::sendWhatsAppMessage(const QString &to, const QString &message)
{
    // This is a placeholder for WhatsApp Business API integration
    // In a real implementation, you would use the Twilio API or similar

    qDebug() << "Sending WhatsApp message to:" << to;
    qDebug() << "Message content:" << message;

    // Simulate successful message sending
    return true;

    /*
    // Example of how to implement with Twilio API
    QNetworkAccessManager manager;
    QEventLoop loop;

    // Set up request to Twilio API
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/YOUR_ACCOUNT_SID/Messages.json");
    QNetworkRequest request(url);

    // Set authentication header (Basic Auth)
    QString credentials = "YOUR_ACCOUNT_SID:YOUR_AUTH_TOKEN";
    QByteArray auth = "Basic " + credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", auth);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Prepare form data
    QUrlQuery postData;
    postData.addQueryItem("From", "whatsapp:+14155238886"); // Your Twilio WhatsApp number
    postData.addQueryItem("To", "whatsapp:" + to);
    postData.addQueryItem("Body", message);

    // Send POST request
    QNetworkReply *reply = manager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    // Connect to reply finished signal
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    // Execute loop until reply is finished
    loop.exec();

    // Check for errors
    if (reply->error() == QNetworkReply::NoError) {
        // Read response
        QString response = reply->readAll();
        qDebug() << "Message sent successfully:" << response;
        reply->deleteLater();
        return true;
    } else {
        // Handle error
        qDebug() << "Error sending message:" << reply->errorString();
        reply->deleteLater();
        return false;
    }
    */
}

QString PredictionModel::getSupplierPhone(int equipmentId)
{
    QString phone;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT FEQ FROM EQUIPEMENTS WHERE IDEQ = :equipmentId");
        query.bindValue(":equipmentId", equipmentId);

        if (query.exec() && query.next()) {
            phone = query.value(0).toString();
        } else {
            qDebug() << "Failed to get supplier phone:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for supplier phone query";
    }

    return phone;
}

QPair<QString, QString> PredictionModel::getEquipmentDetails(int equipmentId)
{
    QString name;
    QString type;

    connection c;
    QSqlDatabase db = c.get_database();

    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT NOMEQ, TYPEEQ FROM EQUIPEMENTS WHERE IDEQ = :equipmentId");
        query.bindValue(":equipmentId", equipmentId);

        if (query.exec() && query.next()) {
            name = query.value(0).toString();
            type = query.value(1).toString();
        } else {
            qDebug() << "Failed to get equipment details:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database for equipment details query";
    }

    return qMakePair(name, type);
}

QString PredictionModel::createOrderMessage(int equipmentId, const QString &equipmentName,
                                            const QString &equipmentType, int quantity)
{
    return QString("AUTOMATED ORDER REQUEST\n\n"
                   "Equipment ID: %1\n"
                   "Name: %2\n"
                   "Type: %3\n"
                   "Quantity: %4\n\n"
                   "Status: DAMAGED - Requires Replacement\n"
                   "Requested Date: %5\n\n"
                   "This is an automated message from your Equipment Management System.")
        .arg(equipmentId)
        .arg(equipmentName)
        .arg(equipmentType)
        .arg(quantity)
        .arg(QDate::currentDate().toString("yyyy-MM-dd"));
}
