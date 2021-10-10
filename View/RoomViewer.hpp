#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RoomViewer.h"

class RoomViewer : public QMainWindow
{
    Q_OBJECT

public:
    RoomViewer(QWidget* parent = Q_NULLPTR);
    ~RoomViewer();
private slots:
    void on_mnuAddItem_triggered();
private:
    Ui::RoomViewer* ui;
};
