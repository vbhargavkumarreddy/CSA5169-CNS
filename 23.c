#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define S_DES_KEY_SIZE 10
#define BLOCK_SIZE 8  // 8 bits per block
#define NUM_ROUNDS 2  // S-DES has 2 rounds

// Function to generate round keys from the 10-bit key
void generate_keys(uint16_t key, uint8_t round_keys[NUM_ROUNDS]) {
    round_keys[0] = (key >> 5) & 0x1F;  // First round key (5 bits)
    round_keys[1] = key & 0x1F;         // Second round key (5 bits)
}

// Dummy S-DES encryption function (simplified for demo purposes)
uint8_t s_des_encrypt(uint8_t plaintext, uint8_t key) {
    return plaintext ^ key;  // XOR with key for simplicity
}

// 00000001 00000010 00000100

// CTR mode encryption function using S-DES
void s_des_encrypt_ctr(const uint8_t *plaintext, uint8_t *ciphertext, size_t length,
                       uint16_t key, uint8_t counter_start) {
    uint8_t round_keys[NUM_ROUNDS];
    generate_keys(key, round_keys);

    uint8_t counter = counter_start;
    uint8_t block, keystream;

    for (size_t i = 0; i < length; ++i) {
        keystream = counter;
        for (int r = 0; r < NUM_ROUNDS; ++r) {
            keystream = s_des_encrypt(keystream, round_keys[r]);
        }

        // XOR the plaintext block with the keystream to produce ciphertext
        ciphertext[i] = plaintext[i] ^ keystream;

        // Increment the counter for the next block
        counter++;
    }
}

// CTR mode decryption function using S-DES (identical to encryption in CTR mode)
void s_des_decrypt_ctr(const uint8_t *ciphertext, uint8_t *plaintext, size_t length,
                       uint16_t key, uint8_t counter_start) {
    // Decryption in CTR mode is identical to encryption
    s_des_encrypt_ctr(ciphertext, plaintext, length, key, counter_start);
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
    char input_str[25];  // To hold 3 binary blocks (24 bits + spaces)
    uint8_t plaintext[3];
    uint8_t ciphertext[3];
    uint8_t decrypted_text[3];
    uint16_t key = 0x1FD;  // Binary key: 01111 11101
    uint8_t counter_start = 0x00;  // Starting counter: 0000 0000

    // User input for three 8-bit binary blocks (e.g., "00000001 00000010 00000100")
    printf("Enter three 8-bit binary blocks (separated by spaces): ");
    fgets(input_str, sizeof(input_str), stdin);

    // Parse the input
    char *token = strtok(input_str, " ");
    int index = 0;
    while (token != NULL && index < 3) {
        plaintext[index] = binary_to_uint8(token);
        token = strtok(NULL, " ");
        index++;
    }

    printf("\nOriginal Plaintext:\n");
    for (int i = 0; i < 3; ++i) {
        print_binary(plaintext[i]);
        printf(" ");
    }
    printf("\n");

    // Encrypt the plaintext using CTR mode with S-DES
    s_des_encrypt_ctr(plaintext, ciphertext, 3, key, counter_start);

    printf("\nEncrypted Ciphertext:\n");
    for (int i = 0; i < 3; ++i) {
        print_binary(ciphertext[i]);
        printf(" ");
    }
    printf("\n");

    // Decrypt the ciphertext back to plaintext
    s_des_decrypt_ctr(ciphertext, decrypted_text, 3, key, counter_start);

    printf("\nDecrypted Plaintext:\n");
    for (int i = 0; i < 3; ++i) {
        print_binary(decrypted_text[i]);
        printf(" ");
    }
    printf("\n");

    return 0;
}
