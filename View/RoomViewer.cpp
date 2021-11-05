#include "RoomViewer.hpp"
#include "CreateItemDialog.hpp"

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
    room = dataManager->getCurrentRoom();
    ui->lblRoomName->setText(QString::fromStdString(room->getName()));
    
    currentLocationInfo->setStyleSheet("QLabel {color: blue;}");
    setTextStatusBar(
        dataManager->getCurrentLocationInfo().first,
        dataManager->getCurrentLocationInfo().second);
    ui->statusbar->addWidget(currentLocationInfo);

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
void RoomViewer::setTextStatusBar(const std::string& str1, const std::string& str2)
{
    QString status = QString::fromStdString(
        "Build: " + str1 + "\tRoom: " + str2);
    currentLocationInfo->setText(status);
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
        }

    }
}