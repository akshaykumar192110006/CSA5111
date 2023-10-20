#include <stdio.h>

typedef unsigned char byte;

// S-DES Data Structures
byte key[10] = {0, 1, 1, 1, 1, 1, 1, 0, 1, 0};
byte plaintext[8] = {0, 0, 0, 0, 0, 1, 0, 0};
byte iv[8] = {1, 0, 1, 0, 1, 0, 1, 0};
byte ciphertext[8];
byte decryptedtext[8];

// S-DES functions
void permute(byte *input, const int *permutation, int size) {
    byte temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = input[permutation[i] - 1];
    }
    for (int i = 0; i < size; i++) {
        input[i] = temp[i];
    }
}

void initialPermutation(byte *input) {
    int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
    permute(input, IP, 8);
}

void expansion(byte *input, byte *output) {
    int E[] = {4, 1, 2, 3, 2, 3, 4, 1};
    permute(input, E, 8);
}

void xorBytes(byte *a, byte *b, int size) {
    for (int i = 0; i < size; i++) {
        a[i] ^= b[i];
    }
}

void substitution(byte *input) {
    int S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    int S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
    int row, col;

    row = (input[0] << 1) | input[3];
    col = (input[1] << 1) | input[2];
    
    byte output[4];
    int tempS0 = S0[row][col];
    int tempS1 = S1[row][col];
    
    for (int i = 0; i < 2; i++) {
        output[i] = (tempS0 >> (1 - i)) & 1;
        output[i + 2] = (tempS1 >> (1 - i)) & 1;
    }
    
    for (int i = 0; i < 4; i++) {
        input[i] = output[i];
    }
}

void permutation(byte *input) {
    int P[] = {2, 4, 3, 1};
    permute(input, P, 4);
}

void finalPermutation(byte *input) {
    int FP[] = {4, 1, 3, 5, 7, 2, 8, 6};
    permute(input, FP, 8);
}

void sdesEncrypt(byte *block, byte *key) {
    byte left[4];
    byte right[4];
    byte temp[4];

    initialPermutation(block);
    
    for (int round = 0; round < 2; round++) {
        for (int i = 0; i < 4; i++) {
            left[i] = block[i];
            right[i] = block[i + 4];
        }

        expansion(right, temp);
        xorBytes(temp, key, 8);
        substitution(temp);
        permutation(temp);
        xorBytes(left, temp, 4);

        for (int i = 0; i < 4; i++) {
            block[i] = right[i];
            block[i + 4] = left[i];
        }
    }

    finalPermutation(block);
}

void sdesDecrypt(byte *block, byte *key) {
    byte left[4];
    byte right[4];
    byte temp[4];

    initialPermutation(block);
    
    for (int round = 0; round < 2; round++) {
        for (int i = 0; i < 4; i++) {
            left[i] = block[i];
            right[i] = block[i + 4];
        }

        expansion(right, temp);
        xorBytes(temp, key, 8);
        substitution(temp);
        permutation(temp);
        xorBytes(left, temp, 4);

        for (int i = 0; i < 4; i++) {
            block[i] = right[i];
            block[i + 4] = left[i];
        }
    }

    finalPermutation(block);
}

int main() {
    printf("Plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", plaintext[i]);
    }
    printf("\n");

    printf("Key: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", key[i]);
    }
    printf("\n");

    printf("Initialization Vector (IV): ");
    for (int i = 0; i < 8; i++) {
        printf("%d", iv[i]);
    }
    printf("\n");

    printf("Encrypting...\n");
    for (int i = 0; i < 8; i++) {
        ciphertext[i] = plaintext[i] ^ iv[i];
    }
    sdesEncrypt(ciphertext, key);

    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    printf("Decrypting...\n");
    byte previousCipherBlock[8];
    for (int i = 0; i < 8; i++) {
        previousCipherBlock[i] = iv[i];
    }
    for (int i = 0; i < 8; i++) {
        temp[i] = ciphertext[i];
    }
    sdesDecrypt(ciphertext, key);

    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 8; i++) {
        decryptedtext[i] = ciphertext[i] ^ previousCipherBlock[i];
        printf("%d", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}
