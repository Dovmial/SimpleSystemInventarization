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
	auto number		{ ui->leName->text().toLongLong()				};
	auto otherInfo	{ ui->teOtherInfo->toPlainText().toStdString()	};

	dataManager->setDataOther(name, otherInfo);
	auto item{ std::move(
		dataManager->createItem(
			DataManager::typeITEquipment::typeoOtherITEquipment,
			number,
			dataManager->getCurrentLocationInfo().second,
			dataManager->getCurrentLocationInfo().first)
	) };
	return item;
}
