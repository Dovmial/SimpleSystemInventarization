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
#include <QFontDialog>
#include <QFile>
#include <QTextBrowser>

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

    deserializer = std::make_unique<Deserializer>(
        dataManager.get(),
        dataManager->getPath(),
        dataManager->getXMLDocument()
        );
    deserializer->loadData();

    currentLocationInfo->setStyleSheet("QLabel {color: rgb(175, 119, 108);}");
    ui->lblRoomName->setStyleSheet("QLabel{color: rgb(76, 57, 121);}");
    
    tablesModelsConfiguration();

   if (dataManager->getRefBuildings().size() > 1) {
        auto newCurrentBuilding{ dataManager->getBuildingByIndex(1) };
        dataManager->setCurrentBuildingLocationInfo(
            std::make_pair(1, newCurrentBuilding->getName())
        );
        if (newCurrentBuilding->size() > 1) {
            room = newCurrentBuilding->getRoom(1);
            dataManager->setCurrentRoomLocationInfo(
                std::make_pair(1, room->getName())
            );
        }
    }
    updateRoomViewer();

    ui->pteInfoItems->setFont(QFont("Consolas", 14));
    ui->pteInfoItems->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->pteInfoItems, &QPlainTextEdit::customContextMenuRequested,
        this, &RoomViewer::slotShowContextMenuInfoDevice);
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
    if (dataManager->getCurrentBuilding() == dataManager->getBuildingByIndex(0)) {
        QMessageBox::warning(
            this,
            QStringLiteral(u"??????!"),
            QStringLiteral(u"? ??????????? ?????? ????????? ????????? ???????!")
        );
        return;
    }
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
            QMessageBox::information(this, QString(QStringLiteral(u"????????? ??????")),
                QString(QStringLiteral(u"???????????? ?? ???????!")));
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
        auto index{ dataManager->getCurrentBuilding()->findRoom(transitToRoom) };

        if (index > -1) {
            dataManager->setCurrentRoomLocationInfo(std::make_pair(index, transitToRoom));
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
        auto index{ dataManager->getBuildingIndex(transitToBuilding) };
        if (index > -1) {
            dataManager->setCurrentBuildingLocationInfo(std::make_pair(index, transitToBuilding));
            updateRoomViewer();
        }
        else
            QMessageBox::critical(this, "Error!", "Such a building does not exist");
    }
}

void RoomViewer::on_mnuSave_triggered()
{
    if (int error{ dataManager->save() }; error != XML_SUCCESS) {
        QMessageBox::warning(this, QStringLiteral(u"??????!"),
            QStringLiteral(u"?????? ??????????\n??? ??????: ") + QString::number(error));
        return;
    }
    QMessageBox::information(this, QStringLiteral(u"??????????"), QStringLiteral(u"???????!"));
}

void RoomViewer::on_mnuHelp_triggered()
{
    QFile file("./sources/help.html");
    file.open(QFile::ReadOnly);
    QString strHelp{ file.readAll() };
    QMessageBox::about(this, QStringLiteral(u"??????"), strHelp);
}

void RoomViewer::on_mnuAbout_triggered()
{
    QString str(QStringLiteral(u"??????? ??????? ?????????????? IT ????????????.\n?????? 0.8 (C++/Qt)"));
    QMessageBox::about(this, QString(QStringLiteral(u"? ?????????")), str);
}

void RoomViewer::on_mnuAbout_QT_triggered()
{
    QMessageBox::aboutQt(this, "About QT Framework");
}

void RoomViewer::slotEditRecord(QModelIndex index)
{
    Item* item = dataManager->getCurrentRoom()->showItem(index.row());
    typeDevice type = item->getITequipment()->getType();
    AbstractEditDialog* dialog;
    switch (type)
    {
    case PC_TYPE:
        dialog = new PCeditDialog      (dataManager.get(), item, this);
        break;
    case MONITOR_TYPE:
        dialog = new MonitorEditDialog (dataManager.get(), item, this);
        break;
    case PRINTER_TYPE:
        dialog = new PrinterEditDialog (dataManager.get(), item, this);
        break;
    case OTHER_TYPE:
        dialog = new OtherEditDialog   (dataManager.get(), item, this);
        break;
    default:
        return;
    }
    
    if (dialog->exec() == QDialog::Accepted) {
        auto newItem { dialog->createItem() };
        
        newItem->setServicesInformation         (item->getServicesInformation         ());
        newItem->setProblemsSolutionsInformation(item->getProblemsSolutionsInformation());

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

void RoomViewer::slotEditFont()
{
    bool bOk;
    QFont font = QFontDialog::getFont(&bOk);
    if (!bOk) return;
    ui->pteInfoItems->setFont(font);
}

void RoomViewer::slotContextMenuItem(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* addProblemSolutionInfo = new QAction(QStringLiteral(u"???????? ????????/???????..."));
    QAction* addServiceInfo = new QAction(QStringLiteral(u"???????? ????????? ??????????..."));
    QAction* removeDevice = new QAction(QStringLiteral(u"??????? ???????"));

    QObject::connect(addProblemSolutionInfo, &QAction::triggered,
        this, &RoomViewer::slotAddProblemSolutionInfo);

    QObject::connect(addServiceInfo, &QAction::triggered,
        this, &RoomViewer::slotAddServiceInfo);

    QObject::connect(removeDevice, &QAction::triggered, this, &RoomViewer::slotRemoveDevice);

    menu->addAction(addProblemSolutionInfo);
    menu->addAction(addServiceInfo);
    menu->addSeparator();
    menu->addAction(removeDevice);

    menu->popup(ui->tvItems->viewport()->mapToGlobal(pos));
}

void RoomViewer::slotContextMenuServices(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* removeSign = new QAction(QStringLiteral(u"??????? ??????"));
    QObject::connect(removeSign, &QAction::triggered,
        this, &RoomViewer::slotRemoveServiceSign);
    menu->addAction(removeSign);
    menu->popup(ui->tvServiceItems->viewport()->mapToGlobal(pos));
}

void RoomViewer::slotContextMenuProblemsSolutions(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    QAction* removeSign = new QAction(QStringLiteral(u"??????? ??????"));
    QObject::connect(removeSign, &QAction::triggered, 
        this, &RoomViewer::slotRemoveProblemSolutiondSign);
    menu->addAction(removeSign);
    menu->popup(ui->tvProblemSolutionItems->viewport()->mapToGlobal(pos));
}

void RoomViewer::slotShowContextMenuInfoDevice(QPoint pos)
{
    auto cMenuPlainText{ ui->pteInfoItems->createStandardContextMenu() };
    QAction* editFont = new QAction(QStringLiteral(u"??????? ?????.."));
    QObject::connect(editFont, &QAction::triggered, this, &RoomViewer::slotEditFont);
    cMenuPlainText->addSeparator();
    cMenuPlainText->addAction(editFont);
    cMenuPlainText->popup(ui->pteInfoItems->viewport()->mapToGlobal(pos));
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
        dataManager->getCurrentLocationNames().first,
        dataManager->getCurrentLocationNames().second);
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
            serviceStringList.append(new QStandardItem(QString::number(i+1)));
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
        << QStringLiteral(u"????????????") << QStringLiteral(u"??????????? ?????")
    );
}
void RoomViewer::setHeadersServiceTable() 
{
    serviceTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"id ????????????")<< QStringLiteral(u"id ??????")
        << QStringLiteral(u"????????????") << QStringLiteral(u"????")
    );
}
void RoomViewer::setHeadersProblemSolutionTable() 
{
    problemSolutionTableModel->setHorizontalHeaderLabels(
        QStringList()
        << QStringLiteral(u"id ????????????") << QStringLiteral(u"id ??????")
        << QStringLiteral(u"????????")
        << QStringLiteral(u"???????")
        << QStringLiteral(u"????")
    );
}

void RoomViewer::showFoundItem(const DeviceLocation* deviceFound)
{
    auto indexBuilding  { deviceFound->getBuildingIndex                          () };
    auto indexRoom      { deviceFound->getRoomIndex                              () };
    auto nameBuilding   { dataManager->getBuildingByIndex(indexBuilding)->getName() };
    auto nameRoom{ dataManager->getBuildingByIndex(indexBuilding)
        ->getRoom(indexRoom)->getName() };
   
    dataManager->setCurrentLocationInfo(
        std::make_pair(indexBuilding, nameBuilding),
        std::make_pair(indexRoom    , nameRoom)
    );
    if (room->getName() != nameRoom)
        updateRoomViewer();
    const size_t SIZE = room->size();
    int index = 0;
    for (; index < SIZE; ++index) {
        if (deviceFound->getItem() == room->showItem(index))
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