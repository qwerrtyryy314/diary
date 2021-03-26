#include "mainwindow.h"

#include <QtCore>
#include <QtGui>

#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //QTranslator qtTranslator;
   // qtTranslator.load("rtf_diary_ru");
    //app.installTranslator(&qtTranslator);

    MainWindow *mainWin = new MainWindow;
    mainWin->resize(900,700);
    mainWin->show();

    return app.exec();
}

