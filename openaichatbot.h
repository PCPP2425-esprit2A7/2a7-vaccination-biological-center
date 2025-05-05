#ifndef OPENAICHATBOT_H
#define OPENAICHATBOT_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QList>
#include <QPair>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QTemporaryFile>

class OpenAIChatBot {
public:
    OpenAIChatBot(const QString &token);
    ~OpenAIChatBot();
    QString getResponse(const QString &userMessage, const QString &currentDescription = "");
    QString analyzeDescription(const QString &description);
    QString generateDescription(const QString &context);
    QString updateDescription(const QString &currentDescription, const QString &newInfo);
    void setSystemPrompt(const QString &prompt);
    void clearConversation();
    QList<QPair<QString, QString>> getConversationHistory() const;

private:
    struct Message {
        QString role;
        QString content;


        bool operator==(const Message &other) const {
            return role == other.role && content == other.content;
        }
    };

    QString token;
    QString systemPrompt;
    QList<Message> messageHistory;
    QNetworkAccessManager *networkManager;


    QJsonObject createChatCompletionRequest(const QList<Message> &messages);
    QString sendRequest(const QJsonObject &requestData);
    QString extractResponseFromReply(QNetworkReply *reply);


    void addMessageToHistory(const QString &role, const QString &content);
    QString parseJsonResponse(const QByteArray &jsonData);
};

#endif // OPENAICHATBOT_H
