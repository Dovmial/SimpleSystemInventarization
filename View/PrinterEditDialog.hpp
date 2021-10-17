#pragma once

#include <QWidget>
#include "ui_PrinterEditDialog.h"
#include "AbstractEditDialog.hpp"

class PrinterEditDialog : public AbstractEditDialog
{
	Q_OBJECT
public:
	PrinterEditDialog(std::shared_ptr<DataManager> dm, QWidget* parent = nullptr);
	~PrinterEditDialog();
	std::unique_ptr<Item> createItem() override;
private:
	Ui::PrinterEditDialog* ui;
};

