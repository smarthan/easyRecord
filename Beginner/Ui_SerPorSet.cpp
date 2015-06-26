#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#include "Ui_SerPorSet.h"

Ui_SerPorSet::Ui_SerPorSet(QWidget *Widget)
{
    setWindowFlags(Qt::FramelessWindowHint);   /* 去除窗体边框 */
    setWindowModality(Qt::ApplicationModal);   /* 设置窗体模态，要求该窗体没有父类，否则无效 */
    //Attribute(Qt::WA_TranslucentBackground, true);   /* 设置边框阴影图片时用到 */
    setupWid(Widget);
}

void Ui_SerPorSet::setupWid(QWidget *Widget)
{
    if (Widget->objectName().isEmpty())
        Widget->setObjectName(QStringLiteral("Setting"));
    resize(640, 320);
    setFixedSize(this->width(), this->height());
    //setStyleSheet("background-color:#000000");
    /* 背景图片 */
    setAutoFillBackground(true);
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Window, QBrush(QPixmap(":/image/BK").scaled(this->size())));
    setPalette(bgPalette);

    widget = new QWidget(this);
    widget->setObjectName(QStringLiteral("Config"));
    widget->setGeometry(QRect(10, 10, 620, 300));

    groupBox_Com = new QGroupBox(widget);
    groupBox_Com->setObjectName(QStringLiteral("groupBox_Com"));
    groupBox_Com->setGeometry(10, 10, 260, 60);
    hLayoutWidget_Com = new QWidget(groupBox_Com);
    hLayoutWidget_Com->setObjectName(QStringLiteral("hLayoutWidget_Com"));
    hLayoutWidget_Com->setGeometry(10, 20, 240, 30);

    comboBox_ComPrt = new QComboBox(hLayoutWidget_Com);
    comboBox_ComSpd = new QComboBox(hLayoutWidget_Com);

    comboBox_ComPrt->setObjectName(QStringLiteral("comboBox_COMList"));
    comboBox_ComPrt->setEditable(false);

    QStringList strComSped = QStringList() << "110bps" << "300bps" << "600bps" << "1200bps" << "2400bps" << "4800bps" << "9600bps"
                                           << "14400bps" << "19200bps" << "38400bps" << "56000bps" << "57600bps" << "115200bps";
    comboBox_ComSpd->setObjectName(QStringLiteral("comboBox_COMRate"));
    comboBox_ComSpd->setEditable(false);
    comboBox_ComSpd->addItems(strComSped);
    comboBox_ComSpd->setCurrentIndex(6);

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
#ifndef QT_NO_DEBUG
        qDebug() << "Name           : " << info.portName();
//        qDebug() << "Description    : " << info.description();
//        qDebug() << "Manufacturer   : " << info.manufacturer();
//        qDebug() << "BaudRates      : " << info.standardBaudRates();
#endif
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            comboBox_ComPrt->insertItem(0, info.portName());
            serial.close();
        }
    }
    comboBox_ComPrt->setCurrentIndex(0);

    hBoxLayout_Com = new QHBoxLayout(hLayoutWidget_Com);
    hBoxLayout_Com->setSpacing(15);
    hBoxLayout_Com->setContentsMargins(0, 0, 0, 0);
    hBoxLayout_Com->setObjectName(QStringLiteral("hBoxLayout_Com"));
    hBoxLayout_Com->addWidget(comboBox_ComPrt);
    hBoxLayout_Com->addWidget(comboBox_ComSpd);

    /* Option */
    groupBox_Opt = new QGroupBox(widget);
    groupBox_Opt->setObjectName(QStringLiteral("groupBox_Opt"));
    groupBox_Opt->setGeometry(10, 90, 160, 190);
    vLayoutWidget_Tag = new QWidget(groupBox_Opt);  // 添加列表框标签
    vLayoutWidget_Tag->setObjectName(QStringLiteral("vLayoutWidget_Tag"));
    vLayoutWidget_Tag->setGeometry(10, 10, 80, 160);
    vLayoutWidget_Opt = new QWidget(groupBox_Opt);  // 串口选项列表框
    vLayoutWidget_Opt->setObjectName(QStringLiteral("hLayoutWidget_Opt"));
    vLayoutWidget_Opt->setGeometry(90, 10, 60, 160);

    label_OptDatLen = new QLabel(vLayoutWidget_Tag);
    label_OptStpBit = new QLabel(vLayoutWidget_Tag);
    label_OptParBit = new QLabel(vLayoutWidget_Tag);
    label_OptFlwCtl = new QLabel(vLayoutWidget_Tag);

    vBoxLayout_Tag = new QVBoxLayout(vLayoutWidget_Tag);
    vBoxLayout_Tag->setSpacing(5);
    vBoxLayout_Tag->setContentsMargins(0, 0, 0, 0);
    vBoxLayout_Tag->setObjectName(QStringLiteral("vBoxLayout_Tag"));
    vBoxLayout_Tag->addWidget(label_OptDatLen);
    vBoxLayout_Tag->addWidget(label_OptStpBit);
    vBoxLayout_Tag->addWidget(label_OptParBit);
    vBoxLayout_Tag->addWidget(label_OptFlwCtl);
    QFont font("Gadugi");
    font.setPointSize(10);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    label_OptDatLen->setFont(font);
    label_OptStpBit->setFont(font);
    label_OptParBit->setFont(font);
    label_OptFlwCtl->setFont(font);
    label_OptDatLen->setPalette(palette);
    label_OptStpBit->setPalette(palette);
    label_OptParBit->setPalette(palette);
    label_OptFlwCtl->setPalette(palette);

    comboBox_OptDatLen = new QComboBox(vLayoutWidget_Opt);
    comboBox_OptDatLen->setObjectName(QStringLiteral("comboBox_OptDatLen"));
    comboBox_OptDatLen->setEditable(false);
    comboBox_OptDatLen->addItems(QStringList() << "5" << "6" << "7" << "8");
    comboBox_OptDatLen->setCurrentIndex(3);

    comboBox_OptStpBit = new QComboBox(vLayoutWidget_Opt);
    comboBox_OptStpBit->setObjectName(QStringLiteral("comboBox_OptStpBit"));
    comboBox_OptStpBit->setEditable(false);
    comboBox_OptStpBit->addItems(QStringList() << "1" << "1.5" << "2");

    comboBox_OptParBit = new QComboBox(vLayoutWidget_Opt);
    comboBox_OptParBit->setObjectName(QStringLiteral("comboBox_OptParBit"));
    comboBox_OptParBit->setEditable(false);
    comboBox_OptParBit->addItems(QStringList() << "None" << "Even" << "Odd" << "Space" << "Mark");

    comboBox_OptFlwCtl = new QComboBox(vLayoutWidget_Opt);
    comboBox_OptFlwCtl->setObjectName(QStringLiteral("comboBox_OptFlwCtl"));
    comboBox_OptFlwCtl->setEditable(false);
    comboBox_OptFlwCtl->addItems(QStringList() << "OFF");

    vBoxLayout_Opt = new QVBoxLayout(vLayoutWidget_Opt);
    vBoxLayout_Opt->setSpacing(5);
    vBoxLayout_Opt->setContentsMargins(0, 0, 0, 0);
    vBoxLayout_Opt->setObjectName(QStringLiteral("vBoxLayout_Opt"));
    vBoxLayout_Opt->addWidget(comboBox_OptDatLen);
    vBoxLayout_Opt->addWidget(comboBox_OptStpBit);
    vBoxLayout_Opt->addWidget(comboBox_OptParBit);
    vBoxLayout_Opt->addWidget(comboBox_OptFlwCtl);

    groupBox_Opt->setEnabled(false);

    pushBtnOnLine = new QPushButton(widget);
    pushBtnOnLine->setObjectName(QStringLiteral("PushBtnOnLine"));
    pushBtnOnLine->setGeometry(QRect(520, 220, 80, 30));

    pushBtnOffLine = new QPushButton(widget);
    pushBtnOffLine->setObjectName(QStringLiteral("PushBtnOffLine"));
    pushBtnOffLine->setGeometry(520, 260, 80, 30);

    /* 串口改变，刷新端口可选速率 */
    QObject::connect(comboBox_ComPrt, SIGNAL(currentTextChanged(QString)), this, SLOT(comPortChng(QString)));

    retranslateSerPort();
}

void Ui_SerPorSet::retranslateSerPort()
{
    groupBox_Com->setTitle(tr("Communication"));
    groupBox_Opt->setTitle(tr("Option"));
    pushBtnOnLine->setText(tr("ON LINE"));
    pushBtnOffLine->setText(tr("OFF LINE"));

    comboBox_ComPrt->setToolTip(tr("Port"));
    comboBox_ComSpd->setToolTip(tr("Speed"));

    label_OptDatLen->setText(tr("Data Length"));
    label_OptStpBit->setText(tr("Stop Bit"));
    label_OptParBit->setText(tr("Parity Bit"));
    label_OptFlwCtl->setText(tr("Flow Control"));

    comboBox_OptDatLen->setToolTip(tr("Data Length"));
    comboBox_OptStpBit->setToolTip(tr("Stop Bit"));
    comboBox_OptParBit->setToolTip(tr("Parity Bit"));
    comboBox_OptFlwCtl->setToolTip(tr("Flow Control"));
}

void Ui_SerPorSet::prtCon()
{
#ifndef QT_NO_TOOLTIP
    qDebug() << comboBox_ComPrt->currentText() << comboBox_ComSpd->currentText();
    qDebug() << comboBox_OptDatLen->currentText() << comboBox_OptStpBit->currentText() << comboBox_OptParBit->currentText();
#endif
}

void Ui_SerPorSet::comPortChng(QString comName)
{
    QSerialPort serial;
    serial.setPortName(comName);
    if(serial.open(QIODevice::ReadWrite))
    {
        comboBox_ComSpd->clear();
        QList<int> nList = QSerialPortInfo(serial).standardBaudRates();
        foreach (int nSpd, nList)
        {
            comboBox_ComSpd->addItem(QString::number(nSpd) + "bps");
        }
        serial.close();
    }
    comboBox_ComSpd->setCurrentIndex(6);
}

void Ui_SerPorSet::comPortUpd()
{
    comboBox_ComPrt->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            comboBox_ComPrt->insertItem(0, info.portName());
            serial.close();
        }
    }
    qDebug() << "@Ui_SerPorSet : Com ports have refreshed";
}
