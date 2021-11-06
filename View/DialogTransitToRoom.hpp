#ifndef __DIALOGTRANSITTOROOM__HPP__
#define __DIALOGTRANSITTOROOM__HPP__

#include <QDialog>
#include "ui_DialogTransitToRoom.h"
#include "../SimpleSystemInventarization/DataManager.hpp"

class DialogTransitToRoom: public QDialog {
public:
	DialogTransitToRoom(DataManager* dm, QWidget* parent = nullptr);
	~DialogTransitToRoom();

	QString getNameRoomTransit() const;
private:
	Ui::DialogTransitToRoom* ui;
	DataManager* dataManager;
};
#endif // ! __DIALOGTRANSITTOROOM__HPP__

