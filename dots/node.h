#ifndef NODE_H
#define NODE_H
#include <QPushButton>
#include <QPoint>
#include <vector>

using namespace std;
class node
{
public:
    node(QPushButton* nodeBtn, bool up, bool down, bool left, bool right, int row, int col);
    QPushButton *nodeBtn;
    bool nodeActive;
    bool canUp;
    bool canDown;
    bool canLeft;
    bool canRight;

    QPoint getQPoint();
    bool makeMove(QPoint pt);
    vector<QWidget*> getNearbyWidgets();
    void addNearbyWidget(QWidget* w);
private:
    vector<QWidget*> nearbyWidgets;
    int col;// j
    int row;// i

};

#endif // NODE_H
