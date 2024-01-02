#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->left_btn, SIGNAL(clicked()), this, SLOT(rotate_left()));
    connect(ui->right_btn, SIGNAL(clicked()), this, SLOT(rotate_right()));
    ui->dial->setValue(dialVal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotate_left() {
    dialVal-=5;
    ui->dial->setValue(dialVal);
}

void MainWindow::rotate_right() {
    dialVal += 5;
    ui->dial->setValue(dialVal);
}

