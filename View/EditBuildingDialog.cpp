#include "EditBuildingDialog.hpp"
#include "ui_EditBuildingDialog.h"
#include "qmessagebox.h"

EditBuildingDialog::EditBuildingDialog(DataManager* dm, QWidget *parent)
	: dataManager{dm},
	QDialog(parent)
{
	ui = new Ui::EditBuildingDialog();
	ui->setupUi(this);
}

EditBuildingDialog::~EditBuildingDialog()
{
	delete ui;
}

void EditBuildingDialog::addBuilding()
{
	std::string nameBuilding{ui->leCreateBuildingName->text().toStdString()};
	if (!dataManager->getBuilding(nameBuilding))
		dataManager->addBuilding(nameBuilding);
	else
		QMessageBox::warning(this, QStringLiteral(u"Ошибка"), QStringLiteral(u"Такое здание уже есть!"));
}

