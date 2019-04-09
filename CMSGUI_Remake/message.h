#pragma once
//#include "CMSGUI.h"

/*
Flags in header:
[0]: file (2), audio (1), or text (0)
[1]: not used
[2]: deflate (3), huffman (2), RLECompression(1), or no compression(0)
*/
//made data length
const unsigned long maxData = 1000968;

//struct definitions
struct TestPacket {
	unsigned char	data[2000];
};

struct Header {
	unsigned short	checkSum;
	unsigned char	bReceiverAddr;
	unsigned char extension[4];
	unsigned long	lDataLength[3];
	char	flags[3][3];
};

struct Frame {   
	Header header;
	unsigned char data[maxData];
};

struct Node {
	Node* pNext;
	Frame frame;
};

enum CHECKSUM {
	CHK_8BIT, CHK_16BIT, CHK_32BIT, CHK_ERROR
};

//functions related to dealing with message data, header data; see .cpp for more details
void RLECompress(Frame* frame);
void RLEDecompress(Frame* frame);
void compHuffmanFrame(Frame* frame);
void decompHuffmanFrame(Frame* frame);
void zCompress(Frame* frame);
void zDecomp(Frame* frame);
void addToQueue(Node* pn);
long compareBits(unsigned char* buffer, long inLen);
long compareBytes(unsigned char* buffer, long inLen);
void completeHeader(Frame* frame);
int VoteOn(unsigned char* Instances, int nInstances, int Size);
int Vote1D(unsigned long* Instances, int nInstance, int Size);
void VoteOnHeader(Frame frame);
unsigned int Checksum(void* buf, int iBufLen, CHECKSUM iType);