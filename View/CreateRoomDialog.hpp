#ifndef __CREATEROOMDIALOG__HPP__
#define __CREATEROOMDIALOG__HPP__

#include <QDialog>
#include "ui_CreateRoomDialog.h"
#include "../../SSI/SimpleSystemInventarization/DataManager.hpp"

class CreateRoomDialog : public QDialog {
	Q_OBJECT
public:
	CreateRoomDialog(DataManager* dm, QWidget* parent = nullptr);
	~CreateRoomDialog();
	void addRoom();
private slots:
	
	
	
private:
	DataManager* dataManager;
	Ui::CreateRoomDialog* ui;
};
#endif // !__CREATEROOMDIALOG__HPP__