#ifndef __DIALOGPROBLEMSOLUTIONINFO__HPP__
#define __DIALOGPROBLEMSOLUTIONINFO__HPP__

#include "ui_DialogProblemSolutionInfo.h" 
#include "../SimpleSystemInventarization/Item.hpp"

class DialogProblemSolutionInfo : public QDialog {
public:
	DialogProblemSolutionInfo(Item* item_, QWidget* parent = nullptr);
	~DialogProblemSolutionInfo();

	void addSignProblemSolutionInfo();
private:
	Ui::DialogProblemSolutionInfo * ui;
	Item* item;
};

#endif
