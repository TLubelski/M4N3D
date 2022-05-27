#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->device = new QSerialPort(this);

    QObject::connect(ui->pushButtonSearch, SIGNAL(pressed()), this, SLOT(handleSearch()));
    QObject::connect(ui->pushButtonConnect, SIGNAL(pressed()), this, SLOT(handleConnect()));
    QObject::connect(ui->pushButtonDisconnect, SIGNAL(pressed()), this, SLOT(handleDisconnect()));
    QObject::connect(ui->pushButtonRun, SIGNAL(pressed()), this, SLOT(handleRun()));
    QObject::connect(ui->pushButtonStop, SIGNAL(pressed()), this, SLOT(handleStop()));
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

// call commands function based on textInput
void MainWindow::handleConsole()
{
    QString input = ui->console->toPlainText();
    ui->console->append(input);
}

// receives data from device
void MainWindow::readFromDevice()
{
    while(this->device->canReadLine())
    {
        int init, work, butt;
        qreal Gy, Gz;
        bool is_data_ok = false;

        QString line = this->device->readLine();

        // reading control values on fixed positions
        init = line.at(0).digitValue();
        work = line.at(2).digitValue();
        butt = line.at(4).digitValue();

        if(init && work && butt)
            is_data_ok = true;

        // getting sensor values
        if(is_data_ok)
        {
            // setting number of chars to read
            //always x.xx = 4 + 1 for sign
            //(if value is positive it reads " " and cuts it during conversion to float)
            int char_num = 5;
            // getting 5 chars from 5th index
            Gy = line.mid(5, char_num).toFloat();
            // getting index of next " " after 6th pos
            int gy_pos = line.indexOf(" ", 6) + 1;
            // getting 5 chars from next " " char
            Gz = line.mid(gy_pos, 5).toFloat();

            this->Gy_raw = Gy;
            this->Gz_raw = Gz;
            this->analyzeData();
        }
        else
        {
            qDebug() << "Please press button or check connection lines!";
        }

    }
}

// prints x, y, z, theta in form layout
void MainWindow::printData()
{
    qDebug() << "xd";
}

// updates status inside panel
void MainWindow::updateStatus()
{
    qDebug() << "xd";
}

// handles run section
void MainWindow::handleRun()
{
    QString input = ui->console->toPlainText();
    input.replace(" \n", "\n");
    input.replace("\n ", "\n");
    input.replace("\n", " ");
    QStringList words = input.split(" ");

    int is_code_ok = 0;
    QRegularExpressionMatch match;

    ui->textEditLogs->clear();
    ui->textEditLogs->append("Running...");

    for(auto i = 0; i < words.size(); ++i)
    {
        if(words.at(i) == "movel")
        {
            // doing this for next 3 arguments needed
            for(int num=0; num < 3; ++num)
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
            // doing this for next 3 arguments needed
            for(int num=0; num < 3; ++num)
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

}

// handles stop section
void MainWindow::handleStop()
{
    qDebug() << "xd";
}
