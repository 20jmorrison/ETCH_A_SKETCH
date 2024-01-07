#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: red;");
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialPortCallback);
    initSerialPort();

    ui->graphicsView->setScene(new QGraphicsScene(this->centralWidget()));
    path = QPainterPath();
    path.moveTo(505, 505);
    currentItem = new QGraphicsPathItem();  // Allocate on the heap
    currentItem->setPath(path);
    currentItem->setPen(pen);
    ui->graphicsView->scene()->addItem(currentItem);  // Add item to the scene
    ui->left_dial->setStyleSheet("background-color: white;");
    ui->right_dial->setStyleSheet("background-color: white;");

}

MainWindow::~MainWindow()
{
    delete currentItem;  // Release the allocated memory
    delete ui;
}

void MainWindow::initSerialPort()
{
    // Set up the serial port settings in your initialization code
    serial.setPortName("tty.usbmodem141201"); // Change this to the port your Arduino is connected to
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    // Connect to the serial port
    if (serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened successfully";
    } else {
        qDebug() << "Error opening serial port";
    }
}

void MainWindow::serialPortCallback()
{
    // Read all available data from the serial port
    QByteArray data = serial.readAll();
    if (data == "\n") {
        startDataCollection = true;
    } else if (data == "\r") {
        startDataCollection = false;
        QRegularExpression regex("(\\d+):(\\d+)");
        QRegularExpressionMatch match = regex.match(QString::fromStdString(serialBuffer.toStdString()));

        if (match.hasMatch()) {
            QString firstNumber = match.captured(1);
            QString secondNumber = match.captured(2);

            ui->left_dial->setValue(firstNumber.toInt());
            ui->right_dial->setValue(secondNumber.toInt());
            path.lineTo(firstNumber.toInt(), secondNumber.toInt());
            currentItem->setPath(path);
        } else {
            qDebug() << "No match found";
        }
        serialBuffer.clear();
    } else if (startDataCollection) {
        serialBuffer.append(data);
    }
}
