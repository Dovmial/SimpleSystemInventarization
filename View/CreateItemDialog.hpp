#pragma once
#include <QWidget>
#include "ui_CreateItemDialog.h"
#include <tuple>

namespace Ui { class CreateItemDialog; }
class CreateItemDialog : public QDialog {
	Q_OBJECT
public:
	CreateItemDialog(QWidget* parent = nullptr);
	~CreateItemDialog();
	//name number type checkinfo
	std::tuple<QString, int64_t, int> getItemBaseInfo();

private slots:
	
private:

	Ui::CreateItemDialog *ui;
	
};