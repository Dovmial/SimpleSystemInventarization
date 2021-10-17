#pragma once

#include <QDialog>
#include "IItemCreatable.hpp"
#include "../SimpleSystemInventarization/DataManager.hpp"
#include <memory>

class AbstractEditDialog : public QDialog, public IItemCreatable {
	Q_OBJECT
public:
	AbstractEditDialog(std::shared_ptr<DataManager> dm,
		QWidget* parent = nullptr);

protected:
	std::shared_ptr<DataManager> dataManager;
};