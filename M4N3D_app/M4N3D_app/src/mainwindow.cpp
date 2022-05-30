#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->device = new QSerialPort(this);

    is_frame_ok = was_exec_success = 0;
    x = y = z = speed = 0;

    QObject::connect(ui->pushButtonSearch, SIGNAL(pressed()), this, SLOT(handleSearch()));
    QObject::connect(ui->pushButtonConnect, SIGNAL(pressed()), this, SLOT(handleConnect()));
    QObject::connect(ui->pushButtonDisconnect, SIGNAL(pressed()), this, SLOT(handleDisconnect()));
    QObject::connect(ui->pushButtonRun, SIGNAL(pressed()), this, SLOT(handleRun()));
    QObject::connect(ui->pushButtonStop, SIGNAL(pressed()), this, SLOT(handleStop()));
    QObject::connect(this, SIGNAL(codePrepared()), this, SLOT(execInstructions()));
    QObject::connect(this, SIGNAL(dataArrived()), this, SLOT(updateDataStatus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// adds message to the textEditLog widget
void MainWindow::addToLogs(QString message)
{
    QString currDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currDateTime + "\t" + message);
}

// search avalaible devices
void MainWindow::handleSearch()
{
    ui->comboBoxDevices->clear();
    this->addToLogs("Szukam urządzeń...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    if(devices.count() > 0)
    {
        for(int i=0; i<devices.count(); i++)
        {
            this->addToLogs(devices.at(i).portName() + " " + devices.at(i).description());
            ui->comboBoxDevices->addItem(devices.at(i).portName());
        }
    }
}

// connect to the chosen device
void MainWindow::handleConnect()
{
    if(ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }
    if(this->device->isOpen())
    {
        this->addToLogs("Port jest już otwarty!");
        return;
    }

    QString portName = "/dev/" + ui->comboBoxDevices->currentText();
    this->device->setPortName(portName);
    //qDebug() << portName;

    if(device->open(QSerialPort::ReadWrite))
    {
        this->device->setBaudRate(QSerialPort::Baud115200);
        this->device->setParity(QSerialPort::NoParity);
        this->device->setDataBits(QSerialPort::Data8);
        this->device->setStopBits(QSerialPort::OneStop);
        this->device->setFlowControl(QSerialPort::NoFlowControl);

        this->addToLogs("Połączono z urządzeniem " + portName);
        connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromDevice()));
    }
    else
    {
        this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        this->addToLogs(device->errorString());
        qDebug() << this->device->error();
    }
}

// disconnect from the device
void MainWindow::handleDisconnect()
{
    if(this->device->isOpen())
    {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
    }
    else
    {
      this->addToLogs("Port nie jest otwarty!");
    }
}

// prints x, y, z, theta in form layout
void MainWindow::updateDataStatus()
{
    qDebug() << "xd";
}

// handles run section
void MainWindow::handleRun()
{
    QString input = ui->console->toPlainText();
    input.replace(" \n", " ");
    input.replace("\n ", " ");
    input.replace("\n", " ");
    words = input.split(" ");

    for(auto i = 0; i< words.size(); ++i)
    {
        if(words.at(i) == " " || words.at(i) == "\n" || words.at(i) == "")
            words.removeAt(i);
    }

    int is_code_ok = 0;
    QRegularExpressionMatch match;

    ui->textEditLogs->clear();
    ui->textEditLogs->append("Running...");

    for(auto i = 0; i < words.size(); ++i)
    {
        if(words.at(i) == "movel")
        {
            // doing this for next 4 arguments needed
            for(int num=0; num < 4; ++num)
            {
                // check if there is next word
                if(i+1 < words.size())
                {
                    QRegularExpression regex("\\d+");
                    match = regex.match(words.at(i+1));
                    // check if word.at(i+1) is a number
                    if(match.hasMatch())
                    {
                        is_code_ok = 1;
                        i++;
                    }
                    // invalid argument given
                    else
                    {
                        is_code_ok = 2;
                        break;
                    }
                }
            }
            if(is_code_ok != 1) break;
        }
        else if(words.at(i) == "movej")
        {
            // doing this for next 4 arguments needed
            for(int num=0; num < 4; ++num)
            {
                // check if there is next word
                if(i+1 < words.size())
                {
                    QRegularExpression regex("\\d+");
                    match = regex.match(words.at(i+1));
                    // check if word.at(i+1) is a number
                    if(match.hasMatch())
                    {
                        is_code_ok = 1;
                        i++;
                    }
                    // invalid argument given
                    else
                    {
                        is_code_ok = 2;
                        break;
                    }
                }
            }
            if(is_code_ok != 1) break;
        }
        // check 'wait' command
        else if(words.at(i) == "wait")
        {
            // check if there is anything after 'wait' command
            if(i+1 < words.size())
            {
                QRegularExpression regex("\\d+");
                match = regex.match(words.at(i+1));
                // check if 'wait' command is ok
                if(match.hasMatch())
                {
                    is_code_ok = 1;
                    i++;
                }
                // invalid argument given
                else
                {
                    is_code_ok = 2;
                    break;
                }
            }
            // lack of argument
            else
            {
                is_code_ok = 3;
                break;
            }
        }
        // check 'magnet' command
        else if(words.at(i) == "magnet")
        {
            // check if there is anything after 'wait' command
            if(i+1 < words.size())
            {
                // check if 'magnet' command is ok
                if(words.at(i+1)== '0' || words.at(i+1)=='1')
                {
                    is_code_ok = 1;
                    i++;
                }
                // invalid argument given
                else
                {
                    is_code_ok = 2;
                    break;
                }
            }
            // lack of argument
            else
            {
                is_code_ok = 3;
                break;
            }
        }
        // wrong function name
        else
        {
            is_code_ok = 0;
            break;
        }
    }

    switch(is_code_ok)
    {
        case 0:
            ui->textEditLogs->append("Wrong function name.\nBreak");
            break;
        case 1:
            ui->textEditLogs->append("Perfect, sending over UART.");
            break;
        case 2:
            ui->textEditLogs->append("Invalid argument.\nBreak");
            break;
        case 3:
            ui->textEditLogs->append("There is no argument.\nBreak");
            break;
    }

    if(is_code_ok) emit codePrepared();
}

// handles stop section
void MainWindow::handleStop()
{
    qDebug() << "xd";
}

void MainWindow::execInstructions()
{
    // sending loop
    for(auto i=0; i < words.size(); ++i)
    {
        i += sendDataFrame(i);
        // wait for answer
    }
}

// send dataframe to robot
int MainWindow::sendDataFrame(int begin)
{
    std::vector<uint8_t> *dataframe = new std::vector<uint8_t>;
    int8_t instr, magnet_status,len;
    int8_t start = 0xFF;
    int8_t x_H, x_L, y_H, y_L, z_H, z_L, speed_H, speed_L, time_H, time_L;

    if(words.at(begin) == "movel") instr = MOVEL;
    else if(words.at(begin) == "movej") instr = MOVEJ;
    else if(words.at(begin) == "wait") instr = WAIT;
    else /*if(words.at(begin) == "magnet")*/ instr = MAGNET;

    dataframe->push_back(start);
    dataframe->push_back(start);

    switch(instr)
    {
        case 0:
        case 1:
            // set all bytes
            x_H = words.at(begin+1).toInt() >> 8;
            x_L = words.at(begin+1).toInt();
            y_H = words.at(begin+2).toInt() >> 8;
            y_L = words.at(begin+2).toInt();
            z_H = words.at(begin+3).toInt() >> 8;
            z_L = words.at(begin+3).toInt();
            speed_H = words.at(begin+4).toInt() >> 8;
            speed_L = words.at(begin+4).toInt();
            len = 9;
            // add bytes to dataframe
            dataframe->push_back(len);
            dataframe->push_back(instr);
            dataframe->push_back(x_H);
            dataframe->push_back(x_L);
            dataframe->push_back(y_H);
            dataframe->push_back(y_L);
            dataframe->push_back(z_H);
            dataframe->push_back(z_L);
            dataframe->push_back(speed_H);
            dataframe->push_back(speed_L);
            break;
        case 2:
            // set all bytes
            time_H = words.at(begin+1).toInt() >> 8;
            time_L = words.at(begin+1).toInt();
            len = 3;
            // add bytes to dataframe
            dataframe->push_back(len);
            dataframe->push_back(instr);
            dataframe->push_back(time_H);
            dataframe->push_back(time_L);
            break;
        case 3:
            // set all bytes
            magnet_status = words.at(begin+1).toInt();
            len = 2;
            // add bytes to dataframe
            dataframe->push_back(len);
            dataframe->push_back(instr);
            dataframe->push_back(magnet_status);
            break;
    }

    //calculating checksum
    int8_t checksum = 0;
    for(int i=2; i < len+3; i++)
        checksum += dataframe->at(i);
    checksum = (~checksum) & 0xFF;
    dataframe->push_back(checksum);

    qDebug() << *dataframe;
    if(instr == 0 || instr == 1)    return 4;
    else return 1;
}

// read from device
void MainWindow::readFromDevice()
{
    // FRAME
    // START START LEN WAS_EXEC_SUCCESS X Y Z SPEED CHECKSUM

    if(is_frame_ok) emit dataArrived();
}









