#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    void rotate_left();
    void rotate_right();
    void serialPortCallback();

private:
    Ui::MainWindow *ui;
    int dialVal = 50;
    QSerialPort serial;
    void initSerialPort();
    QByteArray serialBuffer;
    bool startDataCollection = false;
};
#endif // MAINWINDOW_H
