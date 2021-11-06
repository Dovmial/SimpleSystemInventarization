
#include "CreateRoomDialog.hpp"
#include <qmessagebox.h>
CreateRoomDialog::CreateRoomDialog(DataManager* dm, QWidget* parent):
	dataManager{dm},
	QDialog(parent)
{
	ui = new Ui::CreateRoomDialog;
	ui->setupUi(this);
	ui->lblNameBuilding->setText(
		QString::fromStdString(dataManager->getCurrentLocationInfo().first)
	);
}

CreateRoomDialog::~CreateRoomDialog()
{
	delete ui;
}

void CreateRoomDialog::addRoom()
{
	std::string nameNewRoom = ui->lineEdit->text().toStdString();
	if (dataManager->getCurrentBuilding()->isExistRoom(nameNewRoom)) {
		QMessageBox::critical(this, "Error", "Such a room already exists!\n");
		return;
	}
	dataManager->getCurrentBuilding()->addRoom(nameNewRoom);
}

