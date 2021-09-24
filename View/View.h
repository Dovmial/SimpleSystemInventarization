#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_View.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = Q_NULLPTR);

private:
    Ui::ViewClass ui;
};
