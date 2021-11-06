#ifndef __EDITROOMDIALOG__HPP__
#define __EDITROOMDIALOG__HPP__

#include <QDialog>
#include "ui_EditRoomDialog.h"
#include "../SimpleSystemInventarization/DataManager.hpp"

class EditRoomDialog : public QDialog {
	Q_OBJECT
public:
	EditRoomDialog(DataManager* dm, QWidget* parent = nullptr);
	~EditRoomDialog();
	void addRoom();
private slots:

private:
	DataManager* dataManager;
	Ui::EditRoomDialog* ui;
};
#endif // !__CREATEROOMDIALOG__HPP__