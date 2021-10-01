#include "View.h"


View::View(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}
