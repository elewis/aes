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

#include <getopt.h>

#include "des3.h"

/* Contains the shift amount for rotating the key after each round, indexed by round number */
const uint8_t key_shifts[DES_NROUNDS] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


void permuted_choice_one(uint8_t left_key[DES_KEY_SIZE/2], uint8_t right_key[DES_KEY_SIZE/2], uint8_t round_key[DES_ROUND_KEY_SIZE])
{

}

void permuted_choice_two(uint8_t left_key[DES_KEY_SIZE/2], uint8_t right_key[DES_KEY_SIZE/2], uint8_t round_key[DES_ROUND_KEY_SIZE])
{

}

void next_encrypt_key(uint8_t left_key[DES_KEY_SIZE/2], uint8_t right_key[DES_KEY_SIZE/2], uint8_t round_key[DES_ROUND_KEY_SIZE], size_t round)
{

}

void next_decrypt_key(uint8_t left_key[DES_KEY_SIZE/2], uint8_t right_key[DES_KEY_SIZE/2], uint8_t round_key[DES_ROUND_KEY_SIZE], size_t round)
{

}

bool des_encrypt(const uint8_t input[DES_BLOCK_SIZE], uint8_t output[DES_BLOCK_SIZE], uint8_t key[DES_KEY_SIZE])
{
    return false;
}

bool des_decrypt(const uint8_t input[DES_BLOCK_SIZE], uint8_t output[DES_BLOCK_SIZE], uint8_t key[DES_KEY_SIZE])
{
    return false;
}

bool des3_encrypt(const uint8_t input[DES_BLOCK_SIZE], uint8_t output[DES_BLOCK_SIZE], uint8_t key1[DES_KEY_SIZE], uint8_t key2[DES_KEY_SIZE])
{
    bool status = true;
    uint8_t state[DES_BLOCK_SIZE];
    for (size_t i=0; i<DES_BLOCK_SIZE; i++)
        state[i] = input[i];
    status &= des_encrypt(state, state, key1);
    status &= des_decrypt(state, state, key2);
    status &= des_encrypt(state, state, key1);
    for (size_t i=0; i<DES_BLOCK_SIZE; i++)
        output[i] = state[i] & (status ? 0xff : 0x00); // Output all 0s on failure
    return status;
}

bool des3_decrypt(const uint8_t input[DES_BLOCK_SIZE], uint8_t output[DES_BLOCK_SIZE], uint8_t key1[DES_KEY_SIZE], uint8_t key2[DES_KEY_SIZE])
{
    bool status = true;
    uint8_t state[DES_BLOCK_SIZE];
    for (size_t i=0; i<DES_BLOCK_SIZE; i++)
        state[i] = input[i];
    status &= des_decrypt(state, state, key1);
    status &= des_encrypt(state, state, key2);
    status &= des_decrypt(state, state, key1);
    for (size_t i=0; i<DES_BLOCK_SIZE; i++)
        output[i] = state[i] & (status ? 0xff : 0x00); // Output all 0s on failure
    return status;
}
