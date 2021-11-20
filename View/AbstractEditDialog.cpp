#include "AbstractEditDialog.hpp"

AbstractEditDialog::AbstractEditDialog(DataManager* dm, QWidget* parent) :
	dataManager(dm),
	QDialog(parent)
{}