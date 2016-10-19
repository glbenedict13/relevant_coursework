#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include <gameboard.h>
#include <string>
#include <QDebug>

namespace Ui {
class StartScreen;
}

class StartScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = 0);
    ~StartScreen();

    GameBoard* gb;

private:
    Ui::StartScreen *ui;

private slots:
    void startGame();
    void newGame();

};

#endif // STARTSCREEN_H
