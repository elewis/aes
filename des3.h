/*
 * This file presents a student implementation of Triple DES, a standard revised from the original Data
 * Encryption Standard (DES). This implementation is for learning purposes only and should NOT be
 * considered secure for general use.
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

#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DES_BLOCK_SIZE 8
#define DES_KEY_SIZE 8 // Only 56 bits are actually used
#define DES_EXPANDED_KEY_SIZE 96
#define DES_ROUND_KEY_SIZE 6
#define DES_NROUNDS

bool des3_encrypt(const uint8_t input[DES_BLOCK_SIZE], uint8_t output[DES_BLOCK_SIZE], uint8_t key1[DES_KEY_SIZE], uint8_t key2[DES_KEY_SIZE]);

bool des3_decrypt(const uint8_t input[DES_BLOCK_SIZE], uint8_t output[DES_BLOCK_SIZE], uint8_t key1[DES_KEY_SIZE], uint8_t key2[DES_KEY_SIZE]);

#endif /* DES_H_INCLUDED */
