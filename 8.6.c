#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "xorcipher.h"


/*
 * Encrypts / decrypts the void* buffer named <data>
 * Encrypted data will be saved to the same <data> -buffer.
 * Encryption is based on XOR operation using a 32-bit <key>
 */
void confidentiality_xor(uint32_t key, void* data, int len)
{
	int *encodeme = data;
	for (int i = 0; i<len; i++){
		encodeme[i] ^= key;
	}
}

/*
 * Encrypts / decrypts the void* buffer named <data>
 * Encrypted data will be saved to the same <data> -buffer.
 * Encryption is based on XOR operation using a 32-bit <key>
 * After encrypting one 32-bit block of original data, the key shifts one bit left
 */
void confidentiality_xor_shift(uint32_t key, void* data, int len)
{
	int *encodeme = data;
	int buffer = 0;
	for (int i = 0; i < len; i++){
		encodeme[i] ^= key;
		if (key & (1<<31)){
			buffer = 1;
		}
		else{
			buffer = 0;
		}
		key = key <<1;
		if (buffer){
			key |= 1;
		}
		else{
			key &= ~(1);
		}
	}
}

void print_uint32_hex(void* data, int len)
{
	for(int i = 0; i < len; i++) printf("0x%08x ", ((uint32_t*)data)[i]);
	printf("\n");
}

int main()
{
	srand(time(NULL));

	// uint32_t confidentiality_key = 0x00000000;
	uint32_t confidentiality_key = rand();

	uint32_t copy_key = confidentiality_key;

	char cryptme[] = "This is a test string to try";
	int stringlen = ((strlen(cryptme) + 1) / sizeof(uint32_t)) + ((strlen(cryptme) + 1) % sizeof(uint32_t) ? 1 : 0);

	printf("%d", stringlen);

	printf("Randomly seeded confidentiality_key: 0x%08x\n", confidentiality_key);	

	printf("Before ciphered: %s\n", cryptme);
	print_uint32_hex(cryptme, stringlen);

	confidentiality_xor(confidentiality_key,(void*)cryptme, stringlen);

	printf("After ciphered: %s\n", cryptme);
	print_uint32_hex(cryptme, stringlen);

	confidentiality_xor(copy_key,(void*)cryptme,8);

	printf("After deciphered: %s\n", cryptme);
	print_uint32_hex(cryptme, stringlen);

	copy_key = confidentiality_key;

	printf("Before ciphered: %s\n", cryptme);

	confidentiality_xor_shift(confidentiality_key,(void*)cryptme, stringlen);

	printf("After ciphered with shift: %s\n", cryptme);
	print_uint32_hex(cryptme, stringlen);

	confidentiality_xor_shift(copy_key,(void*)cryptme,8);

	printf("After decciphered with shift: %s\n", cryptme);
	print_uint32_hex(cryptme, stringlen);


	return 0;
}