#ifndef __OTHEREDITDIALOG__HPP__
#define __OTHEREDITDIALOG__HPP__

#include <QWidget>
#include "ui_OtherEditDialog.h"
#include "AbstractEditDialog.hpp"

class OtherEditDialog : public AbstractEditDialog
{
	Q_OBJECT
public:
	OtherEditDialog(DataManager* dm, QWidget* parent = nullptr);
	OtherEditDialog(DataManager* dm, Item* item, QWidget* parent = nullptr);
	~OtherEditDialog();
	Item* createItem() override;
private:
	Ui::OtherEditDialog* ui;
};
#endif
