#include "TableFoundDevices.hpp"
#include <qmessagebox.h>

TableFoundDevices::TableFoundDevices(
	RoomViewer* rm,
	const QVector<const DeviceLocation*>& foundDevices_)
	:QMainWindow(rm),
	roomViewer{ rm },
	foundDevices{ foundDevices_ },
	foundDeviceTableModel{new QStandardItemModel(this)},
	ui{new Ui::TableFoundDevices()}
{
	ui->setupUi(this);
	configTableView();
}

TableFoundDevices::~TableFoundDevices()
{
	delete ui;
}

void TableFoundDevices::on_tableView_clicked(QModelIndex index)
{
	roomViewer->showFoundItem(foundDevices[index.row()]);
}

void TableFoundDevices::configTableView()
{

	foundDeviceTableModel->setColumnCount(4);
	foundDeviceTableModel->setHorizontalHeaderLabels(
		QStringList()
		<< QStringLiteral(u"Здание ID")
		<< QStringLiteral(u"Комната ID")
		<< QStringLiteral(u"Оборудование")
		<< QStringLiteral(u"Инвентарный №")
	);
	ui->tableView->setModel(foundDeviceTableModel);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->resizeColumnsToContents();
	ui->tableView->horizontalHeader()->setStretchLastSection(true);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

	QList<QStandardItem*> deviceStringList;
	for (const auto& device : foundDevices) {
		deviceStringList.append(
			new QStandardItem(QString::number(device->getLocationIndexes().first))
		);

		deviceStringList.append(
			new QStandardItem(QString::number(device->getLocationIndexes().second))
		);

		deviceStringList.append(
			new QStandardItem(QString::fromStdString(device->getItem()->getName()))
		);

		deviceStringList.append(
			new QStandardItem(QString::number(device->getItem()->getInventoryNumber()))
		);

		foundDeviceTableModel->insertRow(
			foundDeviceTableModel->rowCount(), deviceStringList
		);
		deviceStringList.clear();
	}
}
