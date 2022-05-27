#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSerialPort>
#include <QGraphicsView>
#include <QDebug>
#include <QObject>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool exit = 0;

private:
    Ui::MainWindow *ui;
    QSerialPort *device;

public slots:
    // call commands function based on textInput
    void handleConsole();

private slots:
    // adds message to the textEditLog widget
    void addToLogs(QString message);
    // receives data from device
    void readFromDevice();
    // prints x, y, z, theta in form layout
    void printData();
    // updates status in side panel
    void updateStatus();
    // handles run section
    void handleRun();
    // handles stop section
    void handleStop();
    // search avalaible devices
    void handleSearch();
    // connect to the chosen device
    void handleConnect();
    // disconnect from the device
    void handleDisconnect();

};
#endif // MAINWINDOW_HPP
