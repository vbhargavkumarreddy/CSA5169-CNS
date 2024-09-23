
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DES_BLOCK_SIZE 8
#define DES_KEY_SIZE 8

// Dummy DES encryption function (replace with real DES implementation)
void des_encrypt(const uint8_t *key, uint8_t *block) {
    for (int i = 0; i < DES_BLOCK_SIZE; ++i) {
        block[i] ^= key[i];  // Simple XOR for demonstration
    }
}

// Padding function: 1 bit followed by zero bits to complete the block
size_t pad(uint8_t *plaintext, size_t length) {
    size_t padded_length = ((length + DES_BLOCK_SIZE) / DES_BLOCK_SIZE) * DES_BLOCK_SIZE;
    plaintext[length] = 0x80;  // Add '1' bit
  //simats engineering

    memset(plaintext + length + 1, 0, padded_length - length - 1);  // Fill with zeros
    return padded_length;
}

// ECB mode encryption
void des3_encrypt_ecb(const uint8_t *key1, const uint8_t *key2, const uint8_t *key3, 
                      const uint8_t *input, uint8_t *output, size_t length) {
    uint8_t block[DES_BLOCK_SIZE];
    size_t i;

    for (i = 0; i < length; i += DES_BLOCK_SIZE) {
        memcpy(block, input + i, DES_BLOCK_SIZE);
        des_encrypt(key1, block);
        des_encrypt(key2, block);
        des_encrypt(key3, block);
        memcpy(output + i, block, DES_BLOCK_SIZE);
    }
}

// CBC mode encryption
void des3_encrypt_cbc(const uint8_t *key1, const uint8_t *key2, const uint8_t *key3, 
                      const uint8_t *iv, const uint8_t *input, uint8_t *output, size_t length) {
    uint8_t block[DES_BLOCK_SIZE], prev_block[DES_BLOCK_SIZE];
    memcpy(prev_block, iv, DES_BLOCK_SIZE);

    for (size_t i = 0; i < length; i += DES_BLOCK_SIZE) {
        memcpy(block, input + i, DES_BLOCK_SIZE);
        for (int j = 0; j < DES_BLOCK_SIZE; ++j) {
            block[j] ^= prev_block[j];
        }
        des_encrypt(key1, block);
        des_encrypt(key2, block);
        des_encrypt(key3, block);
        memcpy(output + i, block, DES_BLOCK_SIZE);
        memcpy(prev_block, block, DES_BLOCK_SIZE);
    }
}

// CFB mode encryption
void des3_encrypt_cfb(const uint8_t *key1, const uint8_t *key2, const uint8_t *key3, 
                      const uint8_t *iv, const uint8_t *input, uint8_t *output, size_t length) {
    uint8_t temp[DES_BLOCK_SIZE], prev_block[DES_BLOCK_SIZE];
    memcpy(prev_block, iv, DES_BLOCK_SIZE);

    for (size_t i = 0; i < length; i += DES_BLOCK_SIZE) {
        memcpy(temp, prev_block, DES_BLOCK_SIZE);
        des_encrypt(key1, temp);
        des_encrypt(key2, temp);
        des_encrypt(key3, temp);
        for (int j = 0; j < DES_BLOCK_SIZE && i + j < length; ++j) {
            output[i + j] = input[i + j] ^ temp[j];
            prev_block[j] = output[i + j];  // Feedback
        }
    }
}

// Print hex output
void print_hex(const uint8_t *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key1[DES_KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};  // Hardcoded key 1
    uint8_t key2[DES_KEY_SIZE] = {0x1A, 0x56, 0xF9, 0xCD, 0xE3, 0x7B, 0xA5, 0x99};  // Hardcoded key 2
    uint8_t key3[DES_KEY_SIZE] = {0x02, 0x46, 0x8F, 0x7D, 0xD6, 0x9A, 0xEA, 0xB0};  // Hardcoded key 3
    uint8_t iv[DES_BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};  // Hardcoded IV
    uint8_t plaintext[1024], ciphertext[1024];
    size_t length, padded_length;

    // User input for plaintext
    printf("Enter plaintext (max 1024 chars): ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    length = strlen((char *)plaintext);

    // Remove newline character from plaintext
    if (length > 0 && plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';
        length--;
    }

    // Pad the plaintext
    padded_length = pad(plaintext, length);

    // ECB Mode
    printf("ECB Mode:\n");
    des3_encrypt_ecb(key1, key2, key3, plaintext, ciphertext, padded_length);
    print_hex(ciphertext, padded_length);

    // CBC Mode
    printf("CBC Mode:\n");
    des3_encrypt_cbc(key1, key2, key3, iv, plaintext, ciphertext, padded_length);
    print_hex(ciphertext, padded_length);

    // CFB Mode
    printf("CFB Mode:\n");
    des3_encrypt_cfb(key1, key2, key3, iv, plaintext, ciphertext, padded_length);
    print_hex(ciphertext, padded_length);

    return 0;
}
