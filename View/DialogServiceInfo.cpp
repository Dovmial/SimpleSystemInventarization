
#include "DialogServiceInfo.hpp"

DialogServiceInfo::DialogServiceInfo(Item* item_, QWidget* parent) :
	QDialog(parent),
	ui{ new Ui::DialogServiceInfo() },
	item{ item_ }
{
	ui->setupUi(this);
}

DialogServiceInfo::~DialogServiceInfo() {
	delete ui;
}

void DialogServiceInfo::addSignServiceInfo() {
	std::string description{ ui->pteServiceInfo->toPlainText().toStdString() };
	std::string date{ ui->leDate->text().toStdString() };
	item->addSignService(description, date);
}
