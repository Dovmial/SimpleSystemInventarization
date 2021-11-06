#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RoomViewer.h"
#include "../SimpleSystemInventarization/DataManager.hpp"
#include "../SimpleSystemInventarization/Room.hpp"
#include <memory>
#include <QStandardItemModel>

class RoomViewer : public QMainWindow
{
	Q_OBJECT
public:
	RoomViewer(std::unique_ptr<DataManager> dm, QWidget* parent = Q_NULLPTR);
	~RoomViewer();
public:
	void setRoom(Room* room_);
	Room* getRoom()const;


private slots:
	void on_mnuAddItem_triggered();
	void on_mnuAddBuilding_triggered();
	void on_mnuAddRoom_triggered();

	void on_btnTransitRoom_clicked();
	void on_btnTransitBuilding_clicked();
private:
	void setTextStatusBar(const std::string& str1, const std::string& str2);
	void updateRoomViewer();
private:
	Ui::RoomViewer* ui;
	std::unique_ptr<DataManager> dataManager;
	Room* room;
	QLabel* currentLocationInfo;
	QStandardItemModel* deviceTableModel;
	QStandardItemModel* serviceTableModel;
	QStandardItemModel* problemSolutionTableModel;
};
