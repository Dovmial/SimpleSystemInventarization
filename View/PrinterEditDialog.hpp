#ifndef __PRINTEREDITDIALOG__HPP__
#define __PRINTEREDITDIALOG__HPP__

#include <QWidget>
#include "ui_PrinterEditDialog.h"
#include "AbstractEditDialog.hpp"

class PrinterEditDialog : public AbstractEditDialog
{
	Q_OBJECT
public:
	PrinterEditDialog(DataManager* dm, QWidget* parent = nullptr);
	PrinterEditDialog(DataManager* dm, Item* item, QWidget* parent = nullptr);
	~PrinterEditDialog();
	Item* createItem() override;
private:
	Ui::PrinterEditDialog* ui;
};
#endif