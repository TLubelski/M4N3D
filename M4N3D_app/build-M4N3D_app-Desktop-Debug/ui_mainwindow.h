/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *console;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonHelp;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBoxLoop;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonRun;
    QPushButton *pushButtonStop;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QTextEdit *textEditPacket;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButtonPacketsClear;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QWidget *widgetInfo;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxConnectivity;
    QGridLayout *gridLayout;
    QComboBox *comboBoxDevices;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonDisconnect;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *textEditLogs;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonLogsClear;
    QCheckBox *checkBoxDebug;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *x;
    QLineEdit *xValue;
    QHBoxLayout *horizontalLayout;
    QLabel *y;
    QLineEdit *yValue;
    QHBoxLayout *horizontalLayout_8;
    QLabel *z;
    QLineEdit *zValue;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_11;
    QLabel *j1;
    QLineEdit *j1Value;
    QHBoxLayout *horizontalLayout_9;
    QLabel *j2;
    QLineEdit *j2Value;
    QHBoxLayout *horizontalLayout_7;
    QLabel *j3;
    QLineEdit *j3Value;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1116, 751);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widgetControl = new QWidget(centralwidget);
        widgetControl->setObjectName(QString::fromUtf8("widgetControl"));
        verticalLayout_2 = new QVBoxLayout(widgetControl);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_4 = new QGroupBox(widgetControl);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout_7 = new QVBoxLayout(groupBox_4);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        console = new QTextEdit(groupBox_4);
        console->setObjectName(QString::fromUtf8("console"));

        verticalLayout_7->addWidget(console);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pushButtonOpen = new QPushButton(groupBox_4);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));

        horizontalLayout_10->addWidget(pushButtonOpen);

        pushButtonSave = new QPushButton(groupBox_4);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));

        horizontalLayout_10->addWidget(pushButtonSave);

        pushButtonHelp = new QPushButton(groupBox_4);
        pushButtonHelp->setObjectName(QString::fromUtf8("pushButtonHelp"));

        horizontalLayout_10->addWidget(pushButtonHelp);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        checkBoxLoop = new QCheckBox(groupBox_4);
        checkBoxLoop->setObjectName(QString::fromUtf8("checkBoxLoop"));

        horizontalLayout_10->addWidget(checkBoxLoop);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonRun = new QPushButton(groupBox_4);
        pushButtonRun->setObjectName(QString::fromUtf8("pushButtonRun"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonRun->sizePolicy().hasHeightForWidth());
        pushButtonRun->setSizePolicy(sizePolicy1);
        pushButtonRun->setMinimumSize(QSize(0, 0));
        pushButtonRun->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 128, 128);"));

        horizontalLayout_4->addWidget(pushButtonRun);

        pushButtonStop = new QPushButton(groupBox_4);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonStop->sizePolicy().hasHeightForWidth());
        pushButtonStop->setSizePolicy(sizePolicy2);
        pushButtonStop->setMinimumSize(QSize(0, 0));
        pushButtonStop->setStyleSheet(QString::fromUtf8("background-color: #e66100"));

        horizontalLayout_4->addWidget(pushButtonStop);


        verticalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(widgetControl);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        textEditPacket = new QTextEdit(groupBox_3);
        textEditPacket->setObjectName(QString::fromUtf8("textEditPacket"));
        textEditPacket->setReadOnly(true);

        verticalLayout_8->addWidget(textEditPacket);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButtonPacketsClear = new QPushButton(groupBox_3);
        pushButtonPacketsClear->setObjectName(QString::fromUtf8("pushButtonPacketsClear"));

        horizontalLayout_5->addWidget(pushButtonPacketsClear);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_8->addLayout(horizontalLayout_5);


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

        groupBox_2 = new QGroupBox(widgetInfo);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        textEditLogs = new QTextEdit(groupBox_2);
        textEditLogs->setObjectName(QString::fromUtf8("textEditLogs"));
        textEditLogs->setReadOnly(true);

        verticalLayout_6->addWidget(textEditLogs);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonLogsClear = new QPushButton(groupBox_2);
        pushButtonLogsClear->setObjectName(QString::fromUtf8("pushButtonLogsClear"));

        horizontalLayout_3->addWidget(pushButtonLogsClear);

        checkBoxDebug = new QCheckBox(groupBox_2);
        checkBoxDebug->setObjectName(QString::fromUtf8("checkBoxDebug"));

        horizontalLayout_3->addWidget(checkBoxDebug);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(widgetInfo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        x = new QLabel(groupBox);
        x->setObjectName(QString::fromUtf8("x"));
        x->setMinimumSize(QSize(35, 0));
        x->setMaximumSize(QSize(50, 16777215));
        x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(x);

        xValue = new QLineEdit(groupBox);
        xValue->setObjectName(QString::fromUtf8("xValue"));
        sizePolicy2.setHeightForWidth(xValue->sizePolicy().hasHeightForWidth());
        xValue->setSizePolicy(sizePolicy2);
        xValue->setMaximumSize(QSize(100, 16777215));
        xValue->setMouseTracking(true);
        xValue->setReadOnly(true);

        horizontalLayout_6->addWidget(xValue);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        y = new QLabel(groupBox);
        y->setObjectName(QString::fromUtf8("y"));
        y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(y);

        yValue = new QLineEdit(groupBox);
        yValue->setObjectName(QString::fromUtf8("yValue"));
        sizePolicy2.setHeightForWidth(yValue->sizePolicy().hasHeightForWidth());
        yValue->setSizePolicy(sizePolicy2);
        yValue->setMaximumSize(QSize(100, 16777215));
        yValue->setReadOnly(true);

        horizontalLayout->addWidget(yValue);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        z = new QLabel(groupBox);
        z->setObjectName(QString::fromUtf8("z"));
        z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(z);

        zValue = new QLineEdit(groupBox);
        zValue->setObjectName(QString::fromUtf8("zValue"));
        sizePolicy2.setHeightForWidth(zValue->sizePolicy().hasHeightForWidth());
        zValue->setSizePolicy(sizePolicy2);
        zValue->setMaximumSize(QSize(100, 16777215));
        zValue->setReadOnly(true);

        horizontalLayout_8->addWidget(zValue);


        verticalLayout_3->addLayout(horizontalLayout_8);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        j1 = new QLabel(groupBox);
        j1->setObjectName(QString::fromUtf8("j1"));
        j1->setMinimumSize(QSize(50, 0));
        j1->setMaximumSize(QSize(50, 16777215));
        j1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(j1);

        j1Value = new QLineEdit(groupBox);
        j1Value->setObjectName(QString::fromUtf8("j1Value"));
        sizePolicy2.setHeightForWidth(j1Value->sizePolicy().hasHeightForWidth());
        j1Value->setSizePolicy(sizePolicy2);
        j1Value->setMaximumSize(QSize(100, 16777215));
        j1Value->setReadOnly(true);

        horizontalLayout_11->addWidget(j1Value);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        j2 = new QLabel(groupBox);
        j2->setObjectName(QString::fromUtf8("j2"));
        j2->setMaximumSize(QSize(50, 16777215));
        j2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(j2);

        j2Value = new QLineEdit(groupBox);
        j2Value->setObjectName(QString::fromUtf8("j2Value"));
        sizePolicy2.setHeightForWidth(j2Value->sizePolicy().hasHeightForWidth());
        j2Value->setSizePolicy(sizePolicy2);
        j2Value->setMaximumSize(QSize(100, 16777215));
        j2Value->setReadOnly(true);

        horizontalLayout_9->addWidget(j2Value);


        verticalLayout_5->addLayout(horizontalLayout_9);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        j3 = new QLabel(groupBox);
        j3->setObjectName(QString::fromUtf8("j3"));
        j3->setMaximumSize(QSize(50, 16777215));
        j3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(j3);

        j3Value = new QLineEdit(groupBox);
        j3Value->setObjectName(QString::fromUtf8("j3Value"));
        sizePolicy2.setHeightForWidth(j3Value->sizePolicy().hasHeightForWidth());
        j3Value->setSizePolicy(sizePolicy2);
        j3Value->setMaximumSize(QSize(100, 16777215));
        j3Value->setReadOnly(true);

        horizontalLayout_7->addWidget(j3Value);


        verticalLayout_5->addLayout(horizontalLayout_7);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_5);


        verticalLayout_4->addLayout(formLayout);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_2->addWidget(widgetInfo);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "M4N3D app", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Program", nullptr));
#if QT_CONFIG(tooltip)
        console->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        console->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">movej 100 50 20</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">movej 100 -50 20</p></body></html>", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        pushButtonHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        checkBoxLoop->setText(QCoreApplication::translate("MainWindow", "Loop", nullptr));
        pushButtonRun->setText(QCoreApplication::translate("MainWindow", "RUN", nullptr));
        pushButtonStop->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Packets", nullptr));
        pushButtonPacketsClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        groupBoxConnectivity->setTitle(QCoreApplication::translate("MainWindow", "Connectivity", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButtonDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Logs", nullptr));
        pushButtonLogsClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        checkBoxDebug->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Parameters", nullptr));
        x->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        y->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        z->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        j1->setText(QCoreApplication::translate("MainWindow", "j1", nullptr));
        j2->setText(QCoreApplication::translate("MainWindow", "j2", nullptr));
        j3->setText(QCoreApplication::translate("MainWindow", "j3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
