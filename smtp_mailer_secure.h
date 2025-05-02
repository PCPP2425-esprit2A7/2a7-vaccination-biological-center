#ifndef SMTP_MAILER_SECURE_H
#define SMTP_MAILER_SECURE_H

#include <QObject>
#include <QSslSocket>

class SmtpMailerSecure : public QObject
{
    Q_OBJECT

public:
    explicit SmtpMailerSecure(QObject *parent = nullptr);
    void sendMail(const QString &from, const QString &to, const QString &subject,
                  const QString &body, const QString &filePath,
                  const QString &smtpServer, int port,
                  const QString &username, const QString &password);

private slots:
    void onReadyRead();
    void onConnected();
    void onEncrypted();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QSslSocket *socket;
    QString from, to, subject, body, filePath, username, password;
    int currentStep = 0;
};

#endif // SMTP_MAILER_SECURE_H
