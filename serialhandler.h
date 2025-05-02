#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialHandler : public QObject
{
    Q_OBJECT

public:
    explicit SerialHandler(QObject *parent = nullptr);
    void sendMessage(const QString &message);

signals:
    void rfidReceived(const QString &uid);

private slots:
    void readSerial();

private:
    QSerialPort *serial;
};

#endif // SERIALHANDLER_H
