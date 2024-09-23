#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHABET_SIZE 26

void generate_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}

void vigenere_encrypt(char *plaintext, int *key, char *ciphertext, int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + key[i]) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

int main() {
    srand(time(0));
    char plaintext[] = "HELLO VIGENERE CIPHER";
    int length = strlen(plaintext);
    int key[length];
    char ciphertext[length + 1];

    generate_key(key, length);
    vigenere_encrypt(plaintext, key, ciphertext, length);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
