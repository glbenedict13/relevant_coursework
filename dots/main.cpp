#include "startscreen.h"
#include <QApplication>
#include "player.h"
#include <QString>
#include <QApplication>
#include <vector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartScreen w;
    w.show();

    return a.exec();
}

