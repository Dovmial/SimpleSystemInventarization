#include "View.h"

View::View(QWidget* parent)
    : ui{new Ui::ViewClass()},
    QMainWindow(parent)
{
    ui->setupUi(this);
    dataManager = std::make_unique<DataManager>();
    roomViewer = new RoomViewer(nullptr);
}

View::~View()
{
    delete ui;
}

void View::on_pushButtonStart_clicked() {
    roomViewer->show();
    this->close();
}