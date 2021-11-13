#include "OtherEditDialog.hpp"

OtherEditDialog::OtherEditDialog(DataManager* dm, QWidget* parent) :
	ui{ new Ui::OtherEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

OtherEditDialog::~OtherEditDialog() {
	delete ui;
}

Item* OtherEditDialog::createItem()
{
	auto name		{ ui->leName->text().toStdString()				};
	auto number		{ ui->leNumber->text().toLongLong()				};
	auto otherInfo	{ ui->teOtherInfo->toPlainText().toStdString()	};

	dataManager->setDataOther(name, otherInfo);
	auto item{ 
		dataManager->createItem(
			DataManager::typeITEquipment::typeoOtherITEquipment,
			number,
			dataManager->getCurrentLocationInfo().first,
			dataManager->getCurrentLocationInfo().second)
	 };
	return item;
}
