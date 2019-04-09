#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QFileInfo>
#include <thread>
#include <Windows.h>
#include <QtZlib\zlib.h>
#include "sound.h"
#include "ui_CMSGUI.h"
#include "message.h"
#include "RS232Comm.h"

class CMSGUI : public QMainWindow
{
	Q_OBJECT

public:
	CMSGUI(QWidget *parent = Q_NULLPTR);

public slots:
	void on_inputTextButton_clicked(void);
	void on_inputAudioButton_clicked(void);
	void on_testButton_clicked(void);
	void on_fileButton_clicked(void);
	void on_testBox_toggled(void);
	void normalStatus(void);
	void enablePop(void);
	void disablePop(void);

	void on_RLERButton_clicked(void);
	void on_huffmanRButton_clicked(void);
	void on_deflateRButton_clicked(void);
	void on_uncompRButton_clicked(void);
	
	void on_switchButton_clicked(void);
	void toggleSending(void);
	void disableSending(void);
	void enableSending(void);
	void sendData(void);
	void sendTest(void);
	void inputStatus(void);

	void on_commBox_currentIndexChanged(const QString &text);
	void on_speedBox_currentIndexChanged(const QString &text);
	void clearMask(void);
	
	void processFrame(Frame* frame);
	void receive(void);
	void updateText(char* data);
	void on_popButton_clicked(void);
	void outputStatus(void);
	void updateRatio(void);

	void closeEvent(QCloseEvent *event);
	void showEvent(QShowEvent *ev);
	
signals:

private:
	Ui::CMSGUIClass ui;
};

class Receiver : public QObject {
	Q_OBJECT
public slots:
	void checkInput(void);
signals:
	void doneData(void);
	void haveData(void);
	void updateRatio(void);
	void finished(void);
};

class Sender : public QObject {
	Q_OBJECT
public slots:
	void sendData(void);
	void sendTest(void);
signals:
	void finished(void);
};