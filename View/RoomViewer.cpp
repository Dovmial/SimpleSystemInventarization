#include "RoomViewer.hpp"
#include "CreateItemDialog.hpp"

RoomViewer::RoomViewer(QWidget* parent)
    : ui{new Ui::RoomViewer()},
    QMainWindow(parent)
{
    ui->setupUi(this);
}

RoomViewer::~RoomViewer()
{
    delete ui;
}


void RoomViewer::on_mnuAddItem_triggered() {
    auto pCrItemDialog{ std::make_unique<CreateItemDialog>(nullptr) };
    if (pCrItemDialog->exec() == CreateItemDialog::Accepted) {
        auto info{ pCrItemDialog->getItemBaseInfo() };
        auto& [name, numb, type] {info};


    }

}