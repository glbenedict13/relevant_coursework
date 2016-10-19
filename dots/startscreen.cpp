#include "startscreen.h"
#include "ui_startscreen.h"
using namespace std;

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    this->setWindowTitle("Dots");
    gb = NULL;
    connect(ui->startB, SIGNAL(clicked()), SLOT(startGame()));
    connect(ui->actionNew_Game, SIGNAL(triggered()), SLOT(newGame()));
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::newGame()
{
    ui->mainVBL->removeWidget(gb);
    delete gb;
    ui->startScreenWidget->show();
}

void StartScreen::startGame()
{
    char boardSizeChar = ui->boardSizeCB->currentText().toStdString()[0];//first char of boardSize combobox
    char numOfPlayerChar = ui->numberOfPlayersCB->currentText().toStdString()[0];//first char of numOfPlayer combobox
    int boardSize = boardSizeChar - '0';//converting ASCII char to int
    int numOfPlayers = numOfPlayerChar - '0';//converting ASCII char to int

    gb = new GameBoard(boardSize, numOfPlayers, this);//init gameboard of correct size and number of players
    ui->startScreenWidget->hide();//hide current central widget
    ui->mainVBL->addWidget(gb);
}
