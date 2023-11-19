
#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include<time.h>
#include <vector>
#include<stdlib.h>


enum GameType     //模式

{
    SINGLE,
    ONLINE,
    AI
};

enum GameStatus    // 状态
{
    PLAYING,
    WIN,
    LOSE
};

//定义棋盘
const int BOARD_GRAD_SIZE = 15;
const int MARGIN = 30;
const int CHESS_RADIUS = 15;
const int MARK_SIZE = 6;
const int BLOCK_SIZE = 40;
const int POS_OFFSET = BLOCK_SIZE * 0.4;

const int AI_THINK_TIME = 700;

class GameModel{
public:
    GameModel(){};


    std::vector<std::vector<int>> gameMapVec;   //储存当前棋盘和棋子情况

    std::vector<std::vector<int>> scoreMapVec;  //储存各点评分情况
    std::vector<std::pair<int,int>> stepMapVec;   //储存每步棋子落点

    bool playerFlag;

    GameType gameType;

    GameStatus gameStatus;

    void startGame(GameType type);
    void calculateScore();
    void actionByPerson(int row,int col);   //人下棋
    void actionByAI(int &clickRow,int &clickCol);  //机器下棋
    void updateGameMap(int row,int col);
    bool isWin(int row,int col);
    bool isDeadGame();  //判断和棋
    void sinregret();
    void airegret();





};

#endif // GAMEMODEL_H
