#include "player.h"
#include <QString>

player::player()
{

}

player::player(int playerNumber, int playerColor, int playerScore, QString playerName):
    playerNumber(playerNumber),
    playerScore(playerScore),
    playerName(playerName)
{
    setPlayerColor(playerColor);
}

int player::getPlayerNumber(){
    return playerNumber;
}

string player::getPlayerColor(){
    return playerColor;
}

int player::getPlayerScore(){
    return playerScore;
}

QString player::getPlayerName(){
    return playerName;
}

void player::setPlayerNumber(int number){
    playerNumber = number;
}

void player::setPlayerColor(int color){
    string colors[4] = {"red", "blue", "yellow", "green"};
    playerColor = colors[color];
}

void player::setPlayerScore(int score){
    playerScore = score;
}

void player::setPlayerName(QString playerName){
    playerName = playerName;
}
