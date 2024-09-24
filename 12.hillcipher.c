#include <stdio.h>
#include <string.h>
#define MOD 26
void multiplyMatrix(int key[2][2], int vec[2], int res[2]) {
    for (int i = 0; i < 2; i++) {
        res[i] = (key[i][0] * vec[0] + key[i][1] * vec[1]) % MOD;
    }
}
void encryptMessage(char text[], int key[2][2]) {
    int vec[2], res[2];
    printf("Encrypted message: ");
    for (int i = 0; i < strlen(text); i += 2) {
        vec[0] = text[i] - 'a';
        vec[1] = text[i + 1] - 'a';
        multiplyMatrix(key, vec, res);
        printf("%c%c", res[0] + 'A', res[1] + 'A');
    }
    printf("\n");
}

int main() {
    int key[2][2] = {{9, 4}, {5, 7}};
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    if (strlen(plaintext) % 2 != 0) 
	strcat(plaintext, "x");

    encryptMessage(plaintext, key);
    
    return 0;
}
