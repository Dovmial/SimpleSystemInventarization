#include "DialogTransitToRoom.hpp"

DialogTransitToRoom::DialogTransitToRoom(DataManager* dm, QWidget* parent):
	ui{ new Ui::DialogTransitToRoom() },
	dataManager{dm},
	QDialog(parent)
{
	ui->setupUi(this);
	ui->lblNameBuilding->setText(
		QString::fromStdString(dataManager->getCurrentLocationNames().first));
	
	auto roomsList{ dataManager->getListRoomNames() };
	QStringList list;
	for (const auto& room : roomsList) {
		list << QString::fromStdString(room);
	}
	ui->comboBox->addItems(list);
}

DialogTransitToRoom::~DialogTransitToRoom()
{
	delete ui;
}

QString DialogTransitToRoom::getNameRoomTransit() const
{
	return ui->comboBox->currentText();
}
