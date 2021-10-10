#include "CreateItemDialog.hpp"
#include <QDebug>
CreateItemDialog::CreateItemDialog(QWidget* parent) :QDialog(parent)
{
	ui = new Ui::CreateItemDialog();
	ui->setupUi(this);
}

CreateItemDialog::~CreateItemDialog() {
	delete ui;
}

std::tuple<QString, int64_t, int> CreateItemDialog::getItemBaseInfo()
{
	auto name{ ui->leName->text() };
	auto number{ ui->leInvNumber->text().toLongLong() };
	int typePC{
		[&]()->int {
			if (ui->rbPCtype->isChecked()) {
			return 1;
		}
		else if (ui->rbMonitorType->isChecked()) {
			return 2;
		}
		else if (ui->rbPrinterType->isChecked()) {
				return 3;
		}
		else {
			return 4;
		}
	}()
	};
	//qDebug() << typePC;
	return std::make_tuple(name, number, typePC);
}
