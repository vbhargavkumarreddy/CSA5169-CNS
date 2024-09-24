#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 100
void prepareText(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (input[i] != ' ') {
            output[j++] = toupper(input[i]);
            if (input[i] == input[i + 1]) output[j++] = 'X';
        }
    }
    if (j % 2) output[j++] = 'X'; // Add 'X' if odd length
    output[j] = '\0';
}
void encodePlayfair(char *text) {
    char key[5][5] = {
        {'M', 'O', 'N', 'A', 'R'},
        {'C', 'H', 'Y', 'B', 'D'},
        {'E', 'F', 'G', 'I', 'K'},
        {'L', 'P', 'Q', 'S', 'T'},
        {'U', 'V', 'W', 'X', 'Z'}
    };   
    char formatted[MAX_LENGTH];
    prepareText(text, formatted);
    for (int i = 0; formatted[i]; i += 2) {
        int r1, c1, r2, c2;
        for (int r = 0; r < 5; r++)
            for (int c = 0; c < 5; c++)
                if (key[r][c] == formatted[i]) { r1 = r; c1 = c; }
                else if (key[r][c] == formatted[i + 1]) { r2 = r; c2 = c; }
        printf("%c%c", 
            r1 == r2 ? key[r1][(c1 + 1) % 5] : (c1 == c2 ? key[(r1 + 1) % 5][c1] : key[r1][c2]),
            r2 == r1 ? key[r2][(c2 + 1) % 5] : (c2 == c1 ? key[(r2 + 1) % 5][c2] : key[r2][c1])
        );
    }
    printf("\n");
}
int main() {
    char plaintext[MAX_LENGTH] = "Must see you over Cadogan West";
    printf("Encoded Message: ");
    encodePlayfair(plaintext);
    return 0;
}
