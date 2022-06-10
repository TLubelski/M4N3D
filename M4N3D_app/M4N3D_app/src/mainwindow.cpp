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
    QObject::connect(this, SIGNAL(stateUpdate(MSG)), this, SLOT(execInstructions(MSG)));
    // emit for printing data
    QObject::connect(this, SIGNAL(dataArrived()), this, SLOT(updateDataStatus()));
    // emited when data arrived
    QObject::connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromDevice()));
    //logs
    QObject::connect(ui->pushButtonLogsClear, SIGNAL(pressed()), ui->textEditLogs, SLOT(clear()));
    QObject::connect(ui->pushButtonPacketsClear, SIGNAL(pressed()), ui->textEditPacket, SLOT(clear()));
    handleSearch();
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
    this->addToLogs("Scanning...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    if(devices.count() > 0)
    {
        for(int i=0; i<devices.count(); i++)
        {
            if(devices.at(i).portName() != "ttyS0")
            {
                this->addToLogs("Found " + devices.at(i).portName() + " " + devices.at(i).description());
                ui->comboBoxDevices->addItem(devices.at(i).portName());
            }
        }
    }
}

// connect to the chosen device
void MainWindow::handleConnect()
{
    if(ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Not found any device!");
        return;
    }
    if(this->device->isOpen())
    {
        this->addToLogs("Port already open!");
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

        this->addToLogs("Connected to " + portName);
        connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromDevice()));
    }
    else
    {
        this->addToLogs("Opening serial port failed!");
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
      this->addToLogs("Connection closed.");
    }
    else
    {
      this->addToLogs("Port is not open");
    }

}

// handles run section
void MainWindow::handleRun()
{
    curr_index_of_words = 0;
    ui->textEditPacket->clear();
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
            for(int num=0; num < 3; ++num)
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
            for(int num=0; num < 3; ++num)
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

//    for( auto &elem: words)
//      qDebug() << elem;

     parseCommand();



    if(is_code_ok == 1)
    {
        emit stateUpdate(START);
    }
}

void MainWindow::parseCommand()
{
  float t1, t2, t3;
  int i = 0;
  while(!cmd_queue.empty())cmd_queue.pop();
  cmd_queue.push(std::make_shared<CmdStart>(i));
  i++;
  auto iter = words.begin();
  while(iter != words.end())
  {
    if( *iter == "magnet" )
    {
      iter++;
      cmd_queue.push( std::make_shared<CmdMagnet>(i, iter->toInt()) );
      iter++;
    }
    else if( *iter == "wait")
    {
      iter++;
      cmd_queue.push( std::make_shared<CmdWait>(i, iter->toInt()) );
      iter++;
    }
    else if(*iter == "movej")
    {
      iter++;
      t1 = iter->toFloat();
      iter++;
      t2 = iter->toFloat();
      iter++;
      t3 = iter->toFloat();
      iter++;
      cmd_queue.push( std::make_shared<CmdMoveJ>(i, t1,t2,t3) );
    }
    else if( *iter == "movel")
    {
      iter++;
      t1 = iter->toFloat();
      iter++;
      t2 = iter->toFloat();
      iter++;
      t3 = iter->toFloat();
      iter++;
      cmd_queue.push( std::make_shared<CmdMoveL>(i, t1,t2,t3) );
    }
    i++;
  }

  cmd_queue.push(std::make_shared<CmdStop>(i));

  qDebug() << "SIZE: " << cmd_queue.size();

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
void MainWindow::addToLogs(QString message, bool error)
{
  if( error && !ui->checkBoxDebug->isChecked())
    return;

  QString currDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
  QString type = (error) ? "ERROR: " : "";
  ui->textEditLogs->append(currDateTime + " | " + type + message);
}

// read from device
void MainWindow::readFromDevice()
{
    if(this->device->canReadLine())
    {
        uint8_t checksum = 0;
        uint8_t len;
        QByteArray line = this->device->readAll();

        if( frame_buffer.length() == 0)
        {
          is_frame_full = false;

          if(line.at(0) == (char)0xFF && line.at(1) == (char)0xFF)
          {
            frame_buffer.append(line);
            len = frame_buffer.at(2);
            if( len+5 == frame_buffer.length())
              is_frame_full = true;
          }
          else
          {
              addToLogs("Start bytes have wrong values.", 1);
              frame_buffer.clear();
          }
        }
        else
        {
            frame_buffer.append(line);
            len = frame_buffer.at(2);
            if( len+5 == frame_buffer.length())
              is_frame_full = true;
            else
            {
              frame_buffer.clear();
              addToLogs("Packet malformed", 1);
              is_frame_full = false;
            }
        }

        // check checksum
        if(is_frame_full)
        {
            //qDebug() << frame_buffer.toHex();
            len = (uint8_t)frame_buffer.at(2);
            for(int i=2; i < len+3; i++)
                checksum += (uint8_t)frame_buffer.at(i);
            checksum = (~checksum) & 0xFF;

            // if checksum is ok get the data
            if(checksum == (uint8_t)frame_buffer.at(len + 3))
              is_frame_ok = true;
            else
            {
                frame_buffer.clear();
                is_frame_ok = false;
                is_frame_full = false;
                addToLogs("Checksum doesn't match.", 1);
            }
        }

        // parse buffer
        if(is_frame_ok)
        {
            qDebug() << "<< 0x" + frame_buffer.toHex();
            if( frame_buffer.at(3) == ACK || frame_buffer.at(3) == DONE )
              ui->textEditPacket->append("<span style=' font-weight:700; color:#f0bc13;'>&lt;&lt;</span> 0x" + frame_buffer.toHex() + "   " + ((frame_buffer.at(3) == ACK) ? "ACK" : "DONE"));
            is_frame_full = false;
            is_frame_ok = false;
            parseFrameBuffer();
            frame_buffer.clear();
        }

    }        
}

void MainWindow::parseFrameBuffer()
{

  // getting data from line
  floatArray f_pool;
  msg_type = (MSG)frame_buffer.at(3);
  int len = frame_buffer.at(2);
  std::vector<uint8_t> *error = new std::vector<uint8_t>;

  switch(msg_type)
  {
      case ACK:
          emit stateUpdate(ACK);
          break;
      case DONE:
          emit stateUpdate(DONE);
          break;
      case DATA:
          memcpy(f_pool.bytes, frame_buffer.constData()+4, 4);
          x_in = f_pool.var;
          memcpy(f_pool.bytes, frame_buffer.constData()+8, 4);
          y_in = f_pool.var;
          memcpy(f_pool.bytes, frame_buffer.constData()+12, 4);
          z_in = f_pool.var;
          memcpy(f_pool.bytes, frame_buffer.constData()+16, 4);
          j1 = f_pool.var;
          memcpy(f_pool.bytes, frame_buffer.constData()+20, 4);
          j2 = f_pool.var;
          memcpy(f_pool.bytes, frame_buffer.constData()+24, 4);
          j3 = f_pool.var;
          emit dataArrived();
          break;
      case DEBUG:
          for(int i=0; i < len; i++)
              error->push_back(frame_buffer.at(i+3));
          ui->textEditLogs->append((char*)error);
          break;
      default:
          ui->textEditLogs->append("Not possible, but readFromDevice fucked up :(");
      break;
  }
  delete error;
}



void MainWindow::execInstructions(MSG msg)
{
    switch(msg)
    {
        case STOP:
            while(!cmd_queue.empty()) cmd_queue.pop();
            sendPacket(CmdStop(-1).getPacket());
            break;
        case ACK:
            got_ack = true;
            break;
        case START:
        case DONE:
            if( !cmd_queue.empty() )
            {
                sendPacket( cmd_queue.front()->getPacket() );
                cmd_queue.pop();
            }
            break;
        case DEBUG:
            break;
    }
}


void MainWindow::sendPacket(QByteArray data)
{
  QByteArray packet;
  packet.append(0xFF);
  packet.append(0xFF);
  packet.append(data);

  uint8_t checksum = 0;
  for(auto &elem : data)
      checksum += elem;
  checksum = (~checksum) & 0xFF;

  packet.append(checksum);
  packet.append('\n');

  this->device->write(packet);

  qDebug() << ">> 0x" + packet.toHex();
  ui->textEditPacket->append("<span style=' font-weight:700; color:#62a0ea;'>&gt;&gt;</span> 0x" + packet.toHex());
}




