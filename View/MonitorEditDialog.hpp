#pragma once

#include <QWidget>
#include "ui_MonitorEditDialog.h"
#include "AbstractEditDialog.hpp" 

class MonitorEditDialog: public AbstractEditDialog {
	Q_OBJECT
public:
	MonitorEditDialog(DataManager* dm, QWidget* parent = nullptr);
	MonitorEditDialog(DataManager* dm, Item* item, QWidget* parent = nullptr);
	~MonitorEditDialog();
	Item* createItem() override;
private slots:
	
private:
	Ui::MonitorEditDialog* ui;
};