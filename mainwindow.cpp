#include "mainwindow.h"
#include <QtGui>
#include <QtWidgets>
#include "browser.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(QObject::tr("diary"));
    browser = new Browser;
    setCentralWidget(browser);
    createActions();
    createMenus();

    browser->addConnection();
}

void MainWindow::createActions()
{
    /*addTreeWidgetItemAction = new QAction(tr("Add tree element"), treeWidget);
    connect(addTreeWidgetItemAction,SIGNAL(triggered()),this,SLOT(addTreeWidgetItemSlot()));*/
    connectAction = new QAction(tr("Connect to database"),this);
    connect(connectAction,SIGNAL(triggered()),browser,SLOT(addConnection()));
}

void MainWindow::createMenus()
{
    QMenu *dbMenu = menuBar()->addMenu(QObject::tr("Database"));
    dbMenu->addAction(QObject::tr("Connection"), browser, SLOT(addConnection()));
    //dbMenu->addAction(QObject::tr("Export table"),diaryWidget,SLOT(exportTable()));
    //dbMenu->addAction(queryAction);

    //menuBar()->addAction(settingsAction);

    //menuBar()->addSeparator();

    //QMenu *helpMenu = menuBar()->addMenu(QObject::tr("About"));
    //helpMenu->addAction(QObject::tr("About program"), this, SLOT(about()));
    //helpMenu->addAction(QObject::tr("About Qt"), qApp, SLOT(aboutQt()));*/
}

void MainWindow::updateActions(const bool b)
{
    //scheduleProcessAction->setEnabled(b);
    //calcTleAction->setEnabled(b);
}



void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("diary"));
}
