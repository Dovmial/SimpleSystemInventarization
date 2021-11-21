#include "PrinterEditDialog.hpp"
#include <tuple>

PrinterEditDialog::PrinterEditDialog(DataManager* dm, QWidget* parent) :
	ui{ new Ui::PrinterEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

PrinterEditDialog::PrinterEditDialog(DataManager* dm, Item* item, QWidget* parent)
	:AbstractEditDialog(dm, parent),
	ui{ new Ui::PrinterEditDialog() }
{
	ui->setupUi(this);
	ui->leName->setText(QString::fromStdString(item->getName()));
	ui->leNumber->setText(QString::number(item->getInventoryNumber()));
	auto pITEquipment{ item->getITequipment().get() };
	Printer* printer = dynamic_cast<Printer*>(pITEquipment);
	ui->leCartFilName->setText(QString::fromStdString(printer->getCartridge().getName()));
	auto type{ printer->getPrinterType() };
	switch (type)
	{
	case Printer::PrinterType::PRINTER:
		ui->rbPrinterType->setChecked(true);
		break;
	case Printer::PrinterType::MFU:
		ui->rbMFUtype->setChecked(true);
		break;
	case Printer::PrinterType::PRINTER3D:
		ui->rb3Dtype->setChecked(true);
		break;
	}
}

PrinterEditDialog::~PrinterEditDialog() {
	delete ui;
}

Item* PrinterEditDialog::createItem()
{
	auto name		{ ui->leName->text().toStdString		()};
	auto cartridge	{ ui->leCartFilName->text().toStdString	()};
	auto number		{ ui->leNumber->text().toLongLong		()};

	auto printerType{ [&]()->Printer::PrinterType {
		if (ui->rbPrinterType->isChecked()) {
			return Printer::PrinterType::PRINTER;
		}
		else if (ui->rbMFUtype->isChecked()) {
			return Printer::PrinterType::MFU;
		}
		else {
			return  Printer::PrinterType::PRINTER3D;
		}
	}() };
	
	dataManager->setDataPrinter(name, cartridge, printerType);
	auto item{ std::move(dataManager->createItem(
		DataManager::typeITEquipment::typePrinter,
		number,
		dataManager->getCurrentLocationIndexes()
		)
	)};
	return item;
}

