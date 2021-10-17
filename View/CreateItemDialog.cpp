#include "CreateItemDialog.hpp"
#include "PCeditDialog.hpp"
#include "MonitorEditDialog.hpp"
#include "PrinterEditDialog.hpp"
#include "OtherEditDialog.hpp"
#include "qdialog.h"
#include <qfontdialog.h>

CreateItemDialog::CreateItemDialog(QWidget* parent) :QDialog(parent)
{
	ui = new Ui::CreateItemDialog();
	ui->setupUi(this);
}

CreateItemDialog::~CreateItemDialog() {
	delete ui;
}

AbstractEditDialog* CreateItemDialog::getEditItemDialog(std::shared_ptr<DataManager> dm)
{
	if (ui->rbPCtype->isChecked())
		return new PCeditDialog(dm, this);
	else if (ui->rbMonitorType->isChecked())
		return new MonitorEditDialog(dm, this);
	else if (ui->rbPrinterType->isChecked())
		return new PrinterEditDialog(dm,this);
	else
		return new OtherEditDialog(dm, this);
}

