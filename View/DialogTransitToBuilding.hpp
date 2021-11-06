#ifndef __DIALOGTRDNSITTOBUILDING__HPP__
#define __DIALOGTRDNSITTOBUILDING__HPP__

#include "ui_DialogTransitToBuilding.h"
#include <QDialog>
#include "../SimpleSystemInventarization/DataManager.hpp"

class DialogTransitToBuilding : public QDialog {
public:
	DialogTransitToBuilding(DataManager* dm, QWidget* parent = nullptr);
	~DialogTransitToBuilding();
	QString getNameBuildingTransit() const;
private:
	Ui::DialogTransitToBuilding* ui;
	DataManager* dataManager;
};
#endif // !__DIALOGTRDNSITTOBUILDING__HPP__
