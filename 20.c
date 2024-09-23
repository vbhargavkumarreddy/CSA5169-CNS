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

// Function for 3DES encryption in ECB mode
void des3_encrypt_ecb(const uint8_t *key1, const uint8_t *key2, const uint8_t *key3, 
                      const uint8_t *input, uint8_t *output, size_t length) {
    uint8_t block[DES_BLOCK_SIZE];
  // class room
    size_t i;

    for (i = 0; i < length; i += DES_BLOCK_SIZE) {
        // Copy the next block of plaintext
        memcpy(block, input + i, DES_BLOCK_SIZE);

        // Encrypt with the first key
        des_encrypt(key1, block);

        // Encrypt with the second key
        des_encrypt(key2, block);

        // Encrypt with the third key
        des_encrypt(key3, block);

        // Save the current ciphertext block
        memcpy(output + i, block, DES_BLOCK_SIZE);
    }
}

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
    uint8_t plaintext[1024], ciphertext[1024];
    size_t length;

    // User input for plaintext
    printf("Enter plaintext (max 1024 chars): ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    length = strlen((char *)plaintext);

    // Remove newline character from plaintext
    if (length > 0 && plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';
        length--;
    }

    // Ensure length is a multiple of DES_BLOCK_SIZE
    size_t padded_length = ((length + DES_BLOCK_SIZE - 1) / DES_BLOCK_SIZE) * DES_BLOCK_SIZE;
    memset(plaintext + length, 0, padded_length - length);

    // Encrypt the plaintext in ECB mode
    des3_encrypt_ecb(key1, key2, key3, plaintext, ciphertext, padded_length);

    // Print the ciphertext in hexadecimal format
    printf("Ciphertext: ");
    print_hex(ciphertext, padded_length);

    return 0;
}
