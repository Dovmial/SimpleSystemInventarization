#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_View.h"
#include "RoomViewer.hpp"
#include <memory>

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = Q_NULLPTR);
    ~View();
private slots:
    void on_pushButtonStart_clicked();
private:
    Ui::ViewClass* ui;
    RoomViewer* roomViewer;
    std::unique_ptr<DataManager> dataManager;
};
