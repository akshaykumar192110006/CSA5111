#include <stdio.h>
#include <string.h>
#include <ctype.h>


void generateCipherSequence(char keyword[], char cipherSequence[]) {
    int i, j;
    int keywordLength = strlen(keyword);
    int index = 0;

    for (i = 0; i < keywordLength; i++) {
        char currentChar = toupper(keyword[i]);
        if (currentChar != ' ') {
            cipherSequence[index++] = currentChar;
        }
    }

    for (i = 0; i < 26; i++) {
        char currentChar = 'A' + i;
        int found = 0;

        for (j = 0; j < keywordLength; j++) {
            if (toupper(keyword[j]) == currentChar) {
                found = 1;
                break;
            }
        }

        if (!found) {
            cipherSequence[index++] = currentChar;
        }
    }

    cipherSequence[index] = '\0';
}

void monoalphabeticCipher(char plaintext[], char keyword[]) {
    char cipherSequence[27]; 
    generateCipherSequence(keyword, cipherSequence);

    int i;
    int plaintextLength = strlen(plaintext);

    for (i = 0; i < plaintextLength; i++) {
        char currentChar = toupper(plaintext[i]);
        if (isalpha(currentChar)) {
            if (isupper(plaintext[i])) {
                plaintext[i] = cipherSequence[currentChar - 'A'];
            } else {
                plaintext[i] = tolower(cipherSequence[currentChar - 'A']);
            }
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "Hello, World!";

    printf("Plaintext: %s\n", plaintext);
    monoalphabeticCipher(plaintext, keyword);
    printf("Ciphertext: %s\n", plaintext);

    return 0;
}
