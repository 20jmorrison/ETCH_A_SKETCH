#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->left_btn, SIGNAL(clicked()), this, SLOT(rotate_left()));
    connect(ui->right_btn, SIGNAL(clicked()), this, SLOT(rotate_right()));
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialPortCallback);
    ui->dial->setValue(dialVal);
    initSerialPort();
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

void MainWindow::initSerialPort(){
    // Set up the serial port settings in your initialization code
    serial.setPortName("tty.usbmodem141401"); // Change this to the port your Arduino is connected to
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    // Connect to the serial port
    if(serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened successfully";
    } else {
        qDebug() << "Error opening serial port";
    }
}

void MainWindow::serialPortCallback(){
    // Read all available data from the serial port
    QByteArray data = serial.readAll();
    if (data == "\n"){
        startDataCollection = true;
    }
    else if (data == "\r"){
        startDataCollection = false;
        int buffToInt = serialBuffer.toInt();
        ui->dial->setValue(buffToInt);
        serialBuffer.clear();
    }
    else if(startDataCollection){
        serialBuffer.append(data);
    }
}
