#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RoomViewer.h"
#include "../SimpleSystemInventarization/GetDatas.hpp"

class RoomViewer : public QMainWindow
{
    Q_OBJECT

public:
    RoomViewer(QWidget* parent = Q_NULLPTR);
    ~RoomViewer();
private slots:
    void on_mnuAddItem_triggered();
private:
   // GetDatas getDatas;
    Ui::RoomViewer* ui;
};
