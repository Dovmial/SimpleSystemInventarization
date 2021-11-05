#include "RoomViewer.hpp"
#include "CreateItemDialog.hpp"

RoomViewer::RoomViewer(std::unique_ptr<DataManager> dm, QWidget* parent)
    : ui{new Ui::RoomViewer()},
    dataManager{ std::move(dm) },
    room{ nullptr },
    currentLocationInfo(new QLabel(this)),
    QMainWindow(parent)
{
    ui->setupUi(this);
    room = dataManager->getCurrentRoom();
    ui->lblRoomName->setText(QString::fromStdString(room->getName()));
    QString status = QString::fromStdString(
        "Build: " + dataManager->getCurrentLocationInfo().first +
        "\tRoom: " + dataManager->getCurrentLocationInfo().second
    );
    currentLocationInfo->setText(status);
    currentLocationInfo->setStyleSheet("QLabel {color: blue;}");
    ui->statusbar->addWidget(currentLocationInfo);
}

RoomViewer::~RoomViewer()
{
    delete ui;
}

void RoomViewer::setRoom(Room* room_) {
    room = room_;
}
Room* RoomViewer::getRoom()const {
    return room;
}
void RoomViewer::on_mnuAddItem_triggered() {
    auto pCrItemDialog{ new CreateItemDialog(nullptr) };
    if (pCrItemDialog->exec() == CreateItemDialog::Accepted) {
        auto dialog{ pCrItemDialog->getEditItemDialog(dataManager.get()) };
        if (dialog->exec() == QDialog::Accepted) {
            room->addItem(dialog->createItem());
            ui->pteInfoItems->setPlainText(
                QString::fromStdString(room->showItem(0)->getITequipment()->getInfo()));    
        }

    }
}