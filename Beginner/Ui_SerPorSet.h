#ifndef UI_SERPORSET_H
#define UI_SERPORSET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>

class Ui_SerPorSet : public QWidget
{
    Q_OBJECT
public:
    QWidget     *widget;

    QGroupBox   *groupBox_Com;
    QWidget     *hLayoutWidget_Com;
    QHBoxLayout *hBoxLayout_Com;
    QComboBox   *comboBox_ComPrt;
    QComboBox   *comboBox_ComSpd;

    QGroupBox   *groupBox_Opt;
    QWidget     *vLayoutWidget_Tag;
    QWidget     *vLayoutWidget_Opt;
    QVBoxLayout *vBoxLayout_Tag;
    QVBoxLayout *vBoxLayout_Opt;
    QLabel      *label_OptDatLen;
    QLabel      *label_OptStpBit;
    QLabel      *label_OptParBit;
    QLabel      *label_OptFlwCtl;
    QComboBox   *comboBox_OptDatLen;
    QComboBox   *comboBox_OptStpBit;
    QComboBox   *comboBox_OptParBit;
    QComboBox   *comboBox_OptFlwCtl;

    QPushButton *pushBtnOnLine;
    QPushButton *pushBtnOffLine;

    explicit Ui_SerPorSet(QWidget *Widget = 0);

    void setupWid(QWidget *Widget);
    void retranslateSerPort();

public slots:
    void prtCon();      /* print serial communication configure information */
    void comPortChng(QString comName = "COM1"); /* refresh rates while change COM port */
    void comPortUpd();  /* refresh available ports */
};

#endif // Ui_SERPORSET_H
