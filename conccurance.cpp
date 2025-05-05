#include "conccurance.h"

Conccurance::Conccurance(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &Conccurance::onReplyFinished);
    //Dès que manager reçoit une réponse réseau complète, appelle la méthode onReplyFinished(...) sur cet objet (this), en lui passant la réponse
}

void Conccurance::analyserConcurrence(const QString &type, const QString &maladie, const QString &description, const QStringList &descriptionsConcurrents)
{
    QUrl url("");
    QNetworkRequest request(url); //Crée une requête réseau HTTP en se basant sur l’URL spécifiée juste avant.
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");  //Indique que le contenu envoyé sera en JSON.
    request.setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());

    QString prompt = QString(
                         "Tu es un expert en biotechnologie.\n"
                         "Voici un vaccin sélectionné :\n"
                         "- Type : %1\n"
                         "- Maladie : %2\n"
                         "- Description : %3\n\n"
                         "Voici les autres vaccins enregistrés dans notre base de données :\n")
                         .arg(type, maladie, description);

    for (const QString &desc : descriptionsConcurrents) {
        prompt += desc + "\n";
    }

    prompt += "\nAnalyse les descriptions et  indique uniquement les vaccins qui peuvent être considérés comme de véritables concurrents directs du vaccin sélectionné, en excluant ceux qui ciblent un public très différent (comme les enfants uniquement) ou qui utilisent une méthode d'administration radicalement différente. "
              "avec pour chacun :\n"
              "- Le **nom du vaccin**\n"
              "- Une **explication brève** (par exemple : même type, cible la même maladie, description similaire).\n"
              "Sois précis et professionnel.";


    QJsonObject message;
    message["role"] = "user";
    message["content"] = prompt;

    QJsonArray messages; //Crée un tableau JSON nommé messages qui contiendra un ou plusieurs messages.
    messages.append(message); //Ajoute l’objet message (celui qu’on vient de créer) au tableau messages.

    QJsonObject payload;
    payload["model"] = "gpt-3.5-turbo";
    payload["messages"] = messages;
    payload["temperature"] = 0.7;
    QJsonDocument doc(payload); //Crée un QJsonDocument à partir de l’objet JSON payload
    QByteArray data = doc.toJson();//Convertit le document JSON en une séquence de bytes (QByteArray) à envoyer dans la requête HTTP.
    manager->post(request, data);  //cette requete sert rellement a envoier la requete

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

    QJsonDocument doc = QJsonDocument::fromJson(response); //On transforme la réponse JSON brute en un doc JSON qu’on peut parcourir.
    QString result = doc["choices"].toArray()[0].toObject()["message"].toObject()["content"].toString();

    emit analysisReady(result); //emit est utilisé pour envoyer un signal dans Qt.
    reply->deleteLater();
}
