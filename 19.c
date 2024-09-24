#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
void initialPermutation(uint8_t *block);
void finalPermutation(uint8_t *block);
void expansion(uint8_t *block, uint8_t *expanded_block);
void substitution(uint8_t *expanded_block, uint8_t *substituted_block);
void permutation(uint8_t *substituted_block, uint8_t *permuted_block);
void xorBlocks(uint8_t *block1, uint8_t *block2, int size);
void generateSubkeys(uint8_t *key, uint8_t *subkeys[]);
void desEncrypt(uint8_t *block, uint8_t *subkeys[]);
void initialPermutation(uint8_t *block) {
}
void finalPermutation(uint8_t *block) { 
}
void expansion(uint8_t *block, uint8_t *expanded_block) {   
}
void substitution(uint8_t *expanded_block, uint8_t *substituted_block) {   
}
void permutation(uint8_t *substituted_block, uint8_t *permuted_block) {    
}
void xorBlocks(uint8_t *block1, uint8_t *block2, int size) {   
}
void generateSubkeys(uint8_t *key, uint8_t *subkeys[]) {   
}
void desEncrypt(uint8_t *block, uint8_t *subkeys[]) {
}
void cbcEncrypt(uint8_t *plaintext, int plaintext_length, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t *subkeys[16];
    uint8_t block[8];    
    uint8_t temp[8];     
    generateSubkeys(key, subkeys);
    memcpy(block, iv, 8);
    int i;
    for (i = 0; i < plaintext_length; i += 8) {
        xorBlocks(block, plaintext + i, 8);

        desEncrypt(block, subkeys);

    
        memcpy(ciphertext + i, block, 8);
    }
}

int main() {
    uint8_t plaintext[256] = "This is a secret message."; 
    int plaintext_length = strlen((char *)plaintext);      
    uint8_t iv[8] = {0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x90};
    uint8_t ciphertext[256];

    cbcEncrypt(plaintext, plaintext_length, key, iv, ciphertext);

    printf("Ciphertext:\n");
    int i;
    for ( i = 0; i < plaintext_length; ++i) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
}
