#include <stdio.h>
#include <string.h>

// Function to perform polyalphabetic substitution
void polyalphabeticCipher(char plaintext[], char key[]) {
    int i, j;
    int plaintextLength = strlen(plaintext);
    int keyLength = strlen(key);

    for (i = 0; i < plaintextLength; i++) {
        // Shift the character in the plaintext using the corresponding character from the key
        char currentChar = plaintext[i];
        char keyChar = key[i % keyLength];
        char encryptedChar = 'A' + (currentChar - 'A' + keyChar - 'A') % 26;

        // Print the encrypted character
        printf("%c", encryptedChar);
    }
    printf("\n");
}

int main() {
    char plaintext[100];
    char key[100];

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    printf("Enter the key: ");
    scanf("%s", key);

    printf("Encrypted Text: ");
    polyalphabeticCipher(plaintext, key);

    return 0;
}
