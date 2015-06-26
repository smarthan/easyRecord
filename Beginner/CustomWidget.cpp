#include "CustomWidget.h"

/**************** CheckBoxRO ****************/
CheckBoxRO::CheckBoxRO(QWidget *parent) :
    QCheckBox(parent)
{
}

void CheckBoxRO::ChkStsNoChg(void)
{
    if(isTristate())
    {
        if(checkState()%3 == Qt::Checked)
        {
            setCheckState(Qt::PartiallyChecked);
        }
        else if(checkState()%3 == Qt::PartiallyChecked)
        {
            setCheckState(Qt::Unchecked);
        }
        else if(checkState()%3 == Qt::Unchecked)
        {
            setCheckState(Qt::Checked);
        }
        else
        {
            setCheckState(Qt::Unchecked);
        }
    }
    else
    {
        if(isChecked() == true)
        {
            setChecked(false);
        }
        else
        {
            setChecked(true);
        }
    }
}

/**************** LcdNumberCustom ****************/
LcdNumberCustom::LcdNumberCustom(QWidget *parent) :
                     QLCDNumber(parent)
{
    setDigitCount(6);
    setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdp =  this->palette();
    lcdp.setColor(QPalette::Normal, QPalette::WindowText, QColor(220, 20, 180));
    setPalette(lcdp);
}

void LcdNumberCustom::display(int num)
{
    QLCDNumber::display(QString::number(num / 100.0d) + "U");
}

/**************** DialCustom ****************/
DialCustom::DialCustom(QWidget *parent) :
    QDial(parent)
{
    setMinimum(0);
    setMaximum(1000);
    setNotchesVisible(true);
    setSingleStep(10);
    setDisabled(true);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void DialCustom::setMinValue(bool isChecked)
{
    if(isChecked)
    {
        setMinimum(-1000);
    }
    else
    {
        setMinimum(0);
    }
}
