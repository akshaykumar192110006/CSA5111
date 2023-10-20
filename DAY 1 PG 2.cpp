#include <stdio.h>
#include <string.h>
#include <ctype.h>

void constructMatrix(char key[], char matrix[5][5]) {
    int k, flag = 0;
    char table[26] = {0};
    int keylen = strlen(key);
    
    for (k = 0; k < keylen; k++) {
        if (key[k] == 'J')
            key[k] = 'I';
        key[k] = toupper(key[k]);
        if (table[key[k] - 'A'] == 0) {
            table[key[k] - 'A'] = 1;
            matrix[flag / 5][flag % 5] = key[k];
            flag++;
        }
    }
    
    for (k = 0; k < 26; k++) {
        if (table[k] == 0) {
            matrix[flag / 5][flag % 5] = (char)('A' + k);
            flag++;
        }
    }
}

void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char matrix[5][5], char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        char ch1 = plaintext[i];
        char ch2 = plaintext[i + 1];
        int row1, col1, row2, col2;
        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);
        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
}

int main() {
    char key[] = "KEYWORD";
    char matrix[5][5];
    char plaintext[] = "HELLO";
    char ciphertext[100];

    constructMatrix(key, matrix);
    encrypt(matrix, plaintext, ciphertext);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}
