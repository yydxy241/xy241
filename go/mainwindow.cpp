
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamemodel.h"
#include "single.h"
#include "online.h"
#include "ai.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("主菜单");
    setFixedSize(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
                 MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);

    connect(ui->Btn1,&QPushButton::clicked,[=](){
        emit this->chooseSceneBack();

    });





    Single = new single;
    connect(Single,&single::singleBack,this,[=](){
        Single->hide();
        this->show();
    });
    connect(ui->Btn1,&QPushButton::clicked,[=](){
        this->hide();
        Single->show();
    });

    Online = new online;
    connect(Online,&online::onlineBack,this,[=](){
        Online->hide();
        this->show();
    });
    connect(ui->Btn3,&QPushButton::clicked,[=](){
        this->hide();
        Online->show();
    });

    Ai = new ai;
    connect(Ai,&ai::aiBack,this,[=](){
        Ai->hide();
        this->show();
    });
    connect(ui->Btn2,&QPushButton::clicked,[=](){
        this->hide();
        Ai->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);   //画背景

}





