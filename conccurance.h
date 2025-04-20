#ifndef CONCCURANCE_H
#define CONCCURANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Conccurance : public QObject
{
    Q_OBJECT

public:
    explicit Conccurance(QObject *parent = nullptr);
    void analyserConcurrence(const QString &type, const QString &maladie, const QString &description, const QStringList &descriptionsConcurrents);


signals:
    void analysisReady(const QString &result);  // Pour envoyer la réponse au GUI

private slots:
    void onReplyFinished(QNetworkReply *reply);

};

#endif // CONCCURANCE_H
