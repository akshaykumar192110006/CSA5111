#include <stdio.h>
#include <string.h>

// Function to decrypt the affine cipher
char decrypt(char ch, int a, int b) {
    if (ch >= 'A' && ch <= 'Z') {
        return ((ch - 'A' - b + 26) * 15) % 26 + 'A';
    } else if (ch >= 'a' && ch <= 'z') {
        return ((ch - 'a' - b + 26) * 15) % 26 + 'a';
    } else {
        return ch;
    }
}

int main() {
    char ciphertext[] = "your_cipher_text_here"; // Replace with your ciphertext
    char mostFrequentLetter = 'b'; // Replace with the most frequent letter
    char secondMostFrequentLetter = 'U'; // Replace with the second most frequent letter

    int a, b;
    
    // Find the value of 'b' in the affine cipher
    b = (mostFrequentLetter - secondMostFrequentLetter + 26) % 26;
    
    // Iterate over possible values of 'a' and decrypt the text
    for (a = 1; a < 26; a++) {
        printf("a = %d, b = %d: ", a, b);
        for (int i = 0; i < strlen(ciphertext); i++) {
            char decrypted = decrypt(ciphertext[i], a, b);
            printf("%c", decrypted);
        }
        printf("\n");
    }

    return 0;
}
