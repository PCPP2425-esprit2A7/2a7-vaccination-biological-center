#include "conccurance.h"

Conccurance::Conccurance(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &Conccurance::onReplyFinished);
}

void Conccurance::analyserConcurrence(const QString &type, const QString &maladie, const QString &description, const QStringList &descriptionsConcurrents)
{

}

void Conccurance::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit analysisReady("Erreur lors de la requête : " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    qDebug() << "Réponse brute de:\n" << QString(response); //afficher la reponse de l ai dans la sortie d app
    qDebug() << "Code HTTP:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); //On vérifie si l’ a répondu correctement (200), ou s’il y a eu une erreur serveur.

    QJsonDocument doc = QJsonDocument::fromJson(response); //On transforme la réponse JSON brute en un objet JSON qu’on peut parcourir.
    QString result = doc["choices"].toArray()[0].toObject()["message"].toObject()["content"].toString();

    emit analysisReady(result); //emit est utilisé pour envoyer un signal dans Qt.
    reply->deleteLater();
}
