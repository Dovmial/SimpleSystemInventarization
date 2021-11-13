#ifndef __TABLEFOUNDDEVICES__HPP__
#define __TABLEFOUNDDEVICES__HPP__

#include <QtWidgets/QMainWindow>
#include "ui_TableFoundDevices.h"
#include "RoomViewer.hpp"

class TableFoundDevices : public QMainWindow {
	Q_OBJECT
public:
	TableFoundDevices(RoomViewer* rm, const QVector<const DeviceLocation*>& foundDevices_);
	~TableFoundDevices();
private slots:
	
	void on_tableView_clicked(QModelIndex index);

private:
	void configTableView();
private:
	Ui::TableFoundDevices* ui;
	RoomViewer* roomViewer;
	QVector<const DeviceLocation*> foundDevices;
	QStandardItemModel* foundDeviceTableModel;
};
#endif