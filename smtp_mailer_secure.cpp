#include "smtp_mailer_secure.h"
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QDebug>

SmtpMailerSecure::SmtpMailerSecure(QObject *parent) : QObject(parent)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::connected, this, &SmtpMailerSecure::onConnected);
    connect(socket, &QSslSocket::readyRead, this, &SmtpMailerSecure::onReadyRead);
    connect(socket, &QSslSocket::encrypted, this, &SmtpMailerSecure::onEncrypted);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QSslSocket::errorOccurred),
            this, &SmtpMailerSecure::onError);
}

void SmtpMailerSecure::sendMail(const QString &from, const QString &to, const QString &subject,
                                const QString &body, const QString &filePath,
                                const QString &smtpServer, int port,
                                const QString &username, const QString &password)
{
    this->from = from;
    this->to = to;
    this->subject = subject;
    this->body = body;
    this->filePath = filePath;
    this->username = username;
    this->password = password;
    this->currentStep = 0;

    socket->connectToHostEncrypted(smtpServer, port);
}

void SmtpMailerSecure::onConnected()
{
    qDebug() << "Connected to SMTP server (waiting for encryption)...";
}

void SmtpMailerSecure::onEncrypted()
{
    qDebug() << "SSL encryption established.";
}

void SmtpMailerSecure::onReadyRead()
{
    while (socket->canReadLine()) {
        QString response = socket->readLine();
        qDebug() << "SMTP >>" << response.trimmed();

        if (response.startsWith("220") && currentStep == 0) {
            socket->write("EHLO localhost\r\n");
            currentStep++;
        }
        else if (response.startsWith("250") && currentStep == 1) {
            socket->write("AUTH LOGIN\r\n");
            currentStep++;
        }
        else if (response.startsWith("334") && currentStep == 2) {
            socket->write(username.toUtf8().toBase64() + "\r\n");
            currentStep++;
        }
        else if (response.startsWith("334") && currentStep == 3) {
            socket->write(password.toUtf8().toBase64() + "\r\n");
            currentStep++;
        }
        else if (response.startsWith("235") && currentStep == 4) {
            socket->write("MAIL FROM:<" + from.toUtf8() + ">\r\n");
            currentStep++;
        }
        else if (response.startsWith("250") && currentStep == 5) {
            socket->write("RCPT TO:<" + to.toUtf8() + ">\r\n");
            currentStep++;
        }
        else if (response.startsWith("250") && currentStep == 6) {
            socket->write("DATA\r\n");
            currentStep++;
        }
        else if (response.startsWith("354") && currentStep == 7) {
            QFile file(filePath);
            file.open(QIODevice::ReadOnly);
            QString filename = QFileInfo(filePath).fileName();
            QByteArray attachment = file.readAll().toBase64();
            file.close();

            QString boundary = "frontier";

            QString data;
            data += "From: <" + from + ">\r\n";
            data += "To: <" + to + ">\r\n";
            data += "Subject: " + subject + "\r\n";
            data += "MIME-Version: 1.0\r\n";
            data += "Content-Type: multipart/mixed; boundary=" + boundary + "\r\n\r\n";
            data += "--" + boundary + "\r\n";
            data += "Content-Type: text/plain; charset=\"UTF-8\"\r\n\r\n";
            data += body + "\r\n\r\n";
            data += "--" + boundary + "\r\n";
            data += "Content-Type: image/svg+xml; name=\"" + filename + "\"\r\n";
            data += "Content-Transfer-Encoding: base64\r\n";
            data += "Content-Disposition: attachment; filename=\"" + filename + "\"\r\n\r\n";
            data += QString(attachment) + "\r\n";
            data += "--" + boundary + "--\r\n.\r\n";

            socket->write(data.toUtf8());
            currentStep++;
        }
        else if (response.startsWith("250") && currentStep == 8) {
            socket->write("QUIT\r\n");
            currentStep++;
        }
        else if (response.startsWith("221") && currentStep == 9) {
            qDebug() << "Email sent successfully!";
            socket->disconnectFromHost();
        }
    }
}



void SmtpMailerSecure::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << socket->errorString();
}
