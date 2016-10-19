#include "gameboard.h"
#include "ui_gameboard.h"

GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameBoard),
    gridSize(0),
    numOfPlayers(0)
{
    ui->setupUi(this);
    firstLinePoint = NULL;
    secondLinePoint = NULL;
    initGameBoard();
}

GameBoard::GameBoard(int gridSize, int numOfPlayers, QWidget *parent):
    QWidget(parent),
    ui(new Ui::gameBoard),
    gridSize(gridSize),
    numOfPlayers(numOfPlayers)
{
    ui->setupUi(this);
    firstLinePoint = NULL;
    secondLinePoint = NULL;
    initGameBoard();
}

GameBoard::~GameBoard()
{
    delete ui;
}

QPoint GameBoard::fixCornerCoord(QPoint pt)
{
    //minus 10 because button radius is 10 px -- centers button on corner of QWidget
    pt.setX(pt.x() - 10);
    pt.setY(pt.y() - 10);
    return pt;
}

QPoint GameBoard::fixLineCoord(QPoint pt)
{
    //minus 10 because button radius is 10 px -- centers button on corner of QWidget
    pt.setX(pt.x() + 10);
    pt.setY(pt.y() + 10);
    return pt;
}

void GameBoard::initGameBoard()
{
    // --------- setup gameboard -----------
    makeGameBoardWidgets();
    makeNodes();
    addNearbyBoxesToNodes();
    addNearbyNodesToBoxes();
    connectSignalsSlots();
    makePlayers();
    // -------------------------------------
    playerTurn = 0; //sets turn initially to players[0]
    makePlayers();
    updateCurrentPlayer();
}

void GameBoard::makeGameBoardWidgets()
{
    int numOfRects = gridSize - 1; //number of rects in each row/column is 1 less than number of dots
    for(int i = 0; i < numOfRects; i++){
        vector<box*> newRow;
        for(int j = 0; j < numOfRects; j++){
            box* tmpWidget = new box(this);
            newRow.push_back(tmpWidget);
            ui->gameGL->addWidget(tmpWidget, i, j);
        }
        gameBoardBoxes.push_back(newRow);
    }
}

void GameBoard::makeNodes()
{
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            int max = gridSize - 1;
            //corners
            if(i == 0 && j == 0){// top_left
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, false, true, false, true, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            if(i == max && j == max){// bottom_right
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, true, false, true, false, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            if(i == 0 && j == max){// top_right
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, false, true, true, false, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            if(i == max && j == 0){// bottom_left
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, true, false, false, true, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            //edges
            if(i == 0 && j > 0 && j < max){// top
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, false, true, true, true, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            if(i > 0 && i < max && j == 0){// left
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, true, true, false, true, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            if(j == max && i > 0 && i < max){// right
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, true, true, true, false, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            if(i == max && j > 0 && j < max){// bot
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, true, false, true, true, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
            //middle
            if(i > 0 && i < max && j > 0 && j < max){
                QPushButton *tmpBtn = new QPushButton(this);
                node *tmpNode = new node(tmpBtn, true, true, true, true, i, j);
                gameBoardNodes.push_back(tmpNode);
                gameBtnNodeMap[tmpBtn] = tmpNode;
            }
        }
    }
}

void GameBoard::retranslatePushButtons()
{
    int numOfRects = gridSize - 1; //number of rects in each row/column is 1 less than number of dots
    for(int i = 0; i < numOfRects; i+=2){
        for(int j = 0; j < numOfRects; j+=2){
            QWidget *tmpW = gameBoardBoxes[i][j];
            QPoint topL = fixCornerCoord(tmpW->rect().topLeft());
            QPoint topR = fixCornerCoord(tmpW->rect().topRight());
            QPoint botL = fixCornerCoord(tmpW->rect().bottomLeft());
            QPoint botR = fixCornerCoord(tmpW->rect().bottomRight());

            gameBoardNodes[i * gridSize + j]->nodeBtn->move(tmpW->mapToParent(topL));
            gameBoardNodes[(i+1) * gridSize + j]->nodeBtn->move(tmpW->mapToParent(botL));
            gameBoardNodes[i * gridSize + (j+1)]->nodeBtn->move(tmpW->mapToParent(topR));
            gameBoardNodes[(i+1) * gridSize + (j+1)]->nodeBtn->move(tmpW->mapToParent(botR));

        }
    }
}

void GameBoard::makePlayers()
{
    for(int i = 0; i < numOfPlayers;i++){//this loop will give all variable of the class a value
        QString playerName = "Player " + QString::number(i+1);
        player* tmp = new player(i, i, 0, playerName);
        players.push_back(tmp);
    }
}

void GameBoard::addNearbyBoxesToNodes()
{
    for(int i = 0; i < gameBoardBoxes.size(); i++){
        for(int j = 0; j < gameBoardBoxes[i].size(); j++){
            QWidget* tmpW = gameBoardBoxes[i][j];

            gameBoardNodes[i * gridSize + j]->addNearbyWidget(tmpW);//==
            if((i+1) < gridSize)
                gameBoardNodes[(i+1) * gridSize + j]->addNearbyWidget(tmpW);//+=
            if((j+1) < gridSize)
                gameBoardNodes[i * gridSize + (j+1)]->addNearbyWidget(tmpW);//=+
            if((i+1) < gridSize && (j+1) < gridSize)
                gameBoardNodes[(i+1) * gridSize + (j+1)]->addNearbyWidget(tmpW);//++
        }
    }
}

void GameBoard::addNearbyNodesToBoxes()
{
    int numOfRects = gridSize - 1;
    for(int i = 0; i < numOfRects; i++){
        for(int j = 0; j < numOfRects; j++){
            box* tmpW = gameBoardBoxes[i][j];
            tmpW->topLeft = gameBoardNodes[i * gridSize + j];
            tmpW->bottomLeft = gameBoardNodes[(i+1) * gridSize + j];
            tmpW->topRight = gameBoardNodes[i * gridSize + (j+1)];
            tmpW->bottomRight = gameBoardNodes[(i+1) * gridSize + (j+1)];
        }
    }
}

void GameBoard::connectSignalsSlots()
{
    //connect buttons to slot
    for(int i = 0; i < gridSize; i++)
        for(int j = 0; j < gridSize; j++)
            connect(gameBoardNodes[i * gridSize + j]->nodeBtn, SIGNAL(clicked()), this, SLOT(setLineCoord()));
}

void GameBoard::checkGameWin()
{
    updateWinningPlayer();
    bool gameOver = true;
    for(int i=0; i<gridSize-1; i++){
        for(int j=0; j<gridSize-1; j++){
            box* temp = gameBoardBoxes[i][j];
            if(!temp->filled)
                gameOver = false;
        }
    }
    if(gameOver){
        QMessageBox gameOverBox;
        QString gameOverText;
        if(calculateWinningPlayer()==NULL){
            gameOverText = "Game Over! You tied! \n""Go to Menu -> Newgame to play again.";
        }
        else{
        gameOverText = "Game Over! Player " + calculateWinningPlayer()->getPlayerName() + " Won! \n""Go to Menu -> Newgame to play again.";
        }
        gameOverBox.setText(gameOverText);
        gameOverBox.exec();
    }
}

void GameBoard::updateCurrentPlayer()
{
    player* currentPlayer = players[playerTurn];
    ui->playerTurnL->setText(currentPlayer->getPlayerName());
}

void GameBoard::updateWinningPlayer()
{
    player* winningPlayer = calculateWinningPlayer();
    if(winningPlayer)
        ui->winningPlayerL->setText(winningPlayer->getPlayerName());
    else
        ui->winningPlayerL->setText("TIED");
}

void GameBoard::setLineCoord()
{
    //private slot connected to every QPushButton
    QObject *callerBtn = sender();
    QPushButton *castedBtn = qobject_cast<QPushButton*>(callerBtn);

    if(firstLinePoint == NULL)
        firstLinePoint = castedBtn;
    else{
        secondLinePoint = castedBtn;

        node *firstNode = gameBtnNodeMap[firstLinePoint];
        node *secondNode = gameBtnNodeMap[secondLinePoint];

        if(firstNode->makeMove(secondNode->getQPoint()) && secondNode->makeMove(firstNode->getQPoint())){
            vector<QPushButton*> tmp;
            tmp.push_back(firstLinePoint);
            tmp.push_back(secondLinePoint);
            QLine *newLine = new QLine();
            savedLines.push_back(newLine);
            gameLineLocMap[newLine] = tmp;
            processTurn();
            this->update();
        }

        firstLinePoint = NULL;
        secondLinePoint = NULL;
    }
}

void GameBoard::drawLines(QPainter* p)
{
    for(int i = 0; i < savedLines.size(); i++){
        QLine *tmp = savedLines[i];
        vector<QPushButton*> linePoints = gameLineLocMap[tmp];
        QPoint first = fixLineCoord(linePoints[0]->pos());
        QPoint second = fixLineCoord(linePoints[1]->pos());
        tmp->setPoints(first, second);

        p->drawLine(*tmp);
    }
}

void GameBoard::paintEvent(QPaintEvent *pe)
{
    //default line painter
    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(10);
    p.setPen(pen);
    //-----------------------
    retranslatePushButtons();
    drawLines(&p);
}

//returns true if box is filled; else, false
bool GameBoard::checkBoardForFill()
{
    bool returnVal = false;
    for(int x = 0; x < (gridSize - 1); x++)
    {
        for(int y = 0; y < (gridSize - 1); y++)
        {
            box *temp = gameBoardBoxes[x][y];
            //checks top left push button to see if it can move down or right
            if(!(temp->topLeft->canDown) && !(temp->topLeft->canRight))
            {
                //checks bottom right push button to see if it can move up or left
                if(!(temp->bottomRight->canUp) && !(temp->bottomRight->canLeft))
                {
                    if(!temp->filled){

                        //increments the player's score by one
                        players[playerTurn]->setPlayerScore(players[playerTurn]->getPlayerScore()+1);
                        //fills box with player's color
                        temp->fill(players[playerTurn]->getPlayerColor());
                        returnVal = true;
                    }
                }
            }
        }
    }
    return returnVal;
}

void GameBoard::processTurn()
{
    bool filled = checkBoardForFill();
    //if a box was not completed
    checkGameWin();
    if(!filled)
    {
        playerTurn++;
        //checks if the playerTurn has exceeded the number of selected players
        if(playerTurn>=numOfPlayers)
        {
            playerTurn = 0;
        }
    }
    updateCurrentPlayer();
}

player* GameBoard::calculateWinningPlayer()
{
    int max = 0;
    player *winningPlayer = NULL;
    for(int i = 0; i < numOfPlayers; i++)
    {
        if(players[i]->getPlayerScore() == max)
            winningPlayer = NULL;

        //Checks to see if player has higher score than current high score
        if(players[i]->getPlayerScore() > max){
            max = players[i]->getPlayerScore();
            winningPlayer = players[i];
        }

    }
    return winningPlayer;
}
