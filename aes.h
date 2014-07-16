/*
 * This file presents a student implementation of the Advanced Encryption Standard Rijndael cipher.
 * This implementation is for learning purposes only and should NOT be considered secure for general use.
 * 
 * Author: Ethan Lewis <eclewis21@gmail.com>
 *
 * This code is hereby placed in the public domain.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
 
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
