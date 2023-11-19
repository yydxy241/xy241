#include "gamemodel.h"

void GameModel::startGame(GameType type)
{
    gameType = type;
    gameMapVec.clear();
    stepMapVec.clear();
    for(int i = 0;i< BOARD_GRAD_SIZE;i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j<BOARD_GRAD_SIZE;j++)
        {
            lineBoard.push_back(0);
        }
        gameMapVec.push_back(lineBoard);
    }


    if(gameType ==AI)
    {
        scoreMapVec.clear();
        for(int i = 0;i< BOARD_GRAD_SIZE;i++)
        {
            std::vector<int> lineScores;
            for (int j = 0; j<BOARD_GRAD_SIZE;j++)
            {
                lineScores.push_back(0);
            }
            gameMapVec.push_back(lineScores);
        }
    }
    playerFlag = true;


}

void GameModel::updateGameMap(int row,int col)
{


    stepMapVec.push_back(std::make_pair(row,col));
    if(playerFlag)
    {
        gameMapVec[row][col]=1;
    }
    else
    {
        gameMapVec[row][col]=-1;
    }
    playerFlag = !playerFlag;
}

void GameModel::actionByPerson(int row,int col)
{
    updateGameMap(row,col);
}


bool GameModel::isWin(int row,int col)
{
    for(int i=0;i<5;i++)
    {
        if(col-i>0 &&
            col-i+4<BOARD_GRAD_SIZE &&
            gameMapVec[row][col-i]==gameMapVec[row][col-i+1] &&
            gameMapVec[row][col-i]==gameMapVec[row][col-i+2] &&
            gameMapVec[row][col-i]==gameMapVec[row][col-i+3] &&
            gameMapVec[row][col-i]==gameMapVec[row][col-i+4] )
            return true;
    }   //水平方向五子
    for(int i=0;i<5;i++)
    {
        if(row-i>0 &&
            row-i+4<BOARD_GRAD_SIZE &&
            gameMapVec[row-i][col]==gameMapVec[row-i+1][col] &&
            gameMapVec[row-i][col]==gameMapVec[row-i+2][col] &&
            gameMapVec[row-i][col]==gameMapVec[row-i+3][col] &&
            gameMapVec[row-i][col]==gameMapVec[row-i+4][col] )
            return true;
    }   //竖直方向五子
    for(int i = 0;i<5;i++)
    {
        if( row + i < BOARD_GRAD_SIZE &&
            row + i - 4>0 &&
            col-i>0 &&
            col-i+4<BOARD_GRAD_SIZE &&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-1][col-i+1] &&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-2][col-i+2] &&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-3][col-i+3] &&
            gameMapVec[row+i][col-i]==gameMapVec[row+i-4][col-i+4] )
            return true;
    }  //"/"方向五子
    for(int i=0;i<5;i++)
    {
        if( row- i > 0 &&
            row- i + 4 < BOARD_GRAD_SIZE &&
            col - i > 0 &&
            col - i + 4 < BOARD_GRAD_SIZE &&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+1][col-i+1] &&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+2][col-i+2] &&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+3][col-i+3] &&
            gameMapVec[row-i][col-i]==gameMapVec[row-i+4][col-i+4] )
            return true;
    }  //"\"方向五子
    return false;
}


void GameModel::actionByAI(int &clickRow,int &clickCol)
{
    calculateScore();
    int maxScore = 0;
    std::vector<std::pair<int,int>>maxPoints;

    for(int row = 1;row<BOARD_GRAD_SIZE;row++)
    {
        for(int col = 1;col < BOARD_GRAD_SIZE;col++)
        {
            if(gameMapVec[row][col] == 0)
            {
                if(scoreMapVec[row][col] > maxScore)
                {
                    maxPoints.clear();
                    maxScore=scoreMapVec[row][col];
                    maxPoints.push_back(std::make_pair(row,col));
                }
                else if(gameMapVec[row][col] == maxScore)
                {
                    maxPoints.push_back(std::make_pair(row,col));
                }
            }
        }
    }
    srand((unsigned)time(0));
    int index = rand()%maxPoints.size();
    std::pair<int,int>pointPair = maxPoints.at(index);
    clickRow = pointPair.first;
    clickCol = pointPair.second;
    updateGameMap(clickRow,clickCol);
}

void GameModel::calculateScore()   //评分算法
{
    int personNum = 0;
    int botNum = 0;
    int emptyNum = 0;

    scoreMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int>lineScores;
        for(int j = 0;j<BOARD_GRAD_SIZE;j++)
        {
            lineScores.push_back(0);
        }
        scoreMapVec.push_back(lineScores);
    }
    for(int row=0;row<BOARD_GRAD_SIZE;row++)
    {
        for(int col = 0;col<BOARD_GRAD_SIZE;col++)
        {
            if(row>0 && col>0 &&
                gameMapVec[row][col] == 0)
            {
                for(int y = -1;y<=1;y++)
                {
                    for(int x=-1;x<=1;x++)
                    {
                        personNum=0;
                        botNum=0;
                        emptyNum=0;
                        if(!(y == 0 && x==0))
                        {
                            for(int i = 1;i<=4;i++)
                            {
                                if( row + i*y>0 && row + i*y < BOARD_GRAD_SIZE &&
                                    col + i*x>0 && col + i*y < BOARD_GRAD_SIZE &&
                                    gameMapVec[row+i*y][col+i*x] ==1)
                                {
                                    personNum++;
                                }
                                else if( row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                         col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row+i*y][col+i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for(int i = 1;i<=4;i++)
                            {
                                if( row - i*y>0 && row - i*y < BOARD_GRAD_SIZE &&
                                    col - i*x>0 && col - i*y < BOARD_GRAD_SIZE &&
                                    gameMapVec[row-i*y][col-i*x] ==1)
                                {
                                    personNum++;
                                }
                                else if( row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                         col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row-i*y][col-i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if(personNum==1)
                            {
                                scoreMapVec[row][col]+=10;
                            }
                            else if(personNum==2)
                            {
                                if(emptyNum==1)
                                {
                                    scoreMapVec[row][col]+=30;
                                }
                                else if(emptyNum==2)
                                {
                                    scoreMapVec[row][col]+=40;
                                }
                            }
                            else if(personNum==3)
                            {
                                if(emptyNum==1)
                                {
                                    scoreMapVec[row][col]+=60;
                                }
                                else if(emptyNum==2)
                                {
                                    scoreMapVec[row][col]+=241;
                                }
                            }
                            else if(personNum==4)
                            {
                                scoreMapVec[row][col]+=241241;
                            }
                            emptyNum=0;
                            for(int i=1;i<=4;i++)
                            {
                                if( row + i*y>0 && row + i*y < BOARD_GRAD_SIZE &&
                                    col + i*x>0 && col + i*y < BOARD_GRAD_SIZE &&
                                    gameMapVec[row+i*y][col+i*x] ==-1)
                                {
                                    botNum++;
                                }
                                else if( row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                         col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row+i*y][col+i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for(int i = 1;i<=4;i++)
                            {
                                if( row - i*y>0 && row - i*y < BOARD_GRAD_SIZE &&
                                    col - i*x>0 && col - i*y < BOARD_GRAD_SIZE &&
                                    gameMapVec[row-i*y][col-i*x] ==1)
                                {
                                    botNum++;
                                }
                                else if( row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                         col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row-i*y][col-i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }

                            if(botNum==0)
                            {
                                scoreMapVec[row][col]+=5;
                            }
                            else if(botNum==1)
                            {
                                scoreMapVec[row][col]+=10;
                            }
                            else if(botNum==2)
                            {
                                if(emptyNum==1)
                                {
                                    scoreMapVec[row][col]+=25;
                                }
                                else if(emptyNum==2)
                                {
                                    scoreMapVec[row][col]+=50;
                                }
                            }
                            else if(botNum==3)
                            {
                                if(emptyNum==1)
                                {
                                    scoreMapVec[row][col]+=55;
                                }
                                else if(emptyNum==2)
                                {
                                    scoreMapVec[row][col]+=241;
                                }
                            }
                            else if(botNum>=4)
                            {
                                scoreMapVec[row][col]+=241241;
                            }
                        }
                    }
                }
            }
        }
    }
}

void GameModel::sinregret()
{
    int nrow,ncol;
    std::pair<int,int> n;
    n=stepMapVec.back();
    nrow = n.first;
    ncol = n.second;
    stepMapVec.pop_back();
    if(gameMapVec[nrow][ncol]==1)
    {
        playerFlag=true;
    }
    if(gameMapVec[nrow][ncol]==-1)
    {
        playerFlag=false;
    }
    gameMapVec[nrow][ncol]=0;
}

void GameModel::airegret()
{
    int nrow,ncol;
    std::pair<int,int> n;
    n=stepMapVec.back();
    nrow = n.first;
    ncol = n.second;
    stepMapVec.pop_back();
    gameMapVec[nrow][ncol]=0;
    n=stepMapVec.back();
    nrow = n.first;
    ncol = n.second;
    stepMapVec.pop_back();
    gameMapVec[nrow][ncol]=0;
}




