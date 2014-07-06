/*
 * This file presents a student implementation of the Advanced Encryption Standard Rijndael cipher.
 * 
 * This implementation is for learning purposes only and should NOT be considered secure for general use.
 * 
 * Author: Ethan Lewis (eclewis21@gmail.com)
*/

#include <getopt.h>

#include "aes.h"

/*
    PUBLIC INTERFACE FUNCTIONS
*/



/*
    KEY SCHEDULE FUNCTIONS
*/

unsigned char RCON[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
};

unsigned char SBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

unsigned char INV_SBOX[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

void print_bytes(unsigned char *buf, size_t length) {
    for (; length>0; length--) {
        printf("%02x ", *buf++);
    }
    printf("\n");
}

void print_key(unsigned char *buf, size_t length) {
    for (; length>0; length--) {
        printf("%02x ", *buf++);
        if ((length - 1) % 16 == 0) {
            printf("\n");
        }
    }
}

void print_state(unsigned char state[AES_BLOCK_SIZE]) {
    unsigned int i;
    for (i=0; i<4; i++) {
        printf("%02x %02x %02x %02x\n", state[i], state[i+4], state[i+8], state[i+12]);
    }
    printf("\n");
}

void print_readable(aes_status status) {
    switch (status) {
        case AES_BAD_KEYSIZE:
            printf("AES: Bad key size. AES keysize must be 16, 24, or 32 bytes.\n");
            break;
        case AES_OUT_OF_MEMORY:
            printf("AES: Out of memory. Required space could not be acquired.\n");
            break;
        case AES_SUCCEED:
            printf("AES: Successful\n");
            break;
        default:
            printf("AES: Unrecognized status code\n");
    }
}

void key_schedule_core(unsigned char word[4], unsigned int i) {
    unsigned char tmp = word[0];
    word[0] = SBOX[word[1]] ^ RCON[i];
    word[1] = SBOX[word[2]];
    word[2] = SBOX[word[3]];
    word[3] = SBOX[tmp];
}

/*
 * AES_init_spec
 *
 * Initializes the values of an aes key specification according to
 * the given key size (contained in spec->keysize). The key specification
 * contains all public information about the key, but not the key itself.
 *
 * Params
 *   spec - type of aes_spec struct with preinitialized keysize field
 */
void aes_init_spec(aes_spec *spec) {
    switch (spec->keysize) {
        case 16:
            spec->expanded_keysize = 176;
            spec->nrounds = 10; break;
        case 24:
            spec->expanded_keysize = 208;
            spec->nrounds = 12; break;
        case 32:
            spec->expanded_keysize = 240;
            spec->nrounds = 14; break;
        default:
            spec->keysize = AES_BAD_KEYSIZE;
            spec->expanded_keysize = 0; break;
    }
}

/*
 * Rijndael Key Schedule (128, 192, or 256 bit)
 * 
 * The key schedule is used to expand the original cipher key into
 * separate round keys for use in the actual encryption step. The
 * length of the expanded key is dependent on the original key size
 * and the number of encryption rounds performed.
 *
 * Params
 *   key              - pointer to original encryption key
 *   keysize          - size of original key in bytes
 *   expanded_key     - pointer to free memory with enough space to hold the full
 *                      expanded key, determined by aes_expanded_keysize
 *   expanded_keysize - size of expanded key for given keysize
 *
 * Returns status code, indicating success of key_schedule (0=pass, >0 see ERR_KEY_SCHEDULE)
 */
void
key_schedule(unsigned char *key, unsigned char *expanded_key, aes_spec *spec)
{
    int j, n;
    unsigned int i, c;
    unsigned char *word;

    for (j=0; j<spec->keysize; j++) {
        expanded_key[j] = key[j];
    }

    i = 1;
    n = c = spec->keysize;
    while (c < spec->expanded_keysize) {
        word = (unsigned char*) (expanded_key + c);
        for (j=0; j<4; j++) {
            word[j] = word[j-4];
        }
        if (c % n == 0) {
            key_schedule_core(word, i++);
        }
        if (n == 32 && c % n == 16) {
            for (j=0; j<4; j++) {
                word[j] = SBOX[word[j]];
            }
        }
        for (j=0; j<4; j++) {
            word[j] ^= word[j-n];
        }
        c += 4;
    }
}

/*
    END KEY SCHEDULE
*/

/*  
    PRIMARY ALGORITHM STEPS
*/

void sub_bytes(unsigned char state[AES_BLOCK_SIZE]) {
    for (unsigned int i=0; i<AES_BLOCK_SIZE; i++) {
        state[i] = SBOX[state[i]];
    }
}

void shift_rows(unsigned char state[AES_BLOCK_SIZE]) {
    unsigned char state_cpy[AES_BLOCK_SIZE];
    unsigned int i, j=0;
    for (i=0; i<AES_BLOCK_SIZE; i++) {
        state_cpy[i] = state[j];
        j = (j+5) % AES_BLOCK_SIZE;
    }
    for (i=0; i<AES_BLOCK_SIZE; i++) {
        state[i] = state_cpy[i];
    }
}

void mix_column(unsigned char *r) {
    unsigned char i, neg;
    unsigned char one[4], two[4], thr[4];
    for (i=0; i<4; i++) {
        neg = (unsigned char) ((signed char) r[i] >> 7);
        one[i] = r[i];
        two[i] = (r[i] << 1) ^ (0x1b & neg);
        thr[i] = two[i] ^ one[i];
    }
    r[0] = two[0] ^ thr[1] ^ one[2] ^ one[3];
    r[1] = one[0] ^ two[1] ^ thr[2] ^ one[3];
    r[2] = one[0] ^ one[1] ^ two[2] ^ thr[3];
    r[3] = thr[0] ^ one[1] ^ one[2] ^ two[3];
}

void mix_columns(unsigned char state[AES_BLOCK_SIZE]) {
    unsigned char c;
    for (c=0; c<AES_BLOCK_SIZE; c+=4) {
        mix_column(state+c);
    }
}

void add_round_key(unsigned char state[AES_BLOCK_SIZE], unsigned char round_key[AES_BLOCK_SIZE]) {
    for (unsigned int i=0; i<AES_BLOCK_SIZE; i++) {
        state[i] ^= round_key[i];
    }
}

/*
    END PRIMARY ALGORITHM
*/

aes_status aes_encrypt(unsigned char block[AES_BLOCK_SIZE], unsigned char *key, unsigned int keysize) {
    aes_spec s = {0, 0, 0};
    aes_spec *spec = &s;
    unsigned char *expanded_key;
    unsigned int i;

    spec->keysize = keysize;
    aes_init_spec(spec);
    if (spec->keysize == AES_BAD_KEYSIZE) {
        return AES_BAD_KEYSIZE;
    }

    expanded_key = (unsigned char*) malloc(spec->expanded_keysize * sizeof(unsigned char));
    if (expanded_key == NULL) {
        return AES_OUT_OF_MEMORY;
    }
    key_schedule(key, expanded_key, spec);

    unsigned char state[AES_BLOCK_SIZE] = { 0 };
    for (i=0; i<AES_BLOCK_SIZE; i++) {
        state[i] = block[i];
    }

    /* Begin AES core */
    add_round_key(state, expanded_key);

    for (i=1; i<spec->nrounds; i++) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, expanded_key + (AES_BLOCK_SIZE * i));
    }
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, expanded_key + (AES_BLOCK_SIZE * spec->nrounds));
    /* End AES core */

    for (i=0; i<AES_BLOCK_SIZE; i++) {
        block[i] = state[i];
    }

    free(expanded_key);
    return AES_SUCCEED;
}

aes_status aes_decrypt(unsigned char block[AES_BLOCK_SIZE], unsigned char *key, unsigned int keysize) {
    return AES_SUCCEED;
}

void optparse(int argc, char **argv, unsigned int *keysize, char **key_file, char **in_file, char **out_file) {
    int opt, opterrs=0;
    unsigned int k;

    while((opt = getopt(argc, argv, ":b:k:i:o:")) != -1) {
        switch(opt) {
            case 'k':
                if (*key_file) {
                    fprintf(stderr, "Option -%c defined twice\n", optopt);
                    opterrs++;
                }
                *key_file = optarg;
                break;
            case 'i':
                if (*in_file) {
                    fprintf(stderr, "Option -%c defined twice\n", optopt);
                    opterrs++;
                }
                *in_file = optarg;
                break;
            case 'o':
                if (*out_file) {
                    fprintf(stderr, "Option -%c defined twice\n", optopt);
                    opterrs++;
                }
                *out_file = optarg;
                break;
            case 'b':
                k = atoi(optarg);
                if (!(k == 128 || k == 192 || k == 256)) {
                    fprintf(stderr, "Invalid keysize provided (req 128, 192, or 256): %s\n", optarg);
                    opterrs++;
                }
                *keysize = k / 8;
                break;
            case ':':
                fprintf(stderr, "Option -%c requires an operand\n", optopt);
                opterrs++;
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c\n", optopt);
                opterrs++;
            default:
                abort();
        }
    }
    if (opterrs) {
        fprintf(stderr, "Usage: %s [ -i in_file ] [ -o out_file ] [ -k key_file ]\n", argv[0]);
        exit(1);
    }
}

void cleanup(unsigned char *key, unsigned char *block) {
    if (key != NULL)
        free(key);
    if (block != NULL)
        free(block);
}

unsigned char hex_to_byte(unsigned char buf[2]) {
    unsigned char c = 0x00;
    if (buf[0] >= '0' && buf[0] <= '9') {
        c |= (buf[0] - '0') << 4;
    } else if (buf[0] >= 'a' && buf[0] <= 'f') {
        c |= (buf[0] - 'a' + 10) << 4;
    } else if (buf[0] >= 'A' && buf[0] <= 'F') {
        c |= (buf[0] - 'A' + 10) << 4;
    } else {
        printf("Invalid hex character %c\n", buf[0]);
        exit(1);
    }

    if (buf[1] >= '0' && buf[1] <= '9') {
        c |= (buf[1] - '0') & 0xf;
    } else if (buf[1] >= 'a' && buf[1] <= 'z') {
        c |= (buf[1] - 'a' + 10) & 0xf;
    } else if (buf[1] >= 'A' && buf[1] <= 'Z') {
        c |= (buf[1] - 'A' + 10) & 0xf;
    } else {
        printf("Invalid hex character %c\n", buf[1]);
        exit(1);
    }
    return c;
}

void fread_hex(FILE *f, unsigned char *buf, size_t nbytes) {
    unsigned char hbytes[2];
    for (; nbytes > 0; nbytes--) {
        hbytes[0] = fgetc(f);
        hbytes[1] = fgetc(f);
        if (hbytes[1] == EOF) {
            printf("Premature end of file\n");
            exit(1);
        }
        *buf++ = hex_to_byte(hbytes);
    }
}

void fwrite_hex(FILE *f, unsigned char *buf, size_t nbytes) {
    for (; nbytes > 0; nbytes--)
        fprintf(f, "%02x", *buf++);
}

int main(int argc, char **argv) {
    aes_status status;

    unsigned int keysize = 16;
    char *key_filen = NULL;
    char  *in_filen = NULL;
    char *out_filen = NULL;
    optparse(argc, argv, &keysize, &key_filen, &in_filen, &out_filen);

    unsigned char *block = malloc(AES_BLOCK_SIZE * sizeof(unsigned char));
    unsigned char *key   = malloc(keysize * sizeof(unsigned char));
    if (block == NULL || key == NULL) {
        printf("Out of memory. Aborting\n");
        cleanup(key, block);
        exit(1);
    }

    /* Read key */
    FILE *key_file = (key_filen == NULL) ? stdin  : fopen(key_filen, "r");
    fread_hex(key_file, key, keysize);
    fclose(key_file);

    /* Read input block */
    FILE  *in_file =  (in_filen == NULL) ? stdin  : fopen(in_filen, "r");
    fread_hex(in_file, block, AES_BLOCK_SIZE);
    fclose(in_file);

    status = aes_encrypt(block, key, keysize);

    if (status != AES_SUCCEED) {
        print_readable(status);
        cleanup(key, block);
        exit(1);
    }

    /* Write encrypted block */
    FILE *out_file = (out_filen == NULL) ? stdout : fopen(out_filen, "w");
    fwrite_hex(out_file, block, AES_BLOCK_SIZE);
    fclose(out_file);
    cleanup(key, block);
    return 0;
}
