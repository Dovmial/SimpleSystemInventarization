#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RoomViewer.h"
#include "../SimpleSystemInventarization/DataManager.hpp"
#include "../SimpleSystemInventarization/Room.hpp"
#include <memory>

class RoomViewer : public QMainWindow
{
    Q_OBJECT
public:
    RoomViewer(std::unique_ptr<DataManager> dm, QWidget* parent = Q_NULLPTR);
    ~RoomViewer();

    void setRoom(Room* room_);
    Room* getRoom()const;
private slots:
    void on_mnuAddItem_triggered();
private:
    Ui::RoomViewer* ui;
    std::unique_ptr<DataManager> dataManager;
    Room* room;
    QLabel* currentLocationInfo;
};
