/********************************************************************************
** Form generated from reading UI file 'CMSGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMSGUI_H
#define UI_CMSGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMSGUIClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *sendingLabel;
    QPlainTextEdit *inputText;
    QPushButton *inputTextButton;
    QPushButton *inputAudioButton;
    QPushButton *fileButton;
    QPushButton *testButton;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *RLERButton;
    QRadioButton *huffmanRButton;
    QRadioButton *deflateRButton;
    QRadioButton *uncompRButton;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *switchLable;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *switchButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *commBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *speedBox;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *itemsLabel;
    QTextEdit *outputText;
    QCheckBox *testBox;
    QPushButton *popButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMSGUIClass)
    {
        if (CMSGUIClass->objectName().isEmpty())
            CMSGUIClass->setObjectName(QStringLiteral("CMSGUIClass"));
        CMSGUIClass->resize(738, 447);
        centralWidget = new QWidget(CMSGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 717, 381));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        sendingLabel = new QLabel(layoutWidget);
        sendingLabel->setObjectName(QStringLiteral("sendingLabel"));
        sendingLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(sendingLabel);

        inputText = new QPlainTextEdit(layoutWidget);
        inputText->setObjectName(QStringLiteral("inputText"));

        verticalLayout->addWidget(inputText);

        inputTextButton = new QPushButton(layoutWidget);
        inputTextButton->setObjectName(QStringLiteral("inputTextButton"));

        verticalLayout->addWidget(inputTextButton);

        inputAudioButton = new QPushButton(layoutWidget);
        inputAudioButton->setObjectName(QStringLiteral("inputAudioButton"));

        verticalLayout->addWidget(inputAudioButton);

        fileButton = new QPushButton(layoutWidget);
        fileButton->setObjectName(QStringLiteral("fileButton"));

        verticalLayout->addWidget(fileButton);

        testButton = new QPushButton(layoutWidget);
        testButton->setObjectName(QStringLiteral("testButton"));

        verticalLayout->addWidget(testButton);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        RLERButton = new QRadioButton(layoutWidget);
        RLERButton->setObjectName(QStringLiteral("RLERButton"));

        verticalLayout_4->addWidget(RLERButton);

        huffmanRButton = new QRadioButton(layoutWidget);
        huffmanRButton->setObjectName(QStringLiteral("huffmanRButton"));

        verticalLayout_4->addWidget(huffmanRButton);

        deflateRButton = new QRadioButton(layoutWidget);
        deflateRButton->setObjectName(QStringLiteral("deflateRButton"));

        verticalLayout_4->addWidget(deflateRButton);

        uncompRButton = new QRadioButton(layoutWidget);
        uncompRButton->setObjectName(QStringLiteral("uncompRButton"));
        uncompRButton->setChecked(true);

        verticalLayout_4->addWidget(uncompRButton);


        verticalLayout->addLayout(verticalLayout_4);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        switchLable = new QLabel(layoutWidget);
        switchLable->setObjectName(QStringLiteral("switchLable"));
        switchLable->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(switchLable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(48, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        switchButton = new QPushButton(layoutWidget);
        switchButton->setObjectName(QStringLiteral("switchButton"));

        horizontalLayout->addWidget(switchButton);

        horizontalSpacer_2 = new QSpacerItem(48, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Ignored, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        commBox = new QComboBox(layoutWidget);
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->addItem(QString());
        commBox->setObjectName(QStringLiteral("commBox"));

        horizontalLayout_2->addWidget(commBox);

        horizontalSpacer_4 = new QSpacerItem(48, 20, QSizePolicy::Ignored, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        speedBox = new QComboBox(layoutWidget);
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->addItem(QString());
        speedBox->setObjectName(QStringLiteral("speedBox"));

        horizontalLayout_4->addWidget(speedBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        itemsLabel = new QLabel(layoutWidget);
        itemsLabel->setObjectName(QStringLiteral("itemsLabel"));

        verticalLayout_2->addWidget(itemsLabel);

        outputText = new QTextEdit(layoutWidget);
        outputText->setObjectName(QStringLiteral("outputText"));
        outputText->setReadOnly(true);

        verticalLayout_2->addWidget(outputText);

        testBox = new QCheckBox(layoutWidget);
        testBox->setObjectName(QStringLiteral("testBox"));

        verticalLayout_2->addWidget(testBox);

        popButton = new QPushButton(layoutWidget);
        popButton->setObjectName(QStringLiteral("popButton"));

        verticalLayout_2->addWidget(popButton);


        horizontalLayout_3->addLayout(verticalLayout_2);

        CMSGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CMSGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 738, 21));
        CMSGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CMSGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CMSGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CMSGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMSGUIClass->setStatusBar(statusBar);

        retranslateUi(CMSGUIClass);

        QMetaObject::connectSlotsByName(CMSGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *CMSGUIClass)
    {
        CMSGUIClass->setWindowTitle(QApplication::translate("CMSGUIClass", "CMSGUI", nullptr));
        sendingLabel->setText(QApplication::translate("CMSGUIClass", "Sending", nullptr));
        inputTextButton->setText(QApplication::translate("CMSGUIClass", "Input Text", nullptr));
        inputAudioButton->setText(QApplication::translate("CMSGUIClass", "Input Audio", nullptr));
        fileButton->setText(QApplication::translate("CMSGUIClass", "Input File", nullptr));
        testButton->setText(QApplication::translate("CMSGUIClass", "Send Test Packet", nullptr));
        RLERButton->setText(QApplication::translate("CMSGUIClass", "RLE", nullptr));
        huffmanRButton->setText(QApplication::translate("CMSGUIClass", "Huffman", nullptr));
        deflateRButton->setText(QApplication::translate("CMSGUIClass", "Deflate", nullptr));
        uncompRButton->setText(QApplication::translate("CMSGUIClass", "No Compression", nullptr));
        switchLable->setText(QApplication::translate("CMSGUIClass", "Sending", nullptr));
        switchButton->setText(QApplication::translate("CMSGUIClass", "Switch Modes", nullptr));
        commBox->setItemText(0, QApplication::translate("CMSGUIClass", "COM1", nullptr));
        commBox->setItemText(1, QApplication::translate("CMSGUIClass", "COM2", nullptr));
        commBox->setItemText(2, QApplication::translate("CMSGUIClass", "COM3", nullptr));
        commBox->setItemText(3, QApplication::translate("CMSGUIClass", "COM4", nullptr));
        commBox->setItemText(4, QApplication::translate("CMSGUIClass", "COM5", nullptr));
        commBox->setItemText(5, QApplication::translate("CMSGUIClass", "COM6", nullptr));
        commBox->setItemText(6, QApplication::translate("CMSGUIClass", "COM7", nullptr));
        commBox->setItemText(7, QApplication::translate("CMSGUIClass", "COM8", nullptr));
        commBox->setItemText(8, QApplication::translate("CMSGUIClass", "COM9", nullptr));

        commBox->setCurrentText(QApplication::translate("CMSGUIClass", "COM7", nullptr));
        speedBox->setItemText(0, QApplication::translate("CMSGUIClass", "75", nullptr));
        speedBox->setItemText(1, QApplication::translate("CMSGUIClass", "600", nullptr));
        speedBox->setItemText(2, QApplication::translate("CMSGUIClass", "1200", nullptr));
        speedBox->setItemText(3, QApplication::translate("CMSGUIClass", "2400", nullptr));
        speedBox->setItemText(4, QApplication::translate("CMSGUIClass", "4800", nullptr));
        speedBox->setItemText(5, QApplication::translate("CMSGUIClass", "9600", nullptr));
        speedBox->setItemText(6, QApplication::translate("CMSGUIClass", "14400", nullptr));
        speedBox->setItemText(7, QApplication::translate("CMSGUIClass", "19200", nullptr));
        speedBox->setItemText(8, QApplication::translate("CMSGUIClass", "38400", nullptr));
        speedBox->setItemText(9, QApplication::translate("CMSGUIClass", "57600", nullptr));
        speedBox->setItemText(10, QApplication::translate("CMSGUIClass", "115200", nullptr));
        speedBox->setItemText(11, QApplication::translate("CMSGUIClass", "1000000", nullptr));

        speedBox->setCurrentText(QApplication::translate("CMSGUIClass", "2400", nullptr));
        label_2->setText(QApplication::translate("CMSGUIClass", "Receiving", nullptr));
        itemsLabel->setText(QApplication::translate("CMSGUIClass", "Items in Queue: ", nullptr));
        testBox->setText(QApplication::translate("CMSGUIClass", "Receive Test Packet", nullptr));
        popButton->setText(QApplication::translate("CMSGUIClass", "Pop from Queue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMSGUIClass: public Ui_CMSGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMSGUI_H
