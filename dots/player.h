#include <QString>
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

using namespace std;


class player
{

public:
    player();
    player(int playerNumber, int playerColor, int playerScore, QString playerName);
    int getPlayerNumber();
    string getPlayerColor();
    QString getPlayerName();
    int getPlayerScore();
    void setPlayerNumber(int playerNumber);
    void setPlayerColor(int playerColor);
    void setPlayerScore(int playerScore);
    void setPlayerName(QString playerName);

private:


    int playerNumber;
    string playerColor;
    int playerScore;
    QString playerName;
};

#endif // PLAYER_H
