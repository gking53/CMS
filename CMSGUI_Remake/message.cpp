#include "message.h"
#include "huffman.h"
#include "CMSGUI.h"
#include <malloc.h>
#include <string.h>

Node* pHead = NULL;
unsigned char dataHolder[1000968];
unsigned long len;
int numItems = 0;

//add struct to the receiver node
void addToQueue(Node* pn) {
	if (pHead == NULL) {
		pHead = pn;
	}
	else {
		pn->pNext = pHead;
		pHead = pn;
	}
}

//rle comp
void RLECompress(Frame* frame){
	unsigned long i = 0;
	unsigned char count;
	unsigned long curPos = 0;
	unsigned char lastChar = frame->data[i];
	unsigned char curChar = frame->data[i++];
	while (i<frame->header.lDataLength[0]) {
		count = 1;
		while (i<frame->header.lDataLength[0]) {
			curChar = frame->data[i];
			if (curChar == lastChar) {
				count = count + 1;
				i++;
				lastChar = curChar;
				if (count == 255) {
					break;
				}
			}
			else {
				break;
			}
		}
		if (count > 3 || lastChar==0x1b) {
			dataHolder[curPos++] = 0x1b;
			dataHolder[curPos++] = count;
			dataHolder[curPos++] = lastChar;
		}
		else {
			int j = 0;
			for (j = 0; j < count; j++) {
				dataHolder[curPos++] = lastChar;
			}
		}
		lastChar = curChar;
	}
	if (curPos >= frame->header.lDataLength[0]) {
		frame->header.flags[0][2] = 0;
		return;
	}
	frame->header.lDataLength[0] = curPos;
	memcpy(frame->data, dataHolder, frame->header.lDataLength[0]);
	return;
}

//rle decomp
void RLEDecompress(Frame* frame) {
	unsigned long i = 0;
	unsigned j = 0;
	unsigned char count = 0;
	unsigned char curChar;
	unsigned long curPos = 0;
	while (i < (frame->header.lDataLength[0])) {
		curChar = frame->data[i++];
		if (curChar == 0x1b) {
			count = frame->data[i++];
			curChar = frame->data[i++];
			for (j = 0; j < count; j++) {
				dataHolder[curPos++] = curChar;
			}
		}
		else {
			dataHolder[curPos++] = curChar;
		}
	}
	frame->header.lDataLength[0] = curPos;
	memcpy(frame->data, dataHolder, frame->header.lDataLength[0]);
	return;
}

//huffman comp wrapper
void compHuffmanFrame(Frame* frame) {
	len = Huffman_Compress(frame->data, dataHolder, frame->header.lDataLength[0]);
	if (len >= frame->header.lDataLength[0]) {
		frame->header.flags[0][2] = 0;
		return;
	}
	qDebug("Size of original file: %d", frame->header.lDataLength[0]);
	frame->header.lDataLength[0] = len;
	memcpy(frame->data, dataHolder, frame->header.lDataLength[0]);
	qDebug("Size of compressed file: %d", len);
	return;
}

//huffman decomp wrapper
void decompHuffmanFrame(Frame* frame) {
	Huffman_Uncompress(frame->data, dataHolder, frame->header.lDataLength[0], maxData);
	frame->header.lDataLength[0] = frame->header.lDataLength[1];
	memcpy(frame->data, dataHolder, frame->header.lDataLength[0]);
	return;
}

//deflate wrapper from zlib
void zCompress(Frame* frame) {
	uLong sourceSize = frame->header.lDataLength[0];
	uLong destSize = compressBound(sourceSize);
	if (destSize > maxData) {
		frame->header.flags[0][2] = 0;
		return;
	}
	compress((Bytef*)dataHolder, &destSize, (Bytef*)frame->data, sourceSize);
	memcpy(frame->data, dataHolder, destSize);
	qDebug("Size of original file: %d", sourceSize);
	frame->header.lDataLength[0] = destSize;
	qDebug("Size of compressed file: %d", destSize);
}

//inflate wrapper from zlib
void zDecomp(Frame* frame) {
	int status;
	uLong sourceSize = frame->header.lDataLength[0];
	uLong destSize = maxData;
	status = uncompress((Bytef*)dataHolder, &destSize, (Bytef*)frame->data, sourceSize);
	memcpy(frame->data, dataHolder, destSize);
	frame->header.lDataLength[0] = destSize;
}

//compare test packet bits
long compareBits(unsigned char* buffer, long inLen) {
	long counter = 0;
	char charHolder;
	long i = 0;
	long shiftPlace = 1;
	while (i < inLen) {
		shiftPlace = 1;
		charHolder = buffer[i];
		while (shiftPlace < 8) {
			if (shiftPlace % 2 == 0) {
				if (charHolder & 0x00000001 == 0) {
					counter++;
				}
			}
			else {
				if (charHolder & 0x00000001 == 1) {
					counter++;
				}
			}
			charHolder = charHolder >> 1;
			shiftPlace++;
		}
		i++;
	}
	return counter;
}

//compare test packet bytes
long compareBytes(unsigned char* buffer, long inLen) {
	long counter = 0;
	long i = 0;
	while (i < inLen) {
		if (buffer[i] != 0xAA) {
			counter++;
		}
		i++;
	}
	return counter;
}

//copys the data for the vote on receive in the header
void completeHeader(Frame* frame) {
	frame->header.lDataLength[1] = frame->header.lDataLength[0];
	frame->header.lDataLength[2] = frame->header.lDataLength[0];
	memcpy(frame->header.flags[1], frame->header.flags[0], sizeof(frame->header.flags[0]));
	memcpy(frame->header.flags[2], frame->header.flags[0], sizeof(frame->header.flags[0]));
}

int VoteOn(unsigned char* Instances, int nInstances, int Size) { // function that votes on which items is the same to others the most, then returns which offset to the passed array has the most same hits
	int maxOffset = 0; // returns ‐1 if none are the same
	int max = 0; // used to store what the largest amount of same items for thecurrent vote
	int counter; // counts how many same hits there are for each i to j
	int i; // used for first for loop counter
	int j; // used for second for loop counter
	for (i = 0; i < nInstances; i++) { // loop for one axis of the array
		counter = 0; // reset counter when moving to second item on first axis
		for (j = i + 1; j < nInstances; j++) { // loop for second axis of the array
			if (0 == memcmp(&Instances[i], &Instances[j], Size)) { // if the item on axis 1 and axis 2 are the same, increase the counter
				counter++;
			}
		}
		if (counter != 0) { // check if any were the same
			if (counter > max) { // if a new max of comparisons was hit, update that
				max = counter; // set new max of comparisons
				maxOffset = i; // set offset in Instances[] for which item had the most hits
			}
		}
	}
	return maxOffset;
}
//voting for the data length
int Vote1D(unsigned long* Instances, int nInstances, int Size) {
	int maxOffset = -1;
	int max = 0;
	int counter;
	int i;
	int j;
	for (i = 0; i < nInstances; i++) {
		counter = 0;
		for (j = 0; j < nInstances; j++) {
			if (j == i) {
				continue;
			}
			else if (Instances[i] == Instances[j]) {
				counter++;
			}
		}
		if (counter != 0) {
			if (counter > max) {
				max = counter;
				maxOffset = i;
			}
		}
	}
	return maxOffset;
}

void VoteOnHeader(Frame frame) {
	//makes the first item of the header arrays the correct one based on voting
	int i;
	i = Vote1D(frame.header.lDataLength, 3, sizeof(long));
	frame.header.lDataLength[0] = frame.header.lDataLength[i];
	i = VoteOn((unsigned char*)frame.header.flags, 3, 3);
	memcpy(frame.header.flags[0], frame.header.flags[i], 3);
}

unsigned int Checksum(void* buf, int iBufLen, CHECKSUM iType) {
	unsigned int i; //for loop counter
	unsigned int sum = 0; //variable that holds all checksum operations
	unsigned char* store8; //char pointer that the void buf is cast to
	unsigned short* store16; //short pointer that the void buf is cast to
	unsigned long* store32;
	switch (iType) { //switch statements for choosing between 8 or 16 bit checksums and checks for errors if error is passed to this function or something completely different is passed somehow

	case CHK_8BIT: //8 bit checksum
		store8 = (unsigned char*)buf; //cast void pointer to char pointer
		for (i = 0; i < iBufLen; i++) { //for loop to add up each char in buffer
			sum = *store8 + sum; //adds the chars together
			*store8++; //move to the next char
		}
		sum = sum % 256; //mod to remove all top bytes and only leave the bottom byte
		return sum; //return the checksum
		break;
	case CHK_16BIT: //same as above loop but for shorts instead
		store16 = (unsigned short*)buf;
		for (i = 0; i < (iBufLen/2); i++) {
			sum = sum + *store16;
			*store16++;
		}
		sum = sum % 65536; //mod by 0x10000 to remove all top bytes and leave the 16 bit checksum
		return sum;
		break;
	//added 32 bit checksum, prolly shouldnt use this as its easy to overflow the unsigned int sum before the mod operation
	case CHK_32BIT:
		store32 = (unsigned long*)buf;
		for (i = 0; i < (iBufLen/4); i++) {
			sum = sum + *store32;
			*store32++;
		}
		sum = sum % LONG_MAX;
		return sum;
		break;
	case CHK_ERROR:
		return -1;
		break;
	default:
		return -1;
	}
}