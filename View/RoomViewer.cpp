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
#include "DialogServiceInfo.hpp"
#include "DialogProblemSolutionInfo.hpp"
#include "DialogFindItem.hpp"
#include "TableFoundDevices.hpp"
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
    
    tablesModelsConfiguration();
    updateRoomViewer();
   
    QObject::connect(ui->tvItems, &QTableView::doubleClicked,
        this, &RoomViewer::slotEditRecord);
    QObject::connect(ui->tvItems, &QTableView::clicked,
        this, &RoomViewer::slotShowInfoSelectItem);
    QObject::connect(ui->tvItems, &QTableView::customContextMenuRequested,
        this, &RoomViewer::slotContextMenuItem);
    QObject::connect(ui->tvServiceItems, &QTableView::customContextMenuRequested,
        this, &RoomViewer::slotContextMenuServices);
    QObject::connect(ui->tvProblemSolutionItems, &QTableView::customContextMenuRequested,
        this, &RoomViewer::slotContextMenuProblemsSolutions);

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

void RoomViewer::on_mnuFindItem_triggered()
{
    auto dialog = new DialogFindItem(dataManager.get(), this);
    if (dialog->exec() == QDialog::Accepted) {
        auto devicesFound = dialog->findItem();
        switch (devicesFound.size()) {
        case 0:
            QMessageBox::information(this, QString(QStringLiteral(u"Результат поиска")),
                QString(QStringLiteral(u"Оборудование не найдено!")));
            break;

        case 1:
            showFoundItem(devicesFound[0]);
            break;

        default:
            auto tableFoundDevices{ new TableFoundDevices(this, devicesFound) };
            tableFoundDevices->show();
            break;
        }
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

void RoomViewer::on_btnSave_clicked()
{
    dataManager->serialize();
    QMessageBox::information(this, "", "Saved!!");
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

void RoomViewer::slotAddProblemSolutionInfo()
{
    Item* item = getRoom()->showItem(ui->tvItems->selectionModel()->currentIndex().row());
    auto dialog = new DialogProblemSolutionInfo(item, this);
    if (dialog->exec() == QDialog::Accepted) {
        dialog->addSignProblemSolutionInfo();
    }
    updateTableProblemsSolutions();
}

void RoomViewer::slotAddServiceInfo()
{
    Item* item = getRoom()->showItem( ui->tvItems->selectionModel()->currentIndex().row());
    auto dialog = new DialogServiceInfo(item,this);
    if (dialog->exec() == QDialog::Accepted) {
        dialog->addSignServiceInfo();
    }
    updateTableServices();
}

void RoomViewer::slotRemoveDevice()
{
    int row = ui->tvItems->selectionModel()->currentIndex().row();
    Item* item = dataManager->getCurrentRoom()->showItem(row);
    dataManager->eraseItem(dataManager->findItem(item));
    updateRoomContent();
}

void RoomViewer::slotRemoveServiceSign()
{
    auto idItem{ serviceTableModel->data(
        serviceTableModel->index(ui->tvServiceItems->currentIndex().row(), 0)
    ).toInt() - 1 };
    auto idSign{ serviceTableModel->data(
        serviceTableModel->index(ui->tvServiceItems->currentIndex().row(), 1)
    ).toInt() - 1 };
    Item* item{ room->showItem(idItem) };
    item->removeSignService(idSign);
    updateTableServices();
}

void RoomViewer::slotRemoveProblemSolutiondSign()
{
    auto idItem{ problemSolutionTableModel->data(
       problemSolutionTableModel->index(
           ui->tvProblemSolutionItems->currentIndex().row(), 0)
    ).toInt() - 1 };
    auto idSign{ problemSolutionTableModel->data(
        problemSolutionTableModel->index(ui->tvProblemSolutionItems->currentIndex().row(), 1)
    ).toInt() - 1 };
    Item* item{ room->showItem(idItem) };
    item->removeSignProblemSolution(idSign);
    updateTableProblemsSolutions();
}

void RoomViewer::slotContextMenuItem(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* addProblemSoltionInfo = new QAction(QStringLiteral(u"Добавить проблему/решение..."));
    QAction* addServiceInfo = new QAction(QStringLiteral(u"Добавить сервисную информацию..."));
    QAction* removeDevice = new QAction(QStringLiteral(u"Удалить элемент"));

    QObject::connect(addProblemSoltionInfo, &QAction::triggered,
        this, &RoomViewer::slotAddProblemSolutionInfo);

    QObject::connect(addServiceInfo, &QAction::triggered,
        this, &RoomViewer::slotAddServiceInfo);

    QObject::connect(removeDevice, &QAction::triggered, this, &RoomViewer::slotRemoveDevice);

    menu->addAction(addProblemSoltionInfo);
    menu->addAction(addServiceInfo);
    menu->addAction(removeDevice);

    menu->popup(ui->tvItems->viewport()->mapToGlobal(pos));
}

void RoomViewer::slotContextMenuServices(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* removeSign = new QAction(QStringLiteral(u"Удалить запись"));
    QObject::connect(removeSign, &QAction::triggered,
        this, &RoomViewer::slotRemoveServiceSign);
    menu->addAction(removeSign);
    menu->popup(ui->tvServiceItems->viewport()->mapToGlobal(pos));
}

void RoomViewer::slotContextMenuProblemsSolutions(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* removeSign = new QAction(QStringLiteral(u"Удалить запись"));
    QObject::connect(removeSign, &QAction::triggered, 
        this, &RoomViewer::slotRemoveProblemSolutiondSign);
    menu->addAction(removeSign);
    menu->popup(ui->tvProblemSolutionItems->viewport()->mapToGlobal(pos));
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
    updateTableDevices();
    updateTableServices();
    updateTableProblemsSolutions();
}

void RoomViewer::updateTableDevices() 
{
    ui->pteInfoItems->clear();
    if (!room->isEmpty())
        ui->pteInfoItems->setPlainText(
            QString::fromStdString(room->showItem(0)->getITequipment()->getInfo())
        );

    Item* item;
    QList<QStandardItem*> itemStringList;
    deviceTableModel->clear();
    setHeadersDeviceTable();

    for (int i{}; i < room->size(); ++i) {

        item = room->showItem(i);
        itemStringList.append(
            new QStandardItem(QString::fromStdString(item->getName()))
        );
        itemStringList.append(
            new QStandardItem(QString::number(item->getInventoryNumber()))
        );

        deviceTableModel->insertRow(
            deviceTableModel->rowCount(), itemStringList);
        itemStringList.clear();
    }
}
void RoomViewer::updateTableServices()
{
    Item* item;
    QList<QStandardItem*> serviceStringList;
    serviceTableModel->clear();
    setHeadersServiceTable();

    for (int i{}, indexSign{}; i < room->size(); ++i) {
        item = room->showItem(i);
        auto [serviceBeginIter, serviceEndIter] = item->getServiceInfoView();
        indexSign = 0;
        while (serviceBeginIter != serviceEndIter) {
            serviceStringList.append(new QStandardItem(QString::number(++i)));
            serviceStringList.append(new QStandardItem(QString::number(++indexSign)));
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
    }
}
void RoomViewer::updateTableProblemsSolutions() 
{
    Item* item;
    QList<QStandardItem*> problemStringList;
    problemSolutionTableModel->clear();
    setHeadersProblemSolutionTable();

    for (int i{}, indexSign{}; i < room->size(); ++i) {
        item = room->showItem(i);
        auto [problemBeginIter, problemEndIter] = item->getProblemsSolutionsView();
        indexSign = 0;
        while (problemBeginIter != problemEndIter) {
            problemStringList.append(new QStandardItem(QString::number(i+1)));
            problemStringList.append(new QStandardItem(QString::number(++indexSign)));
            problemStringList.append(
                new QStandardItem(QString::fromStdString((*problemBeginIter)->getDescription()))
            );
            problemStringList.append(
                new QStandardItem(QString::fromStdString((*problemBeginIter)->getSolution()))
            );
            problemStringList.append(
                new QStandardItem(QString::fromStdString((*problemBeginIter)->getDate()))
            );
            if (problemStringList.at(0)->text() != "")
                problemSolutionTableModel->insertRow(problemSolutionTableModel->rowCount(),
                    problemStringList);
            problemStringList.clear();
            ++problemBeginIter;
        }
    }
}

void RoomViewer::setHeadersModels() 
{
    setHeadersDeviceTable();
    setHeadersServiceTable();
    setHeadersProblemSolutionTable();
}

void RoomViewer::setHeadersDeviceTable() 
{
    deviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"Оборудование") << QStringLiteral(u"Инвентарный номер")
    );
}
void RoomViewer::setHeadersServiceTable() 
{
    serviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"id оборудования")<< QStringLiteral(u"id записи")
        << QStringLiteral(u"Обслуживание") << QStringLiteral(u"Дата")
    );
}
void RoomViewer::setHeadersProblemSolutionTable() 
{
    problemSolutionTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"id оборудования") << QStringLiteral(u"id записи")
        << QStringLiteral(u"Проблема")
        << QStringLiteral(u"Решение")
        << QStringLiteral(u"Дата")
    );
}

void RoomViewer::showFoundItem(const DeviceLocation*  devicesFound)
{
    auto roomLocation{ devicesFound->location.roomName };
    auto buildingLocation{ devicesFound->location.buildingName };
    dataManager->setCurrentLocationInfo({ buildingLocation, roomLocation });
    if (room->getName() != roomLocation)
        updateRoomViewer();
    const size_t SIZE = room->size();
    int index = 0;
    for (; index < SIZE; ++index) {
        if (devicesFound->item.get() == room->showItem(index))
            break;
    }

    ui->tvItems->scrollTo(deviceTableModel->index(index, 0));
    ui->tvItems->selectRow(index);
}

void RoomViewer::tablesModelsConfiguration()
{
    deviceTableModel->setColumnCount(2);
    ui->tvItems->setModel(deviceTableModel);
    ui->tvItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvItems->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvItems->resizeColumnsToContents();
    ui->tvItems->horizontalHeader()->setStretchLastSection(true);
    ui->tvItems->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvItems->setContextMenuPolicy(Qt::CustomContextMenu);

    serviceTableModel->setColumnCount(4);
    ui->tvServiceItems->setModel(serviceTableModel);
    ui->tvServiceItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvServiceItems->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvServiceItems->resizeColumnsToContents();
    ui->tvServiceItems->horizontalHeader()->setStretchLastSection(true);
    ui->tvServiceItems->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvServiceItems->setContextMenuPolicy(Qt::CustomContextMenu);

    problemSolutionTableModel->setColumnCount(5);
    ui->tvProblemSolutionItems->setModel(problemSolutionTableModel);
    ui->tvProblemSolutionItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvProblemSolutionItems->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvProblemSolutionItems->resizeColumnsToContents();
    ui->tvProblemSolutionItems->horizontalHeader()->setStretchLastSection(true);
    ui->tvProblemSolutionItems->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvProblemSolutionItems->setContextMenuPolicy(Qt::CustomContextMenu);
}