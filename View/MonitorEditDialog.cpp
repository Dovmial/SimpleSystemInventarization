#include "MonitorEditDialog.hpp"

MonitorEditDialog::MonitorEditDialog(DataManager* dm,
	QWidget* parent) :
	ui{ new Ui::MonitorEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

MonitorEditDialog::~MonitorEditDialog() {
	delete ui;
}

std::unique_ptr<Item> MonitorEditDialog::createItem() 
{
	auto name		{ ui->leName	->text().toStdString()	};
	auto diagonal	{ ui->leDiagonal->text().toFloat()		};
	auto number		{ ui->leNumber	->text().toLongLong()	};

	dataManager->setDataMonitor(name, diagonal);
	auto item{ std::move(dataManager->createItem(
		DataManager::typeITEquipment::typeMonitor,
		number))
	};
	return std::move(item);
}
