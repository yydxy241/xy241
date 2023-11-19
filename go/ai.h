
#ifndef AI_H
#define AI_H


#include <QMainWindow>
#include"gamemodel.h"


class ai : public QMainWindow
{
    Q_OBJECT
public:
    explicit ai(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event);
    GameModel *game;   //游戏指针
    GameType game_type;  //储存游戏类型
    void initGame();
    void initAIGame();
    void mouseMoveEvent(QMouseEvent *event);
    int clickPosRow,clickPosCol; //储存将要点击的位置
    bool selectPos = false;   //是否移动到合适的位置
    void mouseReleaseEvent(QMouseEvent *event);
    void chessOneByPerson();



signals:
    void aiBack();
    void airegret();


private slots:
    void chessOneByAI();
};

#endif // AI_H
