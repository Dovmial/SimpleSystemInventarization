#include "RoomViewer.hpp"
#include "CreateItemDialog.hpp"
#include "EditRoomDialog.hpp"
#include "EditBuildingDialog.hpp"
#include "DialogTransitToRoom.hpp"
#include "DialogTransitTobuilding.hpp"
#include <QMessageBox>

RoomViewer::RoomViewer(std::unique_ptr<DataManager> dm, QWidget* parent)
    : ui{new Ui::RoomViewer()},
    dataManager{ std::move(dm) },
    room{ nullptr },
    currentLocationInfo(new QLabel(this)),
    deviceTableModel(new QStandardItemModel(this)),
    serviceTableModel(new QStandardItemModel(this)),
    problemSolutionTableModel(new QStandardItemModel(this)),
    QMainWindow(parent)
{
    ui->setupUi(this);
    currentLocationInfo->setStyleSheet("QLabel {color: blue;}");

    updateRoomViewer();

    deviceTableModel->setColumnCount(2);
    deviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Оборудование") << QStringLiteral(u"Инвентарный номер")
    );
    ui->tvItems->setModel(deviceTableModel);

    serviceTableModel->setColumnCount(2);
    serviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Обслуживание") << QStringLiteral(u"Дата")
    );
    ui->tvServiceItems->setModel(serviceTableModel);

    problemSolutionTableModel->setColumnCount(3);
    problemSolutionTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Проблема")
        << QStringLiteral(u"Решение")
        << QStringLiteral(u"Дата")
    );
    ui->tvProblemSolutionItems->setModel(problemSolutionTableModel);
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
void RoomViewer::on_mnuAddBuilding_triggered()
{
    auto dialog{ new EditBuildingDialog(dataManager.get(), this) };
    if (dialog->exec() == QDialog::Accepted) {
        dialog->addBuilding();
        delete dialog;
    }
}
void RoomViewer::on_mnuAddRoom_triggered()
{
    auto crRoomDialog{ new EditRoomDialog(dataManager.get(), this) };
    if (crRoomDialog->exec() == EditRoomDialog::Accepted) {
        crRoomDialog->addRoom();
        delete crRoomDialog;
    }
}

void RoomViewer::on_btnTransitRoom_clicked()
{
    auto dialog{ new DialogTransitToRoom(dataManager.get(), this) };
    if (dialog->exec() == QDialog::Accepted) {
        std::string transitToRoom = dialog->getNameRoomTransit().toStdString();
        if (dataManager->getCurrentBuilding()->isExistRoom(transitToRoom)) {
            dataManager->setCurrentRoomLocationInfo(transitToRoom);
            updateRoomViewer();
        }

        else
            QMessageBox::critical(this, "Error!", "Such a room does not exist");
    }
}

void RoomViewer::on_btnTransitBuilding_clicked()
{
    auto dialog{ new DialogTransitToBuilding(dataManager.get(), this) };
    if (dialog->exec() == QDialog::Accepted) {
        std::string transitToBuilding = dialog->getNameBuildingTransit().toStdString();
        if (dataManager->getBuilding(transitToBuilding)) {
            dataManager->setCurrentBuildingLocationInfo(transitToBuilding);
            updateRoomViewer();
        }
        else
            QMessageBox::critical(this, "Error!", "Such a building does not exist");
    }
}

void RoomViewer::on_mnuAddItem_triggered() {
    auto pCrItemDialog{ new CreateItemDialog(nullptr) };
    if (pCrItemDialog->exec() == CreateItemDialog::Accepted) {
        auto dialog{ pCrItemDialog->getEditItemDialog(dataManager.get()) };
        if (dialog->exec() == QDialog::Accepted) {
            room->addItem(dialog->createItem());
            ui->pteInfoItems->setPlainText(
                QString::fromStdString(room->showItem(0)->getITequipment()->getInfo())
            );

           QList<QStandardItem*> itemStringList;
            itemStringList.append(
                new QStandardItem(QString::fromStdString(room->showItem(0)->getName())
                    ));
            itemStringList.append(
                new QStandardItem(QString::number(room->showItem(0)->getInventoryNumber()))
                    );
            deviceTableModel->insertRow(
                deviceTableModel->rowCount(), itemStringList);
        }

    }
}
void RoomViewer::setTextStatusBar(const std::string& str1, const std::string& str2)
{
    QString status = QString::fromStdString(
        "Building: " + str1 + "\tRoom: " + str2);
    currentLocationInfo->setText(status);
}

void RoomViewer::updateRoomViewer()
{
    room = dataManager->getCurrentRoom();
    ui->lblRoomName->setText(QString::fromStdString(room->getName()));
    setTextStatusBar(
        dataManager->getCurrentLocationInfo().first,
        dataManager->getCurrentLocationInfo().second);
    ui->statusbar->addWidget(currentLocationInfo);
}
