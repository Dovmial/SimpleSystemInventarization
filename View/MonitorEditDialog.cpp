#include "MonitorEditDialog.hpp"

MonitorEditDialog::MonitorEditDialog(DataManager* dm,
	QWidget* parent) :
	ui{ new Ui::MonitorEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
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
