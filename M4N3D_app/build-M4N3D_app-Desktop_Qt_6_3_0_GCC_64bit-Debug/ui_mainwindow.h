/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widgetControl;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *console;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonRun;
    QPushButton *pushButtonStop;
    QFrame *line;
    QWidget *widgetInfo;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxConnectivity;
    QGridLayout *gridLayout;
    QComboBox *comboBoxDevices;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonDisconnect;
    QTextEdit *textEditLogs;
    QFormLayout *formLayout;
    QLineEdit *statusLine;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widgetControl = new QWidget(centralwidget);
        widgetControl->setObjectName(QString::fromUtf8("widgetControl"));
        verticalLayout_2 = new QVBoxLayout(widgetControl);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(widgetControl);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        console = new QTextEdit(widgetControl);
        console->setObjectName(QString::fromUtf8("console"));

        verticalLayout_2->addWidget(console);

        groupBox_3 = new QGroupBox(widgetControl);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonRun = new QPushButton(groupBox_3);
        pushButtonRun->setObjectName(QString::fromUtf8("pushButtonRun"));

        horizontalLayout_4->addWidget(pushButtonRun);

        pushButtonStop = new QPushButton(groupBox_3);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));

        horizontalLayout_4->addWidget(pushButtonStop);


        verticalLayout_2->addWidget(groupBox_3);


        horizontalLayout_2->addWidget(widgetControl);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        widgetInfo = new QWidget(centralwidget);
        widgetInfo->setObjectName(QString::fromUtf8("widgetInfo"));
        verticalLayout = new QVBoxLayout(widgetInfo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxConnectivity = new QGroupBox(widgetInfo);
        groupBoxConnectivity->setObjectName(QString::fromUtf8("groupBoxConnectivity"));
        gridLayout = new QGridLayout(groupBoxConnectivity);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBoxDevices = new QComboBox(groupBoxConnectivity);
        comboBoxDevices->setObjectName(QString::fromUtf8("comboBoxDevices"));

        gridLayout->addWidget(comboBoxDevices, 0, 2, 1, 1);

        pushButtonSearch = new QPushButton(groupBoxConnectivity);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));

        gridLayout->addWidget(pushButtonSearch, 0, 0, 1, 1);

        pushButtonConnect = new QPushButton(groupBoxConnectivity);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));

        gridLayout->addWidget(pushButtonConnect, 1, 0, 1, 1);

        pushButtonDisconnect = new QPushButton(groupBoxConnectivity);
        pushButtonDisconnect->setObjectName(QString::fromUtf8("pushButtonDisconnect"));

        gridLayout->addWidget(pushButtonDisconnect, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBoxConnectivity);

        textEditLogs = new QTextEdit(widgetInfo);
        textEditLogs->setObjectName(QString::fromUtf8("textEditLogs"));
        textEditLogs->setReadOnly(true);

        verticalLayout->addWidget(textEditLogs);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));

        verticalLayout->addLayout(formLayout);

        statusLine = new QLineEdit(widgetInfo);
        statusLine->setObjectName(QString::fromUtf8("statusLine"));
        statusLine->setEchoMode(QLineEdit::Normal);
        statusLine->setReadOnly(true);

        verticalLayout->addWidget(statusLine);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(widgetInfo);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Program", nullptr));
        groupBox_3->setTitle(QString());
        pushButtonRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        pushButtonStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        groupBoxConnectivity->setTitle(QCoreApplication::translate("MainWindow", "Connectivity", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButtonDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
