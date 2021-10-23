#include "OtherEditDialog.hpp"

OtherEditDialog::OtherEditDialog(
	std::shared_ptr<DataManager> dm, QWidget* parent) :
	ui{ new Ui::OtherEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

OtherEditDialog::~OtherEditDialog() {
	delete ui;
}

std::unique_ptr<Item> OtherEditDialog::createItem()
{
	auto name		{ ui->leName->text().toStdString()				};
	auto number		{ ui->leName->text().toLongLong()				};
	auto otherInfo	{ ui->teOtherInfo->toPlainText().toStdString()	};

	dataManager->setDataOther(name, otherInfo);
	auto item{ std::move(
		dataManager->createItem(
			DataManager::typeITEquipment::typeoOtherITEquipment, number)
	) };
	return std::move(item);
}
