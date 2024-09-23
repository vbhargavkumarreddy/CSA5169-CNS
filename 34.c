#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int blocks) {
    for (int i = 0; i < blocks; i++) {
        // Simple placeholder for encryption (replace with actual encryption function)
        memcpy(ciphertext + i * BLOCK_SIZE, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int blocks) {
    uint8_t iv[BLOCK_SIZE] = {0};
    for (int i = 0; i < blocks; i++) {
        uint8_t temp[BLOCK_SIZE];
        if (i == 0) {
            xor_blocks(plaintext + i * BLOCK_SIZE, iv, temp);
        } else {
            xor_blocks(plaintext + i * BLOCK_SIZE, ciphertext + (i - 1) * BLOCK_SIZE, temp);
        }
        memcpy(ciphertext + i * BLOCK_SIZE, temp, BLOCK_SIZE); // Placeholder for encryption
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int blocks) {
    uint8_t iv[BLOCK_SIZE] = {0};
    memcpy(ciphertext, iv, BLOCK_SIZE);
    for (int i = 0; i < blocks; i++) {
        memcpy(ciphertext + (i + 1) * BLOCK_SIZE, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE); // Placeholder for encryption
        xor_blocks(plaintext + i * BLOCK_SIZE, ciphertext + (i + 1) * BLOCK_SIZE, ciphertext + (i + 1) * BLOCK_SIZE);
    }
}

void pad_plaintext(uint8_t *plaintext, int *len) {
    plaintext[*len] = 0x80;
    for (int i = *len + 1; i < BLOCK_SIZE; i++) {
        plaintext[i] = 0x00;
    }
    *len = BLOCK_SIZE;
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t plaintext[BLOCK_SIZE * 3] = "Hello!";
    int len = strlen((char *)plaintext);
    pad_plaintext(plaintext, &len);

    uint8_t ciphertext[BLOCK_SIZE * 3];

    ecb_encrypt(plaintext, key, ciphertext, len / BLOCK_SIZE);
    printf("ECB Ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    memset(ciphertext, 0, sizeof(ciphertext));
    cbc_encrypt(plaintext, key, ciphertext, len / BLOCK_SIZE);
    printf("CBC Ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    memset(ciphertext, 0, sizeof(ciphertext));
    cfb_encrypt(plaintext, key, ciphertext, len / BLOCK_SIZE);
    printf("CFB Ciphertext: ");
    for (int i = 0; i < len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
