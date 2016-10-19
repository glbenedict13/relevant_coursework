#include "box.h"
#include "ui_box.h"

box::box(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::box)
{
    filled = false;
    ui->setupUi(this);
}

void box::fill(string color)
{
    filled = true;
    QString setColor = "background-color: " + QString::fromStdString(color) + ";";
    ui->fillBox->setStyleSheet(setColor);
}

box::~box()
{
    delete ui;
}
