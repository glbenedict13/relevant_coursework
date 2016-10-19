#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QMessageBox>
#include <vector>
#include <QRect>
#include <QPushButton>
#include <QLine>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <map>
#include "node.h"
#include "box.h"
#include "player.h"

using namespace std;

namespace Ui {
class gameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = 0);
    GameBoard(int gridSize, int numOfPlayers, QWidget *parent = 0);
    ~GameBoard();
    bool checkBoardForFill();

private:
    Ui::gameBoard *ui;
    //functions
    QPoint fixCornerCoord(QPoint pt);
    QPoint fixLineCoord(QPoint pt);
    void initGameBoard();
    void makeGameBoardWidgets();
    void makeNodes();
    void drawLines(QPainter *p);
    void retranslatePushButtons();
    void addNearbyWidgetsToNodes();
    void connectSignalsSlots();
    void addNearbyBoxesToNodes();
    void addNearbyNodesToBoxes();
    void processTurn();
    void makePlayers();
    void checkGameWin();
    player *calculateWinningPlayer();
    void updateCurrentPlayer();
    void updateWinningPlayer();


    //variables
    int gridSize;
    int numOfPlayers;
    int playerTurn;
    QPushButton* firstLinePoint; //holds first button clicked
    QPushButton* secondLinePoint; // holds next button clicked
    vector<vector<box*> > gameBoardBoxes; //holds widgets to be painted when box is completed
    vector<node*> gameBoardNodes;
    vector<QLine*> savedLines; //holds all created lines
    vector<player*> players;
    map<QLine*, vector<QPushButton*>> gameLineLocMap; //map of which points make each button so they can be redrawn
    map<QPushButton*, node*> gameBtnNodeMap;
    QMessageBox gameOverBox();

protected:
    void paintEvent(QPaintEvent *pe);

private slots:
    void setLineCoord();
};

#endif // GAMEBOARD_H
