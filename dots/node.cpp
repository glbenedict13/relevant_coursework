#include "node.h"
#include <QDebug>

node::node(QPushButton *nodeBtn, bool up, bool down, bool left, bool right, int row, int col):
    nodeBtn(nodeBtn),
    nodeActive(true),
    canUp(up),
    canDown(down),
    canLeft(left),
    canRight(right),
    row(row),
    col(col)
{
    //code
}

QPoint node::getQPoint()
{
    return QPoint(row, col);
}

bool node::makeMove(QPoint pt)
{
    bool moveMade = false;
    if(nodeActive){
        QPoint result = getQPoint() - pt;

        if(result == QPoint(0,1)){
            canLeft = false;
            moveMade = true;
        }
        else if(result == QPoint(1,0)){
            canUp = false;
            moveMade = true;
        }
        else if(result == QPoint(-1, 0)){
            canDown = false;
            moveMade = true;
        }
        else if(result == QPoint(0, -1)){
            canRight = false;
            moveMade = true;
        }
    }

    if(!canUp && !canDown && !canLeft && !canRight){
        nodeBtn->setEnabled(false);
        nodeActive = false;
    }

    return moveMade;
}

vector<QWidget*> node::getNearbyWidgets()
{
    return nearbyWidgets;
}

void node::addNearbyWidget(QWidget *w)
{
    nearbyWidgets.push_back(w);
}
