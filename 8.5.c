#include <stdio.h>
#include "tcpheader.h"


int getSourcePort(const unsigned char *tcp_hdr)
{
	int sourceport = 0;
	for(int i = 0; i<2;i++){
		for(int a = 0;a < 8; a++){
			if(tcp_hdr[i] & (1<<a)){
				sourceport |= (1<<(a+(1-i)*8));
			}
		}
	}
	return sourceport;
}

int getDestinationPort(const unsigned char *tcp_hdr)
{
	int destinationport = 0;
	for(int i = 2; i<4;i++){
		for(int a = 0;a < 8; a++){
			if(tcp_hdr[i] & (1<<a)){
				destinationport |= (1<<(a+(1-i)*8));
			}
		}
	}
	return destinationport;
}

void setSourcePort(unsigned char *tcp_hdr, int port)

void setDestinationPort(unsigned char *tcp_hdr, int port)

int getAckFlag(const unsigned char *tcp_hdr)
{
	int ack = 0;
	if (tcp_hdr[13] & (1<<4)){
		ack = 1; 
	}
	return ack;
}

void setAckFlag(unsigned char *tcp_hdr, int flag)

int getDataOffset(const unsigned char *tcp_hdr)
{
	int dataoffset = 0;
	int bit = 4
	for(int i = bit; i<8;i++){
		if(tcp_hdr[12] & (1<<i)){
			dataoffset |= (1<<i-bit);
		}
	}
	return dataoffset;
}

void setDataOffset(unsigned char *tcp_hdr, int offset)





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
}