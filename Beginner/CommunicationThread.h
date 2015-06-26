#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class CommunicationThread : public QThread
{
    Q_OBJECT
public:
    explicit CommunicationThread(QObject *parent = 0);

    QByteArray requestData;
    QByteArray TxData;

    void setMessage(const QString &msg);
    void setPortNo(const QString &number = "COM1");
    void setPortSpeed(const QString &rate = QString::number(QSerialPort::Baud9600));
    void setDataLen(const QString &len = QString::number(QSerialPort::Data8));
    void setParity(const QString &parity = QString::number(QSerialPort::NoParity));
    void setStopBit(const QString &stop = QString::number(QSerialPort::OneStop));
    void setFlowCtl(const QString &flow = QString::number(QSerialPort::NoFlowControl));
    void stop();
    void startCom();
    void changeTxState(bool state);
    void changeRxState(bool state);
    void changeTRState(bool state);
    
protected:
    void run(void);

private:
public:
    QString messages;
    QString portNumber;
    int portSpeed;
    QSerialPort::DataBits dataLength;
    QSerialPort::Parity parityBit;
    QSerialPort::StopBits stopBit;
    QSerialPort::FlowControl flowControl;
    volatile bool comOpened;
    volatile bool comStopped;
    volatile bool txEvent;
    volatile bool rxEvent;

signals:
    void request(const QString &sReq);
    void comRecive(void);
    void comOpenSts(bool);
    
public slots:
    
};

#endif // COMMUNICATIONTHREAD_H
