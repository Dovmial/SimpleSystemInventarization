#pragma once

#include <QWidget>
#include "ui_PCeditDialog.h"
#include "AbstractEditDialog.hpp"

class PCeditDialog : public AbstractEditDialog {
	Q_OBJECT
public:
	PCeditDialog(DataManager* dm, QWidget* parent = nullptr);
	~PCeditDialog();
	Item* createItem() override;
private:
	Ui::PCeditDialog* ui;
};