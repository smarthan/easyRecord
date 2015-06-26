#include "Beginner.h"
#include <QApplication>
#include <QTranslator>
//#include <QIcon>

//#include<QDebug>
//#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Beginner theWin;
    theWin.show();
    emit theWin.ui->pushbutton_Connect->click();
    emit theWin.comThread.comOpenSts(false);
//    QDesktopWidget *desktop = QApplication::desktop();
//    qDebug() << desktop->width() << " " << desktop->height();
    
    return a.exec();
}
