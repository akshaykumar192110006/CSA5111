#include <stdio.h>
#include <string.h>

// Function to perform monoalphabetic substitution
void monoalphabeticCipher(char *plaintext, char *cipherKey) {
    int i, index;
    char ciphertext[1000];

    for (i = 0; i < strlen(plaintext); i++) {
        // Check if the character is an uppercase letter
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            index = plaintext[i] - 'A';
            ciphertext[i] = cipherKey[index];
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            // Check if the character is a lowercase letter
            index = plaintext[i] - 'a';
            ciphertext[i] = tolower(cipherKey[index]);
        } else {
            // If not a letter, keep the character as it is
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';

    printf("Cipher Text: %s\n", ciphertext);
}

int main() {
    char plaintext[1000];
    char cipherKey[] = "ZYXWVUTSRQPONMLKJIHGFEDCBA"; // Replace with your custom key

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    monoalphabeticCipher(plaintext, cipherKey);

    return 0;
}
