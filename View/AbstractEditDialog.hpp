#ifndef __ABSTRACTEDITDIALOG__HPP__
#define __ABSTRACTEDITDIALOG__HPP__

#include <QDialog>
#include "IItemCreatable.hpp"
#include "../SimpleSystemInventarization/DataManager.hpp"

class AbstractEditDialog : public QDialog, public IItemCreatable {
	Q_OBJECT
public:
	AbstractEditDialog(DataManager* dm,
		QWidget* parent = nullptr);
	
protected:
	DataManager* dataManager;
};
#endif