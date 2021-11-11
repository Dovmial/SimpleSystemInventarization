#ifndef __DIALOGSERVICEINFO__HPP__
#define __DIALOGSERVICEINFO__HPP__

#include "ui_dialogServiceInfo.h"
#include "../SimpleSystemInventarization/DataManager.hpp"


class  DialogServiceInfo: public QDialog
{
public:
	 DialogServiceInfo(Item* item_, QWidget* parent);
	~ DialogServiceInfo();

	void addSignServiceInfo();
private:
	Ui::DialogServiceInfo* ui;
	Item* item;
};

#endif