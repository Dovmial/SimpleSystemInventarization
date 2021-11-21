#include "OtherEditDialog.hpp"

OtherEditDialog::OtherEditDialog(DataManager* dm, QWidget* parent) :
	ui{ new Ui::OtherEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

OtherEditDialog::OtherEditDialog(DataManager* dm, Item* item, QWidget* parent)
	:AbstractEditDialog(dm, parent),
	ui{ new Ui::OtherEditDialog() }
{
	ui->setupUi(this);
	ui->leName->setText(QString::fromStdString(item->getName()));
	ui->leNumber->setText(QString::number(item->getInventoryNumber()));
	auto pITEquipment{ item->getITequipment().get() };
	OtherEquipment* pOtherEq = dynamic_cast<OtherEquipment*>(pITEquipment);
	ui->teOtherInfo->setText(QString::fromStdString(pOtherEq->getSomeInfo()));
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
			dataManager->getCurrentLocationIndexes()
		)};
	return item;
}
