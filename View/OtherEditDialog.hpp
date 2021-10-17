#pragma once
#include <QWidget>
#include "ui_OtherEditDialog.h"
#include "AbstractEditDialog.hpp"

class OtherEditDialog : public AbstractEditDialog
{
	Q_OBJECT
public:
	OtherEditDialog(
		std::shared_ptr<DataManager> dm,
		QWidget* parent = nullptr);
	~OtherEditDialog();
	std::unique_ptr<Item> createItem() override;
private:
	Ui::OtherEditDialog* ui;
};

