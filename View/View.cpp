#include "View.hpp"

View::View(QWidget* parent)
    : ui{new Ui::ViewClass()},
    QMainWindow(parent)
{
    ui->setupUi(this);
    dataManager = std::make_unique<DataManager>();
    roomViewer = new RoomViewer(std::move(dataManager));
}

View::~View()
{
    delete ui;
    delete roomViewer;
}

void View::on_pushButtonStart_clicked() {
    roomViewer->show();
    this->close();
}