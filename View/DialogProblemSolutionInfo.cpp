
#include "DialogProblemSolutionInfo.hpp"

DialogProblemSolutionInfo::DialogProblemSolutionInfo(Item* item_, QWidget* parent) :
	QDialog(parent),
	ui{ new Ui::DialogProblemSolutionInfo() },
	item{ item_ }
{
	ui->setupUi(this);
	ui->dateEdit->setDate(QDate::currentDate());
}

DialogProblemSolutionInfo::~DialogProblemSolutionInfo() {
	delete ui;
}

void DialogProblemSolutionInfo::addSignProblemSolutionInfo() {
	std::string problem{ ui->pteProblem->toPlainText().toStdString() };
	std::string solution{ ui->pteSolution->toPlainText().toStdString() };
	std::string date{ ui->dateEdit->text().toStdString() };
	item->addSignProblemsSolutions(problem, date, solution);
}