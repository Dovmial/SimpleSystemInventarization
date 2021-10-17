#pragma once

#include <QWidget>
#include "ui_PCeditDialog.h"
#include "AbstractEditDialog.hpp"

class PCeditDialog : public AbstractEditDialog {
	Q_OBJECT
public:
	PCeditDialog(std::shared_ptr<DataManager> dm, QWidget* parent = nullptr);
	~PCeditDialog();
	std::unique_ptr<Item> createItem() override;
private:
	Ui::PCeditDialog* ui;
};