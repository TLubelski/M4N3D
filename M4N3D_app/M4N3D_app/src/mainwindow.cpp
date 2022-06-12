#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QTextBlock>
#include <QFileDialog>
#include <QDir>
#include <QToolTip>

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

    QObject::connect(ui->pushButtonOpen, SIGNAL(pressed()), this, SLOT(handleOpen()));
    QObject::connect(ui->pushButtonSave, SIGNAL(pressed()), this, SLOT(handleSave()));
    QObject::connect(ui->pushButtonHelp, SIGNAL(clicked()), this, SLOT(showHelp()));

    console_cursor = ui->console->textCursor();
    format_normal.setBackground(Qt::transparent);
    format_selected.setBackground(Qt::red);

    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonRun->setEnabled(false);
    ui->pushButtonStop->setEnabled(false);

    handleSearch();
    if(ui->comboBoxDevices->count() > 0)
      handleConnect();
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
                ui->comboBoxDevices->addItem( devices.at(i).portName() + " (" + devices.at(i).description() + ")", devices.at(i).portName());
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

    QString portName = "/dev/" + ui->comboBoxDevices->currentData().toString();
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

        ui->pushButtonDisconnect->setEnabled(true);
        ui->pushButtonConnect->setEnabled(false);
        ui->pushButtonRun->setEnabled(true);
        ui->pushButtonStop->setEnabled(true);

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
      ui->pushButtonDisconnect->setEnabled(false);
      ui->pushButtonConnect->setEnabled(true);
      ui->pushButtonRun->setEnabled(false);
      ui->pushButtonStop->setEnabled(false);

    }
    else
    {
      this->addToLogs("Port is not open");
    }

}

// handles run section
void MainWindow::handleRun()
{
    ui->textEditPacket->clear();

//    ui->textEditLogs->clear();

    int is_code_ok = runChecker();

    switch(is_code_ok)
    {
        case 0:
            addToLogs("Running...");
//            addToLogs("Perfect, sending over UART.");
            parseCommand();
            emit stateUpdate(START);
            break;
        case 1:
            addToLogs("Wrong function name. Break");
            break;
        case 2:
            addToLogs("Invalid argument. Break");
            break;
        case 3:
            addToLogs("There is no argument. Break");
            break;
        case 4:
            addToLogs("Value out of range. Break");
            break;
    }
}

void MainWindow::parseCommand()
{
  float t1, t2, t3;

  while(!cmd_queue.empty())cmd_queue.pop();
  cmd_queue.push(std::make_shared<CmdStart>(-1));
  int i = 0;
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
  if(!ui->checkBoxLoop->isChecked())
    cmd_queue.push(std::make_shared<CmdStop>(-2));

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

int MainWindow::runChecker()
{
    // getting raw text
    QString input = ui->console->toPlainText().toLower();
    // setting up regex that replaces all whitespaces seqence with a single space
    regex.setPattern("\\s\\s*");
    // using regex
    input.replace(regex, " ");
    // remove single space from begin and end of text if exist
    input = input.trimmed();
    // splitting text after regex by single space
    words = input.split(" ");

//    for(auto i=words.begin(); i< words.end(); i++)
//    {
//        qDebug() << *i;
//    }

    // variable for error code
    int is_code_ok = 0;

    // creating regex for checking numbers
    //regex.setPattern("\\d+");
    regex.setPattern("^[-+]?[0-9]*$");

    // iterating over words elements
    for(int i=0; i < words.size(); ++i)
    {
        qDebug() << words.at(i);
        // checking movel
        if(words.at(i) == "movel")
        {
            // doing this for next 3 arguments needed
            for(int num=0; num < 3; ++num)
            {
                // check if there is next word
                if(i+1 < words.size())
                {
                    match = regex.match(words.at(i+1));
                    // check if word.at(i+1) is a number
                    if(match.hasMatch())
                    {
                        // checking range of value
                        if(num==0 && words.at(i+1).toInt() >= (-XY_LIMIT) && words.at(i+1).toInt() <= XY_LIMIT)
                            is_code_ok = 0;
                        else if(num==1 && words.at(i+1).toInt() >= (-XY_LIMIT) && words.at(i+1).toInt() <= XY_LIMIT)
                            is_code_ok = 0;
                        else if(num==2 && words.at(i+1).toInt() >= 0 && words.at(i+1).toInt() <= Z_LIMIT)
                            is_code_ok = 0;
                        // value out of range
                        else return 4;

                        i++;
                    }
                    // invalid argument given
                    else return 2;
                }
                // lack of argument
                else return 3;
            }
        }
        // checking movej
        else if(words.at(i) == "movej")
        {
            // doing this for next 3 arguments needed
            for(int num=0; num < 3; ++num)
            {
                // check if there is next word
                if(i+1 < words.size())
                {
                    match = regex.match(words.at(i+1));
                    // check if word.at(i+1) is a number
                    if(match.hasMatch())
                    {
                        // checking range of value
                        if(num==0 && words.at(i+1).toInt() >= (-XY_LIMIT) && words.at(i+1).toInt() <= XY_LIMIT)
                            is_code_ok = 0;
                        else if(num==1 && words.at(i+1).toInt() >= (-XY_LIMIT) && words.at(i+1).toInt() <= XY_LIMIT)
                            is_code_ok = 0;
                        else if(num==2 && words.at(i+1).toInt() >= 0 && words.at(i+1).toInt() <= Z_LIMIT)
                            is_code_ok = 0;
                        // value out of range
                        else return 4;

                        i++;
                    }
                    // invalid argument given
                    else return 2;
                }
                // lack of argument
                else return 3;
            }
        }
        // check 'wait' command
        else if(words.at(i) == "wait")
        {
            // check if there is anything after 'wait' command
            if(i+1 < words.size())
            {
                match = regex.match(words.at(i+1));
                // check if param is number and >0
                if(match.hasMatch())
                {
                    if( words.at(i+1).toInt() > 0)
                        is_code_ok = 0;
                    // value out of range
                    else return 4;
                    i++;
                }
                // invalid argument given
                else return 2;
            }
            // lack of argument
            else return 3;
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
                    is_code_ok = 0;
                    i++;
                }
                // invalid argument given
                else return 2;
            }
            // lack of argument
            else return 3;
        }
        // wrong function name
        else return 1;
    }
    // this is called only if everything was fines
    return is_code_ok;
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
            else if(len+5 > frame_buffer.length())
            {
              addToLogs("Packet split", 1);
            }
            else if(len+5 < frame_buffer.length())
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
  QString error;

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
          qDebug() << frame_buffer.toHex();
          for(int i=0; i < len-1; i++)
              error.append(frame_buffer.at(i+4));
          addToLogs("ROBOT: " + error);
          break;
      default:
          break;
  }
}



void MainWindow::execInstructions(MSG msg)
{
    int index;
    switch(msg)
    {
        case STOP:
            while(!cmd_queue.empty()) cmd_queue.pop();
            sendPacket(CmdStop(-1).getPacket());
            ui->checkBoxLoop->setChecked(false);
            highlightReset();
            ui->console->setReadOnly(false);
            break;
        case ACK:
            got_ack = true;
            break;
        case START:
        case DONE:
            if( !cmd_queue.empty() )
            {
                ui->console->setReadOnly(true);
                index = cmd_queue.front()->getIndex();
                if(index >= 0)
                  highlightCodeLine(index);
                sendPacket( cmd_queue.front()->getPacket() );
                cmd_queue.pop();
            }
            else
            {
              ui->console->setReadOnly(false);
              highlightReset();
              if(ui->checkBoxLoop->isChecked())
                handleRun();
            }
            break;
        case DEBUG:
            break;
        default:
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

void MainWindow::highlightReset()
{
  console_cursor.select(QTextCursor::Document);
  console_cursor.setBlockFormat(format_normal);
}

void MainWindow::highlightCodeLine(int line)
{
   highlightReset();
   console_cursor = QTextCursor(ui->console->document()->findBlockByLineNumber(line));
   console_cursor.setBlockFormat(format_selected);
}


void MainWindow::handleOpen()
{
  QString filename = QFileDialog::getOpenFileName(this, "Open Program", QDir::homePath(), "Program files (*.txt)");
  if(filename != "")
  {
    qDebug() << filename;
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ReadFile(&file);
    ui->console->clear();
    ui->console->setText(ReadFile.readAll());
    file.close();
  }
}
void MainWindow::handleSave()
{
  QString filename = QFileDialog::getSaveFileName(this, "Save Program", QDir::homePath(), "Program files (*.txt)");
  if(filename != "")
  {
    QFile file(filename);
    file.open(QFile::WriteOnly | QFile::Text);
    QString program = ui->console->toPlainText();
    QTextStream WriteFile(&file);
    WriteFile << program;
    file.close();
    }
}

void MainWindow::showHelp()
{
  QToolTip::showText(ui->console->mapToGlobal(QPoint(300,0)),
  "<p><span style='font-weight:700;'>WAIT </span><span style='font-style:italic;'>ms</span> [1+]</p>"
  "<p><span style='font-weight:700;'>MAGNET</span> <span style='font-style:italic;'>state</span> [0/1]</p>"
  "<p><span style='font-weight:700;'>MOVEJ</span> <span style='font-style:italic;'>x y z</span></p>"
  "<p><span style='font-weight:700;'>MOVEL</span> <span style='font-style:italic;'>x y z</span></p>"
  "<p><span style='font-style:italic;'>x</span> [-80; 80]</p>"
  "<p><span style='font-style:italic;'>y </span>[-80; 80]</p>"
  "<p><span style='font-style:italic;'>z </span>[0; 150]</p>");
}



