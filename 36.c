#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

int affine_encrypt(int a, int b, char p) {
    if (p >= 'A' && p <= 'Z') {
        return (a * (p - 'A') + b) % ALPHABET_SIZE + 'A';
    }
    return p;
}

void encrypt_message(char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = affine_encrypt(a, b, plaintext[i]);
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char plaintext[] = "HELLO AFFINE CIPHER";
    char ciphertext[sizeof(plaintext)];
    int a = 5, b = 3;

    encrypt_message(plaintext, a, b, ciphertext);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
