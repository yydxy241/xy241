
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "single.h"
#include "online.h"
#include "ai.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    single *Single = NULL;
    ai *Ai = NULL;
    online *Online =NULL;
    ~MainWindow();

signals:
      void chooseSceneBack();

private:
    Ui::MainWindow *ui;


    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
