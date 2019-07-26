#ifndef AALTO_XOR_CIPHER_H
#define AALTO_XOR_CIPHER_H

void confidentiality_xor(uint32_t key, void* data, int len);

void confidentiality_xor_shift(uint32_t key, void* data, int len);

void print_uint32_hex(void* data, int len);

#endif /* AALTO_XOR_CIPHER_H */