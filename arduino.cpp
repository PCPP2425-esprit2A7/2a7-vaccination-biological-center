#include "arduino.h"
#include "qdebug.h"

// Constructor
Arduino::Arduino() {
    serial = new QSerialPort();
    arduino_is_available = false;
    arduino_port_name = "";
}

// Destructor
Arduino::~Arduino() {
    if (serial->isOpen()) {
        serial->close();
    }
    delete serial;
}

// Connect to Arduino
int Arduino::connect_arduino() {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Found port:" << info.portName()
        << "Vendor ID:" << info.vendorIdentifier()
        << "Product ID:" << info.productIdentifier();
        if (info.vendorIdentifier() == arduino_uno_vendor_id &&
            info.productIdentifier() == arduino_uno_product_id) {
            arduino_port_name = info.portName();
            arduino_is_available = true;
        }
        arduino_port_name = info.portName();
        arduino_is_available = true;
        break;
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QIODevice::ReadWrite)) {
            serial->clear(QSerialPort::AllDirections);
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0; // Success
        }
        return 1; // Couldn't open port
    }
    return -1; // Arduino not found
}

// Close connection
int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

// Write data to Arduino
void Arduino::write_to_arduino(QByteArray data) {
    if (serial->isOpen()) {
        serial->write(data);
    }
}

// Read data from Arduino
QByteArray Arduino::read_from_arduino() {
    if (serial->isOpen()) {
        if (serial->waitForReadyRead(100)) {  // Increased timeout
            data = serial->readAll();
            while (serial->waitForReadyRead(50)) {
                data += serial->readAll();
            }
        }
    }
    return data;
}


// Accessors
QSerialPort* Arduino::getserial() {
    return serial;
}

QString Arduino::getarduino_port_name() {
    return arduino_port_name;
}
