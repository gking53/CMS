#include "CMSGUI.h"

//various items uesd to store cross thread values
extern HANDLE hCom;
extern Node* pHead;
extern int numItems;
Frame* frame;
extern Frame* newFrame;
TestPacket* testPacket;
bool switchStatus = 1;
bool testStatus = 0;
long testResults = 0;
bool stopStatus = 0;
char compressionChoice = 0;
char comSelection[5] = { "COM7" };
int comSpeed = 2400;

//inital window decleration
CMSGUI::CMSGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

//INPUT RELATED FUNCTIONS
//get text data and prepare header for transmission
void CMSGUI::on_inputTextButton_clicked(void) {
	ui.switchButton->setEnabled(0);
	disableSending();
	int msgLen = 0;
	QString tempString;
	QByteArray ba;
	frame = (Frame*)calloc(1, sizeof(Frame));
	tempString = ui.inputText->toPlainText();
	ba = tempString.toLocal8Bit();
	msgLen = tempString.length();
	if (msgLen > 140) {
		msgLen = 140;
	}
	ui.inputText->clear();
	memcpy(frame->data, ba, msgLen);
	frame->header.lDataLength[0] = msgLen;
	frame->header.flags[0][0] = 0;
	if(compressionChoice==3){ //deflate
		frame->header.flags[0][2] = 3;
	}
	else if (compressionChoice == 1) { //rle
		frame->header.flags[0][2] = 1;
	}
	else if (compressionChoice == 2) { //huffman
		frame->header.flags[0][2] = 2;
	}
	else {
		frame->header.flags[0][2] = 0;
	}
	sendData();
}

//send arbitrary data
void CMSGUI::sendData(void) {
	QThread *thread = new QThread(this);
	Sender* sender = new Sender();
	sender->moveToThread(thread);
	connect(thread, SIGNAL(started()), sender, SLOT(sendData()));
	connect(thread, SIGNAL(started()), this, SLOT(inputStatus()));
	connect(sender, SIGNAL(finished()), this, SLOT(enableSending()));
	connect(sender, SIGNAL(finished()), sender, SLOT(deleteLater()));
	connect(sender, SIGNAL(finished()), this, SLOT(normalStatus()));
	connect(sender, SIGNAL(finished()), thread, SLOT(quit()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

//get audio and get the frame ready to send
void CMSGUI::on_inputAudioButton_clicked(void) {
	disableSending();
	InitializeRecording();
	frame = (Frame*)calloc(1, sizeof(Frame));
	ui.statusBar->showMessage(tr("Recording Message"));
	RecordBuffer((short*)frame->data, RECORD_TIME*SAMPLES_SEC);
	CloseRecording();
	ui.statusBar->clearMessage();
	frame->header.lDataLength[0] = RECORD_TIME * SAMPLES_SEC * 2;
	frame->header.flags[0][0] = 1;
	if (compressionChoice == 3) { //deflate
		frame->header.flags[0][2] = 3;
	}
	else if (compressionChoice == 1) { //rle
		frame->header.flags[0][2] = 1;
	}
	else if (compressionChoice == 2) { //huffman
		frame->header.flags[0][2] = 2;
	}
	else { //uncompressed
		frame->header.flags[0][2] = 0;
	}
	sendData();
}

//prepare test packet for sending
void CMSGUI::on_testButton_clicked(void) {
	disableSending();
	int i = 0;
	testPacket = (TestPacket*)calloc(1, sizeof(TestPacket));
	while (i < sizeof(TestPacket)) {
		testPacket->data[i] = 0xAA;
		i++;
	}
	sendTest();
}

//send a test packet on seperate thread
void CMSGUI::sendTest(void) {
	QThread *thread = new QThread(this);
	Sender* sender = new Sender();
	sender->moveToThread(thread);
	connect(thread, SIGNAL(started()), sender, SLOT(sendTest()));
	connect(thread, SIGNAL(started()), this, SLOT(inputStatus()));
	connect(sender, SIGNAL(finished()), this, SLOT(enableSending()));
	connect(sender, SIGNAL(finished()), sender, SLOT(deleteLater()));
	connect(sender, SIGNAL(finished()), this, SLOT(normalStatus()));
	connect(sender, SIGNAL(finished()), thread, SLOT(quit()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

//get file from user and prepare for transmission
void CMSGUI::on_fileButton_clicked(void) {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File to Transfer"), "",
		tr("All Files (*)"));
	if (fileName.isEmpty()) {
		return;
	}
	else {
		FILE* fp;
		disableSending();
		frame = (Frame*)calloc(1, sizeof(Frame));
		QByteArray ba = fileName.toLocal8Bit();
		const char* fpName = ba.data();
		fp = fopen(fpName, "rb");
		fseek(fp, 0, SEEK_END);
		unsigned long fLength = ftell(fp);
		rewind(fp);
		if (fLength > sizeof(frame->data)) {
			fclose(fp);
			free(frame);
		}
		else {
			QFileInfo ex = QFileInfo(fileName);
			QString exString = ex.suffix();
			ba = exString.toLocal8Bit();
			const char* exName = ba.data();
			if (strlen(exName) > 5) {
				frame->header.extension[0] = 0;
			}
			else {
				memcpy(frame->header.extension, exName, strlen(exName));
			}
			frame->header.lDataLength[0] = fLength;
			frame->header.flags[0][0] = 2;
			fread(frame->data, fLength, 1, fp);
			if (compressionChoice == 3) { //deflate
				frame->header.flags[0][2] = 3;
			}
			else if (compressionChoice == 1) { //rle
				frame->header.flags[0][2] = 1;
			}
			else if (compressionChoice == 2) { //huffman
				frame->header.flags[0][2] = 2;
			}
			else { //uncompressed
				frame->header.flags[0][2] = 0;
			}
			fclose(fp);
			qDebug("Starting to send data");
			sendData();
		}
	}
}

//buttons used for buttons and checkboxes being toggled
void CMSGUI::on_uncompRButton_clicked(void) {
	compressionChoice = 0;
}

void CMSGUI::on_RLERButton_clicked(void) {
	compressionChoice = 1;
}

void CMSGUI::on_huffmanRButton_clicked(void) {
	compressionChoice = 2;
}

void CMSGUI::on_deflateRButton_clicked(void) {
	compressionChoice = 3;
}

void CMSGUI::on_testBox_toggled(void) {
	testStatus = !testStatus;
}

//status messages for bottom of gui window
void CMSGUI::inputStatus(void) {
	ui.statusBar->showMessage(tr("Sending Data"));
}

void CMSGUI::outputStatus(void) {
	ui.statusBar->showMessage(tr("Receiving Data"));
}

void CMSGUI::normalStatus(void) {
	ui.statusBar->showMessage(tr("COM is open"));
}

//SWITCHING RELATED FUNCTIONS
//button for switching modes, clears the port and if receiving starts to receive
void CMSGUI::on_switchButton_clicked(void) {
	clearMask();
	toggleSending();
	normalStatus();
	if (switchStatus == 0) {
		ui.switchLable->setText("Receiving");
		receive();
	}
	else {
		ui.switchLable->setText("Sending");
	}
}

//disable / enable a ton of gui stuff that shouldnt be used when switching modes
void CMSGUI::toggleSending(void) {
	switchStatus = !switchStatus;
	ui.inputAudioButton->setEnabled(switchStatus);
	ui.inputTextButton->setEnabled(switchStatus);
	ui.RLERButton->setEnabled(switchStatus);
	ui.huffmanRButton->setEnabled(switchStatus);
	ui.deflateRButton->setEnabled(switchStatus);
	ui.uncompRButton->setEnabled(switchStatus);
	ui.testButton->setEnabled(switchStatus);
	ui.fileButton->setEnabled(switchStatus);
}

void CMSGUI::disableSending(void) {
	ui.commBox->setEnabled(0);
	ui.inputAudioButton->setEnabled(0);
	ui.inputTextButton->setEnabled(0);
	ui.RLERButton->setEnabled(0);
	ui.huffmanRButton->setEnabled(0);
	ui.deflateRButton->setEnabled(0);
	ui.uncompRButton->setEnabled(0);
	ui.testButton->setEnabled(0);
	ui.fileButton->setEnabled(0);
}

void CMSGUI::enableSending(void) {
	ui.switchButton->setEnabled(1);
	ui.commBox->setEnabled(1);
	ui.inputAudioButton->setEnabled(1);
	ui.inputTextButton->setEnabled(1);
	ui.RLERButton->setEnabled(1);
	ui.huffmanRButton->setEnabled(1);
	ui.deflateRButton->setEnabled(1);
	ui.uncompRButton->setEnabled(1);
	ui.testButton->setEnabled(1);
	ui.fileButton->setEnabled(1);
}

void CMSGUI::disablePop(void) {
	ui.popButton->setEnabled(0);
}

void CMSGUI::enablePop(void) {
	ui.popButton->setEnabled(1);
}

//update com port number
void CMSGUI::on_commBox_currentIndexChanged(const QString &text) {
	QByteArray ba = text.toLocal8Bit();
	char* temp = ba.data();
	memcpy(comSelection, temp, 5);
	ui.statusBar->showMessage(tr("Closing COM"));
	clearMask();
	purgePort();
	CloseHandle(hCom);
	initPort();
	if (hCom == INVALID_HANDLE_VALUE) {
		ui.statusBar->showMessage(tr("Error opening COM port"));
		stopStatus = 1;
		if (switchStatus == 1) {
			disableSending();
		}
	}
	else {
		ui.statusBar->showMessage(tr("COM is open"));
		stopStatus = 0;
		if (switchStatus == 1) {
			enableSending();
		}
		else {
			receive();
		}
	}
}

//update com port speed
void CMSGUI::on_speedBox_currentIndexChanged(const QString &text) {
	comSpeed = text.toInt();
	ui.statusBar->showMessage(tr("Closing COM"));
	clearMask();
	purgePort();
	CloseHandle(hCom);
	initPort();
	if (hCom == INVALID_HANDLE_VALUE) {
		ui.statusBar->showMessage(tr("Error opening COM port"));
		stopStatus = 1;
		if (switchStatus == 1) {
			disableSending();
		}
	}
	else {
		ui.statusBar->showMessage(tr("COM is open"));
		stopStatus = 0;
		if (switchStatus == 1) {
			enableSending();
		}
		else {
			receive();
		}
	}
}

//clear the mask when switching modes to escape the waitcommevent, uses a seperate thread to do so as its not asyncronous
void CMSGUI::clearMask(void) {
	std::thread first(SetCommMask,hCom,0);
	first.detach();
}

//OUTPUT RELATED FUNCTIONS
//receive data from the port with a seperate thread
void CMSGUI::receive(void) {
	ui.itemsLabel->setText("Items in Queue: " + QString::number(numItems));
	if (switchStatus == 0 && stopStatus==0) {
		QThread *thread = new QThread(this);
		Receiver* receiver = new Receiver();
		receiver->moveToThread(thread);
		connect(thread, SIGNAL(started()), receiver, SLOT(checkInput()));
		//connect(receiver, SIGNAL(haveData()), this, SLOT(outputStatus()));
		//connect(receiver, SIGNAL(haveData()), this, SLOT(disablePop()));
		connect(receiver, SIGNAL(updateRatio()), this, SLOT(updateRatio()));
		connect(receiver, SIGNAL(doneData()), this, SLOT(enablePop()));
		connect(receiver, SIGNAL(finished()), this, SLOT(normalStatus()));
		connect(receiver, SIGNAL(finished()), receiver, SLOT(deleteLater()));
		connect(receiver, SIGNAL(finished()), thread, SLOT(quit()));
		connect(receiver, SIGNAL(finished()), thread, SLOT(deleteLater()));
		connect(receiver, SIGNAL(finished()), this, SLOT(receive()));
		thread->start();
	}
}

//procces a frame of data, aka get it ready for output
void CMSGUI::processFrame(Frame* frame) {
	if (frame->header.flags[0][2] == 1) {
		RLEDecompress(frame);
	}
	else if (frame->header.flags[0][2] == 2) {
		decompHuffmanFrame(frame);
	}
	else if (frame->header.flags[0][2] == 3) {
		zDecomp(frame);
	}
	if (frame->header.flags[0][0] == 0) {
		updateText((char*)frame->data);
	}
	else if (frame->header.flags[0][0] == 1) {
		InitializePlayback();
		PlayBuffer((short*)frame->data, frame->header.lDataLength[0] / 2);
		ClosePlayback();
	}
	else if (frame->header.flags[0][0] == 2) {
		QString fileEx = QString::fromLocal8Bit((const char*)frame->header.extension);

		QString fileName = QFileDialog::getSaveFileName(this,
			tr("Save Transfered File"), "",
			tr("(*."+fileEx.toLocal8Bit()+");;All Files (*)"));
		if (fileName.isEmpty());
		else {
			QByteArray ba = fileName.toLocal8Bit();
			const char* fpName = ba.data();
			FILE* fp;
			fp = fopen(fpName, "wb");
			fwrite(frame->data, frame->header.lDataLength[0], 1, fp);
			fclose(fp);
		}
	}
}

//update the text output
void CMSGUI::updateText(char* data) {
	ui.outputText->clear();
	ui.outputText->setText(data);
}

//take a frame off the queue
void CMSGUI::on_popButton_clicked(void) {
	if (pHead == NULL) {
		return;
	}
	Node* ptemp = pHead;
	pHead = pHead->pNext;
	processFrame(&ptemp->frame);
	free(ptemp);
	numItems = numItems - 1;
	ui.itemsLabel->setText("Items in Queue: " + QString::number(numItems));
}

//used for error ratio on test packet
void CMSGUI::updateRatio(void) {
	ui.outputText->clear();
	double error = ((double)testResults / ((double)sizeof(TestPacket)*8))*100;
	ui.outputText->setText("There were " + QString::number(testResults)+ " bit errors out of "+QString::number(sizeof(TestPacket)*8)+" bits sent ("+QString::number(error)+" percent error)");
}

//CLOSING AND SENDING RELATED FUNCTIONS
//closing event to stop as many threads as possible before the program shuts down
void CMSGUI::closeEvent(QCloseEvent *event) {
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("CMSGUI"), tr("Are you sure?\n"), QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		event->accept();
	}
}

//functions that call when the window / program is opened
void CMSGUI::showEvent(QShowEvent *event) {
	QWidget::showEvent(event);
	initPort();
	ui.itemsLabel->setText("Items in Queue: " + QString::number(numItems));
	if (hCom == INVALID_HANDLE_VALUE) {
		ui.statusBar->showMessage(tr("Error opening COM port"));
	}
	else {
		ui.statusBar->showMessage(tr("COM is open"));
	}
}



//SENDING WORKER FUNCTIONS 
//calls on the sending thread when the thread starts, finilizes data before being send out
void Sender::sendData(void) {
	if (frame->header.flags[0][2] == 1) {
		RLECompress(frame);
	}
	else if (frame->header.flags[0][2] == 2) {
		compHuffmanFrame(frame);
	}
	else if (frame->header.flags[0][2] == 3) {
		zCompress(frame);
	}
	qDebug("Done compressing");
	completeHeader(frame);
	frame->header.checkSum = Checksum(frame->data, frame->header.lDataLength[0], CHK_16BIT);
	frame->header.bReceiverAddr = 0xFF;
	qDebug("Starting to send");
	outputToPort(frame, frame->header.lDataLength[0] + sizeof(Header));
	free(frame);
	qDebug("Done sending");
	emit(finished());
}

//what the sending thread is called to send a test packet
void Sender::sendTest(void) {
	outputToPort(testPacket, sizeof(TestPacket));
	free(testPacket);
	emit(finished());
}


//RECEIVER WORKER FUNCTIONS
//checks for data coming in from the port, if there is data, checks if the user thinks its a test packet and then deals with it either on the queue or error calc for the test packet
void Receiver::checkInput(void) {
	Node* pn;
	pn = (Node*)calloc(1, sizeof(Node));
	pn->pNext = NULL;
	DWORD eventMasks;
	SetCommMask(hCom, EV_RXCHAR);
	WaitCommEvent(hCom, &eventMasks, NULL);
	emit(haveData());
	if (testStatus == 1) {
		TestPacket* testPacket;
		testPacket = (TestPacket*)calloc(1, sizeof(TestPacket));
		long c = inputFromPort(&testPacket->data,sizeof(TestPacket));
		if (c == 0) {
			free(pn);
			free(testPacket);
			emit(doneData());
			emit(finished());
		}
		else {
			testResults = 0;
			testResults = compareBits(testPacket->data, sizeof(TestPacket));
			free(pn);
			free(testPacket);
			emit(doneData());
			emit(updateRatio());
			emit(finished());
		}
	}
	else {
		long c = inputFromPort(&pn->frame, sizeof(Frame));
		if (c == 0) {
			free(pn);
			emit(doneData());
			emit(finished());
		}
		else {
			VoteOnHeader(pn->frame);
			if (Checksum(pn->frame.data, pn->frame.header.lDataLength[0], CHK_16BIT)!=pn->frame.header.checkSum) {
				free(pn);
				emit(doneData());
				emit(finished());
			}
			else if (pn->frame.header.bReceiverAddr != 0xFF) {
				free(pn);
				emit(doneData());
				emit(finished());
			}
			else {
				addToQueue(pn);
				numItems = numItems + 1;
				emit(doneData());
				emit(finished());
			}
		}
	}
}