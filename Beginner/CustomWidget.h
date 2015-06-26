#ifndef CHECKBOXRO_H
#define CHECKBOXRO_H

#include <QCheckBox>
#include <QLCDNumber>
#include <QDial>

namespace Ui {
    class CheckBoxRO;
    class LcdNumberCustom;
}

class CheckBoxRO : public QCheckBox
{
    Q_OBJECT
public:
    explicit CheckBoxRO(QWidget *parent = 0);
    
signals:
    
public slots:
    void ChkStsNoChg(void);
    
};

class LcdNumberCustom : public QLCDNumber
{
    Q_OBJECT
public:
    explicit LcdNumberCustom(QWidget *parent = 0);

public slots:
    void display(int num);
};

class DialCustom : public QDial
{
    Q_OBJECT
public:
    explicit DialCustom(QWidget *parent = 0);

public slots:
    void setMinValue(bool isChecked);
};

#endif // CHECKBOXRO_H
