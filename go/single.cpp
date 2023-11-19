#include"gamemodel.h"
#include "single.h"
#include<QPainter>
#include<QMessageBox>
#include<QMouseEvent>
#include<math.h>
#include<QPushButton>

single::single(QWidget *parent)
    : QMainWindow{parent}
{
    setMouseTracking(true);
    setFixedSize(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
                 MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);
    initGame();
    QPushButton *Btn2 = new QPushButton;
    Btn2->setParent(this);
    Btn2->setText("返回");
    Btn2->setFixedSize(60,30);
    Btn2->move(600,630);
    connect(Btn2,&QPushButton::clicked,[=](){
        emit this->singleBack();
        initGame();
    });
    QPushButton *Btn21 = new QPushButton;
    Btn21->setParent(this);
    Btn21->setText("悔棋");
    Btn21->setFixedSize(60,30);
    Btn21->move(0,630);
    connect(Btn21,&QPushButton::clicked,[=](){
        emit this->singleregret();
    });
    connect(this,&single::singleregret,[=](){
        game->sinregret();
        update();
    });


}



void single::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing,true);  //抗锯齿

    for (int i =0;i<BOARD_GRAD_SIZE + 1;i++)
    {
        painter.drawLine(MARGIN + BLOCK_SIZE * i,MARGIN,
                         MARGIN + BLOCK_SIZE * i,size().height() - MARGIN);    //从左到右，第i+1条竖线

        painter.drawLine(MARGIN,MARGIN + BLOCK_SIZE * i,
                         size().width() - MARGIN, MARGIN + BLOCK_SIZE * i);
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);   //绘制选中点
    if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
        clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
        game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        if(game->playerFlag)
        {
            brush.setColor(Qt::black);
        }
        else
        {
            brush.setColor(Qt::white);
        }
        painter.setBrush(brush);
        painter.drawRect(MARGIN + BLOCK_SIZE * clickPosCol - MARK_SIZE / 2,MARGIN + BLOCK_SIZE * clickPosRow - MARK_SIZE / 2,MARK_SIZE,MARK_SIZE);
    }

    for(int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
        {
            if(game->gameMapVec[i][j]==1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS,2*CHESS_RADIUS,2*CHESS_RADIUS);
            }
            else if(game->gameMapVec[i][j]==-1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS,2*CHESS_RADIUS,2*CHESS_RADIUS);
            }
        }
    }
    if(clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
       clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
        (game->gameMapVec[clickPosRow][clickPosCol]==1 ||
         game->gameMapVec[clickPosRow][clickPosCol]==-1))
    {
        if(game->isWin(clickPosRow,clickPosCol) && game->gameStatus ==PLAYING)
        {
            game->gameStatus = WIN;
            QString str;
            if(game->gameMapVec[clickPosRow][clickPosCol]==1)
            {
                str="黑棋";
            }
            else if(game->gameMapVec[clickPosRow][clickPosCol]==-1)
            {
                str="白棋";
            }
            QMessageBox::StandardButton btnValue = QMessageBox::information(this,"五子棋大战", str + "胜利");

            if(btnValue == QMessageBox::Ok)
            {
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
        }
    }

}


void single::initGame()
{
    game = new GameModel;
    initSINGLEGame();
}

void single::initSINGLEGame()
{
    game_type = SINGLE;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void single::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    if(x >= MARGIN + BLOCK_SIZE / 2 &&
        x < size().width()-MARGIN-BLOCK_SIZE / 2 &&
        y >= MARGIN + BLOCK_SIZE / 2 &&
        y< size().height()-MARGIN-BLOCK_SIZE /2)
    {
        int col =(x-MARGIN)/BLOCK_SIZE;
        int row =(y-MARGIN)/BLOCK_SIZE;

        int leftTopPosX =MARGIN + BLOCK_SIZE * col;
        int leftTopPosY =MARGIN + BLOCK_SIZE * row;


        clickPosRow = -1;
        clickPosCol = -1;
        int len = 0;
        selectPos = false;

        len = sqrt(x - leftTopPosX) * (x - leftTopPosX) + (y- leftTopPosY) * (y - leftTopPosY);
        if (len<POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos = true;
            }
        }

        len = sqrt(x - leftTopPosX-BLOCK_SIZE) * (x - leftTopPosX-BLOCK_SIZE) + (y- leftTopPosY) * (y - leftTopPosY);
        if(len<POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col+1;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos = true;
            }
        }

        len = sqrt(x - leftTopPosX) * (x - leftTopPosX) + (y- leftTopPosY-BLOCK_SIZE) * (y - leftTopPosY-BLOCK_SIZE);
        if(len<POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col+1;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos = true;
            }
        }

        len = sqrt(x - leftTopPosX-BLOCK_SIZE) * (x - leftTopPosX-BLOCK_SIZE) + (y- leftTopPosY-BLOCK_SIZE) * (y - leftTopPosY-BLOCK_SIZE);
        if(len<POS_OFFSET)
        {
            clickPosRow = row+1;
            clickPosCol = col+1;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos = true;
            }
        }
    }
    update();
}


void single::mouseReleaseEvent(QMouseEvent *event)
{
    if(selectPos ==false)
    {
        return;
    }
    else
    {
        selectPos=false;
    }


    chessOneByPerson();

}


void single::chessOneByPerson()
{
    if(clickPosRow !=-1 && clickPosCol !=-1 &&game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        game->actionByPerson(clickPosRow,clickPosCol);
        update();
    }
}



