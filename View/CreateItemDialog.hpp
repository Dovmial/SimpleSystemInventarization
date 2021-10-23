#pragma once
#include <QWidget>
#include "ui_CreateItemDialog.h"
#include "../SimpleSystemInventarization/DataManager.hpp"
#include "AbstractEditDialog.hpp"
#include <memory>

//#include "../SimpleSystemInventarization/Item.hpp"
//namespace Ui { class CreateItemDialog; }
class CreateItemDialog : public QDialog {
	Q_OBJECT
public:
	CreateItemDialog(QWidget* parent = nullptr);
	~CreateItemDialog();

	AbstractEditDialog* getEditItemDialog(std::shared_ptr<DataManager> dm);
private slots:
	
private:
	Ui::CreateItemDialog *ui;
	
};