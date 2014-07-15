
#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define AES_BLOCK_SIZE 16

typedef struct {
    size_t keysize;
    size_t expanded_keysize;
    size_t nrounds;
} aes_spec;

bool aes_encrypt(uint8_t input[AES_BLOCK_SIZE], uint8_t output[AES_BLOCK_SIZE], uint8_t *key, size_t keysize);

bool aes_decrypt(uint8_t input[AES_BLOCK_SIZE], uint8_t output[AES_BLOCK_SIZE], uint8_t *key, size_t keysize);

#endif /* AES_H_INCLUDED */
