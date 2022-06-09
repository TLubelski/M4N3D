#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->device = new QSerialPort(this);

    is_frame_ok = 0;
    x = y = z = speed = 0;
    got_ack = false;

    // connection stuff
    QObject::connect(ui->pushButtonSearch, SIGNAL(pressed()), this, SLOT(handleSearch()));
    QObject::connect(ui->pushButtonConnect, SIGNAL(pressed()), this, SLOT(handleConnect()));
    QObject::connect(ui->pushButtonDisconnect, SIGNAL(pressed()), this, SLOT(handleDisconnect()));
    // emit for run
    QObject::connect(ui->pushButtonRun, SIGNAL(pressed()), this, SLOT(handleRun()));
    // emit for stop
    QObject::connect(ui->pushButtonStop, SIGNAL(pressed()), this, SLOT(handleStop()));
    // emit for connectivity stuff
    QObject::connect(this, SIGNAL(stateUpdate()), this, SLOT(execInstructions()));
    // emit for printing data
    QObject::connect(this, SIGNAL(dataArrived()), this, SLOT(updateDataStatus()));
    // emited when data arrived
    QObject::connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromDevice()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//******************************************* UI SECTION *******************************************

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
    QRegularExpression regex("\\d+");

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

    if(is_code_ok == 1) emit stateUpdate(START);
}

// handles stop section
void MainWindow::handleStop()
{
    emit stateUpdate(STOP);
}

// prints x, y, z, theta in form layout
void MainWindow::updateDataStatus()
{
    ui->xValue->setText(QString::number(x_in));
    ui->yValue->setText(QString::number(y_in));
    ui->zValue->setText(QString::number(z_in));
    ui->j1Value->setText(QString::number(j1));
    ui->j2Value->setText(QString::number(j2));
    ui->j3Value->setText(QString::number(j3));
}

//******************************************* LOGIC SECTION *******************************************

// adds message to the textEditLog widget
void MainWindow::addToLogs(QString message)
{
    QString currDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currDateTime + "\t" + message);
}

// read from device
void MainWindow::readFromDevice()
{
    if(this->device->canReadLine())
    {
        //read it
        //std::vector<uint8_t> *dataframe = new std::vector<uint8_t>;
        uint8_t checksum = 0;
        uint8_t len;
        floatArray f_pool;
        std::vector<uint8_t> *error = new std::vector<uint8_t>;

        QByteArray line = this->device->readLine();

        // check if start bytes are ok
        if(line.at(0) == (char)0xFF && line.at(1) == (char)0xFF)
        {
            // check if checksum is ok
            len = (uint8_t)line.at(2);
            for(int i=2; i < len+3; i++)
                checksum += (uint8_t)line.at(i);
            checksum = (~checksum) & 0xFF;

            // if checksum is ok get the data
            if(checksum == (uint8_t)line.at(len + 3))
            {
                // getting data from line
                msg_type = (MSG)line.at(3);

                switch(msg_type)
                {
                    case ACK:
                        emit stateUpdate(ACK);
                        break;
                    case DONE:
                        emit stateUpdate(DONE);
                        break;
                    case DATA:
                        memcpy(f_pool.bytes, line+4, 4);
                        x_in = f_pool.var;
                        memcpy(f_pool.bytes, line+8, 4);
                        y_in = f_pool.var;
                        memcpy(f_pool.bytes, line+12, 4);
                        x_in = f_pool.var;
                        memcpy(f_pool.bytes, line+16, 4);
                        j1 = f_pool.var;
                        memcpy(f_pool.bytes, line+20, 4);
                        j2 = f_pool.var;
                        memcpy(f_pool.bytes, line+24, 4);
                        j3 = f_pool.var;
                        emit dataArrived();
                        break;
                    case DEBUG:
                        for(auto i=0; i < len; i++)
                            error->push_back(line.at(i));
                        ui->textEditLogs->append((char*)error);
                        break;
                    default:
                        ui->textEditLogs->append("Not possible, but readFromDevice fucked up :(");
                    break;

                }


                is_frame_ok = true;
            }
            else
            {
                is_frame_ok = false;
                ui->textEditLogs->append("Checksum doesn't match.");
            }
        }
        else
        {
            is_frame_ok = false;
            ui->textEditLogs->append("Start bytes have wrong values.");
        }
    }        
}

void MainWindow::execInstructions(MSG msg)
{
    int curr_index_of_words = 0;

    switch(msg)
    {
        case START:
            sendDataFrame(START, -1);
            break;
        case STOP:
            sendDataFrame(STOP, -1);
            break;
        case ACK:
            got_ack = true;
            break;
        case DONE:
            if(curr_index_of_words < words.size())
            {
                if(words.at(curr_index_of_words) == "movel")
                    curr_index_of_words += sendDataFrame(MOVEL, curr_index_of_words);
                else if(words.at(curr_index_of_words) == "movej")
                    curr_index_of_words += sendDataFrame(MOVEJ, curr_index_of_words);
                else if(words.at(curr_index_of_words) == "wait")
                    curr_index_of_words += sendDataFrame(WAIT, curr_index_of_words);
                else if(words.at(curr_index_of_words) == "magnet")
                    curr_index_of_words += sendDataFrame(MAGNET, curr_index_of_words);
            }
            break;
        case DEBUG:
            break;
    }
}

// send dataframe to robot
// this method uses 'words' string, which may contains multiple instructions
// that is why begin is given, it's the index, where sending starts
// begin is index of instruction name
int MainWindow::sendDataFrame(MSG msg, int begin)
{
    //DATA FRAME
    // START START LEN INSTR {PARAMS} CHECKSUM ENDL
    std::vector<uint8_t> *dataframe = new std::vector<uint8_t>;
    uint8_t instr, magnet_status, len;
    uint8_t start = 0xFF;
    uint8_t x_H, x_L, y_H, y_L, z_H, z_L, speed_H, speed_L, time_H, time_L;
    int return_val;

    dataframe->push_back(start);
    dataframe->push_back(start);

    switch(msg)
    {
        case START:
            len = 1;
            dataframe->push_back(len);
            dataframe->push_back(instr);
            return_val = 0;
            break;
        case STOP:
            len = 1;
            dataframe->push_back(len);
            dataframe->push_back(instr);
            return_val = 0;
            break;
        case MOVEL:
        case MOVEJ:
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
            return_val = 4;
            break;
        case WAIT:
            // set all bytes
            time_H = words.at(begin+1).toInt() >> 8;
            time_L = words.at(begin+1).toInt();
            len = 3;
            // add bytes to dataframe
            dataframe->push_back(len);
            dataframe->push_back(instr);
            dataframe->push_back(time_H);
            dataframe->push_back(time_L);
            return_val = 1;
            break;
        case MAGNET:
            // set all bytes
            magnet_status = words.at(begin+1).toInt();
            len = 2;
            // add bytes to dataframe
            dataframe->push_back(len);
            dataframe->push_back(instr);
            dataframe->push_back(magnet_status);
            return_val = 1;
            break;
        default:
            ui->textEditLogs->append("Not possible, but sendDataFrame fucked up :(");
            return_val = -1;
            break;
    }

    //calculating checksum
    uint8_t checksum = 0;
    for(int i=2; i < len+3; i++)
        checksum += dataframe->at(i);
    checksum = (~checksum) & 0xFF;
    dataframe->push_back(checksum);
    dataframe->push_back('\n');

    // sending dataframe over UART
    if(return_val >= 0 && got_ack)
    {
        got_ack = false;
        this->device->write((char*)dataframe);
    }
    else
        ui->textEditLogs->append("Didn't send dataframe, bc You fucked up :(");

    qDebug() << *dataframe;

    return return_val;
}









