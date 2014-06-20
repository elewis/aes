
#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define AES_BLOCK_SIZE 16

typedef enum {
    AES_SUCCEED,
    AES_BAD_KEYSIZE,
    AES_OUT_OF_MEMORY,
    AES_BAD_INPUT
} aes_status;

typedef struct {
    unsigned int keysize;
    unsigned int expanded_keysize;
    unsigned int nrounds;
} aes_spec;

aes_status aes_encrypt(unsigned char block[AES_BLOCK_SIZE], unsigned char *key, unsigned int keysize);

aes_status aes_decrypt(unsigned char block[AES_BLOCK_SIZE], unsigned char *key, unsigned int keysize);

#endif /* AES_H_INCLUDED */
