#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include "node.h"
#include <vector>


using namespace std;

namespace Ui {
class box;
}

class box : public QWidget
{
    Q_OBJECT

public:
    explicit box(QWidget *parent = 0);
    bool filled;
    node* topLeft;
    node* topRight;
    node* bottomLeft;
    node* bottomRight;

    void fill(string color);
    ~box();

private:
    Ui::box *ui;
};

#endif // BOX_H
