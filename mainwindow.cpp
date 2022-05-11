#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_executeButton_clicked()
{
    QString text = "";
    for (auto& result : controller.execute()) {
        text += QString::fromStdString(result.description + ":\nAzonosítója: " + result.greenHouseID +
                                       " - token: " + result.token +
                                       "\nHTTP: " + std::to_string(result.HTTPResponse) + " - hőmérséklet emelve " +
                                       std::to_string((int)round(result.temperatureIncrease)) + " celsius fokkal és locsolásra kerül " +
                                       std::to_string((int)round(result.sprinklerIncrease)) +
                                       " liter víz\n.................................................................\n");
    }
    ui->resultTextBrowser->setText(text);
}

