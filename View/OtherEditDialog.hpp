#pragma once
#include <QWidget>
#include "ui_OtherEditDialog.h"
#include "AbstractEditDialog.hpp"

class OtherEditDialog : public AbstractEditDialog
{
	Q_OBJECT
public:
	OtherEditDialog(DataManager* dm,QWidget* parent = nullptr);
	~OtherEditDialog();
	Item* createItem() override;
private:
	Ui::OtherEditDialog* ui;
};

