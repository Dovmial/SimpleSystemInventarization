#ifndef __ROOMVIEWER__HPP__
#define __ROOMVIEWER__HPP__

#include <QtWidgets/QMainWindow>
#include "ui_RoomViewer.h"
#include "../SimpleSystemInventarization/DataManager.hpp"
#include "../SimpleSystemInventarization/Room.hpp"
#include "../SimpleSystemInventarization/Deserializer.hpp"
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
	void showFoundItem(const DeviceLocation* devicesFound);
private slots:
	void on_mnuAddItem_triggered	();
	void on_mnuAddBuilding_triggered();
	void on_mnuAddRoom_triggered	();
	void on_mnuFindItem_triggered	();
	void on_mnuSave_triggered		();
	void on_mnuHelp_triggered		();
	void on_mnuAbout_triggered		();
	void on_mnuAbout_QT_triggered	();
	
	void on_btnTransitRoom_clicked();
	void on_btnTransitBuilding_clicked();

	void slotEditRecord(QModelIndex index);
	void slotShowInfoSelectItem(QModelIndex index);
	void slotAddProblemSolutionInfo();
	void slotAddServiceInfo();
	void slotRemoveDevice();
	void slotRemoveServiceSign();
	void slotRemoveProblemSolutiondSign();
	void slotEditFont();

	void slotContextMenuItem(QPoint pos);
	void slotContextMenuServices(QPoint pos);
	void slotContextMenuProblemsSolutions(QPoint pos);
	void slotShowContextMenuInfoDevice(QPoint pos);

private:
	void setTextStatusBar(const std::string& str1, const std::string& str2);
	void updateRoomViewer();
	void updateRoomContent();
	void updateTableDevices();
	void updateTableServices();
	void updateTableProblemsSolutions();
	void setHeadersModels();
	void tablesModelsConfiguration();
	void setHeadersDeviceTable();
	void setHeadersServiceTable();
	void setHeadersProblemSolutionTable();
	
private:
	Ui::RoomViewer* ui;
	std::unique_ptr<DataManager > dataManager ;
	std::unique_ptr<Deserializer> deserializer;
	Room* room;
	QLabel* currentLocationInfo;
	QStandardItemModel* deviceTableModel;
	QStandardItemModel* serviceTableModel;
	QStandardItemModel* problemSolutionTableModel;
};
#endif