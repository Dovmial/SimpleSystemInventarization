#include "DialogTransitToBuilding.hpp"

DialogTransitToBuilding::DialogTransitToBuilding(DataManager* dm, QWidget* parent)
	:dataManager{dm},
	ui{new Ui::DialogTransitToBuilding()},
	QDialog(parent)
{
	ui->setupUi(this);
	auto buildingList{ dataManager->getListBuildingNames() };
	for (const auto& building : buildingList) {
		ui->comboBox->addItem(QString::fromStdString(building));
	}

}

DialogTransitToBuilding::~DialogTransitToBuilding()
{
	delete ui;
}

QString DialogTransitToBuilding::getNameBuildingTransit() const
{
	return ui->comboBox->currentText();
}
