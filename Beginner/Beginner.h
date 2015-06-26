#ifndef BEGINNER_H
#define BEGINNER_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QTranslator>

#include "Ui_Widget.h"
#include "Ui_SerPorSet.h"
#include "CommunicationThread.h"

namespace Ui {
    class Beginner : public Ui_Widget{};
}

class Beginner : public QWidget
{
    Q_OBJECT
public:
    explicit Beginner(QWidget *parent = 0);
    ~Beginner();

    void CreatTrayMenu();
    void CreatTrayIcon();
    void retranslateTrayMenu();
    void retranslateTrayIcon();

    QSystemTrayIcon *beginnerTrayIcon;
    QMenu   *beginnerMenu;
    QMenu   *languageMenu;
    QAction *miniSizeAct;
    QAction *restoreAct;
    QAction *en_usAct;
    QAction *zh_cnAct;
    QAction *ja_jpAct;
    QAction *quitAct;
    QActionGroup    *actGroup;
    QTranslator *translator;
    CommunicationThread comThread;

protected:
    void closeEvent(QCloseEvent *event);

public:
    Ui::Beginner *ui;       /* Main window */
    Ui_SerPorSet *comConf;  /* Serial communication port configurate */
    
signals:
    
public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);   /* Tray icon actions */
    void showRxData();      /* Display recived data */
    void btnClkOpenCom();   /* On-line button pressed */
    void btnClkOffLine();   /* Off-line button pressed */
    void sendSxState(bool); /* Send DI's state while checkbox change */
    void sendAiValue(int);  /* Send AI's value while dial change */
    void seemingUpd(bool);  /* Appearance change while com port open state change */
    void setLan();          /* Language set */
};

#endif // BEGINNER_H
