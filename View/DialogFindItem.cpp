#include "DialogFindItem.hpp"

DialogFindItem::DialogFindItem(DataManager* dm, QWidget* parent):
	QDialog(parent),
	ui{ new Ui::DialogFindItem() },
	dataManager{dm}
{
	ui->setupUi(this);

}

DialogFindItem::~DialogFindItem()
{
	delete ui;
}

QVector<const DeviceLocation*> DialogFindItem::findItem()
{
	std::vector<const DeviceLocation*> resultFound;
	if (ui->rbName->isChecked()) {
		std::string nameItem{ ui->lineEdit->text().toStdString() };
		resultFound = dataManager->findItemByName(nameItem);
	}
	else {
		int64_t numberItem{ ui->lineEdit->text().toLongLong() };
		resultFound = dataManager->findItemByNumber(numberItem);
	}
	return QVector<const DeviceLocation*>(resultFound.begin(), resultFound.end());
}
