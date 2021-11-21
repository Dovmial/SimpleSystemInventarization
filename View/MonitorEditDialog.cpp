#include "MonitorEditDialog.hpp"

MonitorEditDialog::MonitorEditDialog(DataManager* dm,
	QWidget* parent) :
	ui{ new Ui::MonitorEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

MonitorEditDialog::MonitorEditDialog(DataManager* dm, Item* item, QWidget* parent)
	:AbstractEditDialog(dm, parent),
	ui{ new Ui::MonitorEditDialog() }	
{
	ui->setupUi(this);
	ui->leName->setText(QString::fromStdString(item->getName()));
	ui->leNumber->setText(QString::number(item->getInventoryNumber()));
	auto pITEquipment{ item->getITequipment().get() };
	Monitor* monitor = dynamic_cast<Monitor*>(pITEquipment);
	ui->leDiagonal->setText(QString::number(monitor->getDiagonal()));
}

MonitorEditDialog::~MonitorEditDialog()
{
	delete ui;
}

Item* MonitorEditDialog::createItem() 
{
	auto name		{ ui->leName	->text().toStdString()	};
	auto diagonal	{ ui->leDiagonal->text().toFloat()		};
	auto number		{ ui->leNumber	->text().toLongLong()	};

	dataManager->setDataMonitor(name, diagonal);
	auto item{ dataManager->createItem(
		DataManager::typeITEquipment::typeMonitor,
		number,
		dataManager->getCurrentLocationIndexes()
	)};
	return item;
}
