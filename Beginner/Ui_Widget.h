#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <QTimer>

class Ui_Widget : public QWidget
{
    Q_OBJECT
public:
    QWidget *widget;

    QTimer *timer1s;
    QLCDNumber *lcdNumber_Clock;

    /* COM Config */
    QPushButton *pushbutton_Connect;

    QLabel *label_Logo;

    /* DO-4 */
    QGroupBox *groupBox_DO;
    QWidget *horizontalLayoutWidget_1;
    QHBoxLayout *horizontalLayout_1;
    QCheckBox *checkBox_DO1;
    QCheckBox *checkBox_DO2;
    QCheckBox *checkBox_DO3;
    QCheckBox *checkBox_DO4;

    /* AI Enable-3 & voltage range select */
    QGroupBox *groupBox_Sel;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_A1Enable;
    QCheckBox *checkBox_A2Enable;
    QCheckBox *checkBox_A3Enable;
    QCheckBox *checkBox_VoltSel;

    /* A1~A3 & percentage display */
    QGroupBox *groupBox_AI;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_1;
    QLCDNumber *lcdNumber_A1;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QLCDNumber *lcdNumber_A2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QLCDNumber *lcdNumber_A3;
    QSpacerItem *horizontalSpacer_6;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QDial *dial_A1;
    QDial *dial_A2;
    QDial *dial_A3;

    /* S1~S8 switcher */
    QGroupBox *groupBox_DI;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_S1;
    QCheckBox *checkBox_S2;
    QCheckBox *checkBox_S3;
    QCheckBox *checkBox_S4;
    QCheckBox *checkBox_S5;
    QCheckBox *checkBox_S6;
    QCheckBox *checkBox_S7;
    QCheckBox *checkBox_S8;

    //Ui_SerPorSet *comConf;

public:
    void setupUi(QWidget *Widget);
    void retranslateUi(QWidget *Widget);

public slots:
    void showDateTime();
};

#endif // UI_WIDGET_H
