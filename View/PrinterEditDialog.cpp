#include "PrinterEditDialog.hpp"
#include <tuple>

PrinterEditDialog::PrinterEditDialog(DataManager* dm, QWidget* parent) :
	ui{ new Ui::PrinterEditDialog() },
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

PrinterEditDialog::~PrinterEditDialog() {
	delete ui;
}

std::unique_ptr<Item> PrinterEditDialog::createItem()
{
	auto name		{ ui->leName->text().toStdString		()};
	auto cartridge	{ ui->leCartFilName->text().toStdString	()};
	auto number		{ ui->leNumber->text().toLongLong		()};

	auto printerType{ [&]()->Printer::PrinterType {
		if (ui->rbPrinterType->isChecked()) {
			return Printer::PrinterType::Printer;
		}
		else if (ui->rbMFUtype->isChecked()) {
			return Printer::PrinterType::MFU;
		}
		else {
			return  Printer::PrinterType::Printer3D;
		}
	}() };
	
	dataManager->setDataPrinter(name, cartridge, printerType);
	auto item{ std::move(dataManager->createItem(
		DataManager::typeITEquipment::typePrinter, number) )};
	return std::move(item);
}

