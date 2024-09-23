#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define S_DES_KEY_SIZE 10
#define BLOCK_SIZE 8  // 8 bits per block
#define NUM_ROUNDS 2  // S-DES has 2 rounds

// Function to generate round keys from the 10-bit key
void generate_keys(uint16_t key, uint8_t round_keys[NUM_ROUNDS]) {
    round_keys[0] = (key >> 5) & 0x1F;  // First round key
    round_keys[1] = key & 0x1F;         // Second round key
}

// Dummy S-DES encryption function (simplified for demo purposes)
uint8_t s_des_encrypt(uint8_t plaintext, uint8_t key) {
    return plaintext ^ key;  // XOR with key for simplicity
}

// 00000001
// 00100011

// Dummy S-DES decryption function (since it is XOR, it's identical to encryption)
uint8_t s_des_decrypt(uint8_t ciphertext, uint8_t key) {
    return ciphertext ^ key;  // XOR reverses itself
}

// CBC mode encryption function using S-DES
void s_des_encrypt_cbc(const uint8_t *plaintext, uint8_t *ciphertext, size_t length,
                       uint16_t key, uint8_t iv) {
    uint8_t block;
    uint8_t round_keys[NUM_ROUNDS];
    
    generate_keys(key, round_keys);

    uint8_t prev_block = iv;

    for (size_t i = 0; i < length; ++i) {
        block = plaintext[i] ^ prev_block;
        for (int r = 0; r < NUM_ROUNDS; ++r) {
            block = s_des_encrypt(block, round_keys[r]);
        }
        ciphertext[i] = block;
        prev_block = ciphertext[i];
    }
}

// CBC mode decryption function using S-DES
void s_des_decrypt_cbc(const uint8_t *ciphertext, uint8_t *plaintext, size_t length,
                       uint16_t key, uint8_t iv) {
    uint8_t block;
    uint8_t round_keys[NUM_ROUNDS];
    
    generate_keys(key, round_keys);

    uint8_t prev_block = iv;

    for (size_t i = 0; i < length; ++i) {
        block = ciphertext[i];
        for (int r = NUM_ROUNDS - 1; r >= 0; --r) {
            block = s_des_decrypt(block, round_keys[r]);
        }
        plaintext[i] = block ^ prev_block;
        prev_block = ciphertext[i];
    }
}

// Function to convert user input from binary string to integer
uint8_t binary_to_uint8(const char *binary_str) {
    uint8_t value = 0;
    for (int i = 0; i < 8; ++i) {
        value <<= 1;
        if (binary_str[i] == '1') {
            value |= 1;
        }
    }
    return value;
}

// Function to print binary data
void print_binary(uint8_t data) {
    for (int i = 7; i >= 0; --i) {
        printf("%d", (data >> i) & 1);
    }
}

int main() {
    char input_str[9];
    uint8_t plaintext[2];
    uint8_t ciphertext[2];
    uint8_t decrypted_text[2];
    uint16_t key = 0x1FD;  // Binary key: 01111 11101
    uint8_t iv = 0xAA;     // Binary IV: 1010 1010

    // User input for plaintext (binary string)
    printf("Enter first block of 8-bit binary plaintext: ");
    scanf("%8s", input_str);
    plaintext[0] = binary_to_uint8(input_str);

    printf("Enter second block of 8-bit binary plaintext: ");
    scanf("%8s", input_str);
    plaintext[1] = binary_to_uint8(input_str);

    printf("\nOriginal Plaintext:\n");
    for (int i = 0; i < 2; ++i) {
        print_binary(plaintext[i]);
        printf(" ");
    }
    printf("\n");

    // Encrypt the plaintext using CBC mode with S-DES
    s_des_encrypt_cbc(plaintext, ciphertext, 2, key, iv);

    printf("\nEncrypted Ciphertext:\n");
    for (int i = 0; i < 2; ++i) {
        print_binary(ciphertext[i]);
        printf(" ");
    }
    printf("\n");

    // Decrypt the ciphertext back to plaintext
    s_des_decrypt_cbc(ciphertext, decrypted_text, 2, key, iv);

    printf("\nDecrypted Plaintext:\n");
    for (int i = 0; i < 2; ++i) {
        print_binary(decrypted_text[i]);
        printf(" ");
    }
    printf("\n");

    return 0;
}
