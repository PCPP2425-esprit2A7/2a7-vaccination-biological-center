#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QString>

    class Arduino {
public:
    Arduino();
    ~Arduino();

    // Public methods
    int connect_arduino();               // Connect PC to Arduino
    int close_arduino();                 // Close the connection
    void write_to_arduino(QByteArray data); // Send data to Arduino
    QByteArray read_from_arduino();      // Receive data from Arduino
    QSerialPort* getserial();            // Serial port accessor
    QString getarduino_port_name();       // Get port name
private:
    QSerialPort* serial;                 // Serial port object
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;                     // Data read from Arduino
};

#endif // ARDUINO_H
