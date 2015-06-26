#include "CommunicationThread.h"

#include <QDebug>

CommunicationThread::CommunicationThread(QObject *parent) :
    QThread(parent)
{
    comStopped = false;
}

void CommunicationThread::run()
{
    QSerialPort *serialPort = new QSerialPort;

    while(!comStopped)
    {
        if(comStopped && comOpened)
        {
            serialPort->close();
            comOpened = false;
            emit comOpenSts(false);
            qDebug() << "--@1st zone close port--";
        }
        if(!comOpened)
        {
            serialPort->setPortName(portNumber);
            bool lgOpenRet = serialPort->open(QIODevice::ReadWrite);
            if(lgOpenRet)
            {
                comOpened = true;
                qDebug() << "--Open" << portNumber << "success--";
                serialPort->setBaudRate(portSpeed);
                serialPort->setDataBits(dataLength);
                serialPort->setParity(parityBit);
                serialPort->setStopBits(stopBit);
                serialPort->setFlowControl(flowControl);
                emit comOpenSts(true);
            }
            else
            {
                comOpened = false;
                qDebug() << "--Fail to open" << portNumber << "--" << comStopped;
            }
        }
        if(comOpened && txEvent)
        {
            txEvent = false;
            serialPort->clear(QSerialPort::AllDirections);
            qDebug() << "---Send data :" << QString(TxData) << "from" << serialPort->portName() << "---";
            serialPort->write(TxData);
            if(serialPort->waitForBytesWritten(5))
            {
                qDebug() << "---Send data success---";
                if (serialPort->waitForReadyRead(150))
                {
                    requestData = serialPort->readAll();
                    while (serialPort->waitForReadyRead(15))
                    {
                        requestData += serialPort->readAll();
                    }
                    emit(this->comRecive());
                }
                else
                {
                    qDebug() << "---Wait return time out---";
                }
            }
            else
            {
                qDebug() << "---Send time out---";
            }
        }
        if(serialPort->waitForReadyRead(5))
        {
            while(serialPort->waitForReadyRead(5))
            {
                msleep(20);
            }
            requestData = serialPort->readAll();
            emit comRecive();
        }
        if(comStopped && comOpened)
        {
            serialPort->close();
            comOpened = false;
            emit comOpenSts(false);
            qDebug() << "--@2nd zone close port--";
        }
    }
    delete serialPort;
    qDebug() << "@CommunicationThread : serialPort destory!";
}

void CommunicationThread::stop()
{
    comStopped = true;
}

void CommunicationThread::startCom()
{
    comStopped = false;
    qDebug() << "--Thread starting--";
}

void CommunicationThread::changeTRState(bool state)
{
    comOpened = state;
}

void CommunicationThread::changeTxState(bool state)
{
    txEvent = state;
}

void CommunicationThread::changeRxState(bool state)
{
    rxEvent = state;
}

void CommunicationThread::setPortNo(const QString &number)
{
    portNumber = number;
}

void CommunicationThread::setPortSpeed(const QString &rate)
{
    //portSpeed = rate.toInt();
    portSpeed = atoi(rate.toStdString().c_str());
}

void CommunicationThread::setDataLen(const QString &len)
{
    dataLength = QSerialPort::DataBits(atoi(len.toStdString().c_str()));
}

void CommunicationThread::setParity(const QString &parity)
{
    parityBit = QSerialPort::Parity(atoi(parity.toStdString().c_str()));
}

void CommunicationThread::setStopBit(const QString &stop)
{
    if(stop == "1")
    {
        stopBit = QSerialPort::OneStop;
    }
    else if(stop == "1.5")
    {
        stopBit = QSerialPort::OneAndHalfStop;
    }
    else if(stop == "2")
    {
        stopBit = QSerialPort::TwoStop;
    }
    else
    {
        stopBit = QSerialPort::UnknownStopBits;
    }
}

void CommunicationThread::setFlowCtl(const QString &flow)
{
    flowControl = QSerialPort::FlowControl(atoi(flow.toStdString().c_str()));
}

void CommunicationThread::setMessage(const QString &msg)
{
    messages = msg;
}
