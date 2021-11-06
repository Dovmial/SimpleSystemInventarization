#ifndef __EDITBUILDINGDIALOG__HPP__
#define __EDITBUILDINGDIALOG__HPP__

#include <QDialog>
#include "../SimpleSystemInventarization/DataManager.hpp"

namespace Ui { class EditBuildingDialog; };

class EditBuildingDialog : public QDialog
{
	Q_OBJECT

public:
	EditBuildingDialog(DataManager* dm, QWidget *parent = Q_NULLPTR);
	~EditBuildingDialog();
	void addBuilding();
private:
	Ui::EditBuildingDialog *ui;
	DataManager* dataManager;
};

#endif // !__CREATEBUILDINGDIALOG__HPP__