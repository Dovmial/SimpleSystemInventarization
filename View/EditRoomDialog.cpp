
#include "EditRoomDialog.hpp"
#include <qmessagebox.h>
EditRoomDialog::EditRoomDialog(DataManager* dm, QWidget* parent):
	dataManager{dm},
	QDialog(parent)
{
	ui = new Ui::EditRoomDialog;
	ui->setupUi(this);
	ui->lblNameBuilding->setText(
		QString::fromStdString(dataManager->getCurrentLocationNames().first)
	);
}

EditRoomDialog::~EditRoomDialog()
{
	delete ui;
}

void EditRoomDialog::addRoom()
{
	std::string nameNewRoom = ui->lineEdit->text().toStdString();
	if (dataManager->getCurrentBuilding()->isExistRoom(nameNewRoom)) {
		QMessageBox::critical(this, "Error", "Such a room already exists!\n");
		return;
	}
	dataManager->getCurrentBuilding()->addRoom(nameNewRoom);
}

