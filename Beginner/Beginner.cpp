#include "Beginner.h"
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

Beginner::Beginner(QWidget *parent) :
    QWidget(parent),
    translator(new QTranslator),
    ui(new Ui::Beginner),
    comConf(new Ui_SerPorSet(this))
{
    QString locSys = QLocale::system().name();
    translator->load(":/language/" + locSys);
    qApp->installTranslator(translator);

    ui->setupUi(this);
    /* Background */
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Window,
                       QBrush(QPixmap(":/image/CALM").scaled(this->size()/*,
                                                              Qt::IgnoreAspectRatio, Qt::SmoothTransformation*/)
                              )
                       );
    this->setPalette(bgPalette);
    /* System Tray */
    CreatTrayIcon();

    if(locSys == QString("zh_CN"))
    {
        zh_cnAct->setChecked(true);
        zh_cnAct->triggered(true);
    }
    else if(locSys == "ja_JP")
    {
        ja_jpAct->setChecked(true);
        ja_jpAct->triggered(true);
    }
    else
    {
        en_usAct->setChecked(true);
        en_usAct->triggered(true);
    }

    /* Communction thread */
    comThread.changeTxState(false);
    comThread.TxData.clear();
    QObject::connect(&comThread, SIGNAL(comRecive()), this, SLOT(showRxData()));
    QObject::connect(&comThread, SIGNAL(comOpenSts(bool)), this, SLOT(seemingUpd(bool)));
    QObject::connect(ui->dial_A1, SIGNAL(valueChanged(int)), this, SLOT(sendAiValue(int)));
    QObject::connect(ui->dial_A2, SIGNAL(valueChanged(int)), this, SLOT(sendAiValue(int)));
    QObject::connect(ui->dial_A3, SIGNAL(valueChanged(int)), this, SLOT(sendAiValue(int)));
    QObject::connect(ui->checkBox_S1, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S2, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S3, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S4, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S5, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S6, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S7, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->checkBox_S8, SIGNAL(clicked(bool)), this, SLOT(sendSxState(bool)));
    QObject::connect(ui->pushbutton_Connect, SIGNAL(clicked()), comConf, SLOT(show()));
    QObject::connect(comConf->pushBtnOnLine, SIGNAL(clicked()), this, SLOT(btnClkOpenCom()));
    QObject::connect(comConf->pushBtnOffLine, SIGNAL(clicked()), this, SLOT(btnClkOffLine()));
}

Beginner::~Beginner()
{
    delete ui;
    delete comConf;
    comThread.stop();
    comThread.wait(20);
    comThread.terminate();
    comThread.quit();
}

void Beginner::CreatTrayMenu()
{
    beginnerMenu    = new QMenu((QWidget*)QApplication::desktop());
    languageMenu    = new QMenu(beginnerMenu);
    miniSizeAct = new QAction(this);
    restoreAct  = new QAction(this);
    actGroup    = new QActionGroup(this);
    en_usAct    = new QAction(this);
    zh_cnAct    = new QAction(this);
    ja_jpAct    = new QAction(this);
    quitAct     = new QAction(this);
    /* 加入菜单项 */
    beginnerMenu->addAction(miniSizeAct);
    beginnerMenu->addAction(restoreAct);
    beginnerMenu->addMenu(languageMenu);
    beginnerMenu->addSeparator();   /* 加入一个分隔符 */
    beginnerMenu->addAction(quitAct);
    /* 加入互斥组 */
    actGroup->addAction(en_usAct);
    actGroup->addAction(zh_cnAct);
    actGroup->addAction(ja_jpAct);
    /* 加入菜单作为子项 */
    languageMenu->addAction(en_usAct);
    languageMenu->addAction(zh_cnAct);
    languageMenu->addAction(ja_jpAct);
    /* 设置可选 */
    en_usAct->setCheckable(true);
    zh_cnAct->setCheckable(true);
    ja_jpAct->setCheckable(true);

    en_usAct->setChecked(true);

    this->connect(miniSizeAct, SIGNAL(triggered()), this, SLOT(hide()));
    this->connect(restoreAct, SIGNAL(triggered()), this, SLOT(showNormal()));
    this->connect(en_usAct, SIGNAL(triggered()), this, SLOT(setLan()));
    this->connect(zh_cnAct, SIGNAL(triggered()), this, SLOT(setLan()));
    this->connect(ja_jpAct, SIGNAL(triggered()), this, SLOT(setLan()));
    this->connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    retranslateTrayMenu();
}

void Beginner::CreatTrayIcon()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable())  /* 判断系统是否支持系统托盘图标 */
    {
        return;
    }

    CreatTrayMenu();

    beginnerTrayIcon = new QSystemTrayIcon(this);
    beginnerTrayIcon->setIcon(QIcon(":/image/EDITOR")); /* 设置图标图片 */
    beginnerTrayIcon->setContextMenu(beginnerMenu);     /* 设置托盘上下文菜单 */
    beginnerTrayIcon->show();
    this->connect(beginnerTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    retranslateTrayIcon();
}

void Beginner::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:

    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;

    case QSystemTrayIcon::MiddleClick:
        beginnerTrayIcon->showMessage(tr("Need Help?"), tr("No Help information now!"), QSystemTrayIcon::Information, 10000);
        break;

    default:
        break;
    }
}

void Beginner::closeEvent(QCloseEvent *event)
{
#ifndef QT_NO_DEBUG
    qApp->exit();
#endif
    if (beginnerTrayIcon->isVisible())
    {
        beginnerTrayIcon->showMessage(tr("Notice"), tr("Window hid itself"), QSystemTrayIcon::Information, 5000);
        hide(); /* 最小化 */
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void Beginner::showRxData()
{
//    QString strToPrt;
//    char *buf, tmp[100];
    QDateTime *dateTime = new QDateTime(QDateTime::currentDateTime());
    int nLen = comThread.requestData.size();
    if(nLen > 0)
    {
        qDebug() << "----Recived date stamp:" << dateTime->time().toString() << "----";

//        buf = comThread.requestData.data();
        if(comThread.requestData.left(2) == QByteArray("DO"))
        {
            int nDo = QString(comThread.requestData.mid(2)).toInt();
            if(nDo & 1)
            {
                ui->checkBox_DO4->setCheckState(Qt::PartiallyChecked);
            }
            else
            {
                ui->checkBox_DO4->setCheckState(Qt::Unchecked);
            }
            if(nDo & 2)
            {
                ui->checkBox_DO3->setCheckState(Qt::PartiallyChecked);
            }
            else
            {
                ui->checkBox_DO3->setCheckState(Qt::Unchecked);
            }
            if(nDo & 4)
            {
                ui->checkBox_DO2->setCheckState(Qt::PartiallyChecked);
            }
            else
                ui->checkBox_DO2->setCheckState(Qt::Unchecked);
            if(nDo & 8)
            {
                ui->checkBox_DO1->setCheckState(Qt::PartiallyChecked);
            }
            else
            {
                ui->checkBox_DO1->setCheckState(Qt::Unchecked);
            }

        }
//        for( ; nLen > 0; --nLen)
//        {
//            ::snprintf(tmp, 100, "%02X", (unsigned char)(*buf));
//            ++buf;
//            strToPrt += QString::fromUtf8(tmp);
//            strToPrt += " ";
//        }
//        qDebug() << strToPrt;
//        qDebug() << "----Ups are recived data----";
    }
    comThread.requestData.clear();
}

void Beginner::btnClkOpenCom()
{
    if(comConf->comboBox_ComPrt->currentIndex() >= 0)
    {
        comThread.stop();
        comThread.wait(20);
        comThread.startCom();
        comThread.setPortNo(comConf->comboBox_ComPrt->currentText());
        comThread.setPortSpeed(comConf->comboBox_ComSpd->currentText());
        comThread.setDataLen(comConf->comboBox_OptDatLen->currentText());
        comThread.setParity(comConf->comboBox_OptParBit->currentText());
        comThread.setFlowCtl(comConf->comboBox_OptFlwCtl->currentText());
        comThread.changeTRState(false);
        comThread.start();
        comConf->hide();
    }
    else
    {
        QMessageBox::warning(this, tr("Notice"), tr("Select a valid port then retry!"), QMessageBox::Yes);
        comConf->comPortUpd();
    }
}

void Beginner::btnClkOffLine()
{
    comThread.stop();
    comThread.wait(10);
    comConf->close();
    comConf->comPortUpd();
    qDebug() << "   #call by Function : " << __FUNCTION__ << "()";
}

void Beginner::sendSxState(bool checked)
{
    static int inputSts;
    QCheckBox *obj = dynamic_cast<QCheckBox *>(sender());
    if(obj != NULL)
    {
        int nNum = obj->text().right(1).toInt() - 1;
        comThread.TxData.clear();
        comThread.changeTxState(true);
        if(checked)
        {
            inputSts |= (1 << nNum);
            comThread.TxData = (QString::number(inputSts) + "$ ").toLatin1();
        }
        else
        {
            inputSts &= ~(1 << nNum);
            comThread.TxData = (QString::number(inputSts) + "$ ").toLatin1();
        }
        comThread.wait(20);
        comThread.changeTxState(false);
    }
    qDebug() << inputSts;
}

void Beginner::sendAiValue(int voltage)
{
    QDial *obj = dynamic_cast<QDial *>(sender());
    comThread.TxData.clear();
    comThread.changeTxState(true);
    if(obj != NULL)
    {
        comThread.TxData = (obj->windowTitle() + " " + QString::number(voltage / 100.0d)).toLatin1() + "$ ";
    }
    comThread.wait(20);
    comThread.changeTxState(false);
}

void Beginner::seemingUpd(bool opened)
{
    if(opened)
    {
        ui->widget->setEnabled(true);
        ui->pushbutton_Connect->setStyleSheet("QPushButton{border-image: url(:/image/CON);}"
                                              "QPushButton:hover{border-image: url(:/image/DISCON);}"
                                              "QPushButton:pressed{border-image: url(:/image/SX);}"
                                              "QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#FFFFF0;}");
    }
    else
    {
        ui->widget->setEnabled(false);
        ui->pushbutton_Connect->setStyleSheet("QPushButton{border-image: url(:/image/DISCON);}"
                                              "QPushButton:hover{border-image: url(:/image/CON);}"
                                              "QPushButton:pressed{border-image: url(:/image/SX);}"
                                              "QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#FFFFF0;}");
    }
}

void Beginner::setLan()
{
    QAction *obj = dynamic_cast<QAction *>(sender());
    QString lan = obj->text().split(':').first();
    if(lan == "English")
    {
        translator->load(":/language/en_US");
    }
    else if(lan == "Chinese")
    {
        translator->load(":/language/zh_CN");
    }
    else if(lan == "Japanese")
    {
        translator->load(":/language/ja_JP");
    }
    else
    {
        translator->load(":/language/en_US");
    }
    ui->retranslateUi(this);
    retranslateTrayIcon();
    retranslateTrayMenu();
    comConf->retranslateSerPort();
}

void Beginner::retranslateTrayMenu()
{
    miniSizeAct->setText(tr("MiniSize(&N)"));
    restoreAct->setText(tr("ReSize(&R)"));
    languageMenu->setTitle(tr("Language(&L)"));
    en_usAct->setText("English: " + tr("English"));
    zh_cnAct->setText("Chinese: " + tr("Chinese"));
    ja_jpAct->setText("Japanese: " + tr("Japanese"));
    quitAct->setText(tr("Quit(&Q)"));
}

void Beginner::retranslateTrayIcon()
{
    beginnerTrayIcon->setToolTip(tr("Beginner Ver. 1.0"));  /* 托盘时，鼠标放上去的提示信息 */
    beginnerTrayIcon->showMessage(tr("Beginner"), tr("Hi, This is simple Demo"), QSystemTrayIcon::Information, 1000);
}
