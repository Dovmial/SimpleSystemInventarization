#ifndef __DIALOGFINDITEM__HPP__
#define __DIALOGFINDITEM__HPP__

#include "ui_DialogFindItem.h"
#include "../SimpleSystemInventarization/DataManager.hpp"
class DialogFindItem : public QDialog {
public:
	DialogFindItem(DataManager* dm, QWidget* parent = nullptr);
	~DialogFindItem();
	QVector<const DeviceLocation*> findItem();
private:
	Ui::DialogFindItem* ui;
	DataManager* dataManager;
};
#endif // __DIALOGFINDITEM__HPP__

