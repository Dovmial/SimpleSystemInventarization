#include "View.h"

View::View(QWidget* parent)
    : ui{new Ui::ViewClass()},
    QMainWindow(parent)
{
    ui->setupUi(this);
    roomViewer = new RoomViewer(nullptr);
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