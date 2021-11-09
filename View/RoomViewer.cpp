#include "RoomViewer.hpp"
#include "CreateItemDialog.hpp"
#include "EditRoomDialog.hpp"
#include "EditBuildingDialog.hpp"
#include "DialogTransitToRoom.hpp"
#include "DialogTransitTobuilding.hpp"
#include "PCeditDialog.hpp"
#include "MonitorEditDialog.hpp"
#include "PrinterEditDialog.hpp"
#include "OtherEditDialog.hpp"

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
    ui->tvItems->setModel(deviceTableModel);
    ui->tvItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tvItems->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvItems->resizeColumnsToContents();
    ui->tvItems->horizontalHeader()->setStretchLastSection(true);
    ui->tvItems->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->tvServiceItems->setModel(serviceTableModel);
    ui->tvServiceItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvServiceItems->resizeColumnsToContents();
    ui->tvServiceItems->horizontalHeader()->setStretchLastSection(true);
    ui->tvServiceItems->setEditTriggers(QAbstractItemView::NoEditTriggers);
    serviceTableModel->setColumnCount(2);
   
    problemSolutionTableModel->setColumnCount(3);
    ui->tvProblemSolutionItems->setModel(problemSolutionTableModel);
    ui->tvProblemSolutionItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvProblemSolutionItems->resizeColumnsToContents();
    ui->tvProblemSolutionItems->horizontalHeader()->setStretchLastSection(true);
    ui->tvProblemSolutionItems->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateRoomContent();
    QObject::connect(ui->tvItems, &QTableView::doubleClicked,
        this, &RoomViewer::slotEditRecord);
    QObject::connect(ui->tvItems, &QTableView::clicked,
        this, &RoomViewer::slotShowInfoSelectItem);
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

void RoomViewer::slotEditRecord(QModelIndex index)
{
    Item* item = dataManager->getCurrentRoom()->showItem(index.row());
    typeDevice type = item->getITequipment()->getType();
 
    AbstractEditDialog* dialog;
    switch (type)
    {
    case PC_TYPE:
        dialog = new PCeditDialog(dataManager.get(), this);
        break;
    case MONITOR_TYPE:
        dialog = new MonitorEditDialog(dataManager.get(), this);
        break;
    case PRINTER_TYPE:
        dialog = new PrinterEditDialog(dataManager.get(), this);
        break;
    case OTHER_TYPE:
        dialog = new OtherEditDialog(dataManager.get(), this);
        break;
    default:
        return;
    }
    /*TODO edit
    std::string str = item->getITequipment()->getInfo();
    dialog->setParams(str);
    if (dialog->exec() == QDialog::Accepted) {
        dialog->create...
    }
    */
    if (dialog->exec() == QDialog::Accepted) {
        dialog->createItem();
        dataManager->eraseItem(dataManager->findItem(item));

        updateRoomContent();
    }
}

void RoomViewer::slotShowInfoSelectItem(QModelIndex index)
{
    auto str{ QString::fromStdString(room->showItem(index.row())
        ->getITequipment()->getInfo()) 
    };
    ui->pteInfoItems->setPlainText(str);
}

void RoomViewer::on_mnuAddItem_triggered() {
    auto pCrItemDialog{ new CreateItemDialog(nullptr) };
    if (pCrItemDialog->exec() == CreateItemDialog::Accepted) {
        auto dialog{ pCrItemDialog->getEditItemDialog(dataManager.get()) };
        if (dialog->exec() == QDialog::Accepted) {
            dialog->createItem();
            updateRoomContent();
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
    updateRoomContent();
    ui->lblRoomName->setText(QString::fromStdString(room->getName()));
    setTextStatusBar(
        dataManager->getCurrentLocationInfo().first,
        dataManager->getCurrentLocationInfo().second);
    ui->statusbar->addWidget(currentLocationInfo);
}

void RoomViewer::updateRoomContent()
{
   
    ui->pteInfoItems->clear();
    if(!room->isEmpty())
        ui->pteInfoItems->setPlainText(
            QString::fromStdString(room->showItem(0)->getITequipment()->getInfo())
        );

    QList<QStandardItem*> itemStringList;
    QList<QStandardItem*> serviceStringList;
    QList<QStandardItem*> problemStringList;
    Item* item; 

    deviceTableModel->clear();
    problemSolutionTableModel->clear();
    serviceTableModel->clear();
    setHeadersModels();

    for (int i{}; i < room->size(); ++i) {
        
        item = room->showItem(i);
        itemStringList.append(
            new QStandardItem(QString::fromStdString(item->getName())));
        itemStringList.append(
            new QStandardItem(QString::number(item->getInventoryNumber())));
        
        deviceTableModel->insertRow(
            deviceTableModel->rowCount(), itemStringList);
        itemStringList.clear();

        auto[serviceBeginIter, serviceEndIter] = item->getServiceInfoView();
        auto[problemBeginIter, problemEndIter] = item->getProblemsSolutionsView();
        while (serviceBeginIter != serviceEndIter) {
            serviceStringList.append(
                new QStandardItem(QString::fromStdString((*serviceBeginIter)->getDescription()))
            );
            serviceStringList.append(
                new QStandardItem(QString::fromStdString((*serviceBeginIter)->getDate()))
            );
            if (serviceStringList.at(0)->text() != "")
                serviceTableModel->insertRow(serviceTableModel->rowCount(), serviceStringList);
            serviceStringList.clear();
            ++serviceBeginIter;
        }

        while (problemBeginIter != problemEndIter) {
            problemStringList.append(
                new QStandardItem(QString::fromStdString((*problemBeginIter)->getDescription()))
            );
            problemStringList.append(
                new QStandardItem(QString::fromStdString((*problemBeginIter)->getSolution()))
            );
            problemStringList.append(
                new QStandardItem(QString::fromStdString((*problemBeginIter)->getDate()))
            );
            if (problemStringList.at(0)->text() == "")
                problemSolutionTableModel->insertRow(problemSolutionTableModel->rowCount(),
                    problemStringList);
            problemStringList.clear();
            ++problemBeginIter;
        }
        
    }
}

void RoomViewer::setHeadersModels() {

    deviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Оборудование") << QStringLiteral(u"Инвентарный номер")
    );
    serviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Обслуживание") << QStringLiteral(u"Дата")
    );
    problemSolutionTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Проблема")
        << QStringLiteral(u"Решение")
        << QStringLiteral(u"Дата")
    );
}
