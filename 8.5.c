#include <stdio.h>
#include "tcpheader.h"


int getSourcePort(const unsigned char *tcp_hdr)
{
	int sourceport = 0;
	int byte = 0;
	int bit = 7;
	int sizeinbits = 16;
	int bitschecked = 0;
	while(bitschecked < sizeinbits){
		if (tcp_hdr[byte] & (1<<bit)){
			sourceport |= (1<<(bit + (1-byte)*8));
		}
		bitschecked++;
		bit--;
		if (bit < 0){
			bit = 7;
			byte++;
		}
	}
	return sourceport;
}

int getDestinationPort(const unsigned char *tcp_hdr)
{
	int destinationport = 0;
	int byte = 2;
	int bit = 7;
	int sizeinbits = 16;
	int bitschecked = 0;
	while(bitschecked < sizeinbits){
		if (tcp_hdr[byte] & (1<<bit)){
			destinationport |= (1<<(bit + (3-byte)*8));
		}
		bitschecked++;
		bit--;
		if (bit < 0){
			bit = 7;
			byte++;
		}
	}
	return destinationport;
}

void setSourcePort(unsigned char *tcp_hdr, int port)
{

	int byte = 0;
	int bit = 7;
	int sizeinbits = 16;
	int bitschecked = 0;
	while(bitschecked < sizeinbits){
		if (port & (1<<(bit+(1-byte)*8))){
			tcp_hdr[byte] |= (1<<bit);
		}
		else{
			tcp_hdr[byte] &= ~(1<<bit);
		}
		bitschecked++;
		bit--;
		if (bit < 0){
			bit = 7;
			byte++;
		}
	}
}

void setDestinationPort(unsigned char *tcp_hdr, int port)
{
	int byte = 2;
	int bit = 7;
	int sizeinbits = 16;
	int bitschecked = 0;
	while(bitschecked < sizeinbits){
		if (port & (1<<(bit+(3-byte)*8))){
			tcp_hdr[byte] |= (1<<bit);
		}
		else{
			tcp_hdr[byte] &= ~(1<<bit);
		}
		bitschecked++;
		bit--;
		if (bit < 0){
			bit = 7;
			byte++;
		}
	}
}

int getAckFlag(const unsigned char *tcp_hdr)
{
	int ack = 0;
	int byte = 13;
	int bit = 4;
	if (tcp_hdr[byte] & (1<<bit)){
		ack = 1;
	}
	return ack;
}

void setAckFlag(unsigned char *tcp_hdr, int flag)    
{
	if(flag == 1){
		tcp_hdr[13] |= (1<<4);
	}
	else{
		tcp_hdr[13] &= ~(1<<4);
	}
}

int getDataOffset(const unsigned char *tcp_hdr)
{
	int dataoffset = 0;
	int byte = 12;
	int sizeinbits = 4;
	int bit = 7;
	int bitschecked = 0;
	while(bitschecked < sizeinbits){
		if (tcp_hdr[byte] & (1<<bit)){
			dataoffset |= (1<<(bit-sizeinbits));
		}
		bitschecked++;
		bit--;
		if (bit < 0){
			bit = 7;
			byte++;
		}
	}	
	
	return dataoffset;
}

void setDataOffset(unsigned char *tcp_hdr, int offset)
{
	int dataoffset = 0;
	int byte = 12;
	int sizeinbits = 4;
	int bit = 7;
	int bitschecked = 0;
	
	while(bitschecked < sizeinbits){
		if (offset & (1<<(bit-sizeinbits)){
			tcp_hdr[byte] |= (1<<bit);
		}
		else{
			tcp_hdr[byte] &= ~(1<<bit);
		}
		bitschecked++;
		bit--;
		}
	}
}

// 001001000110100 = 4660, hex 1234
// 000000000110100
// 000000000001010


// 100010101100111 = 17767


int main()
{
    /* Feel free to modify this function to test different things */

    unsigned char bytes[] = {
        0x12,0x34,0x45,0x67,0xaa,0xbb,0xcc,0xdd,
        0xee,0xff,0xaa,0xbb,0xb1,0x5c,0x08,0x00,
        0x12,0x34,0x00,0x00 };
    
    printf("Source port: %d\n", getSourcePort(bytes));
    printf("Destination port: %d\n", getDestinationPort(bytes));
    printf("ACK flag: %d\n", getAckFlag(bytes));
    printf("Data Offset: %d\n", getDataOffset(bytes));   
	printf("setting: S: 1111, D: 420, 0, 12\n");
	setSourcePort(bytes, 1111);
	setDestinationPort(bytes,420);
	setAckFlag(bytes,0);
	setDataOffset(bytes,12);
	printf("\n");
    printf("Source port: %d\n", getSourcePort(bytes));
    printf("Destination port: %d\n", getDestinationPort(bytes));
    printf("ACK flag: %d\n", getAckFlag(bytes));
    printf("Data Offset: %d\n", getDataOffset(bytes));   
	return 1;
}