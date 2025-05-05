#include "serialhandler.h"
#include <QDebug>

SerialHandler::SerialHandler(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);

    // Choose your port name (e.g., COM3 on Windows, /dev/ttyUSB0 on Linux)
    serial->setPortName("COM9"); // <--- Change this to your Arduino's port
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened!";
        connect(serial, &QSerialPort::readyRead, this, &SerialHandler::readSerial);
    } else {
        qDebug() << "Failed to open serial port:" << serial->errorString();
    }
}

