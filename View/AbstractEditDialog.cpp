#include "AbstractEditDialog.hpp"

AbstractEditDialog::AbstractEditDialog(
	std::shared_ptr<DataManager> dm, QWidget* parent) :
	dataManager(dm),
	QDialog(parent)
{}