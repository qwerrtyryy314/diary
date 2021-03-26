#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
//#include "treemodel.h"
#include <QTreeWidget>
//#include "diarywidget.h"

class Browser;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
public slots:
    void updateActions(const bool b);
signals:
    //void deleteFromTle(QString);
private slots:
    void about();
private:

    //DiaryWidget *diaryWidget;
    void createActions();
    void createMenus();
    Browser *browser;
    QAction *connectAction;
};

#endif // MAINWINDOW_H
