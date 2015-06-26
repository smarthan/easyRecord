#include <QDateTime>

#include "Ui_Widget.h"
#include "CustomWidget.h"

void Ui_Widget::setupUi(QWidget *Widget)
{
    if (Widget->objectName().isEmpty())
        Widget->setObjectName(QStringLiteral("Widget"));
    Widget->resize(680, 460);
    Widget->setFixedSize(Widget->width(), Widget->height());
    //Widget->setStyleSheet("background-color:green");
    Widget->setAutoFillBackground(true);

    QIcon icon;
    icon.addFile(QStringLiteral(":/image/SETTING"), QSize(), QIcon::Normal, QIcon::Off);
    Widget->setWindowIcon(icon);

    label_Logo = new QLabel(Widget);
    label_Logo->setObjectName(QStringLiteral("label_Logo"));
    label_Logo->setGeometry(QRect(20, 10, 185, 60));
    label_Logo->setPixmap(QPixmap(":/image/TPC"));

    lcdNumber_Clock = new QLCDNumber(Widget);
    lcdNumber_Clock->setObjectName(QStringLiteral("lcdNumber_Clock"));
    lcdNumber_Clock->setGeometry(QRect(320, 25, 180, 28));
    lcdNumber_Clock->setDigitCount(19);
    lcdNumber_Clock->setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdt =  lcdNumber_Clock->palette();
    lcdt.setColor(QPalette::Normal, QPalette::WindowText, Qt::blue);
    lcdNumber_Clock->setPalette(lcdt);
    lcdNumber_Clock->setStyleSheet("background-color: lightgreen");
    timer1s = new QTimer();
    timer1s->start(1000);
    lcdNumber_Clock->display("1970-01-01 00:00:00");

    //comConf = new Ui_SerPorSet(this);

    pushbutton_Connect = new QPushButton(Widget);
    pushbutton_Connect->setObjectName(QStringLiteral("pushbutton_Connect"));
    pushbutton_Connect->setGeometry(QRect(530, 25, 100, 35));
    /*
     *pushbutton_Connect->setIcon(QPixmap(":/image/SX"));
     *pushbutton_Connect->setIconSize(QSize(100, 35));
     */

    widget = new QWidget(Widget);
    widget->setObjectName(QStringLiteral("widget"));
    widget->setGeometry(QRect(20, 60, 640, 420));

    /* DO */
    {
    groupBox_DO = new QGroupBox(widget);
    groupBox_DO->setObjectName(QStringLiteral("groupBox_DO"));
    groupBox_DO->setGeometry(QRect(10, 10, 271, 71));
    horizontalLayoutWidget_1 = new QWidget(groupBox_DO);
    horizontalLayoutWidget_1->setObjectName(QStringLiteral("horizontalLayoutWidget_1"));
    horizontalLayoutWidget_1->setGeometry(QRect(7, 20, 256, 41));
    horizontalLayout_1 = new QHBoxLayout(horizontalLayoutWidget_1);
    horizontalLayout_1->setSpacing(6);
    horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
    horizontalLayout_1->setContentsMargins(0, 0, 0, 0);

    checkBox_DO1 = new QCheckBox(horizontalLayoutWidget_1);
    checkBox_DO1->setObjectName(QStringLiteral("checkBox_DO1"));
    checkBox_DO1->setEnabled(false);
    checkBox_DO1->setChecked(true);
    QFont font;
    font.setFamily(QStringLiteral("SimSun"));
    font.setPointSize(9);
    font.setBold(true);
    font.setWeight(75);
    checkBox_DO1->setFont(font);

    horizontalLayout_1->addWidget(checkBox_DO1);

    checkBox_DO2 = new CheckBoxRO(horizontalLayoutWidget_1);
    checkBox_DO2->setObjectName(QStringLiteral("checkBox_DO2"));
    checkBox_DO2->setTristate();
    checkBox_DO2->setCheckState(Qt::Unchecked);

    QObject::connect(checkBox_DO2,SIGNAL(clicked()),checkBox_DO2,SLOT(ChkStsNoChg()));

    horizontalLayout_1->addWidget(checkBox_DO2);

    checkBox_DO3 = new CheckBoxRO(horizontalLayoutWidget_1);
    checkBox_DO3->setObjectName(QStringLiteral("checkBox_DO3"));
    checkBox_DO3->setChecked(true);
    checkBox_DO3->setTristate();
    checkBox_DO3->setCheckState(Qt::Unchecked);

    QObject::connect(checkBox_DO3,SIGNAL(clicked()),checkBox_DO3,SLOT(ChkStsNoChg()));

    horizontalLayout_1->addWidget(checkBox_DO3);

    checkBox_DO4 = new CheckBoxRO(horizontalLayoutWidget_1);
    checkBox_DO4->setObjectName(QStringLiteral("checkBox_DO4"));
    checkBox_DO4->setTristate();
    checkBox_DO4->setCheckState(Qt::Unchecked);

    QObject::connect(checkBox_DO4,SIGNAL(clicked()),checkBox_DO4,SLOT(ChkStsNoChg()));

    horizontalLayout_1->addWidget(checkBox_DO4);}

    /* Voltage control */
    {
    groupBox_Sel = new QGroupBox(widget);
    groupBox_Sel->setObjectName(QStringLiteral("groupBox_Sel"));
    groupBox_Sel->setGeometry(QRect(290, 10, 341, 71));
    horizontalLayoutWidget_2 = new QWidget(groupBox_Sel);
    horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
    horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 320, 41));
    horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    checkBox_A1Enable = new QCheckBox(horizontalLayoutWidget_2);
    checkBox_A1Enable->setObjectName(QStringLiteral("checkBox_A1Enable"));

    horizontalLayout_2->addWidget(checkBox_A1Enable);

    checkBox_A2Enable = new QCheckBox(horizontalLayoutWidget_2);
    checkBox_A2Enable->setObjectName(QStringLiteral("checkBox_A2Enable"));

    horizontalLayout_2->addWidget(checkBox_A2Enable);

    checkBox_A3Enable = new QCheckBox(horizontalLayoutWidget_2);
    checkBox_A3Enable->setObjectName(QStringLiteral("checkBox_A3Enable"));

    horizontalLayout_2->addWidget(checkBox_A3Enable);

    checkBox_VoltSel = new QCheckBox(horizontalLayoutWidget_2);
    checkBox_VoltSel->setObjectName(QStringLiteral("checkBox_VoltSel"));

    horizontalLayout_2->addWidget(checkBox_VoltSel);
    }

    /* AI */
    {
    groupBox_AI = new QGroupBox(widget);
    groupBox_AI->setObjectName(QStringLiteral("groupBox_AI"));
    groupBox_AI->setGeometry(QRect(10, 90, 621, 221));
    horizontalLayoutWidget_3 = new QWidget(groupBox_AI);
    horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
    horizontalLayoutWidget_3->setGeometry(QRect(30, 20, 551, 41));
    horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    
    horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_1);

    lcdNumber_A1 = new LcdNumberCustom(horizontalLayoutWidget_3);
    lcdNumber_A1->setObjectName(QStringLiteral("lcdNumber_A1"));
    horizontalLayout_3->addWidget(lcdNumber_A1);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_2);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_3);

    lcdNumber_A2 = new LcdNumberCustom(horizontalLayoutWidget_3);
    lcdNumber_A2->setObjectName(QStringLiteral("lcdNumber_A2"));
    horizontalLayout_3->addWidget(lcdNumber_A2);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_4);

    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_5);

    lcdNumber_A3 = new LcdNumberCustom(horizontalLayoutWidget_3);
    lcdNumber_A3->setObjectName(QStringLiteral("lcdNumber_A3"));
    horizontalLayout_3->addWidget(lcdNumber_A3);

    horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_6);

    horizontalLayoutWidget_4 = new QWidget(groupBox_AI);
    horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
    horizontalLayoutWidget_4->setGeometry(QRect(30, 70, 551, 131));
    horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    dial_A1 = new DialCustom(horizontalLayoutWidget_4);
    dial_A1->setObjectName(QStringLiteral("dial_A1"));
    dial_A1->setWindowTitle("A1");

    horizontalLayout_4->addWidget(dial_A1);

    dial_A2 = new DialCustom(horizontalLayoutWidget_4);
    dial_A2->setObjectName(QStringLiteral("dial_A2"));
    dial_A2->setWindowTitle("A2");

    horizontalLayout_4->addWidget(dial_A2);

    dial_A3 = new DialCustom(horizontalLayoutWidget_4);
    dial_A3->setObjectName(QStringLiteral("dial_A3"));
    dial_A3->setWindowTitle("A3");

    horizontalLayout_4->addWidget(dial_A3);
    }

    /* DI */
    {
    groupBox_DI = new QGroupBox(widget);
    groupBox_DI->setObjectName(QStringLiteral("groupBox_DI"));
    groupBox_DI->setGeometry(QRect(10, 320, 621, 51));
    horizontalLayoutWidget_5 = new QWidget(groupBox_DI);
    horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
    horizontalLayoutWidget_5->setGeometry(QRect(10, 20, 601, 30));
    horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    checkBox_S1 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S1->setObjectName(QStringLiteral("checkBox_S1"));

    horizontalLayout_5->addWidget(checkBox_S1);

    checkBox_S2 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S2->setObjectName(QStringLiteral("checkBox_S2"));

    horizontalLayout_5->addWidget(checkBox_S2);

    checkBox_S3 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S3->setObjectName(QStringLiteral("checkBox_S3"));

    horizontalLayout_5->addWidget(checkBox_S3);

    checkBox_S4 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S4->setObjectName(QStringLiteral("checkBox_S4"));

    horizontalLayout_5->addWidget(checkBox_S4);

    checkBox_S5 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S5->setObjectName(QStringLiteral("checkBox_S5"));

    horizontalLayout_5->addWidget(checkBox_S5);

    checkBox_S6 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S6->setObjectName(QStringLiteral("checkBox_S6"));

    horizontalLayout_5->addWidget(checkBox_S6);

    checkBox_S7 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S7->setObjectName(QStringLiteral("checkBox_S7"));

    horizontalLayout_5->addWidget(checkBox_S7);

    checkBox_S8 = new QCheckBox(horizontalLayoutWidget_5);
    checkBox_S8->setObjectName(QStringLiteral("checkBox_S8"));

    horizontalLayout_5->addWidget(checkBox_S8);
    }

    retranslateUi(Widget);
    QObject::connect(timer1s, &QTimer::timeout, this, &Ui_Widget::showDateTime);
    QObject::connect(checkBox_A1Enable, SIGNAL(clicked(bool)), dial_A1, SLOT(setEnabled(bool)));
    QObject::connect(checkBox_A2Enable, SIGNAL(clicked(bool)), dial_A2, SLOT(setEnabled(bool)));
    QObject::connect(checkBox_A3Enable, SIGNAL(clicked(bool)), dial_A3, SLOT(setEnabled(bool)));
    QObject::connect(dial_A1, SIGNAL(valueChanged(int)), lcdNumber_A1, SLOT(display(int)));
    QObject::connect(dial_A2, SIGNAL(valueChanged(int)), lcdNumber_A2, SLOT(display(int)));
    QObject::connect(dial_A3, SIGNAL(valueChanged(int)), lcdNumber_A3, SLOT(display(int)));
    QObject::connect(checkBox_VoltSel, SIGNAL(clicked(bool)), dial_A1, SLOT(setMinValue(bool)));
    QObject::connect(checkBox_VoltSel, SIGNAL(clicked(bool)), dial_A2, SLOT(setMinValue(bool)));
    QObject::connect(checkBox_VoltSel, SIGNAL(clicked(bool)), dial_A3, SLOT(setMinValue(bool)));
    //QObject::connect(pushbutton_Connect, SIGNAL(clicked()), comConf, SLOT(show()));

#ifndef QT_NO_DEBUG
    emit checkBox_A1Enable->clicked(true);
    checkBox_A1Enable->setChecked(true);
#endif

    pushbutton_Connect->setStyleSheet("QPushButton{border-image: url(:/image/DISCON);}"
                                      "QPushButton:hover{border-image: url(:/image/CON);}"
                                      "QPushButton:pressed{border-image: url(:/image/SX);}"
                                      "QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#FFFFF0;}");

    QMetaObject::connectSlotsByName(Widget);
} // setupUi

void Ui_Widget::retranslateUi(QWidget *Widget)
{
    Widget->setWindowTitle(QApplication::translate("Widget", "Beginner", 0));

    pushbutton_Connect->setText(QApplication::translate("Widget", "Connect", 0));

    groupBox_DO->setTitle(QApplication::translate("Widget", "DigitalOutputs", 0));
    checkBox_DO1->setText(QApplication::translate("Widget", "MA-MB", 0));
    checkBox_DO2->setText(QApplication::translate("Widget", "M1-M2", 0));
    checkBox_DO3->setText(QApplication::translate("Widget", "P1-PC", 0));
    checkBox_DO4->setText(QApplication::translate("Widget", "P2-PC", 0));

    groupBox_Sel->setTitle(QApplication::translate("Widget", "VoltageSelect", 0));
    checkBox_A1Enable->setText(QApplication::translate("Widget", "A1 ON", 0));
    checkBox_A2Enable->setText(QApplication::translate("Widget", "A2 ON", 0));
    checkBox_A3Enable->setText(QApplication::translate("Widget", "A3 ON", 0));
    checkBox_VoltSel->setText(QApplication::translate("Widget", "-10V Range", 0));

    groupBox_AI->setTitle(QApplication::translate("Widget", "AnalogyInputs", 0));

    groupBox_DI->setTitle(QApplication::translate("Widget", "DigitalInputs", 0));
    checkBox_S1->setText(QApplication::translate("Widget", "S1", 0));
    checkBox_S2->setText(QApplication::translate("Widget", "S2", 0));
    checkBox_S3->setText(QApplication::translate("Widget", "S3", 0));
    checkBox_S4->setText(QApplication::translate("Widget", "S4", 0));
    checkBox_S5->setText(QApplication::translate("Widget", "S5", 0));
    checkBox_S6->setText(QApplication::translate("Widget", "S6", 0));
    checkBox_S7->setText(QApplication::translate("Widget", "S7", 0));
    checkBox_S8->setText(QApplication::translate("Widget", "S8", 0));
} // retranslateUi

void Ui_Widget::showDateTime()
{
    QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    this->lcdNumber_Clock->display(strTime);
}
