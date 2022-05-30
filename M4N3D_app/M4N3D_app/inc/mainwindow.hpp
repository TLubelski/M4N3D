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

#include "communication.hpp"

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

signals:
    // emited after 'Run' instruction validation
    // triggers instructions sending event
    void codePrepared();
    // emited after reading and validating dataframe from robot
    // triggers printing values and status in form event
    void dataArrived();

private:
    Ui::MainWindow *ui;
    QSerialPort *device;
    QStringList words;

    qreal x, y, z, speed;
    bool is_frame_ok, was_exec_success;

private slots:

    //************************* UI SECTION *************************
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

    //************************ LOGIC SECTION ************************
    // adds message to the textEditLog widget
    void addToLogs(QString message);
    // read data from device
    void readFromDevice();
    // prints x, y, z, theta in form layout
    void updateDataStatus();
    // execute instructions on robot
    void execInstructions();
    // send dataframe to robot
    int sendDataFrame(int begin);

};
#endif // MAINWINDOW_HPP
