#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsScene>
#include <QPainterPath>  // Add this line
#include <QGraphicsPathItem>  // Add this line
#include <QPen>  // Add this line

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void serialPortCallback();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    void initSerialPort();
    QByteArray serialBuffer;
    bool startDataCollection = false;

    QPainterPath path;
    QGraphicsPathItem *currentItem;
    QPen pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
};
#endif // MAINWINDOW_H
